import pandas as pd
import numpy as np
from typing import List, Tuple
from scipy.stats import norm

__all__ = ["traitement_total", "detecter_colonne_temps", "haversine"]


def haversine(
    lat1: float,
    lon1: float,
    lat2: float,
    lon2: float,
    rayon_terre_km: int = 6371,
) -> float:
    """
    Calcule la distance en mètres entre deux points géographiques via la formule de Haversine.

    Args:
        lat1 (float): latitude du point de départ (degrés).
        lon1 (float): longitude du point de départ (degrés).
        lat2 (float): latitude du point d’arrivée (degrés).
        lon2 (float): longitude du point d’arrivée (degrés).
        rayon_terre_km (int): rayon de la Terre en kilomètres (par défaut 6371).

    Returns:
        float: distance entre les deux points en mètres.
    """
    lat1_r, lon1_r, lat2_r, lon2_r = np.radians([lat1, lon1, lat2, lon2])
    dlat = lat2_r - lat1_r
    dlon = lon2_r - lon1_r
    a = np.sin(dlat / 2.0) ** 2
    a += np.cos(lat1_r) * np.cos(lat2_r) * np.sin(dlon / 2.0) ** 2
    distance_km = 2 * rayon_terre_km * np.arcsin(np.sqrt(a))
    return distance_km * 1000


def detecter_colonne_temps(df: pd.DataFrame) -> str:
    """
    Détecte la colonne temporelle parmi 'Timestamp' ou 'UTC' et convertit en datetime si nécessaire.

    Args:
        df (pd.DataFrame): DataFrame à analyser.

    Returns:
        str: nom de la colonne temporelle retenue.
    """
    col_temps = "Timestamp" if "Timestamp" in df.columns else "UTC"
    # Conversion si nécessaire (pour la colonne UTC uniquement)
    if col_temps == "UTC" and df[col_temps].dtype == object:
        df[col_temps] = pd.to_datetime(df[col_temps])
    return col_temps


def indices_outliers_bruts(
    vitesses: np.ndarray,
    seuil_ratio: float = 10.0,
) -> List[int]:
    """
    Identifie les indices où la vitesse dépasse un multiple de la moyenne.

    Args:
        vitesses (np.ndarray): tableau de vitesses en m/s.
        seuil_ratio (float): seuil multiplicatif par rapport à la moyenne.

    Returns:
        List[int]: indices des vitesses considérées comme outliers bruts.
    """
    moyenne = np.mean(vitesses)
    return [i for i, v in enumerate(vitesses) if v >= seuil_ratio * moyenne]


def indices_outliers_statistiques(
    vitesses: np.ndarray,
    mu: float,
    sigma: float,
    seuil_prob: float = 0.05,
) -> List[int]:
    """
    Repère les indices (i+1) dont la densité de probabilité est ≤ seuil_prob.

    Args:
        vitesses (np.ndarray): tableau de vitesses en m/s.
        mu (float): moyenne de la distribution filtrée.
        sigma (float): écart-type de la distribution filtrée.
        seuil_prob (float): seuil minimal de densité de probabilité.

    Returns:
        List[int]: indices des points d’arrivée considérés aberrants.
    """
    densites = norm.pdf(vitesses, loc=mu, scale=sigma)
    return [
        i + 1
        for i, (v, p) in enumerate(zip(vitesses, densites))
        if p <= seuil_prob and v > 1
    ]


def detecter_points_aberrants(
    df: pd.DataFrame,
    seuil_prob: float = 0.05,
) -> Tuple[List[int], np.ndarray]:
    """
    Calcule les vitesses entre points et renvoie les indices aberrants + vitesses.

    Args:
        df (pd.DataFrame): DataFrame avec colonnes 'Latitude', 'Longitude' et temporelle.
        seuil_prob (float): seuil de densité pour l’outlier statistique.

    Returns:
        Tuple[List[int], np.ndarray]:
            - indices d’outliers statistiques,
            - vitesses calculées (m/s).
    """
    col_temps = detecter_colonne_temps(df)
    n_pts = len(df[col_temps])

    # Calcul distances et temps
    distances = [
        haversine(
            df["Latitude"].iat[i],
            df["Longitude"].iat[i],
            df["Latitude"].iat[i + 1],
            df["Longitude"].iat[i + 1],
        )
        for i in range(n_pts - 1)
    ]
    deltas = []
    for i in range(n_pts - 1):
        delta = df[col_temps].iat[i + 1] - df[col_temps].iat[i]
        if hasattr(delta, "total_seconds"):
            deltas.append(delta.total_seconds())
        else:
            deltas.append(delta)  # garde la valeur brute si pas de total_seconds

    vitesses = np.array([d / t if t > 0 else 0 for d, t in zip(distances, deltas)])

    ind_bruts = indices_outliers_bruts(vitesses)
    filtres = [v for idx, v in enumerate(vitesses) if idx not in ind_bruts]
    mu, sigma = np.mean(filtres), np.std(filtres)

    ind_stats = indices_outliers_statistiques(vitesses, mu, sigma, seuil_prob)
    return ind_stats, vitesses


def interpolation_aberrants(
    df: pd.DataFrame,
    seuil_prob: float = 0.05,
) -> Tuple[pd.DataFrame, List[int], np.ndarray]:
    """
    Interpole linéairement les points aberrants détectés.

    Args:
        df (pd.DataFrame): DataFrame original (copié en interne).
        seuil_prob (float): seuil statistique d’outlier.

    Returns:
        Tuple[pd.DataFrame, List[int], np.ndarray]:
            - DataFrame interpolé,
            - indices des points supprimés,
            - vitesses initiales.
    """
    df_copy = df.copy()
    indices_supprimes, vitesses = detecter_points_aberrants(df_copy, seuil_prob)
    if indices_supprimes:
        df_copy.loc[indices_supprimes, ["Latitude", "Longitude"]] = np.nan
        df_copy[["Latitude", "Longitude"]] = df_copy[
            ["Latitude", "Longitude"]
        ].interpolate(method="linear")
    return df_copy, indices_supprimes, vitesses


ERREUR_STATIQUE_LATITUDE: float = -2.885505986799034e-05
ERREUR_STATIQUE_LONGITUDE: float = -1.7819133444287528e-05


def corriger_erreur_statique(
    df: pd.DataFrame,
    erreur_lat: float = ERREUR_STATIQUE_LATITUDE,
    erreur_lon: float = ERREUR_STATIQUE_LONGITUDE,
) -> None:
    """
    Applique directement un décalage constant sur latitude et longitude.

    Args:
        df (pd.DataFrame): DataFrame modifié in-place.
        erreur_lat (float): ajustement de latitude à ajouter.
        erreur_lon (float): ajustement de longitude à ajouter.
    """
    df["Latitude"] += erreur_lat
    df["Longitude"] += erreur_lon


def traitement_total(
    df: pd.DataFrame,
) -> Tuple[pd.DataFrame, List[int], np.ndarray]:
    """
    Pipeline complet : interpolation puis correction statique.

    Args:
        df (pd.DataFrame): DataFrame original.

    Returns:
        Tuple[pd.DataFrame, List[int], np.ndarray]:
            - DataFrame nettoyé,
            - indices des points interpolés,
            - vitesses initiales.
    """
    df_temp = df.copy(deep=True)
    df_interp, indices_suppr, vitesses = interpolation_aberrants(df_temp)
    corriger_erreur_statique(df_interp)
    return df_interp, indices_suppr, vitesses
