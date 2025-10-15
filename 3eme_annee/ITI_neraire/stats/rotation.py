import numpy as np
import math




# u = np.array([0.2075416544869921,-0.24057293189125986,-0.06328558900906167])
# v = np.array([-0.983076,0.262727,-0.023546])

def normalize(a):
    return a /np.linalg.norm(a)

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

u = np.array([0.20140309850920785,-0.03390821397252265,0.19073370359543992])
v = np.array([-0.9761219999999999,-0.053436,-0.290665])

lat = 49.38424486666667
long = 1.06876165

proju = (np.dot(u, v) / np.linalg.norm(v)**2) * v
up = u - proju
unorme = np.linalg.norm(u) * (up / np.linalg.norm(up))
troisiemeaxe = np.cross(unorme, v)

lat = np.radians(lat)
lon = np.radians(long)

matrice_rotation = np.array([
        [-np.sin(lat)*np.cos(lon), -np.sin(lon), -np.cos(lat)*np.cos(lon)],
        [-np.sin(lat)*np.sin(lon),  np.cos(lon), -np.cos(lat)*np.sin(lon)],
        [ np.cos(lat),              0,           -np.sin(lat)]
    ])

unorme = normalize(unorme)
troisiemeaxe = normalize(troisiemeaxe)
v = normalize(v)
u = normalize(u)
print("nord : ", u)
print("gravité : ", v)
print(unorme, troisiemeaxe, v)
matrice_repere = np.array([unorme, troisiemeaxe, v])

nouveau_repere = matrice_rotation@matrice_repere

print("la")
print(matrice_rotation@np.array([-0.98, -0.053, -0.29]))

print("nouveau repère : ")
for i in range(3):
    print(tuple(nouveau_repere[:,i]))

rouen = [4146.040147659082, 77.34675668968164, 4835.4181384062995]
rouen_sur_sphere_1 = project_point_on_sphere(rouen, 6370, 1)
print("rouen normalise : ",rouen_sur_sphere_1)

accel_l_5 = [-0.9761219999999999,-0.053436,-0.290665]
accel_l_5_ecef = matrice_rotation@accel_l_5 + rouen_sur_sphere_1
print("gravite rotation et deplacée sur rouen : ", tuple(accel_l_5_ecef))



