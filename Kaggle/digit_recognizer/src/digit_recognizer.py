import numpy as np
import pandas as pd
import torch
import torch.nn as nn
import torch.utils.data as data
from torch.autograd import Variable

# Hyper Parameters
input_size = 784
hidden_size = 500
num_classes = 10
num_epochs = 5
batch_size = 100
learning_rate = 0.001


class CustomDataset(data.Dataset):
    training_file = '../resources/train.csv'
    test_file = '../resources/test.csv'

    def __init__(self, train=True):
        self.train = train  # training set or test set

        if self.train:
            self.train_data = pd.read_csv(self.training_file)
            self.train_images = self.train_data.ix[:, 1:].values.astype('float32')
            self.train_labels = self.train_data.ix[:, 0].values.astype('int32')
        else:
            self.test_data = pd.read_csv(self.test_file).ix[:, 0:].values.astype('float32')

    def __getitem__(self, index):
        if self.train:
            img, target = torch.from_numpy(self.train_images)[index], torch.from_numpy(self.train_labels)[index]
        else:
            img, target = torch.from_numpy(self.test_data)[index], 0  # test集没有标签，默认初始化为0
        return img, target

    def __len__(self):
        if self.train:
            return len(self.train_data)
        else:
            return len(self.test_data)


train_dataset = CustomDataset()
test_dataset = CustomDataset(train=False)
# Data Loader (Input Pipeline)
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)

test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=False)


# Neural Network Model (1 hidden layer)
class Net(nn.Module):
    def __init__(self, input_size, hidden_size, num_classes):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(hidden_size, num_classes)

    def forward(self, x):
        out = self.fc1(x)
        out = self.relu(out)
        out = self.fc2(out)
        return out


net = Net(input_size, hidden_size, num_classes)

# Loss and Optimizer
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(net.parameters(), lr=learning_rate)

# Train the Model
for epoch in range(num_epochs):
    for i, (images, labels) in enumerate(train_loader):
        # Convert torch tensor to Variable
        images = Variable(images.view(-1, 28 * 28))
        labels = Variable(labels)

        # Forward + Backward + Optimize
        optimizer.zero_grad()  # zero the gradient buffer
        outputs = net(images)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        if (i + 1) % 100 == 0:
            print('Epoch [%d/%d], Step [%d/%d], Loss: %.4f'
                  % (epoch + 1, num_epochs, i + 1, len(train_dataset) // batch_size, loss.data[0]))

# Test the Model
out = []
for images, labels in test_loader:
    images = Variable(images.view(-1, 28 * 28))
    outputs = net(images)
    _, labels = torch.max(outputs.data, 1)
    out = np.append(out, labels.numpy())

df = pd.DataFrame(np.array(out), dtype='int32', index=range(1, len(out) + 1))
df.to_csv('../resources/submission.csv', index_label='ImageId', header=['Label'])
