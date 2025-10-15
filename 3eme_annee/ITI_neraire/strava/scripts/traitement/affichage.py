# affichage.py #3

"""
Module d'affichage des résultats de traitement GPS et IMU.

Fonctions :
- tracer_parcours : affiche la trajectoire GPS avant et après traitement.
- afficher_stats : imprime distance, vitesse et nombre de pas estimés.
- afficher_norme_acc : trace la norme brute et filtrée du vecteur d'accélération.
- afficher_temps : affiche les intervalles de temps entre points GPS.
- afficher_indices_supprimes : visualise les points GPS supprimés.
- afficher_vitesses_aberrantes : trace les vitesses et marque les aberrations en rouge.
- enregister_parcours_map : enregistre une carte interactive au format HTML.
- plot_imu_data : trace les données IMU de l'accéléromètre et du gyroscope.
- affichage_total : regroupe tous les affichages en une seule vue.
"""

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import folium
from typing import List

from .traitements import detecter_colonne_temps
from .analyse import (
    calculer_distance,
    calculer_vitesse,
    calculer_pas,
    norme_vecteur_acc,
    filtrer_signal,
)


def tracer_parcours(
    df_avant: pd.DataFrame,
    df_apres: pd.DataFrame,
) -> None:
    """
    Trace la trajectoire GPS avant et après traitement.

    Args:
        df_avant (pd.DataFrame): données GPS initiales.
        df_apres (pd.DataFrame): données GPS après correction.
    """
    plt.figure(figsize=(10, 6))
    plt.plot(
        df_avant["Longitude"], df_avant["Latitude"],
        label="Avant traitement", marker="o", linestyle="-", alpha=0.5
    )
    plt.plot(
        df_apres["Longitude"], df_apres["Latitude"],
        label="Après traitement", marker="o", linestyle="-", alpha=0.5
    )
    plt.xlabel("Longitude")
    plt.ylabel("Latitude")
    plt.title("Trajectoire GPS")
    plt.legend()
    plt.show()


def afficher_stats(
    df: pd.DataFrame,
    df_imu: pd.DataFrame,
) -> None:
    """
    Calcule et affiche la distance, la vitesse et le nombre de pas estimé.

    Args:
        df (pd.DataFrame): données GPS nettoyées.
        df_imu (pd.DataFrame): données IMU.
    """
    distance = calculer_distance(df)
    vitesse = calculer_vitesse(df)
    pas = calculer_pas(df_imu, distance, vitesse)

    print(f"Distance totale : {distance:.2f} mètres")
    print(f"Vitesse moyenne : {vitesse:.2f} km/h")
    print(f"Nombre estimé de pas : {pas:.0f}")


def afficher_norme_acc(
    df: pd.DataFrame,
    fs: float = 12.5,
) -> None:
    """
    Affiche la norme brute et filtrée du vecteur d'accélération.

    Args:
        df (pd.DataFrame): données IMU contenant 'Accel X', 'Accel Y', 'Accel Z'.
        fs (float): fréquence d'échantillonnage (Hz).
    """
    norme = norme_vecteur_acc(df)
    norme_filtre = filtrer_signal(norme, fs)

    plt.figure(figsize=(12, 4))
    plt.plot(norme, alpha=0.4, label="Norme brute")
    plt.plot(norme_filtre, label="Filtrée", linewidth=2)
    plt.title("Norme des vecteurs d'accélération")
    plt.xlabel("Échantillons")
    plt.ylabel("Accélération (m/s²)")
    plt.legend()
    plt.grid()
    plt.show()


def afficher_temps(
    df: pd.DataFrame,
) -> None:
    """
    Trace les intervalles de temps entre points GPS.

    Args:
        df (pd.DataFrame): données GPS contenant une colonne temporelle.
    """
    col_temps = detecter_colonne_temps(df)
    temps = df[col_temps]
    deltas = [
        (temps.iloc[i + 1] - temps.iloc[i]) for i in range(len(temps) - 1)
    ]

    plt.figure(figsize=(10, 3))
    plt.plot(deltas)
    plt.title("Intervalle de temps entre points GPS")
    plt.ylabel("Secondes")
    plt.xlabel("Index")
    plt.grid()
    plt.show()


def afficher_indices_supprimes(
    df: pd.DataFrame,
    indices_supprimes: List[int],
) -> None:
    """
    Visualise les points GPS supprimés sur la trajectoire.

    Args:
        df (pd.DataFrame): données GPS originales.
        indices_supprimes (List[int]): indices des points supprimés.
    """
    plt.figure(figsize=(15, 15))
    plt.plot(
        df["Longitude"], df["Latitude"],
        marker="o", linestyle="-", alpha=0.3
    )
    plt.scatter(
        df["Longitude"].iloc[indices_supprimes],
        df["Latitude"].iloc[indices_supprimes],
        label="Points éliminés", s=100, color='red', edgecolor='black', alpha=1.0
    )
    plt.xlabel("Longitude")
    plt.ylabel("Latitude")
    plt.title("Parcours GPS avec points supprimés")
    plt.legend()
    plt.show()


