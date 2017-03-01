import pickle

import matplotlib.pyplot as plt

from enron.feature_format import featureFormat

# read in data dictionary, convert to numpy array
data_dict = pickle.load(open("../../resources/enron/enron_dataset.pkl", "rb"))

data_dict.pop('TOTAL', 0)

features = ["salary", "bonus"]
data = featureFormat(data_dict, features)

for point in data:
    salary = point[0]
    bonus = point[1]
    plt.scatter(salary, bonus)

plt.xlabel("salary")
plt.ylabel("bonus")
plt.show()
