from math import *


def f(mu, sigma2, x):
    return 1 / sqrt(2 * pi * sigma2) * exp(-0.5 * (x - mu) ** 2 / sigma2)


# Instead, please just change the last argument
# in f() to maximize the output.
print(f(10, 4, 10))


# Write a program to update your mean and variance
# when given the mean and variance of your belief
# and the mean and variance of your measurement.
# This program will update the parameters of your
# belief function.
def update(mean1, var1, mean2, var2):
    # 注意，算new_mean的时候是var1跟mean2、var2跟mean1相乘，别弄反了
    new_mean = 1 / (var1 + var2) * (var1 * mean2 + var2 * mean1)
    new_var = 1 / (1 / var1 + 1 / var2)
    return [new_mean, new_var]


print(update(10, 8, 13, 2))
