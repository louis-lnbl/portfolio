import math

def convert(lat, long):
    r = 6370
    theta = (90 - lat) * math.pi / 180
    phi = long * math.pi / 180
    x = r * math.sin(theta) * math.cos(phi)
    y = r * math.sin(theta) * math.sin(phi)
    z = r * math.cos(theta)
    return [x, y, z]

def convert_xyz_to_latlon(x, y, z):
    r = math.sqrt(x**2 + y**2 + z**2)
    lat = 90 - math.degrees(math.acos(z / r))
    lon = math.degrees(math.atan2(y, x))
    return [lat, lon]
