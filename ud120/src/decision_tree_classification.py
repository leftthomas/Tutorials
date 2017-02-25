"""
    This is the code to accompany the Lesson 3 (decision tree) mini-project.
    Use a Decision Tree to identify emails from the Enron corpus by author:    
    Sara has label 0
    Chris has label 1
"""

from sklearn import tree
from sklearn.metrics import accuracy_score

from email_preprocess import preprocess

# features_train and features_test are the features for the training
# and testing datasets, respectively
# labels_train and labels_test are the corresponding item labels
features_train, features_test, labels_train, labels_test = preprocess()
# clf=tree.DecisionTreeClassifier(min_samples_split=2)
# clf.fit(features_train,labels_train)
# pred=clf.predict(features_test)
# print(accuracy_score(labels_test,pred))
#
# clf=tree.DecisionTreeClassifier(min_samples_split=50)
# clf.fit(features_train,labels_train)
# pred=clf.predict(features_test)
# print(accuracy_score(labels_test,pred))

# print(len(features_train[0]))
clf = tree.DecisionTreeClassifier(min_samples_split=40)
clf.fit(features_train, labels_train)
pred = clf.predict(features_test)
print(accuracy_score(labels_test, pred))
