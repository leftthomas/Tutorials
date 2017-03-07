'''
Assignment 1

The objective of this assignment is to learn about simple data curation practices,
and familiarize you with some of the data we'll be reusing later.

This notebook uses the notMNIST dataset to be used with python experiments.
This dataset is designed to look like the classic MNIST dataset,
while looking a little more like real data: it's a harder task,
and the data is a lot less 'clean' than MNIST.
'''

# These are all the modules we'll be using later. Make sure you can import them
# before proceeding further.
import os
import sys
from urllib.request import urlretrieve

# First, we'll download the dataset to our local machine.
# The data consists of characters rendered in a variety of fonts on a 28x28 image.
# The labels are limited to 'A' through 'J' (10 classes).
# The training set has about 500k and the testset 19000 labelled examples.
# Given these sizes, it should be possible to train models quickly on any machine.
url = 'http://commondatastorage.googleapis.com/books1000/'
last_percent_reported = None
data_root = '../../../../'  # Change me to store data elsewhere


def download_progress_hook(count, blockSize, totalSize):
    """A hook to report the progress of a download. This is mostly intended for users with
    slow internet connections. Reports every 5% change in download progress.
    """
    global last_percent_reported
    percent = int(count * blockSize * 100 / totalSize)

    if last_percent_reported != percent:
        if percent % 5 == 0:
            sys.stdout.write("%s%%" % percent)
            sys.stdout.flush()
        else:
            sys.stdout.write(".")
            sys.stdout.flush()

        last_percent_reported = percent


def maybe_download(filename, expected_bytes, force=False):
    """Download a file if not present, and make sure it's the right size."""
    dest_filename = os.path.join(data_root, filename)
    if force or not os.path.exists(dest_filename):
        print('Attempting to download:', filename)
        filename, _ = urlretrieve(url + filename, dest_filename, reporthook=download_progress_hook)
        print('\nDownload Complete!')
    statinfo = os.stat(dest_filename)
    if statinfo.st_size == expected_bytes:
        print('Found and verified', dest_filename)
    else:
        raise Exception(
            'Failed to verify ' + dest_filename + '. Can you get to it with a browser?')
    return dest_filename


train_filename = maybe_download('notMNIST_large.tar.gz', 247336696)
test_filename = maybe_download('notMNIST_small.tar.gz', 8458043)