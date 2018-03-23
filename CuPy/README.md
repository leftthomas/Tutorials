# CuPyLearn
Learn how to use CuPy to write CUDA Kernel Function and invoke it by PyTorch,
how to use scikit-cuda to call cublas function and invoke it by PyTorch.

## Requirements
* [Anaconda](https://www.anaconda.com/download/)
* PyTorch
```
conda install pytorch torchvision cuda90 -c pytorch
```
* CuPy
```
pip install cupy
```
* scikit-cuda
```
pip install scikit-cuda
```

## Usage
```
git clone https://github.com/leftthomas/CuPyLearn.git
cd CuPyLearn/test
pytest
```
