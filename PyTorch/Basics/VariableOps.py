import torch
from torch.autograd import Variable

x = Variable(torch.ones(2, 2), requires_grad=True)
print('x:', x)
print('x.data:', x.data)

y = x + 2
print('y:', y)
print('x.grad_fn:', y.grad_fn)

z = y * y * 3
out = z.mean()
print('z:', z)
print('out:', out)

out.backward()
print('x.grad:', x.grad)
