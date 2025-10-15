import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def plot_vec3(ax, x, y, z):
    l = 1
    ax.quiver(0, 0, 0, x * l, y * l, z * l, color='r', arrow_length_ratio=0.1)

data = pd.read_csv("capt/data/gyroscope/imu_2_12,5_2_12,5_4_0,625.csv")
gyro = data[["Gyro X", "Gyro Y", "Gyro Z"]]

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

for x, y, z in gyro.values:
    plot_vec3(ax, x, y, z)

plt.title("Vecteur Gyroscopes")
plt.show()