def afficher_vitesses_aberrantes(
    vitesses: np.ndarray,
    indices_supprimes: List[int],
) -> None:
    """
    Trace les vitesses et marque celles supprimées en rouge.

    Args:
        vitesses (np.ndarray): tableau des vitesses.
        indices_supprimes (List[int]): indices des vitesses éliminées.
    """
    plt.plot(vitesses)
    indices_plot = [i - 1 for i in indices_supprimes]
    plt.scatter(
        indices_supprimes,
        vitesses[indices_plot],
        color='red',
        label="Valeurs éliminées"
    )
    plt.xlabel("Indices")
    plt.ylabel("Vitesse (m/s)")
    plt.title("Vitesses aberrantes supprimées")
    plt.legend()
    plt.show()


def enregister_parcours_map(
    file_path: str,
) -> None:
    """
    Génère et sauvegarde une carte interactive du parcours GPS au format HTML.

    Args:
        file_path (str): chemin vers le fichier CSV d'entrée (Latitude, Longitude).
    """
    data = pd.read_csv(file_path)
    debut = [data['Latitude'].iloc[0], data['Longitude'].iloc[0]]
    carte = folium.Map(location=debut, zoom_start=12)

    coords = list(zip(data['Latitude'], data['Longitude']))
    folium.PolyLine(coords, weight=2.5, opacity=1).add_to(carte)

    sortie = file_path.replace('.csv', '.html')
    carte.save(sortie)
    print(f"Carte enregistrée : {sortie}")


def plot_imu_data(
    data: pd.DataFrame,
) -> None:
    """
    Trace les signaux d'accéléromètre et de gyroscope en fonction du temps.

    Args:
        data (pd.DataFrame): données IMU contenant 'Timestamp',
                             'Accel X/Y/Z', 'Gyro X/Y/Z'.
    """
    colonnes_req = [
        'Timestamp', 'Accel X', 'Accel Y', 'Accel Z',
        'Gyro X', 'Gyro Y', 'Gyro Z'
    ]
    if not all(col in data.columns for col in colonnes_req):
        raise ValueError(f"Colonnes manquantes : {colonnes_req}")

    data_ts = data.copy()
    if hasattr(data_ts['Timestamp'].iloc[0], 'timestamp'):
        origine = data_ts['Timestamp'].iloc[0]
        data_ts['Timestamp'] = (
            data_ts['Timestamp'] - origine
        ).apply(lambda td: td.total_seconds())

    fig, axes = plt.subplots(2, 1, figsize=(12, 6), sharex=True)
    axes[0].plot(data_ts['Timestamp'], data_ts['Accel X'], label='Accel X')
    axes[0].plot(data_ts['Timestamp'], data_ts['Accel Y'], label='Accel Y')
    axes[0].plot(data_ts['Timestamp'], data_ts['Accel Z'], label='Accel Z')
    axes[0].set(title='Accéléromètre', ylabel='Accélération (g)')
    axes[0].legend()
    axes[0].grid()

    axes[1].plot(data_ts['Timestamp'], data_ts['Gyro X'], label='Gyro X')
    axes[1].plot(data_ts['Timestamp'], data_ts['Gyro Y'], label='Gyro Y')
    axes[1].plot(data_ts['Timestamp'], data_ts['Gyro Z'], label='Gyro Z')
    axes[1].set(title='Gyroscope', ylabel='Vitesse angulaire (dps)', xlabel='Temps (s)')
    axes[1].legend()
    axes[1].grid()

    plt.tight_layout()
    plt.show()


def affichage_total(
    df: pd.DataFrame,
    df_imu: pd.DataFrame,
    df_traite: pd.DataFrame,
    indices_supprimes: List[int],
    vitesses: np.ndarray
) -> None:
    """
    Regroupe et exécute tous les affichages.

    Args:
        df (pd.DataFrame): données GPS originales.
        df_imu (pd.DataFrame): données IMU.
        df_traite (pd.DataFrame): données GPS traitées.
        indices_supprimes (List[int]): indices des points supprimés.
        vitesses (np.ndarray): vitesses calculées.
    """
    afficher_norme_acc(df_imu)
    afficher_temps(df)
    afficher_vitesses_aberrantes(vitesses, indices_supprimes)
    afficher_indices_supprimes(df, indices_supprimes)
    tracer_parcours(df, df_traite)
    afficher_stats(df_traite, df_imu)
