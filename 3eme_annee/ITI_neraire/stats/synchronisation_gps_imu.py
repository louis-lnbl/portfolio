import pandas as pd
import numpy as np

class SynchroniserGpsImu:

    def __init__(self, fichier_gps, fichier_imu, fichier_gpx, destination_path):
        self.data_gps = pd.read_csv(fichier_gps)
        self.data_imu = pd.read_csv(fichier_imu)
        self.data_gpx = pd.read_csv(fichier_gpx)
        self.destination_path = destination_path


    def valeur_init(self):
        temps1_gps = self.data_gps["Timestamp"][0]
        temps1_imu = self.data_imu["Timestamp"][0]

        if temps1_gps > temps1_imu:
            return "gps"
        return "imu"

    def valeur_plus_proche(self, data_gps):
        min_val = abs((self.data_imu['Timestamp'] - data_gps)).argmin()
        return self.data_imu.Timestamp[min_val]

    def arg_plus_proche(self, data_gps):
        min_val = abs((self.data_imu['Timestamp'] - data_gps)).argmin()
        return min_val


    def premier_indice_superieur(self, data_imu):
        i = 0
        while True:
            if self.data_gps.Timestamp[i] > data_imu:
                return i
            i += 1


    def synchroniser_imu_to_gps(self):
        premier = self.valeur_init()
        tab_gps = []
        tab_imu = []
        n, p = self.data_gps.shape

        val_start_gps = 0
        if premier == "imu":
            val_start_gps = self.premier_indice_superieur(self.data_imu.Timestamp[0])

        for i in range(val_start_gps, n):
            tab_gps.append(self.data_gps.Timestamp[i])
            val_imu_close = self.valeur_plus_proche(self.data_gps.Timestamp[i])
            tab_imu.append(val_imu_close)
            if val_imu_close == self.data_imu["Timestamp"].iloc[-1]:
                break

        return tab_gps, tab_imu

    def synchroniser_gps_to_imu(self):
        arguments_plus_proches = []
        n_gps, p_gps = self.data_gps.shape
        n_imu, p_imu = self.data_imu.shape
        for i in range(n_gps):
            arg = self.arg_plus_proche(self.data_gps.Timestamp[i])
            arguments_plus_proches.append(arg)
            if arg == n_imu - 1:
                self.data_gps = self.data_gps.drop([j for j in range(i + 1, n_gps)])
                break
        
        #print(len(arguments_plus_proches))
        #print(arguments_plus_proches)
        #print(self.data_gps.iloc[0])

        n, p = self.data_gps.shape
        colonnes = ['Timestamp', 'Latitude', 'Longitude']
        data_gps_interpole = pd.DataFrame(columns=colonnes)
        # for i in range(2):
        for i in range(n - 1):
            nv_ligne = pd.DataFrame([{'Timestamp':self.data_gps.iloc[i]['Timestamp'], 'Latitude':self.data_gps.iloc[i]['Latitude'], 'Longitude':self.data_gps.iloc[i]['Longitude']}])
            data_gps_interpole = pd.concat([data_gps_interpole, nv_ligne], ignore_index=True)
            ligne_debut = self.data_gps.iloc[i]
            ligne_fin = self.data_gps.iloc[i + 1]
            timestamp_interpoles = np.linspace(ligne_debut.Timestamp, ligne_fin.Timestamp, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            latitude_interpolees = np.linspace(ligne_debut.Latitude, ligne_fin.Latitude, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            longitude_interpolees = np.linspace(ligne_debut.Longitude, ligne_fin.Longitude, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            timestamp_interpoles = timestamp_interpoles[1:-1]
            latitude_interpolees = latitude_interpolees[1:-1]
            longitude_interpolees = longitude_interpolees[1:-1]
            for j in range(timestamp_interpoles.size):
                nv_ligne = pd.DataFrame([{'Timestamp':timestamp_interpoles[j], 'Latitude':latitude_interpolees[j], 'Longitude':longitude_interpolees[j]}])
                data_gps_interpole = pd.concat([data_gps_interpole, nv_ligne], ignore_index=True)

        nv_ligne = pd.DataFrame([{'Timestamp':self.data_gps.iloc[-1]['Timestamp'], 'Latitude':self.data_gps.iloc[-1]['Latitude'], 'Longitude':self.data_gps.iloc[-1]['Longitude']}])
        data_gps_interpole = pd.concat([data_gps_interpole, nv_ligne], ignore_index=True)

        data_gps_interpole.to_csv(self.destination_path, index=False)
        return data_gps_interpole

    def synchroniser_gpx_to_imu(self):
        arguments_plus_proches = []
        n_gpx, p_gpx = self.data_gpx.shape
        n_imu, p_imu = self.data_imu.shape
        for i in range(n_gpx):
            arg = self.arg_plus_proche(self.data_gpx.Timestamp[i])
            arguments_plus_proches.append(arg)
            if arg == n_imu - 1:
                self.data_gpx = self.data_gpx.drop([j for j in range(i + 1, n_gpx)])
                break

        n, p = self.data_gpx.shape
        colonnes = ['Timestamp', 'Latitude', 'Longitude','Elevation','Speed']
        data_gpx_interpole = pd.DataFrame(columns=colonnes)
        for i in range(n - 1):
            nv_ligne = pd.DataFrame([{'Timestamp':self.data_gpx.iloc[i]['Timestamp'], 'Latitude':self.data_gpx.iloc[i]['Latitude'], 'Longitude':self.data_gpx.iloc[i]['Longitude'], 'Elevation':self.data_gpx.iloc[i]['Elevation'], 'Speed':self.data_gpx.iloc[i]['Speed']}])
            data_gpx_interpole = pd.concat([data_gpx_interpole, nv_ligne], ignore_index=True)
            ligne_debut = self.data_gpx.iloc[i]
            ligne_fin = self.data_gpx.iloc[i + 1]
            timestamp_interpoles = np.linspace(ligne_debut.Timestamp, ligne_fin.Timestamp, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            latitude_interpolees = np.linspace(ligne_debut.Latitude, ligne_fin.Latitude, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            longitude_interpolees = np.linspace(ligne_debut.Longitude, ligne_fin.Longitude, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            elevation_interpolees = np.linspace(ligne_debut.Elevation, ligne_fin.Elevation, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            speed_interpolees = np.linspace(ligne_debut.Speed, ligne_fin.Speed, arguments_plus_proches[i + 1] - arguments_plus_proches[i] + 1)
            timestamp_interpoles = timestamp_interpoles[1:-1]
            latitude_interpolees = latitude_interpolees[1:-1]
            longitude_interpolees = longitude_interpolees[1:-1]
            elevation_interpolees = elevation_interpolees[1:-1]
            speed_interpolees = speed_interpolees[1:-1]
            for j in range(timestamp_interpoles.size):
                nv_ligne = pd.DataFrame([{'Timestamp':timestamp_interpoles[j], 'Latitude':latitude_interpolees[j], 'Longitude':longitude_interpolees[j], 'Elevation':elevation_interpolees[j], 'Speed':speed_interpolees[j]}])
                data_gpx_interpole = pd.concat([data_gpx_interpole, nv_ligne], ignore_index=True)

        nv_ligne = pd.DataFrame([{'Timestamp':self.data_gpx.iloc[-1]['Timestamp'], 'Latitude':self.data_gpx.iloc[-1]['Latitude'], 'Longitude':self.data_gpx.iloc[-1]['Longitude'], 'Elevation':self.data_gpx.iloc[-1]['Elevation'], 'Speed':self.data_gpx.iloc[-1]['Speed']}])
        data_gpx_interpole = pd.concat([data_gpx_interpole, nv_ligne], ignore_index=True)

        data_gpx_interpole.to_csv(self.destination_path, index=False)
        return data_gpx_interpole


if __name__ == "__main__":
    sync = SynchroniserGpsImu("../data/GR11_2/boucle1_dumont/boucle1_dumont_gps.csv", "../data/GR11_2/boucle1_dumont/boucle1_dumont_imu.csv", "data/boucle1_dumont/gpx.csv", "data/boucle1_dumont/gpx_synchro.csv")
    gps_inter = sync.synchroniser_gpx_to_imu()
