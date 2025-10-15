import os
import pandas as pd
import folium
from strava.scripts.traitement.syncronisation import syncronisation
from filtrage import plot_GNSS

def plot_GNSS(file_path_1, file_path_2):
    """
    Trace deux fichiers GNSS sur une carte OpenStreetMap et sauvegarde en HTML.
    
    Arguments:
    - file_path_1: Chemin du fichier CSV pour le premier jeu de données (ex: référence).
    - file_path_2: Chemin du fichier CSV pour le second jeu de données (ex: téléphone).
    """
    # Load both datasets
    data1 = pd.read_csv(file_path_1)
    data2 = pd.read_csv(file_path_2)

    # Output path based on first file
    out_path, filename = os.path.split(file_path_1)
    filename_base = filename.replace('.csv', '')

    # Create map centered on first point
    m = folium.Map(location=[data1['Latitude'][0], data1['Longitude'][0]], zoom_start=14)

    # Plot track 1 (blue)
    points1 = list(zip(data1['Latitude'], data1['Longitude']))
    folium.PolyLine(points1, color="blue", weight=2.5, opacity=1, tooltip="Référence GPS").add_to(m)

    # Plot track 2 (red)
    points2 = list(zip(data2['Latitude'], data2['Longitude']))
    folium.PolyLine(points2, color="red", weight=2.5, opacity=1, tooltip="Téléphone GPS").add_to(m)

    # Add legend via custom HTML
    legend_html = '''
        <div style="position: fixed; 
                    bottom: 50px; left: 50px; width: 180px; height: 70px; 
                    background-color: white; border:2px solid grey; z-index:9999; font-size:14px;
                    padding: 10px;">
        <b>Légende</b><br>
        <span style="color:blue;">●</span> Référence GPS<br>
        <span style="color:red;">●</span> Téléphone GPS
        </div>
    '''
    m.get_root().html.add_child(folium.Element(legend_html))

    # Save the map
    output_file = os.path.join(out_path, f"{filename_base}_comparison.html")
    m.save(output_file)
    print(f"Carte générée : {output_file}")


if __name__ == "__main__":
    trajet = "boucle4"
    PATH = f"../data/GR11_2/{trajet}_dumont/"
    PATH_GPS_REF_GPX = f"{trajet}_dumont_gps_ref.gpx"
    PATH_GPS_CSV = f"{trajet}_dumont_gps.csv"

    syncronisation(PATH + PATH_GPS_REF_GPX, PATH + PATH_GPS_CSV)

    plot_GNSS(PATH_GPS_REF_GPX.replace(".gpx", ".csv"), PATH_GPS_CSV)

    os.remove(PATH_GPS_REF_GPX.replace(".gpx", ".csv"))
    os.remove(PATH_GPS_CSV)