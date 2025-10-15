import smbus
import time
from scripts.config import OUTX_L_A
from scripts.config.constants import DICT_FREQ, DICT_RANGE, DICT_RANGE_FACTOR

def accelerometer_configuration(accel_range, accel_freq):
    """
    Configure les paramètres du LSM6DSO pour l'accéléromètre.

    Arguments: 
    - accel_range: la range de l'accélérateur
    - accel_freq: la fréquence d'acquisition de l'accélérateur

    Résultat : l'octet à écrire dans le registre CTRL1_XL pour configurer l'accéléromètre
    """
    # Configuration de l'accéléromètre
    # A COMPLETER
    ...
    return (DICT_FREQ[accel_freq] * 2**4 + DICT_RANGE[accel_range] * 2**2)

def read_accelerometer(device_addr, accel_range):
    """
    Lit les données de l'accéléromètre et les convertit.

    Arguments: 
    - device_addr: l'adresse I2C du composant
    - accel_range: la range de l'accéléromètre

    Résultat: les données acquises par de l'accéléromètre en unité physique sur les 3 axes
    """
    from sensors.IMU import read_raw_data
    x, y, z = read_raw_data(device_addr, OUTX_L_A)

    # A COMPLETER
    sensitivity = DICT_RANGE_FACTOR[accel_range] / 1000
    return x * sensitivity, y * sensitivity, z * sensitivity
