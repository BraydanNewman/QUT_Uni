import pandas as pd
from matplotlib import *


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


def operating_time(df):
    pass


def main():
    csv_file_name = "Chiller1Raw.csv"
    df = read_data(csv_file_name)
    create_kwr(df)
    create_cop(df)

    print(df.head())
    print(df.info())


if __name__ == "__main__":
    main()
