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


def predict(mean1, var1, mean2, var2):
    new_mean = mean1 + mean2
    new_var = var1 + var2
    return [new_mean, new_var]


print(predict(10, 4, 12, 4))

# Write a program that will iteratively update and
# predict based on the location measurements
# and inferred motions shown below.
measurements = [5., 6., 7., 9., 10.]
motion = [1., 1., 2., 1., 1.]
measurement_sig = 4.
motion_sig = 2.
mu = 0.
sig = 10000.
# Please print out ONLY the final values of the mean
# and the variance in a list [mu, sig].

for i in range(len(measurements)):
    [mu, sig] = update(measurements[i], measurement_sig, mu, sig)
    [mu, sig] = predict(mu, sig, motion[i], motion_sig)
print([mu, sig])
