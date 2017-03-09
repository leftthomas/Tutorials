# Python3 学习
此代码为我在[优达学城](https://cn.udacity.com)上对Python等相关课程学习时所做的项目
* 建议安装[Anaconda](https://www.continuum.io/downloads)，后续代码依赖Anaconda
* 不同课程以课程号单独为一个文件夹
* src目录下的内容为对应课程代码
* resources目录下的内容为对应课程开发所需的一些资源文件

## ud036
ud036文件夹下的内容对应[编程基础：Python学习面向对象编程方法](https://cn.udacity.com/course/programming-foundations-with-python--ud036)课程

## ud170
ud170文件夹下的内容对应[数据分析入门：使用 NumPy 和 Pandas 进行数据分析](https://cn.udacity.com/course/intro-to-data-analysis--ud170)课程

## ud120
ud120文件夹下的内容对应[机器学习入门（中/英）：有趣及有利的特征识别](https://cn.udacity.com/course/intro-to-machine-learning--ud120)课程
* 首先需运行 [**download_mails_data.py**](ud120/src/enron/download_mails_data.py)，下载安然事件邮件数据集

## ud730
ud730文件夹下的内容对应[深度学习（中/英）：将机器学习技能更上一个台阶](https://cn.udacity.com/course/deep-learning--ud730)课程
* 首先需安装[TensorFlow](https://www.tensorflow.org/install)，建议通过Anaconda的方式来安装
* 然后需运行[**download_data.py**](ud730/src/notmnist/download_data.py)，下载notMNIST数据集
    
    > 若下载数据集过程中遇到问题，可点击以下链接直接下载数据集到本地  
    [notMNIST_small.tar.gz](http://commondatastorage.googleapis.com/books1000/notMNIST_small.tar.gz)  
    [notMNIST_large.tar.gz](http://commondatastorage.googleapis.com/books1000/notMNIST_large.tar.gz)
* 接着需运行[**extract_pickle_data.py**](ud730/src/notmnist/extract_pickle_data.py)，解压notMNIST数据集，生成pickle文件