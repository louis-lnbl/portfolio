from filterpy.kalman import KalmanFilter
import numpy as np
from scipy.spatial.transform import Rotation as R
import pandas as pd
from convert_latlong_to_xyz import convert


def normalize(v):
    return v / np.linalg.norm(v)

def R_body_to_NED(accel, mag):
    g_b = normalize(accel)
    m_b = normalize(mag)

    z_n = -g_b
    m_proj = m_b - np.dot(m_b, g_b) * g_b

    x_n = normalize(m_proj)
    y_n = np.cross(z_n, x_n)

    R_body_to_NED = np.column_stack((x_n,y_n,z_n))
    return R_body_to_NED


def R_NED_to_earth(lat_deg, lon_deg):
    lat = np.radians(lat_deg)
    lon = np.radians(lon_deg)

    m_R_NED_to_earth = np.array([
        [-np.sin(lat)*np.cos(lon), -np.sin(lon), -np.cos(lat)*np.cos(lon)],
        [-np.sin(lat)*np.sin(lon), np.cos(lon), -np.cos(lat)*np.sin(lon)],
        [np.cos(lat), 0, -np.sin(lat)]
    ])

    return m_R_NED_to_earth


def R_body_to_earth(accel,mag,lat_deg,lon_deg):
    m_R_body_to_NED = R_body_to_NED(accel, mag)
    m_R_NED_to_earth = R_NED_to_earth(lat_deg,lon_deg)

    m_R_body_to_earth = m_R_NED_to_earth @ m_R_body_to_NED

    return m_R_body_to_earth

def update_orientation(accel, mag, lat_deg, lon_deg, gyro, dt):
    
    R_body_to_earth = R_body_to_earth(accel, mag, lat_deg, lon_deg)
    
    q_current = R.from_matrix(R_body_to_earth)
    angle = np.linalg.norm(gyro) * dt

def project_point_on_sphere(point, old_radius, new_radius):
    """
    Projette un point situé sur une sphère de rayon `old_radius` sur une sphère de rayon `new_radius`.
    
    :param point: tuple ou liste de 3 coordonnées (x, y, z)
    :param old_radius: rayon de la sphère initiale
    :param new_radius: rayon de la sphère cible
    :return: tuple des nouvelles coordonnées (x', y', z')
    """
    point = np.array(point)
    norm = np.linalg.norm(point)
    
    if not np.isclose(norm, old_radius):
        raise ValueError(f"Le point ne semble pas être sur la sphère de rayon {old_radius}. Norme = {norm}")
    
    scale = new_radius / old_radius
    new_point = scale * point
    return tuple(new_point)

def point_apres_rotation_et_deplacement(point_repere_imu, matrice_rota_imu_terre, point_repere_terre):
    return matrice_rota_imu_terre@point_repere_imu + point_repere_terre



#ligne 5 de boucle1 dumont et donnees synchronisees
# accel = np.array([-0.9761219999999999,-0.053436,-0.290665])
# mag = np.array([0.20140309850920785,-0.03390821397252265,0.19073370359543992])
#ligne 57 imu2
accel = np.array([-1.014064,0.11022699999999999,-0.02257])
mag = np.array([0.2318035662087109,-0.16749488453668518,-0.08477053493130664])
lat_deg = 49.38424486666667
lon_deg = 1.06876165

rbodytoearth = R_body_to_earth(accel, mag, lat_deg, lon_deg)

rouen = [4146.040147659082, 77.34675668968164, 4835.4181384062995]
rouen_sur_sphere_1 = project_point_on_sphere(rouen, 6370, 1)


accel_ecef = point_apres_rotation_et_deplacement(accel, rbodytoearth, rouen_sur_sphere_1)
print("gravite rotation et deplacée sur rouen : ", tuple(accel_ecef))

nord_ecef = point_apres_rotation_et_deplacement(mag, rbodytoearth, rouen_sur_sphere_1)
print("nord rotation et deplacé sur rouen : ", tuple(nord_ecef))


def init_kf(dt):
    kf = KalmanFilter(dim_x=6, dim_z=3, dim_u=3)
    kf.P = np.eye(6) * 2 #incertitude initiale
    kf.R = np.eye(3)        # bruit de mesure du gps # Si ton GPS a une précision de 3 mètres (écart-type), alors la variance est 9
    kf.Q = np.eye(6) * 0.001  # bruit de l'imu
    kf.x = np.zeros(6)
    kf.H = np.array([
        [1, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 0],
    ])
    update_matrices_kf_dt(kf, dt)

    return kf

def update_matrices_kf_dt(kf, dt):
    
    kf.F = np.array([
        [1, 0, 0, dt, 0, 0],
        [0, 1, 0, 0, dt, 0],
        [0, 0, 1, 0, 0, dt],
        [0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 1],
    ])

    kf.B = np.array([
        [0.5*dt**2, 0, 0],
        [0, 0.5*dt**2, 0],
        [0, 0, 0.5*dt**2],
        [dt, 0, 0],
        [0, dt, 0],
        [0, 0, dt],
    ])

