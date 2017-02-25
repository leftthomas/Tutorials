import numpy as np
import pandas as pd
# Subway ridership for 5 stations on 10 different days
ridership = np.array([
    [0, 0, 2, 5, 0],
    [1478, 3877, 3674, 2328, 2539],
    [1613, 4088, 3991, 6461, 2691],
    [1560, 3392, 3826, 4787, 2613],
    [1608, 4802, 3932, 4477, 2705],
    [1576, 3933, 3909, 4979, 2685],
    [95, 229, 255, 496, 201],
    [2, 0, 1, 27, 0],
    [1438, 3785, 3589, 4174, 2215],
    [1342, 4043, 4009, 4665, 3033]
])


def mean_riders_for_max_station(ridership):
    overall_mean = ridership.mean()
    mean_for_max = ridership[:, ridership[0, :].argmax()].mean()

    return (overall_mean, mean_for_max)


# print(mean_riders_for_max_station(ridership))


def min_and_max_riders_per_day(ridership):

    max_daily_ridership = ridership.mean(axis=0).max()
    min_daily_ridership = ridership.mean(axis=0).min()

    return (max_daily_ridership, min_daily_ridership)


# print(min_and_max_riders_per_day(ridership))


filename = '/Users/left/workspace/python/learn/ud170/resources/nyc_subway/nyc-subway-weather.csv'
subway_df = pd.read_csv(filename)


def correlation(x, y):
    std_x = (x - x.mean()) / x.std(ddof=0)
    std_y = (y - y.mean()) / y.std(ddof=0)
    return (std_x * std_y).mean()


entries = subway_df['ENTRIESn_hourly']
cum_entries = subway_df['ENTRIESn']
rain = subway_df['meanprecipi']
temp = subway_df['meantempi']

# print(correlation(entries, rain))
# print(correlation(entries, temp))
# print(correlation(rain, temp))
# print(correlation(entries, cum_entries))

entries_and_exits = pd.DataFrame({
    'ENTRIESn': [3144312, 3144335, 3144353, 3144424, 3144594,
                 3144808, 3144895, 3144905, 3144941, 3145094],
    'EXITSn': [1088151, 1088159, 1088177, 1088231, 1088275,
               1088317, 1088328, 1088331, 1088420, 1088753]
})


def get_hourly_entries_and_exits(entries_and_exits):
    return entries_and_exits - entries_and_exits.shift(1)


print(get_hourly_entries_and_exits(entries_and_exits))
