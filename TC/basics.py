import tensor_comprehensions as tc
import torch
from torch.autograd import Variable
from torch.nn.parameter import Parameter

matmul = tc.define(tc.database['matmul']['lang'], name='matmul')
mat1, mat2 = torch.randn(3, 4).cuda(), torch.randn(4, 5).cuda()
out = matmul(mat1, mat2, options=tc.Options("mlp"))
print(out)

CONV_LANG = """
def convolution(float(N,C,H,W) I, float(M,C,KH,KW) W1) -> (O) {{
   O(n, m, h, w) +=! I(n, c, {sh} * h + kh, {sw} * w + kw) * W1(m, c, kh, kw)
}}
def convolution_grad(float(N,C,H,W) I, float(M,C,KH,KW) W1, float(N,M,H,W) O_grad) -> (I_grad, W1_grad) {{
   I_grad(n, c, h, w) +=! O_grad(n, m, {sh} * h - kh, {sw} * w - kw) * W1(m, c, kh, kw)
   W1_grad(m, c, kh, kw) +=! O_grad(n, m, {sh} * h - kh, {sw} * w - kw) * I(n, c, h, w)
}}
"""
N, C, H, W, O, kH, kW, sH, sW = 32, 4, 56, 56, 16, 1, 1, 1, 1
convolution = tc.define(CONV_LANG, training=True, name="convolution", backward="convolution_grad",
                        constants={"sh": sH, "sw": sW})
I = Variable(torch.randn(N, C, H, W).cuda(), requires_grad=True)
W = Parameter(torch.randn(O, C, kH, kW).cuda())
out = convolution(I, W, options=[tc.Options("conv"), tc.Options("group_conv")])
out[0].sum().backward()

lang = """
def matmul(float(M,N) A, float(N,K) B) -> (output) {
  output(i, j) +=! A(i, kk) * B(kk, j)
}
"""
matmul = tc.define(lang, name="matmul")
mat1, mat2 = torch.randn(3, 4).cuda(), torch.randn(4, 5).cuda()
out = matmul(mat1, mat2)
print(out)
mat3, mat4 = torch.randn(3, 4).cuda(), torch.randn(4, 5).cuda()
# outputs re-used
matmul(mat3, mat4, outputs=out)
print(out)

tc.GlobalDebugInit(["--dump_cuda=true", "--debug_tc_mapper=true", "--debug_lang=false"])
matmul = tc.define(tc.database['matmul']['lang'], name='matmul')
mat1, mat2 = torch.randn(3, 4).cuda(), torch.randn(4, 5).cuda()
out = matmul(mat1, mat2)
