"""
    This is the code to accompany the Lesson 2 (SVM) mini-project.
    Use a SVM to identify emails from the Enron corpus by their authors:    
    Sara has label 0
    Chris has label 1
"""
import time

from sklearn import svm
from sklearn.metrics import accuracy_score

from email_preprocess import preprocess

# features_train and features_test are the features for the training
# and testing datasets, respectively
# labels_train and labels_test are the corresponding item labels
features_train, features_test, labels_train, labels_test = preprocess()

# features_train = features_train[:int(len(features_train)/100)]
# labels_train = labels_train[:int(len(labels_train)/100)]

# clf = svm.LinearSVC()
clf = svm.SVC(10000, 'rbf')
t0 = time.time()
clf.fit(features_train, labels_train)
print("training time:", round(time.time() - t0, 3), "s")

t0 = time.time()
pred = clf.predict(features_test)
print("predict time:", round(time.time() - t0, 3), "s")
print(accuracy_score(labels_test, pred))
# print(pred[10])
# print(pred[26])
# print(pred[50])
print("Chris number:", list(pred).count(1))
