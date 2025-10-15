import time
from scripts.utils import CSVHandler
from scripts.sensors.IMU import read_IMU, initialize_sensors

def acquisition_imu(XL_addr, MAG_ADDR, accel_range, accel_freq, gyro_range, gyro_freq, magneto_range, magneto_freq, csv_out=None, lcd=None, console=False):
    """
    Fait l'acquisition des données IMU (accéléromètre et gyroscope) en fonction des paramètres d'acquisition.

    Arguments:
    - XL_addr: l'adresse I2C du LSM6DSO 
    - MAG_addr: l'adresse I2C du LIS3MDL 
    - accel_range: la plage de mesure de l'accéléromètre (g).
    - accel_freq: la fréquence d'échantillonnage de l'accéléromètre (Hz).
    - gyro_range: la plage de mesure du gyroscope (dps).
    - gyro_freq: la fréquence d'échantillonnage du gyroscope (Hz).
    - magneto_range: la range du magnétomètre
    - magneto_freq: la fréquence d'acquisition du magnétomètre
    - csv_out: le chemin du fichier CSV d'enregistrement (si définit à None, aucun enregistrement n'est effectué)
    """
    
    # Calculer l'intervalle en secondes (en fonction de la fréquence)
    interval = 1 / min(accel_freq,gyro_freq)

    # Création du fichier CSV d'enregistrement
    if csv_out is not None:
        if not csv_out.endswith('.csv'):
            csv_out += '.csv'
        record = CSVHandler(csv_out)
        record.create_csv_with_header(['Timestamp', 'Accel X', 'Accel Y', 'Accel Z', 'Gyro X', 'Gyro Y', 'Gyro Z', 'Magneto X', 'Magneto Y', 'Magneto Z'])

    # Initialisation des capteurs
    initialize_sensors(XL_addr, MAG_ADDR, accel_range, accel_freq, gyro_range, gyro_freq, magneto_range, magneto_freq)

    try:
        while True:
            start_time = time.time()

            # Lecture des données
            accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z, magneto_x, magneto_y, magneto_z = read_IMU(XL_addr, MAG_ADDR, accel_range, gyro_range, magneto_range)

            # Enregistrement des données dans le fichier CSV
            if csv_out is not None:
                record.append_row([time.time(), accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z, magneto_x, magneto_y, magneto_z])

            if lcd is not None:
                lcd.afficher(f"Accelerometer (g): X={accel_x:.3f}, Y={accel_y:.3f}, Z={accel_z:.3f}")

            # Affichage des résultats
            if console:
                print("-------------------- IMU --------------------------------------------")
                print(f"Accelerometer (g): X={accel_x:.3f}, Y={accel_y:.3f}, Z={accel_z:.3f}")
                print(f"Gyroscope (dps): X={gyro_x:.3f}, Y={gyro_y:.3f}, Z={gyro_z:.3f}")
                print(f"Magnetometer (gauss): X={magneto_x:.3f}, Y={magneto_y:.3f}, Z={magneto_z:.3f}")
                print('-' * 50)

            # Calcul de la durée de la boucle et ajustement du délai
            elapsed_time = time.time() - start_time
            time_to_sleep = max(0, interval - elapsed_time)
            time.sleep(time_to_sleep)

    except KeyboardInterrupt:
        print("Arrêt du programme.")