from functools import partial

import pytest
import torch
from pytest import approx
from torch.autograd import Variable, gradcheck

from CuPy.functions.matrix_functions import MatrixMul

mul_test_data = [(dim1, dim2, dim3) for dim1 in [2, 5, 32, 128] for dim2 in [2, 5, 32, 128] for dim3 in [2, 5, 32, 128]]


@pytest.mark.parametrize('dim1, dim2, dim3', mul_test_data)
def test_matrix_mul(dim1, dim2, dim3):
    for test_type in [torch.FloatTensor, torch.DoubleTensor]:
        m1 = Variable(torch.randn(dim1, dim2).type(test_type).cuda(), requires_grad=True)
        m2 = Variable(torch.randn(dim2, dim3).type(test_type).cuda(), requires_grad=True)
        go = torch.randn(dim1, dim3).type(test_type).cuda()

        y_fast = MatrixMul()(m1, m2)
        y_ref = torch.mm(m1, m2)
        assert y_fast.cpu().data.numpy() == approx(y_ref.cpu().data.numpy())

        y_fast.backward(go)
        gm1_fast = m1.grad.data.clone()
        gm2_fast = m2.grad.data.clone()

        m1.grad.data.zero_()
        m2.grad.data.zero_()
        y_ref.backward(go)
        gm1_ref = m1.grad.data.clone()
        gm2_ref = m2.grad.data.clone()
        assert gm1_fast.cpu().numpy() == approx(gm1_ref.cpu().numpy())
        assert gm2_fast.cpu().numpy() == approx(gm2_ref.cpu().numpy())
        # only check grad at double precision
        if test_type is torch.DoubleTensor:
            assert gradcheck(partial(MatrixMul()), (m1, m2))
