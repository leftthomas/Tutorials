import torch
import torch.nn as nn
import torch.nn.functional as F
from torch import optim
from torch.autograd import Variable

test_sentence = """When forty winters shall besiege thy brow,
And dig deep trenches in thy beauty's field,
Thy youth's proud livery so gazed on now,
Will be a totter'd weed of small worth held:
Then being asked, where all thy beauty lies,
Where all the treasure of thy lusty days;
To say, within thine own deep sunken eyes,
Were an all-eating shame, and thriftless praise.
How much more praise deserv'd thy beauty's use,
If thou couldst answer 'This fair child of mine
Shall sum my count, and make my old excuse,'
Proving his beauty by succession thine!
This were to be new made when thou art old,
And see thy blood warm when thou feel'st it cold.""".split()


class NGramLanguageModeler(nn.Module):

    def __init__(self, vocab_size, embedding_dim, context_size):
        super(NGramLanguageModeler, self).__init__()
        self.embeddings = nn.Embedding(vocab_size, embedding_dim)
        self.linear1 = nn.Linear(context_size * embedding_dim, 128)
        self.linear2 = nn.Linear(128, vocab_size)

    def forward(self, inputs):
        embeds = self.embeddings(inputs).view((1, -1))
        out = F.relu(self.linear1(embeds))
        out = self.linear2(out)
        return out


if __name__ == '__main__':

    CONTEXT_SIZE = 2
    EMBEDDING_DIM = 10

    trigrams = [([test_sentence[i], test_sentence[i + 1]], test_sentence[i + 2])
                for i in range(len(test_sentence) - 2)]
    print(trigrams[:3])

    vocab = set(test_sentence)
    word_to_ix = {word: i for i, word in enumerate(vocab)}

    losses = []
    loss_function = nn.CrossEntropyLoss()
    model = NGramLanguageModeler(len(vocab), EMBEDDING_DIM, CONTEXT_SIZE)
    optimizer = optim.SGD(model.parameters(), lr=0.001)

    for epoch in range(10):
        total_loss = torch.Tensor([0])
        for context, target in trigrams:
            context_idxs = [word_to_ix[w] for w in context]
            context_var = Variable(torch.LongTensor(context_idxs))
            model.zero_grad()
            output = model(context_var)
            loss = loss_function(output, Variable(torch.LongTensor([word_to_ix[target]])))
            loss.backward()
            optimizer.step()
            total_loss += loss.data
        losses.append(total_loss)
    print(losses)
