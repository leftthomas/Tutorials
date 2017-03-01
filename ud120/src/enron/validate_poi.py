"""
    Starter code for the validation mini-project.
    The first step toward building your POI identifier!

    Start by loading/formatting the data

    After that, it's not our code anymore--it's yours!
"""

import pickle

from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier

from enron.feature_format import featureFormat, targetFeatureSplit

data_dict = pickle.load(open("../../resources/enron/enron_dataset.pkl", "rb"))

# first element is our labels, any added elements are predictor
# features. Keep this the same for the mini-project, but you'll
# have a different feature list when you do the final project.
features_list = ["poi", "salary"]

data = featureFormat(data_dict, features_list, sort_keys='../../resources/enron/python2_lesson13_keys.pkl')
labels, features = targetFeatureSplit(data)

X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.3, random_state=42)

dtc = DecisionTreeClassifier()
dtc.fit(X_train, y_train)
print(dtc.score(X_test, y_test))
