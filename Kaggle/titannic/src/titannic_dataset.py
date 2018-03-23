import math

import numpy as np
import pandas as pd
import torch
import torch.utils.data as data


class CustomDataset(data.Dataset):
    training_file = '../resources/train.csv'
    test_file = '../resources/test.csv'

    def __init__(self, train=True):
        self.train = train  # training set or test set

        if self.train:
            self.train_data = pd.read_csv(self.training_file)
            self.train_pclass = self.train_data.ix[:, 2].values.astype('int32')
            self.train_sex = self.train_data.ix[:, 4].values
            # 将sex数据转成int
            for i in range(len(self.train_sex)):
                if self.train_sex[i] == 'male':
                    self.train_sex[i] = 0
                else:
                    self.train_sex[i] = 1
            self.train_sex = self.train_sex.astype('int32')
            self.train_age = self.train_data.ix[:, 5].values.astype('float32')
            # 将有nan值的数据处理成0
            for j in range(len(self.train_age)):
                if math.isnan(self.train_age[j]):
                    self.train_age[j] = 0
            self.train_age = self.train_age.astype('float32')
            self.train_sibsp = self.train_data.ix[:, 6].values.astype('int32')
            self.train_parch = self.train_data.ix[:, 7].values.astype('int32')
            self.train_labels = self.train_data.ix[:, 1].values.astype('int32')
            # 将所有数据整合成一个新的特征矩阵
            self.train_features = np.zeros((len(self.train_data), 5)).astype('float32')
            # 每一行是一个数据，一共5列，包含5个特征
            for k in range(len(self.train_data)):
                self.train_features[k][0] = self.train_pclass[k]
                self.train_features[k][1] = self.train_sex[k]
                self.train_features[k][2] = self.train_age[k]
                self.train_features[k][3] = self.train_sibsp[k]
                self.train_features[k][4] = self.train_parch[k]
        else:
            self.test_data = pd.read_csv(self.test_file)
            self.test_pclass = self.test_data.ix[:, 1].values.astype('int32')
            self.test_sex = self.test_data.ix[:, 3].values
            for i in range(len(self.test_sex)):
                if self.test_sex[i] == 'male':
                    self.test_sex[i] = 0
                else:
                    self.test_sex[i] = 1
            self.test_sex = self.test_sex.astype('int32')
            self.test_age = self.test_data.ix[:, 4].values.astype('float32')
            for j in range(len(self.test_age)):
                if math.isnan(self.test_age[j]):
                    self.test_age[j] = 0
            self.test_age = self.test_age.astype('float32')
            self.test_sibsp = self.test_data.ix[:, 5].values.astype('int32')
            self.test_parch = self.test_data.ix[:, 6].values.astype('int32')
            self.test_features = np.zeros((len(self.test_data), 5)).astype('float32')
            for k in range(len(self.test_data)):
                self.test_features[k][0] = self.test_pclass[k]
                self.test_features[k][1] = self.test_sex[k]
                self.test_features[k][2] = self.test_age[k]
                self.test_features[k][3] = self.test_sibsp[k]
                self.test_features[k][4] = self.test_parch[k]

    def __getitem__(self, index):
        if self.train:
            features, target = torch.from_numpy(self.train_features)[index], torch.from_numpy(self.train_labels)[index]
        else:
            features, target = torch.from_numpy(self.test_features)[index], 0  # test集没有标签，默认初始化为0
        return features, target

    def __len__(self):
        if self.train:
            return len(self.train_features)
        else:
            return len(self.test_features)
