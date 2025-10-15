import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from geopy.distance import geodesic
from math import radians, sin, cos, sqrt, atan2


class ComparaisonParcours:
    """
    Classe permettant la comparaison d'un ensemble de parcours
    [parcour_ref1, parcour_gps1, parcour_ref2, parcour_gps2]
    """
    def __init__(self, nom , *parcours):
        self._nom = nom
        self._les_parcours = []
        for parcour in parcours:
            self.ajouter_parcour(parcour)
    
#-------------------------------------------------------------------------------------------



    def __len__(self):
        return len(self._les_parcours)

#-------------------------------------------------------------------------------------------



    def ajouter_parcour(self, parcour : pd.DataFrame):
        """
        
        """
        if isinstance(parcour, pd.DataFrame):
            self._les_parcours.append(parcour)
        else:
            raise TypeError("Erreur : L'élément à ajouter n'est pas un Parcour.")
    

#-------------------------------------------------------------------------------------------

    def syncronisation(self, p1 : int, p2 : int) -> None:
        data1 = self._les_parcours[p1]
        data2 = self._les_parcours[p2]

        data1['UTC'] = pd.to_datetime(data1['UTC'], utc=True, errors='raise')
        data2['UTC'] = pd.to_datetime(data2['UTC'], utc=True, errors='raise')

        merged = pd.merge(data1, data2, on='UTC', suffixes=('_1', '_2'))

        self._les_parcours[p1] = merged[['UTC', 'Latitude_1', 'Longitude_1']].rename(
            columns={'Latitude_1': 'Latitude', 'Longitude_1': 'Longitude'})
        self._les_parcours[p2] = merged[['UTC', 'Latitude_2', 'Longitude_2']].rename(
            columns={'Latitude_2': 'Latitude', 'Longitude_2': 'Longitude'})



#-------------------------------------------------------------------------------------------


    def haversine_distance(self, lat1, lon1, lat2, lon2):
        """Calcule la distance haversine entre deux points GPS."""
        return geodesic((lat1, lon1), (lat2, lon2)).meters
    
    def calculer_vitesse_acceleration(self, ind, lat_col='Latitude', lon_col='Longitude', time_col='UTC'):
        df = self._les_parcours[ind]
        df = df.copy().sort_values(time_col)
    
        df['time_diff'] = df[time_col].diff().dt.total_seconds()
        df['lat_diff'] = df[lat_col].diff()
        df['lon_diff'] = df[lon_col].diff()
    
        df['distance_diff'] = df.apply(
            lambda row: self.haversine_distance(
                row[lat_col] - row['lat_diff'],
                row[lon_col] - row['lon_diff'],
                row[lat_col],          
                row[lon_col]                    
                )
 if not np.isnan(row['lat_diff']) else np.nan,
            axis=1
        )
    
        df['vitesse'] = df['distance_diff'] / df['time_diff']
    
        df['acceleration'] = df['vitesse'].diff() / df['time_diff']
    
        self._les_parcours[ind] = df


    def identifier_valeurs_aberrantes_boxplot(self, ind, k=1.5):
        """
        Identifie les valeurs aberrantes en utilisant les limites des boxplots (méthode IQR).
        k: facteur pour ajuster la longueur des moustaches (typiquement 1.5)
        """
        self.calculer_vitesse_acceleration(ind)
        df = self._les_parcours[ind]
        
        df = df.copy()
    
        Q1_v = df['vitesse'].quantile(0.25)
        Q3_v = df['vitesse'].quantile(0.75)
        IQR_v = Q3_v - Q1_v
        limite_basse_v = Q1_v - k * IQR_v
        limite_haute_v = Q3_v + k * IQR_v
    
        Q1_a = df['acceleration'].quantile(0.25)
        Q3_a = df['acceleration'].quantile(0.75)
        IQR_a = Q3_a - Q1_a
        limite_basse_a = Q1_a - k * IQR_a
        limite_haute_a = Q3_a + k * IQR_a
    
        df['aberrant_vitesse'] = (df['vitesse'] < limite_basse_v) | (df['vitesse'] > limite_haute_v)
        df['aberrant_acceleration'] = (df['acceleration'] < limite_basse_a) | (df['acceleration'] > limite_haute_a)
        df['aberrant'] = df['aberrant_vitesse'] | df['aberrant_acceleration']
    
        df['limite_basse_vitesse'] = limite_basse_v
        df['limite_haute_vitesse'] = limite_haute_v
        df['limite_basse_acceleration'] = limite_basse_a
        df['limite_haute_acceleration'] = limite_haute_a
    
        self._les_parcours[ind] = df



#-------------------------------------------------------------------------------------------


    def plot_parcours(self, nom, *ind):
        """
        Affiche tous les parcours superposés sur une même figure après correction.
        Les points marqués comme aberrants sont affichés différemment.
        """
        if len(self) % 2 != 0:
            raise IndexError("Les parcours doivent être chargés 2 à 2.")

        plt.figure(figsize=(10, 8))

        for i in ind:
            p = self._les_parcours[i]

            # Tracer les points normaux
            normaux = p[~p.get("aberrant", False)]
            plt.plot(normaux["Longitude"], normaux["Latitude"],
                     marker="o", linestyle="-", alpha=0.7, label=f"Parcours : {i}")

            # Tracer les points aberrants s’ils existent
            if "aberrant" in p.columns:
                aberrants = p[p["aberrant"] == True]
                plt.scatter(aberrants["Longitude"], aberrants["Latitude"],
                            color='red', marker='x', s=60, label=f"Aberrants : {i}")

        plt.xlabel("Longitude")
        plt.ylabel("Latitude")
        plt.title(nom)
        plt.legend()
        plt.grid(True, linestyle="--", alpha=0.5)
        plt.gca().set_facecolor("white")
        plt.show()

    

