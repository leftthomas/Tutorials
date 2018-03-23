"""
    Starter code for the evaluation mini-project.
    Start by copying your trained/tested POI identifier from
    that which you built in the validation mini-project.

    This is the second step toward building your POI identifier!

    Start by loading/formatting the data...
"""

import pickle

from  sklearn.metrics import recall_score, precision_score
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier

from enron.feature_format import featureFormat, targetFeatureSplit

data_dict = pickle.load(open("../../resources/enron/enron_dataset.pkl", "rb"))

# add more features to features_list!
features_list = ["poi", "salary"]

data = featureFormat(data_dict, features_list)
labels, features = targetFeatureSplit(data)

data = featureFormat(data_dict, features_list, sort_keys='../../resources/enron/python2_lesson13_keys.pkl')
labels, features = targetFeatureSplit(data)

X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.3, random_state=42)

dtc = DecisionTreeClassifier()
dtc.fit(X_train, y_train)
# print(dtc.score(X_test,y_test))
pred = dtc.predict(X_test)
num = 0
i = 0
print(len(y_test))
print(pred)
print(y_test)
while i < len(y_test):
    if y_test[i] == 1 and pred[i] == 1:
        num += 1
    i += 1

print(num)

print(recall_score(y_test, pred))
print(precision_score(y_test, pred))
