import os
import pickle

import numpy as np
from sklearn.linear_model import LogisticRegression

from notmnist.extract_pickle_data import maybe_extract
from notmnist.extract_pickle_data import maybe_pickle

# Problem 3
# Another check: we expect the data to be balanced across classes. Verify that.
# Merge and prune the training data as needed. Depending on your computer setup,
# you might not be able to fit it all in memory, and you can tune train_size as needed.
# The labels will be stored into a separate array of integers 0 through 9.
# Also create a validation dataset for hyperparameter tuning.
image_size = 28  # Pixel width and height.


def make_arrays(nb_rows, img_size):
    if nb_rows:
        dataset = np.ndarray((nb_rows, img_size, img_size), dtype=np.float32)
        labels = np.ndarray(nb_rows, dtype=np.int32)
    else:
        dataset, labels = None, None
    return dataset, labels


def merge_datasets(pickle_files, train_size, valid_size=0):
    num_classes = len(pickle_files)
    valid_dataset, valid_labels = make_arrays(valid_size, image_size)
    train_dataset, train_labels = make_arrays(train_size, image_size)
    vsize_per_class = valid_size // num_classes
    tsize_per_class = train_size // num_classes

    start_v, start_t = 0, 0
    end_v, end_t = vsize_per_class, tsize_per_class
    end_l = vsize_per_class + tsize_per_class
    for label, pickle_file in enumerate(pickle_files):
        try:
            with open(pickle_file, 'rb') as f:
                letter_set = pickle.load(f)
                # let's shuffle the letters to have random validation and training set
                np.random.shuffle(letter_set)
                if valid_dataset is not None:
                    valid_letter = letter_set[:vsize_per_class, :, :]
                    valid_dataset[start_v:end_v, :, :] = valid_letter
                    valid_labels[start_v:end_v] = label
                    start_v += vsize_per_class
                    end_v += vsize_per_class

                train_letter = letter_set[vsize_per_class:end_l, :, :]
                train_dataset[start_t:end_t, :, :] = train_letter
                train_labels[start_t:end_t] = label
                start_t += tsize_per_class
                end_t += tsize_per_class
        except Exception as e:
            print('Unable to process data from', pickle_file, ':', e)
            raise

    return valid_dataset, valid_labels, train_dataset, train_labels


train_size = 200000
valid_size = 10000
test_size = 10000
data_root = '../../../../'
train_folders = maybe_extract(os.path.join(data_root, 'notMNIST_large.tar.gz'))
test_folders = maybe_extract(os.path.join(data_root, 'notMNIST_small.tar.gz'))
train_datasets = maybe_pickle(train_folders, 45000)
test_datasets = maybe_pickle(test_folders, 1800)

valid_dataset, valid_labels, train_dataset, train_labels = merge_datasets(
    train_datasets, train_size, valid_size)
_, _, test_dataset, test_labels = merge_datasets(test_datasets, test_size)

print('Training:', train_dataset.shape, train_labels.shape)
print('Validation:', valid_dataset.shape, valid_labels.shape)
print('Testing:', test_dataset.shape, test_labels.shape)


# Next, we'll randomize the data. It's important to have the labels well shuffled
# for the training and test distributions to match.
def randomize(dataset, labels):
    permutation = np.random.permutation(labels.shape[0])
    shuffled_dataset = dataset[permutation, :, :]
    shuffled_labels = labels[permutation]
    return shuffled_dataset, shuffled_labels


train_dataset, train_labels = randomize(train_dataset, train_labels)
test_dataset, test_labels = randomize(test_dataset, test_labels)
valid_dataset, valid_labels = randomize(valid_dataset, valid_labels)

# Problem 4
# Convince yourself that the data is still good after shuffling!
# Finally, let's save the data for later reuse:
pickle_file = os.path.join(data_root, 'notMNIST.pickle')

try:
    f = open(pickle_file, 'wb')
    save = {
        'train_dataset': train_dataset,
        'train_labels': train_labels,
        'valid_dataset': valid_dataset,
        'valid_labels': valid_labels,
        'test_dataset': test_dataset,
        'test_labels': test_labels,
    }
    pickle.dump(save, f, pickle.HIGHEST_PROTOCOL)
    f.close()
except Exception as e:
    print('Unable to save data to', pickle_file, ':', e)
    raise

statinfo = os.stat(pickle_file)
print('Compressed pickle size:', statinfo.st_size)

# Problem 5
# By construction, this dataset might contain a lot of overlapping samples,
# including training data that's also contained in the validation and test set!
# Overlap between training and test can skew the results if you expect to use your
# model in an environment where there is never an overlap, but are actually ok if
# you expect to see training samples recur when you use it. Measure how much overlap
# there is between training, validation and test samples.
# Optional questions:
# What about near duplicates between datasets? (images that are almost identical)
# Create a sanitized validation and test set, and compare your accuracy on those
# in subsequent assignments.
print('the number of overlap between training and validation:',
      len([val for val in train_dataset if val in valid_dataset]))
print('the number of overlap between training and test:', len([val for val in train_dataset if val in test_dataset]))
print('the number of overlap between validation and test:', len([val for val in valid_dataset if val in test_dataset]))


# Problem 6
# Let's get an idea of what an off-the-shelf classifier can give you on this data.
# It's always good to check that there is something to learn, and that it's a problem
# that is not so trivial that a canned solution solves it.
# Train a simple model on this data using 50, 100, 1000 and 5000 training samples.
# Hint: you can use the LogisticRegression model from sklearn.linear_model.
# Optional question: train an off-the-shelf model on all the data!
lrc = LogisticRegression()
lrc.fit(train_dataset.reshape(len(train_dataset), image_size * image_size)[0:5000, ], train_labels[0:5000])
print(lrc.score(test_dataset.reshape(len(test_dataset), image_size * image_size), test_labels))
