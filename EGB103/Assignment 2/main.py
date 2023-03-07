import pandas as pd
from matplotlib import pyplot as plt
import matplotlib.dates as md

def read_data(name):
    df = pd.read_csv(name, low_memory=False)
    df["Time"] = pd.to_datetime(df["Time"], errors="coerce")
    df["Flow"] = pd.to_numeric(df["Flow"], errors="coerce")
    df["EnterTemp"] = pd.to_numeric(df["EnterTemp"], errors="coerce")
    df["LeaveTemp"] = pd.to_numeric(df["LeaveTemp"], errors="coerce")
    df["kWE"] = pd.to_numeric(df["kWE"], errors="coerce")
    df.dropna(inplace=True, axis=0, how="any")
    df['Day'] = df.Time.dt.day_name()
    return df


def create_kwr(df):
    df["kWR"] = df["EnterTemp"] - df["LeaveTemp"]


def create_cop(df):
    df["COP"] = df["kWR"] / df["kWE"]


def time(df, intervals):
    times = pd.to_datetime(df.Time)
    if intervals == "hour":
        grouped_data = df.groupby([times.dt.hour])
        time_period = "of Day"
    elif intervals == "day":
        grouped_data = df.groupby(['Day'])
        time_period = "of Week"
    elif intervals == "month":
        grouped_data = df.groupby([times.dt.month])
        time_period = "of Year"
    else:
        return
    return grouped_data, time_period


def plot(df, intervals, column):
    grouped_data, time_period = time(df, intervals)
    column_data = grouped_data[column]
    mean = column_data.mean()
    error = column_data.std()

    plt.errorbar(x=mean.index,
                 y=mean,
                 yerr=error,
                 ecolor="lightgreen",
                 color='orange',
                 elinewidth=5,
                 capsize=5)
    plt.title(f'{column} vs {intervals.capitalize()} {time_period}')
    plt.ylabel(column)
    plt.xlabel(intervals.capitalize())


def percent_operating_plot(df, intervals):
    df.loc[(df.kWE > 0), 'kWE'] = 1
    grouped_data, time_period = time(df, intervals)
    on_time = grouped_data["kWE"].sum()
    total_time = grouped_data["kWE"].size()
    percentage = 100 - ((on_time / total_time)*100)
    plt.plot(percentage, color='orange')
    plt.title(f'%Operating vs {intervals.capitalize()} {time_period}')
    plt.ylabel("%")
    plt.xlabel(intervals.capitalize())


def birth_date_plot(df, birth_date, column):
    date = df[df.Time.dt.date == pd.to_datetime(birth_date).date()]
    plt.plot(date.Time,
             date[column],
             color='orange')
    plt.title(f'{column} vs Minute During {birth_date}')
    plt.ylabel(column)
    plt.xlabel("Minutes")


def main():
    time_intervals = ['hour', 'day', 'month']
    column_plot = ['kWE', 'kWR', 'COP']
    birth_date = '2021-11-05'
    csv_file_name = "Chiller1Raw.csv"
    df = read_data(csv_file_name)
    for interval in time_intervals:
        percent_operating_plot(df, interval)
        plt.show()

    df = read_data(csv_file_name)
    create_kwr(df)
    create_cop(df)
    df = df[df.kWE > 0]
    for interval in time_intervals:
        for column in column_plot:
            plot(df, interval, column)
            plt.show()

    df = read_data(csv_file_name)
    create_kwr(df)
    create_cop(df)
    df = df[df.kWE > 0]
    for column in column_plot:
        birth_date_plot(df, birth_date, column)
        plt.show()


if __name__ == "__main__":
    main()
