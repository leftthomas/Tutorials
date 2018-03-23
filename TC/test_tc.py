import pytest
import tensor_comprehensions as tc
import torch
import torch.nn.functional as F
from pytest import approx
from torch.autograd import Variable

from kernels import abs, mv, matmul, maxpool

test_abs_data = [(M, N) for M in [1, 5, 128] for N in [1, 7, 256]]
test_mv_data = [(R, C) for R in [1, 2, 128] for C in [1, 5, 128, 256]]
test_matmul_data = [(M, N, K) for M in [1, 2, 10, 100] for N in [1, 5, 20, 128] for K in [1, 4, 8, 512]]
test_maxpool_data = [(B, C, H, W) for B in [1, 2, 8] for C in [1, 3, 6] for H in [4, 72] for W in [5, 36]]


@pytest.mark.parametrize('M, N', test_abs_data)
def test_abs(M, N):
    mat = Variable(torch.randn(M, N).cuda())
    out_tc = abs(mat, options=tc.Options("pointwise"))
    out_pt = torch.abs(mat)
    assert out_tc.cpu().data.view(-1).tolist() == approx(out_pt.cpu().data.view(-1).tolist())


@pytest.mark.parametrize('R, C', test_mv_data)
def test_mv(R, C):
    mat = Variable(torch.randn(R, C).cuda())
    vector = Variable(torch.randn(C).cuda())
    out_tc = mv(mat, vector, options=tc.Options("mlp"))
    out_pt = torch.mv(mat, vector)
    assert out_tc.cpu().data.view(-1).tolist() == approx(out_pt.cpu().data.view(-1).tolist(), abs=1e-4)


@pytest.mark.parametrize('M, N, K', test_matmul_data)
def test_matmul(M, N, K):
    mat1 = Variable(torch.randn(M, N).cuda())
    mat2 = Variable(torch.randn(N, K).cuda())
    matmul.autotune(mat1, mat2, cache=True, options=tc.Options("mlp"), **tc.autotuner_settings)
    out_tc = matmul(mat1, mat2)
    out_pt = torch.matmul(mat1, mat2)
    assert out_tc.cpu().data.view(-1).tolist() == approx(out_pt.cpu().data.view(-1).tolist(), abs=1e-4)


@pytest.mark.parametrize('B, C, H, W', test_maxpool_data)
def test_maxpool(B, C, H, W):
    tensor = Variable(torch.randn(B, C, H, W).cuda())
    out_tc = maxpool(tensor, options=tc.Options("conv"))
    out_pt = F.max_pool2d(tensor, kernel_size=2, stride=1)
    assert out_tc.cpu().data.view(-1).tolist() == approx(out_pt.cpu().data.view(-1).tolist())