#-------------------------------------------------------------------------------------------

    def corriger_parcours_global(self):

        for i in range(0, len(self), 2):
            p1 = self._corriger_parcour(self._les_parcours[i])
            p2 = self._corriger_parcour(self._les_parcours[i + 1])



#-------------------------------------------------------------------------------------------    
#     

    def afficher_parcours(self):
        plt.show()


#-------------------------------------------------------------------------------------------



    def DADerreur_statique(self, ind_parcour_ref, ind_parcour_reel):
        if ind_parcour_ref >= len(self._les_parcours) or ind_parcour_reel >= len(self._les_parcours):
            raise IndexError("L'un des indices fournis est hors des limites des parcours disponibles.")

        if len(self._les_parcours[ind_parcour_ref]) != len(self._les_parcours[ind_parcour_reel]):
            raise ValueError("Les fichiers CSV doivent contenir le même nombre de points.")

        latitude_ref = self._les_parcours[ind_parcour_ref]["Latitude"].values
        longitude_ref = self._les_parcours[ind_parcour_ref]["Longitude"].values
        latitude_reel = self._les_parcours[ind_parcour_reel]["Latitude"].values
        longitude_reel = self._les_parcours[ind_parcour_reel]["Longitude"].values

        erreur_stat_lat = np.mean(latitude_ref - latitude_reel)
        erreur_stat_lon = np.mean(longitude_ref - longitude_reel)

        return erreur_stat_lat, erreur_stat_lon

        

#-------------------------------------------------------------------------------------------


    def calculer_erreur_statique_globale(self):
        if len(self) % 2 != 0:
            raise IndexError("Les parcours doivent être chargés 2 à 2.")
        
        erreurs = []
        for i in range(0, len(self), 2):
            i1, i2 = i, i + 1
            self.syncronisation(i1, i2)
            erreurs.append(self.DADerreur_statique(i1, i2))

        df_erreurs = pd.DataFrame(erreurs, columns=("erreur_lat", "erreur_long"))
        return df_erreurs["erreur_lat"].mean(), df_erreurs["erreur_long"].mean()


#-------------------------------------------------------------------------------------------


    def corriger_erreur_statique_globale(self):
        erreur_lat, erreur_long = self.calculer_erreur_statique_globale()

        for i in range(0, len(self), 2):
            self._les_parcours[i + 1]["Latitude"] += erreur_lat
            self._les_parcours[i + 1]["Longitude"] += erreur_long


#-------------------------------------------------------------------------------------------


    def afficher_parcours_moyen_ref(self):
        for i in range(0, len(self), 2):
            i1, i2 = i, i + 1
            self.syncronisation(i1, i2)
        for i in range(0,len(self), 2):
            lat.append()



if __name__ == "__main__":
    data1_ref = pd.read_csv("data/GR11_2/boucle1_dumont/boucle1_dumont_gps.csv")
    data2_ref = pd.read_csv("data/GR11_2/boucle2_dumont/boucle2_dumont_gps.csv")
    data3_ref = pd.read_csv("data/GR11_2/boucle3_dumont/boucle3_dumont_gps.csv")
    data4_ref = pd.read_csv("data/GR11_2/boucle4_dumont/boucle4_dumont_gps.csv")
    data1_mes = pd.read_csv("data/GR11_2/data_en_csv/data_dumont_1.csv")
    data2_mes = pd.read_csv("data/GR11_2/data_en_csv/data_dumont_2.csv")
    data3_mes = pd.read_csv("data/GR11_2/data_en_csv/data_dumont_3.csv")
    data4_mes = pd.read_csv("data/GR11_2/data_en_csv/data_dumont_4.csv")

    comp1 = ComparaisonParcours("comparaison1", data1_ref, data1_mes)
    comp1.syncronisation(0,1)
    #comp1._les_parcours[0].at[0, "Latitude"] = 49.084246
    #comp1.plot_parcours("non corrigé", 0,1)
    print(comp1._les_parcours[0]["Latitude"][0])
    #comp1.corriger_parcour(0)
    #comp1.corriger_parcour(1)
    #comp1.plot_parcours("corrigé", 0,1)
    #comp1.afficher_parcours()

    # comp1.plot_parcours("Avant correction")
    # comp1.corriger_erreur_statique_globale()
    # comp1.plot_parcours("Après correction")
    # comp1.afficher_parcours()
    comp1.identifier_valeurs_aberrantes_boxplot(0)
    comp1.identifier_valeurs_aberrantes_boxplot(1)
    print(comp1._les_parcours[0])
    comp1.plot_parcours("test", 0,1)
    comp1.afficher_parcours()