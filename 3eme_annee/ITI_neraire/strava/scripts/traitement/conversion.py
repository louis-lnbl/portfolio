import pandas as pd
import xml.etree.ElementTree as ET
import re
from datetime import datetime
import math

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
    
    def format_time(date_str):
        date_obj = datetime.strptime(date_str, "%Y-%m-%dT%H:%M:%SZ")
        return f"{date_obj.year:04}/{date_obj.month:02}/{date_obj.day:02} - {date_obj.hour:02}:{date_obj.minute:02}:{date_obj.second:02}"
    
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
                data.append([format_time(timestamp), lat, lon])

    # Convertir en DataFrame
    df = pd.DataFrame(data, columns=["UTC", "Latitude", "Longitude"])

    # Enregistrer en fichier CSV
    df.to_csv(csv_file, index=False)
    print(f"Conversion terminée ! Fichier enregistré : {csv_file}")
    
def convert(lat, long):
    r = 6370
    theta = (90 - lat) * math.pi / 180
    phi = long * math.pi / 180
    x = r * math.sin(theta) * math.cos(phi)
    y = r * math.sin(theta) * math.sin(phi)
    z = r * math.cos(theta)
    return [x, y, z]

def convert_xyz_to_latlon(x, y, z):
    r = math.sqrt(x**2 + y**2 + z**2)
    lat = 90 - math.degrees(math.acos(z / r))
    lon = math.degrees(math.atan2(y, x))
    return [lat, lon]

def res_kalman_csv_to_latlon(input_path):
    df = pd.read_csv(input_path)
    df_res = pd.DataFrame({
        'Latitude': df['Latitude'],
        'Longitude': df['Longitude']
    })
    return res