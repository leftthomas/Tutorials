import numpy as np
import torch

x=torch.Tensor(5,3)
print('x:', x)

y = torch.FloatTensor(2, 3)
print('y:', y)

u = np.array([1, 2, 3])
print('u:', u)
print('tensor from numpy u:', torch.from_numpy(u))
print('y\'s numpy :', y.numpy())


z = torch.DoubleTensor(2, 3)
print('z:', z)

t = torch.rand(2, 3)
print('t:', t)

r = torch.randn(2, 3)
print('r:', r)
print('abs(r):', torch.abs(r))

print('t+r:', t + r)
# note it is an inplace operation
print('t.add_(r):', t.add_(r))
print('t:', t)
print('t+r:', torch.add(t, r))

print('t cat r:', torch.cat((t, r)))
