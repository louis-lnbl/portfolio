#!/bin/python3

import sys
import os
import pandas as pd
import xml.etree.ElementTree as ET
import re

def convert_gpx_to_csv(gpx_file, csv_file):
    """
    Convertit un fichier GPX en un fichier CSV avec les colonnes 'Timestamp', 'Latitude' et 'Longitude'.
    
    Arguments:
    - gpx_file: Chemin du fichier GPX d'entrée.
    - csv_file: Chemin du fichier CSV de sortie.
    """
    
    def get_namespace(element):
        """ Récupère l'espace de noms utilisé dans le fichier GPX """
        match = re.match(r'\{.*\}', element.tag)
        return match.group(0) if match else ''
    
    # Parse le fichier GPX
    tree = ET.parse(gpx_file)
    root = tree.getroot()

    # Détecter l'espace de noms utilisé
    namespace = get_namespace(root)

    # Extraire les données
    data = []
    for trk in root.findall(f"{namespace}trk"):
        for trkseg in trk.findall(f"{namespace}trkseg"):
            for trkpt in trkseg.findall(f"{namespace}trkpt"):
                lat = trkpt.get("lat")
                lon = trkpt.get("lon")
                time_element = trkpt.find(f"{namespace}time")
                timestamp = time_element.text if time_element is not None else None
                data.append([timestamp, lat, lon])

    # Convertir en DataFrame
    df = pd.DataFrame(data, columns=["UTC", "Latitude", "Longitude"])

    # Enregistrer en fichier CSV
    df.to_csv(csv_file, index=False)
    print(f"Conversion terminée ! Fichier enregistré : {csv_file}")


if __name__ == "__main__":
    
    if len(sys.argv) < 3:
        raise Exception("No file found : converter_gpx.py {file_gpx} {file_csv} !")

    file_gpx = sys.argv[1]
    file_csv = sys.argv[2]

    if not os.path.exists(file_gpx):
        raise FileNotFoundError(f"File {file_gpx} not found !")

    print("[Converting data...]")
    convert_gpx_to_csv(file_gpx, file_csv)