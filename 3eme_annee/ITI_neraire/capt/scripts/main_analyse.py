from traitement_general import traitement_total, syncronisation
import pandas as pd

def analyse_donnees(path):
    df_gps = traitement_total(path)
    df_imu = pd.read_csv(path.replace("gps", "imu"))

    df_sync_gps, df_sync_imu = syncronisation(df_gps, df_imu)

    df_sync_gps.to_csv(path)
    df_sync_imu.to_csv(path.replace("gps", "imu"))

if __name__ == "__main__":
	# analyse_donnees("data/actest1/actest1_gps.csv")