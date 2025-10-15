import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
import os
import folium

def calculer_erreurs_trajectoires(fichier_ref, fichier_mes):
    """
    Charge deux fichiers CSV contenant des trajectoires et calcule :
    - L'erreur statique (biais moyen)
    - L'erreur sur l'écart-type (écart de dispersion)
    
    :param fichier_ref: str, chemin du fichier CSV contenant la trajectoire de référence
    :param fichier_mes: str, chemin du fichier CSV contenant la trajectoire mesurée
    :return: tuple (erreur_stat_lat, erreur_std_lat, erreur_stat_lon, erreur_std_lon)
    """
    # Charger les fichiers CSV
    df_ref = pd.read_csv(fichier_ref)
    df_mes = pd.read_csv(fichier_mes)

    # Vérifier que les fichiers ont le même nombre de points
    if len(df_ref) != len(df_mes):
        raise ValueError("Les fichiers CSV doivent contenir le même nombre de points.")

    # Extraire les valeurs sous forme de tableaux numpy
    lat_ref = df_ref.iloc[:, 1].to_numpy()  # 2ème colonne (Latitude)
    lon_ref = df_ref.iloc[:, 2].to_numpy()  # 3ème colonne (Longitude)
    lat_mes = df_mes.iloc[:, 1].to_numpy()
    lon_mes = df_mes.iloc[:, 2].to_numpy()

    # Calcul des erreurs
    erreur_stat_lat = np.mean(lat_ref - lat_mes)
    erreur_std_lat = np.std(lat_ref, ddof=1) - np.std(lat_mes, ddof=1)
    erreur_stat_lon = np.mean(lon_ref - lon_mes)
    erreur_std_lon = np.std(lon_ref, ddof=1) - np.std(lon_mes, ddof=1)

    return erreur_stat_lat, erreur_std_lat, erreur_stat_lon, erreur_std_lon

def filtrer_valeures_aberrantes_avec_interpolation(donnees):
    pass

def afficher_donnees(data_ref, data_gps):
    plt.figure(figsize=(15,15))
    plt.grid()
    plt.scatter(data_ref["Latitude"], data_ref["Longitude"], label="Téléphone GPS")
    plt.scatter(data_gps["Latitude"], data_gps["Longitude"], label="Carte GPS")

    plt.xlabel("Latitude")
    plt.ylabel("Longitude")
    plt.title("Trajets GPS - Carte vs Téléphone")
    plt.legend()
    plt.show()

def plot_GNSS(file_path):
    """
    Fonction pour tracer les données GNSS d'un parcours sur une carte OpenStreetMap, enregistrée dans un fichier HTML.
    
    Arguments:
    - file_path: Le chemin du fichier CSV contenant les données GNSS.
    """
    out_path,filename = os.path.split(file_path)
    data = pd.read_csv(file_path)

    m = folium.Map(location=[data['Latitude'][0], data['Longitude'][0]], zoom_start=12)

    points = list(zip(data['Latitude'], data['Longitude']))
    folium.PolyLine(points, color="blue", weight=2.5, opacity=1).add_to(m)

    m.save(out_path+filename.replace('.csv','.html'))
    print("Carte générée")

if __name__ == "__main__":
    afficher_donnees(pd.read_csv("boucle1_dumont_gps_ref.csv"), pd.read_csv("boucle1_dumont_gps.csv"))