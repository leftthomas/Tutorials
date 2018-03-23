import tensor_comprehensions as tc

lang = '''
def abs(float(M, N) A) -> (O) {
  O(m, n) = fabs(A(m, n))
}

def mv(float(R,C) A, float(C) B) -> (O) {
  O(i) +=! A(i,j) * B(j)
}

def matmul(float(M,N) A, float(N,K) B) -> (O) {
  O(i, j) +=! A(i, kk) * B(kk, j)
}
'''

maxpool_lang = '''
def maxpool(float(B, C, H, W) input) -> (output) {{
    output(b, c, h, w) max=! input(b, c, h * {sH} + kh, w * {sW} + kw) where kh in 0:{kH}, kw in 0:{kW}
}}
'''

abs = tc.define(lang, name="abs")
mv = tc.define(lang, name="mv")
matmul = tc.define(lang, name="matmul")
maxpool = tc.define(maxpool_lang, name="maxpool", constants={"sH": 1, "sW": 1, "kH": 2, "kW": 2})
