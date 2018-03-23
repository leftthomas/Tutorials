import argparse

import pandas as pd
import torch
import torchnet as tnt
from torch import nn
from torch.autograd import Variable
from torch.optim import Adam
from torch.optim.lr_scheduler import ReduceLROnPlateau
from torch.utils.data import DataLoader, TensorDataset
from torchnet.engine import Engine
from torchnet.logger import VisdomPlotLogger
from tqdm import tqdm

from Kaggle.iceberg_classifier import utils
from Kaggle.iceberg_classifier.model import CapsuleNet


def test():
    print('loading test data...')
    data = pd.read_json('data/test.json')
    data['inc_angle'] = pd.to_numeric(data['inc_angle'], errors='coerce')
    data = data.fillna(0)
    test_ids, test_data, test_angles = utils.load_data('test', data)
    test_loader = DataLoader(TensorDataset(test_data, torch.zeros(len(test_data)).long()), batch_size=8,
                             num_workers=4)
    print('test data has been loaded...')
    model.load_state_dict(torch.load('epochs/' + MODEL_NAME))
    model.eval()

    results = []
    for data, _ in tqdm(test_loader, desc='predicting test data'):
        if torch.cuda.is_available():
            data = data.cuda()
        data = Variable(data, volatile=True)
        output = model(data)
        max_length, max_length_indices = output.max(dim=1)
        results.append(max_length.data.cpu())
    results = torch.cat(results)
    data_frame = pd.DataFrame({'id': test_ids, 'is_iceberg': results.numpy()})
    data_frame.to_csv("results/submission.csv", index=False)
    print('prediction has been done!')


def train():
    def processor(sample):
        data, labels, training = sample

        data = utils.augmentation(data.float())

        data = Variable(data)
        labels = Variable(labels)
        if torch.cuda.is_available():
            data = data.cuda()
            labels = labels.cuda()

        classes = model(data)
        loss = capsule_loss(classes, labels.long())

        return loss, classes

    def on_sample(state):
        state['sample'].append(state['train'])

    def reset_meters():
        meter_loss.reset()

    def on_forward(state):
        meter_loss.add(state['loss'].data[0])

    def on_start_epoch(state):
        reset_meters()
        state['iterator'] = tqdm(state['iterator'])

    def on_end_epoch(state):
        print('[Epoch %d] Training Loss: %.4f' % (state['epoch'], meter_loss.value()[0]))

        train_loss_logger.log(state['epoch'], meter_loss.value()[0])

        reset_meters()

        engine.test(processor, utils.get_iterator(False, test_data))
        test_loss_logger.log(state['epoch'], meter_loss.value()[0])

        print('[Epoch %d] Testing Loss: %.4f' % (state['epoch'], meter_loss.value()[0]))

        torch.save(model.state_dict(), 'epochs/epoch_%d.pt' % state['epoch'])

        scheduler.step(meter_loss.value()[0])

    print("# parameters:", sum(param.numel() for param in model.parameters()))

    optimizer = Adam(model.parameters())
    scheduler = ReduceLROnPlateau(optimizer, verbose=True)

    engine = Engine()
    meter_loss = tnt.meter.AverageValueMeter()
    train_loss_logger = VisdomPlotLogger('line', opts={'title': 'Train Loss'})
    test_loss_logger = VisdomPlotLogger('line', opts={'title': 'Test Loss'})

    capsule_loss = nn.CrossEntropyLoss()

    engine.hooks['on_sample'] = on_sample
    engine.hooks['on_forward'] = on_forward
    engine.hooks['on_start_epoch'] = on_start_epoch
    engine.hooks['on_end_epoch'] = on_end_epoch

    d = pd.read_json('data/train.json')
    d['inc_angle'] = pd.to_numeric(d['inc_angle'], errors='coerce')
    d = d.fillna(0)
    train_data = d.sample(frac=0.8)
    test_data = d[~d.isin(train_data)].dropna()
    engine.train(processor, utils.get_iterator(True, train_data), maxepoch=100, optimizer=optimizer)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Iceberg Classfication')
    parser.add_argument('--is_train', default='yes', type=str, choices=['yes', 'no'], help='train or test')
    parser.add_argument('--model_name', default='epoch_100.pt', type=str, help='test model name')

    opt = parser.parse_args()

    IS_TRAIN = opt.is_train
    MODEL_NAME = opt.model_name

    model = CapsuleNet()
    if torch.cuda.is_available():
        model.cuda()
    if IS_TRAIN == 'yes':
        train()
    else:
        test()
