import torch
from torch import nn
from torch import optim
from torch.autograd import Variable

train_data = [("me gusta comer en la cafeteria".split(), "SPANISH"),
              ("Give it to me".split(), "ENGLISH"),
              ("No creo que sea una buena idea".split(), "SPANISH"),
              ("No it is not a good idea to get lost at sea".split(), "ENGLISH")]

test_data = [("Yo creo que si".split(), "SPANISH"),
             ("it is lost on me".split(), "ENGLISH")]


class BoWClassifier(nn.Module):
    def __init__(self, num_labels, vocab_size):
        super(BoWClassifier, self).__init__()
        self.linear = nn.Linear(vocab_size, num_labels)

    def forward(self, vec):
        return self.linear(vec)


def make_bow_vector(sentence, vocab):
    vec = torch.zeros(len(vocab))
    for word in sentence:
        vec[vocab[word]] += 1
    return vec.view(1, -1)


def make_target(label, labels):
    return torch.LongTensor([labels[label]])


if __name__ == '__main__':
    vocab = {}
    for sent, _ in train_data + test_data:
        for word in sent:
            if word not in vocab:
                vocab[word] = len(vocab)

    VOCAB_SIZE = len(vocab)
    NUM_LABELS = 2
    labels = {"SPANISH": 0, "ENGLISH": 1}

    model = BoWClassifier(NUM_LABELS, VOCAB_SIZE)

    loss_function = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=0.1)

    for epoch in range(100):
        for data, label in train_data:
            model.zero_grad()
            bow_vec = Variable(make_bow_vector(data, vocab))
            target = Variable(make_target(label, labels))
            output = model(bow_vec)
            loss = loss_function(output, target)
            loss.backward()
            optimizer.step()

    for data, label in test_data:
        bow_vec = Variable(make_bow_vector(data, vocab))
        output = model(bow_vec)
        print(output)
