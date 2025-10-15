import gpxpy
from datetime import datetime
import pandas as pd

def gpx_to_csv(path):
    lat = []
    lon = []
    ele = []
    tps = []
    speed = []
    with open(path, 'r') as f:
        gpx = gpxpy.parse(f)
    for track in gpx.tracks:
        for segment in track.segments:
            for point in segment.points:
                time = point.time
                iso_str = str(time)
                dt = datetime.fromisoformat(iso_str)
                timestamp = dt.timestamp()
                lat.append(point.latitude)
                lon.append(point.longitude)
                ele.append(point.elevation)
                tps.append(timestamp)
                speed.append(point.speed)
    df = pd.DataFrame({
        'Timestamp': tps,
        'Latitude': lat,
        'Longitude': lon,
        'Elevation': ele,
        'Speed': speed,
    })
    df.to_csv("data/boucle1_dumont/gpx.csv", index=False)



gpx_to_csv("../data/GR11_2/boucle1_dumont/boucle1_dumont_gps_ref.gpx")