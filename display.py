import csv
import numpy as np
import matplotlib.pyplot as plt

with open("data.txt")as fp:
    reader = csv.reader(fp, delimiter=";")

    time = []
    pos = []
    vel = []

    for row in reader:
        time.append(float(row[0]))
        pos.append(float(row[1]))
        vel.append(float(row[2]))

    time_np = np.array(time)
    pos_np = np.array(pos)
    vel_np = np.array(vel)

    plt.plot(time_np, pos_np)
    plt.plot(time_np, vel_np)
    plt.show()