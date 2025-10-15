from converter_gpx import convert_gpx_to_csv
import pandas as pd
import os

def syncronisation_to_df(path_data_ref_gpx: str, path_data_gps_csv: str):
    path_data_ref_csv = os.path.basename(path_data_ref_gpx).replace(".gpx", ".csv")
    convert_gpx_to_csv(path_data_ref_gpx, path_data_ref_csv)

    data_ref = pd.read_csv(path_data_ref_csv)
    data_gps = pd.read_csv(path_data_gps_csv)

    data_ref['UTC'] = pd.to_datetime(data_ref['UTC'], utc=True, errors='raise')
    data_gps['UTC'] = pd.to_datetime(data_gps['UTC'], utc=True, errors='raise')

    # Exact UTC-based merge
    merged = pd.merge(data_ref, data_gps, on='UTC', suffixes=('_ref', '_gps'))

    # Extract and rename
    data_ref_sync = merged[['UTC', 'Latitude_ref', 'Longitude_ref']].rename(
        columns={'Latitude_ref': 'Latitude', 'Longitude_ref': 'Longitude'}
    )
    data_gps_sync = merged[['UTC', 'Latitude_gps', 'Longitude_gps']].rename(
        columns={'Latitude_gps': 'Latitude', 'Longitude_gps': 'Longitude'}
    )

    return data_ref_sync, data_gps_sync

def syncronisation(path_data_ref_gpx: str, path_data_gps_csv: str):
    # Save synced CSVs
    data_ref_sync, data_gps_sync = syncronisation_to_df(path_data_ref_gpx, path_data_gps_csv)
    data_ref_sync.to_csv(os.path.basename(path_data_ref_gpx).replace(".gpx", ".csv"), index=False)
    data_gps_sync.to_csv(os.path.basename(path_data_gps_csv), index=False)

if __name__ == "__main__":
    syncronisation("../data/GR11_2/boucle1_dumont/boucle1_dumont_gps_ref.gpx", "../data/GR11_2/boucle1_dumont/boucle1_dumont_gps.csv")