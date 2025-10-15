import numpy as np
import pandas as pd
import os

class GyroData:

    def __init__(self, path):
        self.params = os.path.basename(path)[4:].replace(".csv", "").split("_")
        map(lambda x : float(x), self.params)
        self.data = pd.read_csv(path)
        self.gyro = self.data[["Gyro X", "Gyro Y", "Gyro Z"]]
        self.mean = self.gyro.mean()

    def print_params(self):
        print("ACCEL_RANGE   :", self.params[0])
        print("ACCEL_FREQ    :", self.params[1])
        print("GYRO_RANGE    :", self.params[2])
        print("GYRO_FREQ     :", self.params[3])
        print("MAGNETO_RANGE :", self.params[4])
        print("MAGNETO_FREQ  :", self.params[5])

    @classmethod
    def calculate_best_calibration(cls, gyro_datas):
        means = [abs(gyro_data.mean.mean()) for gyro_data in gyro_datas]
        min_index = means.index(min(means))
        return gyro_datas[min_index]


if __name__ == "__main__":
    path = "../capt/data/gyroscope"
    gyro_datas = [GyroData(os.path.join(path, data_path)) for data_path in os.listdir("../capt/data/gyroscope")]
    x_means = []
    y_means = []
    z_means = []

    for gyro in gyro_datas:
        print(gyro.mean)
        gyro.print_params()
        x_means.append(gyro.mean["Gyro X"])
        y_means.append(gyro.mean["Gyro Y"])
        z_means.append(gyro.mean["Gyro Z"])
        print("-------------------")
    
    print("X mean : ", np.array(x_means).mean())
    print("Y mean : ", np.array(y_means).mean())
    print("Z mean : ", np.array(z_means).mean())
    
    GyroData.calculate_best_calibration(gyro_datas).print_params()