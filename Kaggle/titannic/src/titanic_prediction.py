import numpy as np
import pandas as pd
import torch
import torch.nn as nn
from torch.autograd import Variable

from titannic_dataset import CustomDataset

# Hyper Parameters
input_size = 5
num_classes = 2
num_epochs = 200
batch_size = 100
learning_rate = 0.001

train_dataset = CustomDataset()
test_dataset = CustomDataset(train=False)
# Data Loader (Input Pipeline)
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)

test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=False)


# Neural Network Model (2 hidden layer)
class Net(nn.Module):
    def __init__(self, input_size, num_classes):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(input_size, 40)
        self.relu1 = nn.ReLU()
        self.fc2 = nn.Linear(40, 80)
        self.relu2 = nn.ReLU()
        self.fc3 = nn.Linear(80, num_classes)

    def forward(self, x):
        out = self.fc1(x)
        out = self.relu1(out)
        out = self.fc2(out)
        out = self.relu2(out)
        out = self.fc3(out)
        return out


net = Net(input_size, num_classes)

# Loss and Optimizer
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(net.parameters(), lr=learning_rate)

# Train the Model
for epoch in range(num_epochs):
    for i, (features, labels) in enumerate(train_loader):
        features = Variable(features.view(-1, input_size))
        labels = Variable(labels)

        # Forward + Backward + Optimize
        optimizer.zero_grad()
        outputs = net(features)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        if (i + 1) % 100 == 0:
            print('Epoch [%d/%d], Iter [%d/%d] Loss: %.4f'
                  % (epoch + 1, num_epochs, i + 1, len(train_dataset) // batch_size, loss.data[0]))


# Test the Model
out = []
for features, labels in test_loader:
    features = Variable(features.view(-1, input_size))
    outputs = net(features)
    _, predicted = torch.max(outputs.data, 1)
    out = np.append(out, predicted.numpy())

df = pd.DataFrame(np.array(out), dtype='int32', index=range(892, 892 + len(out)))
df.to_csv('../resources/submission.csv', index_label='PassengerId', header=['Survived'])
