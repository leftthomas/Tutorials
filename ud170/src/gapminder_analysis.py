import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# First 20 countries with employment data
countries = np.array([
    'Afghanistan', 'Albania', 'Algeria', 'Angola', 'Argentina',
    'Armenia', 'Australia', 'Austria', 'Azerbaijan', 'Bahamas',
    'Bahrain', 'Bangladesh', 'Barbados', 'Belarus', 'Belgium',
    'Belize', 'Benin', 'Bhutan', 'Bolivia',
    'Bosnia and Herzegovina'
])

countries = [
    'Afghanistan', 'Albania', 'Algeria', 'Angola', 'Argentina',
    'Armenia', 'Australia', 'Austria', 'Azerbaijan', 'Bahamas',
    'Bahrain', 'Bangladesh', 'Barbados', 'Belarus', 'Belgium',
    'Belize', 'Benin', 'Bhutan', 'Bolivia',
    'Bosnia and Herzegovina'
]

# Employment data in 2007 for those 20 countries
employment = np.array([
    55.70000076, 51.40000153, 50.5, 75.69999695,
    58.40000153, 40.09999847, 61.5, 57.09999847,
    60.90000153, 66.59999847, 60.40000153, 68.09999847,
    66.90000153, 53.40000153, 48.59999847, 56.79999924,
    71.59999847, 58.40000153, 70.40000153, 41.20000076
])

employment_values = [
    55.70000076, 51.40000153, 50.5, 75.69999695,
    58.40000153, 40.09999847, 61.5, 57.09999847,
    60.90000153, 66.59999847, 60.40000153, 68.09999847,
    66.90000153, 53.40000153, 48.59999847, 56.79999924,
    71.59999847, 58.40000153, 70.40000153, 41.20000076
]

# Female school completion rate in 2007 for those 20 countries
female_completion = np.array([
    97.35583, 104.62379, 103.02998, 95.14321, 103.69019,
    98.49185, 100.88828, 95.43974, 92.11484, 91.54804,
    95.98029, 98.22902, 96.12179, 119.28105, 97.84627,
    29.07386, 38.41644, 90.70509, 51.7478, 95.45072
])

# Male school completion rate in 2007 for those 20 countries
male_completion = np.array([
    95.47622, 100.66476, 99.7926, 91.48936, 103.22096,
    97.80458, 103.81398, 88.11736, 93.55611, 87.76347,
    102.45714, 98.73953, 92.22388, 115.3892, 98.70502,
    37.00692, 45.39401, 91.22084, 62.42028, 90.66958
])


def max_employment(countries, employment):
    i = employment.argmax()
    return (countries[i], employment[i])


# print(max_employment(countries,employment))


def overall_completion_rate(female_completion, male_completion):
    return (female_completion + male_completion) / 2


# print(overall_completion_rate(female_completion, male_completion))

def standardize_data(values):
    return (values - values.mean()) / values.std()


# print(standardize_data(employment))


def mean_time_for_paid_students(time_spent, days_to_cancel):
    return time_spent[days_to_cancel >= 7].mean()


# Time spent in the classroom in the first week for 20 students
time_spent = np.array([
    12.89697233, 0., 64.55043217, 0.,
    24.2315615, 39.991625, 0., 0.,
    147.20683783, 0., 0., 0.,
    45.18261617, 157.60454283, 133.2434615, 52.85000767,
    0., 54.9204785, 26.78142417, 0.
])

# Days to cancel for 20 students
days_to_cancel = np.array([
    4, 5, 37, 3, 12, 4, 35, 38, 5, 37, 3, 3, 68,
    38, 98, 2, 249, 2, 127, 35
])

# print(mean_time_for_paid_students(time_spent, days_to_cancel))

# Employment data in 2007 for 20 countries
employment = pd.Series(employment_values, index=countries)


def max_employment(employment):
    max_country = employment.argmax()
    max_value = employment[max_country]
    return (max_country, max_value)

# print(max_employment(employment))


path = '/Users/left/workspace/python/learn/ud170/resources/gapminder/'
employment = pd.read_csv(path + 'employment_above_15.csv', index_col='Country')
female_completion = pd.read_csv(path + 'female_completion_rate.csv', index_col='Country')
male_completion = pd.read_csv(path + 'male_completion_rate.csv', index_col='Country')
life_expectancy = pd.read_csv(path + 'life_expectancy.csv', index_col='Country')
gdp = pd.read_csv(path + 'gdp_per_capita.csv', index_col='Country')

# The following code creates a Pandas Series for each variable for the United States.
# You can change the string 'United States' to a country of your choice.

employment_us = employment.loc['United States']
female_completion_us = female_completion.loc['United States']
male_completion_us = male_completion.loc['United States']
life_expectancy_us = life_expectancy.loc['United States']
gdp_us = gdp.loc['United States']

# Uncomment the following line of code to see the available country names
# print(employment.index.values)
# plt.hist(employment_us)
employment_us.plot()
plt.show()
