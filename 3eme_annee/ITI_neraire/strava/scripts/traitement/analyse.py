# analyse #2

"""
Module d’analyse de données IMU et GPS.

Fonctions :
- norme_vecteur_acc : calcule la norme du vecteur d’accélération.
- filtrer_signal : filtre passe-bas d’un signal.
- compter_pas_par_IMU : compte le nombre de pas via IMU.
- estimer_pas_par_distance_vitesse : estime le nombre de pas par distance et vitesse.
- moyenne_nb_pas : moyenne pondérée des deux méthodes.
- calculer_distance : somme des distances Haversine.
- calculer_vitesse : vitesse moyenne en km/h.
- calculer_pas : renvoie le nombre de pas global.
"""

import numpy as np
import pandas as pd
from scipy.signal import butter, filtfilt, find_peaks
from typing import List, Tuple
from .traitements import detecter_colonne_temps, haversine


def norme_vecteur_acc(df_imu: pd.DataFrame) -> np.ndarray:
    """
    Calcule la norme du vecteur d’accélération à partir des axes X, Y, Z.

    Args:
        df_imu (pd.DataFrame): DataFrame contenant les colonnes 'Accel X', 'Accel Y', 'Accel Z'.

    Returns:
        np.ndarray: Array des valeurs de la norme de l’accélération.
    """
    return np.sqrt(
        df_imu["Accel X"]**2 + df_imu["Accel Y"]**2 + df_imu["Accel Z"]**2
    )


def filtrer_signal(
    signal: np.ndarray,
    fs: float,
    fc: float = 3.0,
) -> np.ndarray:
    """
    Applique un filtre passe-bas Butterworth 4e ordre.

    Args:
        signal (np.ndarray): Signal brut à filtrer.
        fs (float): Fréquence d’échantillonnage (Hz).
        fc (float): Fréquence de coupure (Hz), par défaut 3.0.

    Returns:
        np.ndarray: Signal filtré.
    """
    b, a = butter(N=4, Wn=fc / (fs / 2), btype='low')
    return filtfilt(b, a, signal)


def compter_pas_par_IMU(
    df_imu: pd.DataFrame,
    fs: float = 12.5,
) -> int:
    """
    Compte le nombre de pas en détectant les pics du signal d’accélération.

    Args:
        df_imu (pd.DataFrame): DataFrame IMU.
        fs (float): Fréquence d’échantillonnage (Hz), par défaut 12.5.

    Returns:
        int: Nombre de pics (pas) détectés.
    """
    acc_norme = norme_vecteur_acc(df_imu)
    acc_filtrée = filtrer_signal(acc_norme, fs)

    moyenne = np.mean(acc_filtrée)
    ecart_type = np.std(acc_filtrée)
    seuil = moyenne + 1.0 * ecart_type
    distance_min = int(0.3 * fs)

    pics, _ = find_peaks(
        acc_filtrée,
        height=seuil,
        distance=distance_min,
    )
    return len(pics)


def estimer_pas_par_distance_vitesse(
    distance: float,
    vitesse: float,
) -> float:
    """
    Estime le nombre de pas basée sur la distance parcourue et la vitesse.

    Args:
        distance (float): distance parcourue (m).
        vitesse (float): vitesse moyenne (m/s).

    Returns:
        float: estimation du nombre de pas.
    """
    VITESSE_MARCHE_MOYENNE = 4.5  # km/h
    longueur_moyenne_pas = 0.65  # m

    pas_distance = distance / longueur_moyenne_pas
    facteur_vitesse = VITESSE_MARCHE_MOYENNE / vitesse
    return pas_distance * facteur_vitesse

def moyenne_nb_pas(
    df_imu: pd.DataFrame,
    distance: float,
    vitesse: float,
    coef: float = 0.8,
) -> float:
    """
    Calcule la moyenne pondérée du nombre de pas IMU et distance/vitesse.
    """

    pas_imu = compter_pas_par_IMU(df_imu, fs=12.5)
    pas_dist_vitesse = estimer_pas_par_distance_vitesse(distance, vitesse)
    return (1 - coef) * pas_imu + coef * pas_dist_vitesse

def calculer_distance(df: pd.DataFrame) -> float:
    """
    Calcule la distance totale parcourue en sommant les distances Haversine.

    Args:
        df (pd.DataFrame): DataFrame contenant 'Latitude', 'Longitude' et temps.

    Returns:
        float: distance totale en mètres.
    """
    col_temps = detecter_colonne_temps(df)
    total = 0.0
    for i in range(len(df[col_temps]) - 1):
        total += haversine(
            df["Latitude"][i],
            df["Longitude"][i],
            df["Latitude"][i + 1],
            df["Longitude"][i + 1],
        )
    return total


def calculer_vitesse(df: pd.DataFrame) -> float:
    """
    Calcule la vitesse moyenne en km/h.

    Args:
        df (pd.DataFrame): DataFrame contenant 'Latitude', 'Longitude' et temps.

    Returns:
        float: vitesse moyenne en km/h.
    """
    col_temps = detecter_colonne_temps(df)
    temps = []
    for i in range(len(df[col_temps]) - 1):
        delta = df[col_temps][i + 1] - df[col_temps][i]
        if hasattr(delta, "total_seconds"):
            temps.append(delta.total_seconds())
        else:
            temps.append(delta)

    distances = [
        haversine(
            df["Latitude"][i],
            df["Longitude"][i],
            df["Latitude"][i + 1],
            df["Longitude"][i + 1],
        )
        for i in range(len(df[col_temps]) - 1)
    ]
    vitesses = np.array([d / t if t != 0 else 0.0 for d, t in zip(distances, temps)])
    return np.mean(vitesses) * 3.6


def calculer_pas(
    df_imu: pd.DataFrame,
    distance: float,
    vitesse: float,
) -> float:
    """
    Renvoie le nombre de pas estimé global.

    Args:
        df_imu (pd.DataFrame): DataFrame IMU.
        distance (float): distance parcourue (m).
        vitesse (float): vitesse moyenne (m/s).

    Returns:
        float: estimation du nombre de pas.
    """
    return moyenne_nb_pas(df_imu, distance, vitesse)
