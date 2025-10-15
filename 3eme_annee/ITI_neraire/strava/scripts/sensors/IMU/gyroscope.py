import smbus
import time
from scripts.config import OUTX_L_G
from scripts.config.constants import DICT_FREQ, DICT_RANGE, DICT_RANGE_FACTOR

def gyroscope_configuration(gyro_range, gyro_freq):
    """
    Configure les paramètres du LSM6DSO pour le gyroscope.

    Arguments: 
    - gyro_range: la range du gyroscope
    - gyro_freq: la fréquence d'acquisition du gyroscope

    Résultat : l'octet à écrire dans le registre CTRL2_G pour configurer le gyroscope
    """
    # Configuration du gyroscope
    # A COMPLETER
    ...
    return (DICT_FREQ[gyro_freq] * 2**4 + DICT_RANGE[gyro_range] * 2**2)

def read_gyroscope(device_addr, gyro_range):
    """
    Lit les données du gyroscope et les convertit.

    Arguments: 
    - device_addr: l'adresse I2C du composant
    - gyro_range: la range du gyroscope

    Résultat: les données acquises par le gyroscope en unité physique sur les 3 axes
    """
    from sensors.IMU import read_raw_data
    x, y, z = read_raw_data(device_addr, OUTX_L_G)
    
    # A COMPLETER
    sensitivity = DICT_RANGE_FACTOR[gyro_range] / 1000
    return x * sensitivity, y * sensitivity, z * sensitivity
