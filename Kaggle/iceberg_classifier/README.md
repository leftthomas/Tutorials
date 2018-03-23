# IcebergClassifier
Iceberg Classifier Challenge

## Requirements
* [Anaconda](https://www.anaconda.com/download/)
* PyTorch
```
conda install pytorch torchvision cuda90 -c pytorch
```
* PyTorchNet
```
pip install git+https://github.com/pytorch/tnt.git@master
```
* tqdm
```
pip install tqdm
```

## Datasets
Download datasets from [Statoil/C-CORE Iceberg Classifier Challenge](https://www.kaggle.com/c/statoil-iceberg-classifier-challenge/data),
then extract the `*.json` files into `data` directory.


## Usage
```
python -m visdom.server & python main.py
optional arguments:
--is_train            train or test [default value is True]
--model_name          test model name [default value is epoch_100.pt]
```
Visdom now can be accessed by going to `127.0.0.1:8097` in your browser, or your own host address if specified.