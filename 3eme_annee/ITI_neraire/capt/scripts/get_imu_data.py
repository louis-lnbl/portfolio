import sys
import os
print("PYTHONPATH =", sys.path)
print("cwd =", sys.argv[0])

# Obtenir le chemin du dossier parent
parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# L'ajouter au sys.path
sys.path.insert(0, parent_dir)

import time
import argparse
from config.constants import LSM6DSO_ADDR, LIS3MDL_ADDR
from config.parameters import ACCEL_RANGE, ACCEL_FREQ, GYRO_RANGE, GYRO_FREQ, MAGNETO_RANGE, MAGNETO_FREQ
from core.imu_acquisition import get_imu_data

#def main():
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--save-path', '-s',
                        type=str,
                        default=None,
                        help="Chemin où sauvegarder les données.")
    args = parser.parse_args()

#    path = input("Chemin de Sauvegarde des Données : ")
#    if not os.path.exists(path):
#        raise FileNotFoundError("Le fichier n'existe pas : " + path)

    get_imu_data(LSM6DSO_ADDR, LIS3MDL_ADDR, ACCEL_RANGE, ACCEL_FREQ, GYRO_RANGE, GYRO_FREQ, MAGNETO_RANGE, MAGNETO_FREQ, args.save_path)