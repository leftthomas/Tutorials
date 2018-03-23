import cupy as cp
import numpy as np

# these kernels are modified from CUDA C Programming Guide
vector_add = cp.ElementwiseKernel(in_params='float32 x, float32 y', out_params='float32 z', operation='z = x+y',
                                  name='vector_add')

mat_add = cp.ElementwiseKernel(in_params='float32 x, float32 y', out_params='float32 z', operation='z = x+y',
                               name='mat_add')

mat_dot = cp.ElementwiseKernel(in_params='float32 x, float32 y', out_params='float32 z', operation='z = x * y',
                               name='mat_dot')

# basic op
x = cp.array([1, 2, 3])
print(x)
x_l2 = cp.linalg.norm(x)
print(x_l2)
print(x.device)

y = np.array([1, 2, 3, 4])
print(y)
z = cp.asarray(y)
print(z)
w = cp.asnumpy(z)
print(w)

# define kernel
squared_diff = cp.ElementwiseKernel(in_params='float32 x, float32 y', out_params='float32 z',
                                    operation='z = (x-y) * (x-y)', name='squared_diff')
# call kernel
x = cp.arange(10, dtype=np.float32).reshape(2, 5)
print(x)
y = cp.arange(5, dtype=np.float32)
print(y)
z = squared_diff(x, y)
print(z)
z = squared_diff(x, 5)
print(z)

# call vector_add kernel
print('test vector_add kernel')
x = cp.random.random_sample(5, dtype=np.float32)
print(x)
y = cp.random.random_sample(5, dtype=np.float32)
print(y)
z = vector_add(x, y)
print(z)
w = x + y
print(w)
print(cp.equal(w, z))

# call mat_add kernel
print('test mat_add kernel')
x = cp.random.random_sample((2, 3), dtype=np.float32)
# test broadcast op
# x = cp.random.random_sample((2, 1), dtype=np.float32)
print(x)
y = cp.random.random_sample((2, 3), dtype=np.float32)
print(y)
z = mat_add(x, y)
print(z)
w = x + y
print(w)
print(cp.equal(w, z))

# call mat_dot kernel
print('test mat_dot kernel')
x = cp.random.random_sample((2, 3), dtype=np.float32)
print(x)
y = cp.random.random_sample((2, 3), dtype=np.float32)
print(y)
z = mat_dot(x, y)
print(z)
w = x * y
print(w)
print(cp.equal(w, z))