# def predict():
#     imu = pd.read_csv("../data/GR11_2/boucle1_dumont/boucle1_dumont_imu.csv")
#     gps = pd.read_csv("data/boucle1_dumont/donnees_synchronisees.csv")
#     n, p = imu.shape
#     dt = imu.iloc[1]['Timestamp'] - imu.iloc[0]['Timestamp']
#     kf = init_kf(dt)

#     lat_deg = gps.iloc[0]['Latitude']
#     lon_deg = gps.iloc[0]['Longitude']
#     accel = np.array([imu.iloc[0]['Accel X'], imu.iloc[0]['Accel Y'], imu.iloc[0]['Accel Z']])
#     mag = np.array([imu.iloc[0]['Magneto X'], imu.iloc[0]['Magneto Y'], imu.iloc[0]['Magneto Z']])
#     matrice_rota_imu_terre = R_body_to_earth(accel, mag, lat_deg, lon_deg)
#     coord = np.array(convert(lat_deg, lon_deg))
#     kf.x[0:3] = coord
    

#     tab_predictions_pos = []
#     tab_predictions_vit = []
#     tab_pos_reelles = []
#     for i in range(1, len(imu) - 1):
#         lat_deg = gps.iloc[i]['Latitude']
#         lon_deg = gps.iloc[i]['Longitude']
#         accel = np.array([imu.iloc[i]['Accel X'], imu.iloc[i]['Accel Y'], imu.iloc[i]['Accel Z']])
#         mag = np.array([imu.iloc[i]['Magneto X'], imu.iloc[i]['Magneto Y'], imu.iloc[i]['Magneto Z']])
#         matrice_rota_imu_terre = R_body_to_earth(accel, mag, lat_deg, lon_deg)
#         coord = np.array(convert(lat_deg, lon_deg))
#         accel = point_apres_rotation_et_deplacement(accel, matrice_rota_imu_terre, coord) - np.array([0,0,9.81])

#         kf.predict(u=accel)
#         kf.update(coord)

#         tab_predictions_pos.append(kf.x[0:3])
#         tab_predictions_vit.append(kf.x[3:6])
#         tab_pos_reelles.append(coord)

#         dt = gps.iloc[i+1]['Timestamp'] - gps.iloc[i]['Timestamp']
#         update_matrices_kf_dt(kf, dt)
#     return tab_predictions_pos, tab_predictions_vit, tab_pos_reelles


def predict(imu_path, gps_path):
    imu = pd.read_csv(imu_path)
    gps = pd.read_csv(gps_path)
    n, p = imu.shape
    dt = imu.iloc[1]['Timestamp'] - imu.iloc[0]['Timestamp']
    kf = init_kf(dt)
    erreur_statique_gyro = np.array([-0.002083729547678172,
                                     -0.0023561316292167373,
                                     0.004562626584318093])

    lat_deg_init = gps.iloc[0]['Latitude']
    lon_deg_init = gps.iloc[0]['Longitude']
    accel_init = np.array([imu.iloc[0]['Accel X'], imu.iloc[0]['Accel Y'], imu.iloc[0]['Accel Z']])
    mag_init = np.array([imu.iloc[0]['Magneto X'], imu.iloc[0]['Magneto Y'], imu.iloc[0]['Magneto Z']])
    matrice_rota_imu_terre_init = R_body_to_earth(accel_init, mag_init, lat_deg_init, lon_deg_init)
    coord = np.array(convert(lat_deg_init, lon_deg_init))
    vitesse_angulaire_init = np.array([imu.iloc[0]['Gyro X'], imu.iloc[0]['Gyro Y'], imu.iloc[0]['Gyro Z']]) - erreur_statique_gyro
    kf.x[0:3] = coord
    

    tab_predictions_pos = [coord]
    tab_predictions_vit = [[0,0,0]]
    tab_pos_reelles = [coord]
    angles_total_repere_imu = vitesse_angulaire_init * dt 
    for i in range(1, len(imu) - 1):
        lat_deg = gps.iloc[i]['Latitude']
        lon_deg = gps.iloc[i]['Longitude']
        coord = np.array(convert(lat_deg, lon_deg))

        dt = imu.iloc[i]['Timestamp'] - imu.iloc[i-1]['Timestamp']
        update_matrices_kf_dt(kf, dt)

        vitesse_angulaire = np.array([imu.iloc[i]['Gyro X'], imu.iloc[i]['Gyro Y'], imu.iloc[i]['Gyro Z']]) - erreur_statique_gyro
        angles_xyz = vitesse_angulaire * dt
        angles_total_repere_imu += angles_xyz
        
        accel = np.array([imu.iloc[i]['Accel X'], imu.iloc[i]['Accel Y'], imu.iloc[i]['Accel Z']])
        mag = np.array([imu.iloc[i]['Magneto X'], imu.iloc[i]['Magneto Y'], imu.iloc[i]['Magneto Z']])

        phi = angles_total_repere_imu[0]
        theta = angles_total_repere_imu[1]
        psi = angles_total_repere_imu[2]
        matrice_rotation_imu_gyro = np.array([
            [np.cos(theta)*np.cos(psi), -np.cos(theta)*np.sin(psi), np.sin(theta)],
            [np.sin(phi)*np.sin(theta)*np.cos(psi)+np.cos(phi)*np.sin(psi), -np.sin(phi)*np.sin(theta)*np.sin(psi)+np.cos(phi)*np.cos(psi), -np.sin(phi)*np.cos(theta)],
            [-np.cos(phi)*np.sin(theta)*np.cos(psi)+np.sin(phi)*np.sin(psi), np.cos(phi)*np.sin(theta)*np.sin(psi)+np.sin(phi)*np.cos(psi), np.cos(phi)*np.cos(theta)]
        ])

        accel_corrigee_angles = accel@matrice_rotation_imu_gyro.T
        accel_corrigee_repere_terre = accel_corrigee_angles@matrice_rota_imu_terre_init
        accel_corrigee_repere_terre -= np.array([0, 0, 9.81])

        kf.predict(u=accel_corrigee_repere_terre)
        # kf.update(coord)
        kf.update(tab_predictions_pos[-1])

        tab_predictions_pos.append(kf.x[0:3])
        tab_predictions_vit.append(kf.x[3:6])
        tab_pos_reelles.append(coord)
    return tab_predictions_pos, tab_predictions_vit, tab_pos_reelles

