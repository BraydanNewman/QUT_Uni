import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import pyplot as plt


def read_data(name):
    df = pd.read_csv(name)
    df["Time"] = pd.to_datetime(df["Time"], errors="coerce")
    df["Flow"] = pd.to_numeric(df["Flow"], errors="coerce")
    df["EnterTemp"] = pd.to_numeric(df["EnterTemp"], errors="coerce")
    df["LeaveTemp"] = pd.to_numeric(df["LeaveTemp"], errors="coerce")
    df["kWE"] = pd.to_numeric(df["kWE"], errors="coerce")
    df.dropna(inplace=True, axis=0, how="any")
    return df


def create_kwr(df):
    df["kWR"] = df["EnterTemp"] - df["LeaveTemp"]


def create_cop(df):
    df["COP"] = df["kWR"] / df["kWE"]


def kwr_time_plot(df):
    times = pd.to_datetime(df.Time)
    kwr_hours = df.groupby([times.dt.hour])
    mean_kwr = kwr_hours.kWR.mean()
    error_kwr = abs(kwr_hours.kWR.max())

    # plt.figure()
    # plt.errorbar(
    #     data=mean_kwr,
    #     yerr=error_kwr[1],
    #     capsize=4,
    #     marker='s',
    #     color='red',
    #     markersize=4,
    #     linewidth=1,
    #     linestyle='--')

    # print(mean_kwr.status())

    plt.plot(mean_kwr)

    plt.title('kWR Vs Hour Of Day')
    plt.xlabel('Hour')
    plt.ylabel('kWR')
    plt.show()




def operating_time(df):
    pass


def main():
    csv_file_name = "Chiller1Raw.csv"
    df = read_data(csv_file_name)
    create_kwr(df)
    create_cop(df)
    kwr_time_plot(df)

    # print(df.head())
    # print(df.info())


if __name__ == "__main__":
    main()
