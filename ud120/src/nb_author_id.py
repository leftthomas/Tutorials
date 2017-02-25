"""
    This is the code to accompany the Lesson 1 (Naive Bayes) mini-project.
    Use a Naive Bayes Classifier to identify emails by their authors
    authors and labels:
    Sara has label 0
    Chris has label 1
"""
from sklearn.naive_bayes import GaussianNB

from email_preprocess import preprocess

# features_train and features_test are the features for the training
# and testing datasets, respectively
# labels_train and labels_test are the corresponding item labels
features_train, features_test, labels_train, labels_test = preprocess()


def nb_accuracy(features_train, labels_train, features_test, labels_test):
    clf = GaussianNB()
    clf.fit(features_train, labels_train)
    accuracy = clf.score(features_test, labels_test)
    return accuracy


print(nb_accuracy(features_train, labels_train, features_test, labels_test))
