# acquisition_strava_toggle #3

from multiprocessing import Process
from utils import Button, LED, LCD
from config.constants import PORT_BOUTON, PORT_LED, LCD_DEVICE_ADDR, GPS_BEIDOU_GLONASS
from config import LSM6DSO_ADDR, LIS3MDL_ADDR, ACCEL_RANGE, ACCEL_FREQ, GYRO_RANGE, GYRO_FREQ, MAGNETO_RANGE, MAGNETO_FREQ
from datetime import datetime
from core.IMU_wrapper import acquisition_imu
from core.GNSS_wrapper import acquisition_gnss
from sys import exit
import os
import pandas as pd

# from ...stats.traitement_general import traitement_total, syncronisation

def quitter_strava():
    global attente
    attente = False
    print("[Enregistrement]")
    lcd.afficher("[Enregistrement...]")

    desc_file = os.path.join(sample_data_path,  os.path.basename(sample_data_path) + "_description.md")
    with open(desc_file, "w") as fichier:
        fichier.write("## Configuration\n")
        fichier.write(f"-Acceleration Range : {ACCEL_RANGE}\n")
        fichier.write(f"-Acceleration Fréquence : {ACCEL_FREQ}\n")
        fichier.write(f"-Gyroscope Range : {GYRO_RANGE}\n")
        fichier.write(f"-Gyroscope Fréquence : {GYRO_FREQ}\n")
        fichier.write(f"-Magnétoscope Range : {MAGNETO_RANGE}\n")
        fichier.write(f"-Magnétoscope Fréquence : {MAGNETO_FREQ}\n")
        fichier.write("## Conditions\n")
        fichier.write(str(datetime.now()))

    if imu_proc is not None:
        imu_proc.terminate()
        imu_proc.join()
    if gnss_proc is not None:
        gnss_proc.terminate()
        gnss_proc.join()

    button.cleanup()
    led.off()
    led.cleanup()

    analyse_donnees()

    exit()

def acquisition_strava():
    global acquisition
    global imu_proc, gnss_proc
    acquisition = True

    print("[Acquisition...]")
    lcd.afficher("[Acquisition...]")
    led.on()

    gnss_file = os.path.join(sample_data_path, os.path.basename(sample_data_path) + "_gps.csv")
    imu_file = os.path.join(sample_data_path, os.path.basename(sample_data_path) + "_imu.csv")

    imu_proc = Process(
        target=acquisition_imu,
        args=(
            LSM6DSO_ADDR, LIS3MDL_ADDR,
            ACCEL_RANGE, ACCEL_FREQ,
            GYRO_RANGE, GYRO_FREQ,
            MAGNETO_RANGE, MAGNETO_FREQ,
            imu_file, lcd, True
        )
    )

    gnss_proc = Process(
        target=acquisition_gnss,
        args=(GPS_BEIDOU_GLONASS, gnss_file, lcd, True)
    )

    imu_proc.start()
    gnss_proc.start()

def toggle_acquisition():
    global acquisition
    if not acquisition:
        acquisition_strava()
    else:
        quitter_strava()

# def analyse_donnees(path):
#     df_gps = traitement_total(path)
#     df_imu = pd.read_csv(path.replace("gps", "imu"))

#     df_sync_gps, df_sync_imu = syncronisation(df_gps, df_imu)

#     df_sync_gps.to_csv(path)
#     df_sync_imu.to_csv(path.replace("gps", "imu"))


if __name__ == "__main__":
    imu_proc = None
    gnss_proc = None
    attente = True
    acquisition = False
    sample_data_path = input("Sample data path : ")
    if not os.path.exists(sample_data_path):
        raise ValueError("Le chemin n'existe pas !")

    button = Button(PORT_BOUTON)
    led = LED(PORT_LED)
    lcd = LCD(LCD_DEVICE_ADDR)

    lcd.afficher("[Initialisation...]")

    button.on_press(toggle_acquisition)

    print("[En Attente...]")
    while attente:
        pass

    #analyse_donnees(sample_data_path, os.path.basename(sample_data_path) + "_gps.csv")