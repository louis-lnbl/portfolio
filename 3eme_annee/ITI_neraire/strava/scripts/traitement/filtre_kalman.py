"""Module implementant le filtre de kalman"""
from filterpy.kalman import KalmanFilter
import numpy as np
from scipy.spatial.transform import Rotation as R
import pandas as pd
from .conversion import *

__all__ = ["filtre_kalman"]

def normalize(v):
    """Fonction qui normalise un vecteur"""
    return v / np.linalg.norm(v)

def R_body_to_NED(accel, mag):
    """Cree un repere orthogonal a partir d un repere imu"""
    g_b = normalize(accel)
    m_b = normalize(mag)

    z_n = -g_b
    m_proj = m_b - np.dot(m_b, g_b) * g_b

    x_n = normalize(m_proj)
    y_n = np.cross(z_n, x_n)

    R_body_to_NED = np.column_stack((x_n,y_n,z_n))
    return R_body_to_NED


def R_NED_to_earth(lat_deg, lon_deg):
    """Transforme un repere terrestre en repere geocentrique"""
    lat = np.radians(lat_deg)
    lon = np.radians(lon_deg)

    m_R_NED_to_earth = np.array([
        [-np.sin(lat)*np.cos(lon), -np.sin(lon), -np.cos(lat)*np.cos(lon)],
        [-np.sin(lat)*np.sin(lon), np.cos(lon), -np.cos(lat)*np.sin(lon)],
        [np.cos(lat), 0, -np.sin(lat)]
    ])

    return m_R_NED_to_earth


def R_body_to_earth(accel,mag,lat_deg,lon_deg):
    """Transforme un repere imu en repere geocentrique"""
    m_R_body_to_NED = R_body_to_NED(accel, mag)
    m_R_NED_to_earth = R_NED_to_earth(lat_deg,lon_deg)

    m_R_body_to_earth = m_R_NED_to_earth @ m_R_body_to_NED

    return m_R_body_to_earth

def update_orientation(accel, mag, lat_deg, lon_deg, gyro, dt):
    """Actualise l orientation a partir des donnees du gyroscope"""
    R_body_to_earth_matrix = R_body_to_earth(accel, mag, lat_deg, lon_deg)
    q_current = R.from_matrix(R_body_to_earth_matrix)

    delta_rotation = R.from_rotvec(gyro * dt)

    q_new = q_current * delta_rotation

    return q_new  # ou q_new.as_matrix() si tu veux une matrice

def project_point_on_sphere(point, old_radius, new_radius):
    """Projette un point situé sur une sphère de rayon old_radius sur une sphère de rayon new_radius"""
    point = np.array(point)
    norm = np.linalg.norm(point)
    
    if not np.isclose(norm, old_radius):
        raise ValueError(f"Le point ne semble pas être sur la sphère de rayon {old_radius}. Norme = {norm}")
    
    scale = new_radius / old_radius
    new_point = scale * point
    return tuple(new_point)

def point_apres_rotation_et_deplacement(point_repere_imu, matrice_rota_imu_terre, point_repere_terre):
    """calcule la position d un point apres une rotation et une translation"""
    return matrice_rota_imu_terre@point_repere_imu + point_repere_terre

def init_kf(dt):
    """initialise les matrices du filtre de kalman"""
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
    """met a jour les matrices de kalman"""
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

def predict(imu_path, gps_path):
    """effectue les predictions successives de la position grace aux donnees de l imu en utilisant un filtre de kalman"""
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
        kf.update(tab_predictions_pos[coord])

        tab_predictions_pos.append(kf.x[0:3])
        tab_predictions_vit.append(kf.x[3:6])
        tab_pos_reelles.append(coord)
    return tab_predictions_pos, tab_predictions_vit, tab_pos_reelles

def kalman_to_csv(output_path, pospred, vitpred, posreel):
    """change en csv les resultats du filtre de kalman"""
    pospred = np.array(pospred)
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
    df.to_csv(output_path)

def filtre_kalman(imu_path, gps_path, output_path):
    """lance le filtre"""
    pospred, vitpred, posreel = predict(imu_path, gps_path)
    kalman_to_csv(output_path, pospred, vitpred, posreel)