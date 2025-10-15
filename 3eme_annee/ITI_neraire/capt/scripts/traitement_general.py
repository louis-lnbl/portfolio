from scipy.stats import norm
from datetime import datetime
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from typing import Tuple

__all__ = ["traitement_total", "syncronisation"]

def premier_traitement(vit):
    res = []
    moyenne_vit = np.mean(vit)
    for i in range(len(vit)):
        if vit[i] >= 10 * moyenne_vit:
            res.append(i)
    return res

def haversine(lat1, lon1, lat2, lon2, earth_radius=6371):
    lat1, lon1, lat2, lon2 = np.radians([lat1, lon1, lat2, lon2])

    a = np.sin((lat2-lat1)/2.0)**2 + np.cos(lat1) * np.cos(lat2) * np.sin((lon2-lon1)/2.0)**2
    km = earth_radius * 2 * np.arcsin(np.sqrt(a))
    m = km * 1000
    return m

def traitement_point_aberrant(df, seuil_prob=0.05):
    time_column = 'Timestamp' if 'Timestamp' in df.columns else 'UTC'
    
    if time_column == 'UTC' and df['UTC'].dtype == object:
        df['UTC'] = pd.to_datetime(df['UTC'])

    distances = [
        haversine(df["Latitude"][i], df["Longitude"][i],
                  df["Latitude"][i+1], df["Longitude"][i+1])
        for i in range(len(df[time_column]) - 1)
    ]

    temps = [
        (df[time_column][i+1] - df[time_column][i]).total_seconds()
        if hasattr(df[time_column][i+1] - df[time_column][i], "total_seconds")
        else df[time_column][i+1] - df[time_column][i]
        for i in range(len(df[time_column]) - 1)
    ]

    vitesses = np.array([
        d / t if t != 0 else 0
        for d, t in zip(distances, temps)
    ])
    
    indices_a_ignorer = premier_traitement(vitesses)
    distances_filtrees_v1 = [d for i, d in enumerate(distances) if i not in indices_a_ignorer]
    vitesses_filtrees_v1 = [v for i, v in enumerate(vitesses) if i not in indices_a_ignorer]
    
    mu = np.mean(vitesses_filtrees_v1)
    sigma = np.std(vitesses_filtrees_v1)
    prob_vitesses = norm.pdf(vitesses, mu, sigma)
    
    indices_enleves = [i+1 for i, (v, p) in enumerate(zip(vitesses, prob_vitesses)) if ((p <= seuil_prob) and (v > 1))]
    vitesses_filtrees_v2 = [v for i, v in enumerate(vitesses_filtrees_v1) if i not in indices_enleves]
    distances_filtrees_v2 = [d for i, d in enumerate(distances_filtrees_v1) if i not in indices_enleves]
    
    plt.plot(vitesses)
    indices_affichage = [i-1 for i in indices_enleves]
    plt.scatter(indices_enleves, vitesses[indices_affichage], color='red', label='Valeurs éliminées')
    plt.legend()
    plt.show()
    
    return indices_enleves, distances_filtrees_v2, vitesses_filtrees_v2

def afficher_post_traitement(df, indices_enleves):
    plt.figure(figsize=(15,15))
    plt.plot(df["Longitude"], df["Latitude"], marker="o", linestyle="-", alpha=0.3)
    plt.scatter(df["Longitude"][indices_enleves], df["Latitude"][indices_enleves],
                color='red', marker="o", s=100, edgecolor='black', label='Points éliminés', alpha=1.0)
    plt.legend()
    plt.show()

def afficher_parcours(*df):
    plt.figure(figsize=(15,15))
    for parcour in df:
        plt.plot(parcour["Longitude"], parcour["Latitude"], marker="o", linestyle="-", alpha=0.3)
    plt.show()

def nettoyage_dataset_2(df, seuil_prob=0.05):
    indices_enleves, d, v = traitement_point_aberrant(df, seuil_prob)
    
    if not indices_enleves:
        return df.copy()

    # Création d'une copie pour interpolation
    df_interpole = df.copy()
    # Mise à NaN des points aberrants
    colonnes_a_interpoler = ['Latitude', 'Longitude']
    for col in colonnes_a_interpoler:
        df_interpole.loc[indices_enleves, col] = np.nan
    # Interpolation linéaire sur les colonnes choisies
    df_interpole[colonnes_a_interpoler] = df_interpole[colonnes_a_interpoler].interpolate(method='linear')
    afficher_post_traitement(df, indices_enleves)
    return df_interpole, d, v


ERREUR_STATIQUE_LATITUDE =-2.885505986799034e-05
ERREUR_STATIQUE_LONGITUDE =-1.7819133444287528e-05

def enlever_erreur_statique(df, erreur_lat = ERREUR_STATIQUE_LATITUDE, erreur_long = ERREUR_STATIQUE_LONGITUDE):
    for i in range(len(df["Latitude"])):
        df.at[i, "Latitude"] += erreur_lat
        df.at[i, "Longitude"] += erreur_long

def traitement_total(path : str):
    df = pd.read_csv(path)
    df2, d, v = nettoyage_dataset_2(df)
    enlever_erreur_statique(df2)
    afficher_parcours(df, df2)
    print("distance =", np.sum(d), " mètres.")
    print("vitesse moyenne =", np.mean(v)*3.6, " km / h.")
    return df2

def syncronisation(df_gps: pd.DataFrame, df_imu: pd.DataFrame) -> Tuple[pd.DataFrame, pd.DataFrame]:
    df_gps['UTC'] = pd.to_datetime(df_gps['UTC'], utc=True, errors='raise')
    df_imu['UTC'] = pd.to_datetime(df_imu['Timestamp'], utc=True, errors='raise')

    # Exact UTC-based merge
    merged = pd.merge(df_gps, df_imu, on='UTC', suffixes=('_imu', '_gps'))

    # Extract and rename
    df_gps_sync = merged[['UTC', 'Latitude_gps', 'Longitude_gps']].rename(
        columns={'Latitude_gps': 'Latitude', 'Longitude_gps': 'Longitude'}
    )
    df_imu_sync = merged[['UTC', 'Latitude_imu', 'Longitude_imu']].rename(
        columns={'Latitude_imu': 'Latitude', 'Longitude_imu': 'Longitude'}
    )

    return df_gps_sync, df_imu_sync