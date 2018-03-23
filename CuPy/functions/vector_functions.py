import torch
from skcuda import cublas
from torch.autograd import Function

from CuPy.kernels.vector_kernels import vector_mul_forward_kernel, vector_mul_backward_kernel, \
    vector_dot_backward_kernel
from CuPy.utils import load_kernel, Dtype, Stream, num_threads, get_thread_blocks


class VectorMul(Function):

    def forward(self, vector1, vector2):
        with torch.cuda.device_of(vector1):
            output = vector1.new(vector1.size())
            n = output.numel()
            f = load_kernel('vector_mul_forward', vector_mul_forward_kernel, Dtype=Dtype(vector1), nthreads=n)
            f(args=[vector1.data_ptr(), vector2.data_ptr(), output.data_ptr()],
              block=(num_threads, 1, 1),
              grid=(get_thread_blocks(n), 1, 1),
              stream=Stream(ptr=torch.cuda.current_stream().cuda_stream))

        self.save_for_backward(vector1, vector2)
        return output

    def backward(self, grad_output):
        vector1, vector2 = self.saved_tensors
        with torch.cuda.device_of(vector1):
            if self.needs_input_grad[0]:
                grad_vector1 = vector1.new(vector1.size())
                n = grad_vector1.numel()
                f = load_kernel('vector_mul_backward', vector_mul_backward_kernel, Dtype=Dtype(vector1), nthreads=n)
                f(args=[grad_output.data_ptr(), vector2.data_ptr(), grad_vector1.data_ptr()],
                  block=(num_threads, 1, 1),
                  grid=(get_thread_blocks(n), 1, 1),
                  stream=Stream(ptr=torch.cuda.current_stream().cuda_stream))

            if self.needs_input_grad[1]:
                grad_vector2 = vector2.new(vector2.size())
                n = grad_vector2.numel()
                f = load_kernel('vector_mul_backward', vector_mul_backward_kernel, Dtype=Dtype(vector2), nthreads=n)
                f(args=[grad_output.data_ptr(), vector1.data_ptr(), grad_vector2.data_ptr()],
                  block=(num_threads, 1, 1),
                  grid=(get_thread_blocks(n), 1, 1),
                  stream=Stream(ptr=torch.cuda.current_stream().cuda_stream))
        return grad_vector1, grad_vector2


class VectorDot(Function):

    def forward(self, vector1, vector2):
        with torch.cuda.device_of(vector1):
            output = vector1.new(1)
            handle = torch.cuda.current_blas_handle()
            stream = torch.cuda.current_stream()
            cublas.cublasSetStream(handle, stream)
            if isinstance(vector1, torch.cuda.FloatTensor):
                result = cublas.cublasSdot(handle, vector1.numel(), vector1.data_ptr(), 1, vector2.data_ptr(), 1)
            elif isinstance(vector1, torch.cuda.DoubleTensor):
                result = cublas.cublasDdot(handle, vector1.numel(), vector1.data_ptr(), 1, vector2.data_ptr(), 1)
            output = output.fill_(float(result))
        self.save_for_backward(vector1, vector2)
        return output

    def backward(self, grad_output):
        vector1, vector2 = self.saved_tensors
        with torch.cuda.device_of(vector1):
            if self.needs_input_grad[0]:
                grad_vector1 = vector1.new(vector1.size())
                n = grad_vector1.numel()
                f = load_kernel('vector_dot_backward', vector_dot_backward_kernel, Dtype=Dtype(vector1), nthreads=n)
                f(args=[grad_output.data_ptr(), vector2.data_ptr(), grad_vector1.data_ptr()],
                  block=(num_threads, 1, 1),
                  grid=(get_thread_blocks(n), 1, 1),
                  stream=Stream(ptr=torch.cuda.current_stream().cuda_stream))

            if self.needs_input_grad[1]:
                grad_vector2 = vector2.new(vector2.size())
                n = grad_vector2.numel()
                f = load_kernel('vector_dot_backward', vector_dot_backward_kernel, Dtype=Dtype(vector2), nthreads=n)
                f(args=[grad_output.data_ptr(), vector1.data_ptr(), grad_vector2.data_ptr()],
                  block=(num_threads, 1, 1),
                  grid=(get_thread_blocks(n), 1, 1),
                  stream=Stream(ptr=torch.cuda.current_stream().cuda_stream))
        return grad_vector1, grad_vector2
