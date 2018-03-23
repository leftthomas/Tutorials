import torch
import torch.nn as nn
from torch.autograd import Variable

word_to_ix = {"hello": 0, "world": 1}
embeds = nn.Embedding(num_embeddings=2, embedding_dim=4)
lookup_tensor = torch.LongTensor([word_to_ix["hello"]])
hello_embed = embeds(Variable(lookup_tensor))
print(hello_embed)