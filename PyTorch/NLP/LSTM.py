import torch
from torch import nn
from torch.autograd import Variable

lstm = nn.LSTM(3, 3)
# make a sequence of length 5
inputs = [Variable(torch.randn((1, 3))) for _ in range(5)]
# initialize the hidden state.
hidden = (Variable(torch.randn(1, 1, 3)), Variable(torch.randn((1, 1, 3))))

for i in inputs:
    # Step through the sequence one element at a time.
    # after each step, hidden contains the hidden state.
    out, hidden = lstm(i.view(1, 1, -1), hidden)

inputs = torch.cat(inputs).view(len(inputs), 1, -1)
# clean out hidden state
hidden = (Variable(torch.randn(1, 1, 3)), Variable(torch.randn((1, 1, 3))))
out, hidden = lstm(inputs, hidden)
print(out)
print(hidden)
