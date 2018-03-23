vector_mul_forward_kernel = '''
extern "C"
__global__ void vector_mul_forward(const ${Dtype}* vector1, const ${Dtype}* vector2, ${Dtype}* output)
{
  int index = threadIdx.x + blockIdx.x * blockDim.x;
  if (index < ${nthreads}){
    output[index] = vector1[index] * vector2[index];
  }
}
'''

vector_mul_backward_kernel = '''
extern "C"
__global__ void vector_mul_backward(const ${Dtype}* grad_output, const ${Dtype}* other_vector, ${Dtype}* grad_input)
{
  int index = threadIdx.x + blockIdx.x * blockDim.x;
  if (index < ${nthreads}){
    grad_input[index] = grad_output[index] * other_vector[index];
  }
}
'''

vector_dot_backward_kernel = '''
extern "C"
__global__ void vector_dot_backward(const ${Dtype}* grad_output, const ${Dtype}* other_vector, ${Dtype}* grad_input)
{
  int index = threadIdx.x + blockIdx.x * blockDim.x;
  if (index < ${nthreads}){
    grad_input[index] = grad_output[0] * other_vector[index];
  }
}
'''
