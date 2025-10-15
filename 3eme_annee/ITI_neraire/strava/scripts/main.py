#!/bin/python3

__author__ = "Maxime Etienne"
__version__ = 1.0

import pandas as pd

from scripts.traitement.traitements import *
from scripts.traitement.syncronisation import *
from scripts.traitement.analyse import *
from scripts.traitement.affichage import *
from scripts.traitement.conversion import *
from scripts.traitement.filtre_kalman import *

if __name__ == "__main__":
    from scripts.acquisition.carte import *

    df = pd.read_csv(gnss_file)
    df_imu = pd.read_csv(imu_file)
    df_traite, indices_supprimes, vitesses = traitement_total(df)
    # syncroniseur = SynchroniserGpsImu(df_traite, df_imu, gnss_file)
    # df_gps_sync = syncroniseur.synchroniser_gps_to_imu()
    # ---- Affichage ----
    affichage_total(df, df_imu, df_traite, indices_supprimes, vitesses)
    # ---- Enregistrement ----
    df_traite.to_csv(gnss_file)
    enregister_parcours_map(gnss_file)

    #gnss_path, _ = gnss_file.split(".")
    #kalman_file = gnss_path + "_kalman.csv"
    #filtre_kalman(imu_file, gnss_file, kalman_file)
    #df_res_kalman = res_kalman_csv_to_latlon(kalman_file)
    #df_res_kalman.to_csv(kalman_file)
    #enregister_parcours_map(kalman_file)
