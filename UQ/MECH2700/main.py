import numpy as np
import matplotlib.pyplot as plt


def main():
    # Altitude (m), Temperature (Celsius), Density (kg.m−3)
    atmosphere_data = np.array([
        [-1000, 21.5, 1.347],
        [0, 15.0, 1.225],
        [1000, 8.5, 1.112],
        [2000, 2.0, 1.007],
        [3000, -4.5, 0.9093],
        [4000, -11.0, 0.8194],
        [5000, -17.5, 0.7364],
        [6000, -24.0, 0.6601],
        [7000, -30.5, 0.5900],
        [8000, -36.9, 0.5258],
        [9000, -43.4, 0.4671],
        [10000, -49.9, 0.4135],
        [15000, -56.5, 0.1948],
        [20000, -56.5, 0.08891],
        [25000, -51.6, 0.04008],
        [30000, -46.6, 0.01841],
        [40000, -22.8, 0.003996],
        [50000, -2.5, 0.001027],
        [60000, -26.1, 0.0003097],
        [70000, -53.6, 0.00008283],
        [80000, -74.5, 0.00001846],
    ])
    task1(atmosphere_data)


def drag_force(air_density, skydiver_speed):
    dimensionless_drag = 0.92
    effective_area = 0.5
    drag = (air_density*pow(skydiver_speed, 2)*dimensionless_drag*effective_area)/2
    return drag


def task1(atmosphere_data):
    reduced_range = np.array([item for item in atmosphere_data if 0 <= item[0] <= 5000])
    x = list(range(5000))
    xp = reduced_range[:, 0]
    fp = reduced_range[:, 2]
    interpolated_value = np.interp(x, xp, fp)

    plt.plot(interpolated_value, x, marker="o")  # Interpolated Value
    # plt.plot(atmosphere_data[:, 2], atmosphere_data[:, 0], marker="o")  # Full Data Set
    plt.plot(reduced_range[:, 2], reduced_range[:, 0], marker="o")  # Reduced Data Set
    plt.show()


if __name__ == "__main__":
    main()