def syncroniser(df_gps: pd.DataFrame, df_imu: pd.DataFrame) -> tuple[pd.DataFrame, pd.DataFrame]:
    """
    Synchronise deux DataFrame GPS et IMU sur les timestamps GPS.

    - GPS (UTC) : format "YYYY/MM/DD - HH:MM:SS"
    - IMU (Timestamp) : timestamp Unix en secondes
    - Alignement : pour chaque timestamp GPS, associe l'échantillon IMU le plus proche.
    - Ne suffixe que les colonnes dupliquées (celle de l’IMU devient "<col>_imu"), 
      pour conserver intactes les colonnes GPS (Latitude, Longitude…).
    - Retourne deux DataFrame de même longueur : positions GPS et données IMU associées.
    """
    gps = df_gps.copy()
    imu = df_imu.copy()

    # conversion en datetime UTC
    gps['UTC'] = pd.to_datetime(
        gps['UTC'],
        format="%Y/%m/%d - %H:%M:%S",
        utc=True,
        errors='raise'
    )
    imu['UTC'] = pd.to_datetime(
        imu['Timestamp'],
        unit='s',
        utc=True,
        errors='raise'
    )

    # tri croissant
    gps.sort_values('UTC', inplace=True)
    imu.sort_values('UTC', inplace=True)

    # merge_asof : ne suffixe que les colonnes communes
    merged = pd.merge_asof(
        gps,
        imu,
        on='UTC',
        direction='nearest',
        suffixes=('', '_imu')
    )

    # extraction GPS (colonnes intactes)
    df_gps_sync = merged[['UTC', 'Latitude', 'Longitude']].reset_index(drop=True)

    # extraction IMU (UTC + tout le reste, y compris les colonnes suffixées)
    imu_cols = [c for c in merged.columns if c not in ('UTC', 'Latitude', 'Longitude')]
    df_imu_sync = merged[['UTC'] + imu_cols].reset_index(drop=True)


    return df_gps_sync, df_imu_sync

def sync_csv_to_csv(input_gps, input_csv, output_gps, output_csv):
    df_gps = pd.read_csv(input_gps)
    df_imu = pd.read_csv(input_csv)
    df_gps_sync, df_imu_sync = syncroniser(df_gps, df_imu)
    df_gps_sync.to_csv("data_en_csv/gps_sync.csv")
    df_imu_sync.to_csv("data_en_csv/imu_sync.csv")


# sync_csv_to_csv("../data/GR11_2/boucle1_dumont/boucle1_dumont_gps.csv", "../data/GR11_2/boucle1_dumont/boucle1_dumont_gps.csv", "data_en_csv/gps_sync.csv", "data_en_csv/imu_sync.csv")
pospred, vitpred, posreel = predict("../data/GR11_2/boucle1_dumont/boucle1_dumont_imu.csv", "data/boucle1_dumont/donnees_synchronisees.csv")
pospred = np.array(pospred)
print("jfkldsjflkdsmklf")
vitpred = np.array(vitpred)
posreel = np.array(posreel)
df = pd.DataFrame({
    'positions_pred_x': pospred[:,0],
    'positions_pred_y': pospred[:,1],
    'positions_pred_z': pospred[:,2],
    'pos_reel_x': posreel[:,0],
    'pos_reel_y': posreel[:,1],
    'pos_reel_z': posreel[:,2],
    'vit_pred_x': vitpred[:,0],
    'vit_pred_y': vitpred[:,1],
    'vit_pred_z': vitpred[:,2]
})
df.to_csv("data/boucle1_dumont/resultats_kalman.csv", index=False)


    