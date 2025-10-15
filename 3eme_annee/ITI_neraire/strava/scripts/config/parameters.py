from . import GPS_BEIDOU_GLONASS,GPS_GLONASS,BEIDOU_GLONASS,GPS_BEIDOU,GLONASS,GPS,BEIDOU

# Paramètres du GNSS
MODE_GNSS = GPS_BEIDOU_GLONASS

# Paramètres de l'IMU
ACCEL_RANGE=2                  # Plage de mesure de l'accéléromètre (g)
ACCEL_FREQ=833               # Fréquence d'échantillonnage de l'accéléromètre (Hz)  
GYRO_RANGE=2                  # Plage de mesure du gyroscope (dps)
GYRO_FREQ=833                # Fréquence d'échantillonnage du gyroscope (Hz)
MAGNETO_RANGE=4                # Plage de mesure du magnétomètre (gauss)
MAGNETO_FREQ=40                # Fréquence d'échantillonnage du magnétomètre (Hz)

# Paramètres du LiDAR
MIN_ANGLE=0                    # Angle minimal du scan en degrés
MAX_ANGLE=0                    # Angle maximal du scan en degrés
QUALITY_THRESHOLD=...            # Seuil de qualité des mesures du LiDAR (entre 0 et 15)
SCAN_SKIP = 3                    # Ignorer X scans pour alléger l'affichage (via stream_scan.py)
