import torch
from skcuda import cublas
from torch.autograd import Function


class MatrixMul(Function):

    def forward(self, matrix1, matrix2):
        with torch.cuda.device_of(matrix1):
            dim1, dim2 = matrix1.size()
            dim2, dim3 = matrix2.size()
            output = matrix1.new(dim1, dim3)
            handle = torch.cuda.current_blas_handle()
            stream = torch.cuda.current_stream()
            cublas.cublasSetStream(handle, stream)
            if isinstance(matrix1, torch.cuda.FloatTensor):
                cublas.cublasSgemm(handle, 'n', 'n', dim3, dim1, dim2, 1, matrix2.data_ptr(), dim3, matrix1.data_ptr(),
                                   dim2, 0, output.data_ptr(), dim3)
            elif isinstance(matrix1, torch.cuda.DoubleTensor):
                cublas.cublasDgemm(handle, 'n', 'n', dim3, dim1, dim2, 1, matrix2.data_ptr(), dim3, matrix1.data_ptr(),
                                   dim2, 0, output.data_ptr(), dim3)
        self.save_for_backward(matrix1, matrix2)
        return output

    def backward(self, grad_output):
        matrix1, matrix2 = self.saved_tensors
        with torch.cuda.device_of(matrix1):
            if self.needs_input_grad[0]:
                grad_matrix1 = torch.mm(grad_output, matrix2.t())

            if self.needs_input_grad[1]:
                grad_matrix2 = torch.mm(matrix1.t(), grad_output)

        return grad_matrix1, grad_matrix2
