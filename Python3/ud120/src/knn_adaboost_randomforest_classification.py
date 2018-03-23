import matplotlib.pyplot as plt
from sklearn import ensemble
from sklearn import neighbors

from classification_visualization import prettyPicture
from prepare_terrain_data import makeTerrainData
features_train, labels_train, features_test, labels_test = makeTerrainData()

# the training data (features_train, labels_train) have both "fast" and "slow"
# points mixed together--separate them so we can give them different colors
# in the scatterplot and identify them visually
grade_fast = [features_train[ii][0] for ii in range(0, len(features_train)) if labels_train[ii] == 0]
bumpy_fast = [features_train[ii][1] for ii in range(0, len(features_train)) if labels_train[ii] == 0]
grade_slow = [features_train[ii][0] for ii in range(0, len(features_train)) if labels_train[ii] == 1]
bumpy_slow = [features_train[ii][1] for ii in range(0, len(features_train)) if labels_train[ii] == 1]

# initial visualization
plt.xlim(0.0, 1.0)
plt.ylim(0.0, 1.0)
plt.scatter(bumpy_fast, grade_fast, color="b", label="fast")
plt.scatter(grade_slow, bumpy_slow, color="r", label="slow")
plt.legend()
plt.xlabel("bumpiness")
plt.ylabel("grade")
plt.show()

# knn
clf = neighbors.KNeighborsClassifier()
clf.fit(features_train, labels_train)

# AdaBoost
clf = ensemble.AdaBoostClassifier()
clf.fit(features_train, labels_train)

# Random Forest
clf = ensemble.RandomForestClassifier()
clf.fit(features_train, labels_train)

# visualization code (prettyPicture) to show you the decision boundary
try:
    prettyPicture(clf, features_test, labels_test)
except NameError:
    pass
