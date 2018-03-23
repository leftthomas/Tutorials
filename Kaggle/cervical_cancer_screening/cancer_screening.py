import numpy as np
import pandas as pd
from PIL import ImageFile
from torch import nn
from torch import optim
from torch.autograd import Variable
from torch.utils import data as datautils
from torchvision import datasets
from torchvision import transforms

from Kaggle.cervical_cancer_screening import left_net

# 防止报"OSError: image file is truncated (54 bytes not processed)"这个奇葩错误
ImageFile.LOAD_TRUNCATED_IMAGES = True

# parameters
image_size = 300  # image_size最后尺寸为[300，300]
mean = [0.5, 0.5, 0.5]
std = [0.5, 0.5, 0.5]
batch_size = 128
lr = 0.001
momentum = 0.9
epoch_num = 10

# transform images
transform = transforms.Compose([
    transforms.RandomSizedCrop(size=image_size),
    # transforms.RandomCrop(size=image_size),
    # transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Normalize(mean=mean, std=std),
])

# Data Loading
train_data = datasets.ImageFolder(root="train", transform=transform)
# print(train_data.imgs)

train_loader = datautils.DataLoader(dataset=train_data, batch_size=batch_size, shuffle=True)

# define model
model = left_net.Net()
# print(model)

# define Loss Function and Optimizer
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=lr, momentum=momentum)

# train the model
for epoch in range(epoch_num):
    for i, data in enumerate(train_loader):
        # get the inputs
        inputs, labels = data

        # wrap them in Variable
        inputs, labels = Variable(inputs), Variable(labels)

        # zero the parameter gradients
        optimizer.zero_grad()

        # forward + backward + optimize
        outputs = model(inputs)

        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        # print statistics
        print('[%d, %3d] loss: %.3f' % (epoch + 1, i + 1, loss.data[0]))

print('Finished Training')


# Test Data Loading
# 记得在test文件夹下新建一个Type_unknow的子文件夹，把测试图片全部移到这个文件夹下，
# 不然的话无法通过datasets.ImageFolder方法载入数据集
test_data = datasets.ImageFolder(root="test", transform=transform)
test_loader = datautils.DataLoader(dataset=test_data, batch_size=batch_size)
# 用来保存所有image的name
img_names = []
for img in test_data.imgs:
    img_names.append(img[0][12:])
# print(img_names)
# print(test_data.classes)
# print(test_data.class_to_idx)

# 用来记录全部测试图片的结果
output_probabilities = []
is_first = True
# perform on test data
for data in test_loader:
    images, _ = data
    outputs = model(Variable(images))
    if is_first:
        output_probabilities = outputs.data.numpy()
        is_first = False
    else:
        output_probabilities = np.append(output_probabilities, outputs.data.numpy(), axis=0)
        # print(output_probabilities)

df = pd.DataFrame(output_probabilities, index=img_names, columns=['Type_1', 'Type_2', 'Type_3'])
df.to_csv('submission.csv', index_label='image_name')
print('Finished Testing')
