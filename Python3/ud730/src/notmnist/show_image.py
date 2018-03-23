import os
import pickle

import matplotlib.pyplot as plt
import numpy as np
from PIL import Image

from notmnist.extract_pickle_data import maybe_extract
from notmnist.extract_pickle_data import maybe_pickle

# Problem 1
# Let's take a peek at some of the data to make sure it looks sensible.
# Each exemplar should be an image of a character A through J rendered in a different font.
# Display a sample of the images that we just downloaded.
# Hint: you can use the package PIL.
t = Image.open("../../../../notMNIST_small/A/Q0NXaWxkV29yZHMtQm9sZEl0YWxpYy50dGY=.png")
t.show()

# Problem 2
# Let's verify that the data still looks good.
#  Displaying a sample of the labels and images from the ndarray.
# Hint: you can use matplotlib.pyplot.
data_root = '../../../../'
train_folders = maybe_extract(os.path.join(data_root, 'notMNIST_large.tar.gz'))
test_folders = maybe_extract(os.path.join(data_root, 'notMNIST_small.tar.gz'))
train_datasets = maybe_pickle(train_folders, 45000)
test_datasets = maybe_pickle(test_folders, 1800)
pickle_file = train_datasets[0]  # index 0 should be all As, 1 = all Bs, etc.

with open(pickle_file, 'rb') as f:
    letter_set = pickle.load(f)  # unpickle
    sample_idx = np.random.randint(len(letter_set))  # pick a random image index
    sample_image = letter_set[sample_idx, :, :]  # extract a 2D slice
    plt.figure()
    plt.imshow(sample_image)  # display it
    # plt.imshow(sample_image,cmap=plt.cm.gray )
    plt.show()


