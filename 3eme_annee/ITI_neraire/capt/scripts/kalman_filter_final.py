from filterpy.kalman import KalmanFilter
import numpy as np
from scipy.spatial.transform import Rotation as R
import pandas as pd
from convert_latlong_to_xyz import convert

__all__ = ["filtre_kalman"]

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

def init_kf(dt):
    kf = KalmanFilter(dim_x=6, dim_z=3, dim_u=3)
    kf.P = np.eye(6) * 0.5 #incertitude initiale
    kf.R = np.eye(3)        # bruit GPS
    kf.Q = np.eye(6) * 0.1  # bruit du modèle (process noise)
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

def predict(imu_path, gps_path):
    imu = pd.read_csv(imu_path)
    gps = pd.read_csv(gps_path)
    n, p = imu.shape
    dt = imu.iloc[1]['Timestamp'] - imu.iloc[0]['Timestamp']
    kf = init_kf(dt)

    lat_deg = gps.iloc[0]['Latitude']
    lon_deg = gps.iloc[0]['Longitude']
    accel = np.array([imu.iloc[0]['Accel X'], imu.iloc[0]['Accel Y'], imu.iloc[0]['Accel Z']])
    mag = np.array([imu.iloc[0]['Magneto X'], imu.iloc[0]['Magneto Y'], imu.iloc[0]['Magneto Z']])
    matrice_rota_imu_terre = R_body_to_earth(accel, mag, lat_deg, lon_deg)
    coord = np.array(convert(lat_deg, lon_deg))
    kf.x[0:3] = coord
    

    tab_predictions_pos = []
    tab_predictions_vit = []
    tab_pos_reelles = []
    for i in range(1, len(imu) - 1):
        lat_deg = gps.iloc[i]['Latitude']
        lon_deg = gps.iloc[i]['Longitude']
        accel = np.array([imu.iloc[i]['Accel X'], imu.iloc[i]['Accel Y'], imu.iloc[i]['Accel Z']])
        mag = np.array([imu.iloc[i]['Magneto X'], imu.iloc[i]['Magneto Y'], imu.iloc[i]['Magneto Z']])
        matrice_rota_imu_terre = R_body_to_earth(accel, mag, lat_deg, lon_deg)
        coord = np.array(convert(lat_deg, lon_deg))
        accel = point_apres_rotation_et_deplacement(accel, matrice_rota_imu_terre, coord) - np.array([0,0,9.81])

        kf.predict(u=accel)
        kf.update(coord)

        tab_predictions_pos.append(kf.x[0:3])
        tab_predictions_vit.append(kf.x[3:6])
        tab_pos_reelles.append(coord)

        dt = gps.iloc[i+1]['Timestamp'] - gps.iloc[i]['Timestamp']
        update_matrices_kf_dt(kf, dt)
    return tab_predictions_pos, tab_predictions_vit, tab_pos_reelles

def kalman_to_csv(output_path, pospred, vitpred, posreel):
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
	pospred, vitpred, posreel = predict(imu_path, gps_path)
	kalman_to_csv(output_path, pospred, vitpred, posreel)