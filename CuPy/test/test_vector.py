from functools import partial
import pytest
import torch
from torch.autograd import Variable, gradcheck
from functions.vector_functions import VectorMul, VectorDot
from pytest import approx

test_data = [length for length in [1, 2, 5, 10, 18, 32, 74, 128, 256, 512, 1024, 2048, 4096]]


@pytest.mark.parametrize('length', test_data)
def test_vector_mul(length):
    for test_type in [torch.FloatTensor, torch.DoubleTensor]:
        v1 = Variable(torch.randn(length).type(test_type).cuda(), requires_grad=True)
        v2 = Variable(torch.randn(length).type(test_type).cuda(), requires_grad=True)
        go = torch.randn(length).type(test_type).cuda()

        y_fast = VectorMul()(v1, v2)
        y_ref = v1 * v2
        assert y_fast.cpu().data.numpy() == approx(y_ref.cpu().data.numpy())

        y_fast.backward(go)
        gv1_fast = v1.grad.data.clone()
        gv2_fast = v2.grad.data.clone()

        v1.grad.data.zero_()
        v2.grad.data.zero_()
        y_ref.backward(go)
        gv1_ref = v1.grad.data.clone()
        gv2_ref = v2.grad.data.clone()
        assert gv1_fast.cpu().numpy() == approx(gv1_ref.cpu().numpy())
        assert gv2_fast.cpu().numpy() == approx(gv2_ref.cpu().numpy())
        # only check grad at double precision
        if test_type is torch.DoubleTensor:
            assert gradcheck(partial(VectorMul()), (v1, v2))


@pytest.mark.parametrize('length', test_data)
def test_vector_dot(length):
    for test_type in [torch.FloatTensor, torch.DoubleTensor]:
        v1 = Variable(torch.randn(length).type(test_type).cuda(), requires_grad=True)
        v2 = Variable(torch.randn(length).type(test_type).cuda(), requires_grad=True)
        go = torch.randn(1).type(test_type).cuda()

        y_fast = VectorDot()(v1, v2)
        y_ref = torch.dot(v1, v2)
        assert y_fast.cpu().data.numpy() == approx(y_ref.cpu().data.numpy())

        y_fast.backward(go)
        gv1_fast = v1.grad.data.clone()
        gv2_fast = v2.grad.data.clone()

        v1.grad.data.zero_()
        v2.grad.data.zero_()
        y_ref.backward(go)
        gv1_ref = v1.grad.data.clone()
        gv2_ref = v2.grad.data.clone()
        assert gv1_fast.cpu().numpy() == approx(gv1_ref.cpu().numpy())
        assert gv2_fast.cpu().numpy() == approx(gv2_ref.cpu().numpy())
        # only check grad at double precision
        if test_type is torch.DoubleTensor:
            assert gradcheck(partial(VectorDot()), (v1, v2))
