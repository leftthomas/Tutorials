"""
    Skeleton code for k-means clustering mini-project.
"""

import pickle

import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.preprocessing import minmax_scale

from enron.feature_format import featureFormat, targetFeatureSplit


def Draw(pred, features, poi, mark_poi=False, name="image.png", f1_name="feature 1", f2_name="feature 2"):
    """ some plotting code designed to help you visualize your clusters """

    # plot each cluster with a different color--add more colors for
    # drawing more than five clusters
    colors = ["b", "c", "k", "m", "g"]
    for ii, pp in enumerate(pred):
        plt.scatter(features[ii][0], features[ii][1], color=colors[pred[ii]])

    # if you like, place red stars over points that are POIs (just for funsies)
    if mark_poi:
        for ii, pp in enumerate(pred):
            if poi[ii]:
                plt.scatter(features[ii][0], features[ii][1], color="r", marker="*")
    plt.xlabel(f1_name)
    plt.ylabel(f2_name)
    plt.savefig(name)
    plt.show()


# load in the dict of dicts containing all the data on each person in the dataset
data_dict = pickle.load(open("../../resources/enron/enron_dataset.pkl", "rb"))
# there's an outlier--remove it!
data_dict.pop("TOTAL", 0)

stock_max = -float("inf")
stock_min = float("inf")
for value in data_dict.values():
    if value['exercised_stock_options'] != 'NaN':
        if stock_max < value['exercised_stock_options']:
            stock_max = value['exercised_stock_options']
        if stock_min > value['exercised_stock_options']:
            stock_min = value['exercised_stock_options']
print('stock_max:', stock_max, ';stock_min', stock_min)

salary_max = -float("inf")
salary_min = float("inf")
for value in data_dict.values():
    if value['salary'] != 'NaN':
        if salary_max < value['salary']:
            salary_max = value['salary']
        if salary_min > value['salary']:
            salary_min = value['salary']
print('salary_max:', salary_max, ';salary_min', salary_min)

# the input features we want to use
# can be any key in the person-level dictionary (salary, director_fees, etc.)
feature_1 = "salary"
feature_2 = "exercised_stock_options"
feature_3 = 'total_payments'
poi = "poi"
features_list = [poi, feature_1, feature_2, feature_3]
data = featureFormat(data_dict, features_list)
data[:, 1] = minmax_scale(data[:, 1])
data[:, 2] = minmax_scale(data[:, 2])
print('salary_scale:', 200000 / salary_max)
print('exercised_stock_options_scale:', 100 / stock_min)

poi, finance_features = targetFeatureSplit(data)

# in the "clustering with 3 features" part of the mini-project,
# you'll want to change this line to
# for f1, f2, _ in finance_features:
# (as it's currently written, the line below assumes 2 features)
for f1, f2, f3 in finance_features:
    plt.scatter(f1, f2)
plt.show()

# cluster here; create predictions of the cluster labels
# for the data and store them to a list called pred

pred = KMeans(3).fit_predict(finance_features)

# rename the "name" parameter when you change the number of features
# so that the figure gets saved to a different file
try:
    Draw(pred, finance_features, poi, mark_poi=False, name="clusters.pdf", f1_name=feature_1, f2_name=feature_2)
except NameError:
    print("no predictions object named pred found, no clusters to plot")
