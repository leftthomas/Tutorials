import pandas as pd
from sklearn.neural_network import MLPRegressor


# 从csv文件提取出数据，并做一些数据处理，形成特征表示
def extract_feature_from_data(file, is_train=True):
    data = pd.read_csv(file)
    if is_train:
        # 提取feature，排除掉Id与SalePrice列
        feature_data = data.iloc[:, 1:len(data.keys()) - 1]
    else:
        # 只需排除掉Id列
        feature_data = data.iloc[:, 1:len(data.keys())]
    # 处理缺失值，用中位数填充
    feature_data.fillna(value=feature_data.median(), inplace=True)
    for key in feature_data.keys():
        # 非数值特征转换为数值
        if feature_data[key].dtypes == 'object':
            feature_data.replace(to_replace={
                key: dict(
                    zip(set(feature_data[key].values), range(1, len(set(feature_data[key].values)) + 1)))},
                inplace=True)
        # 数据格式转换
        if feature_data[key].dtypes == 'int64':
            feature_data = feature_data.astype(dtype={key: 'int32'})
        if feature_data[key].dtypes == 'float64':
            feature_data = feature_data.astype(dtype={key: 'float32'})
    # print(feature_data)
    if is_train:
        return feature_data, data['SalePrice'].astype('float32')
    else:
        return feature_data, data['Id'].astype('int32')


# 数据准备
training_file = 'train.csv'
train_feature_data, train_label_data = extract_feature_from_data(training_file)
# print(train_label_data)
test_file = 'test.csv'
test_feature_data, test_id_data = extract_feature_from_data(test_file, is_train=False)
# print(test_id_data)

# 线性分类器
# classifier = LogisticRegression()
# 神经网络
classifier = MLPRegressor(max_iter=1000)
classifier.fit(train_feature_data, train_label_data)
# print(classifier.score(train_feature_data,train_label_data))
# print(classifier.predict(test_feature_data))
predication = classifier.predict(test_feature_data)
df = pd.DataFrame(predication, index=test_id_data)
df.to_csv('submission.csv', index_label='Id', header=['SalePrice'])
