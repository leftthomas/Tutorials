import numpy as np
import torch
import torchnet as tnt


def load_data(data_type, data):
    data['band_1'] = data['band_1'].apply(lambda x: np.array(x).reshape(75, 75))
    data['band_2'] = data['band_2'].apply(lambda x: np.array(x).reshape(75, 75))
    # print(data.head())
    # print(data['inc_angle'])
    # data.info()
    band_1 = np.concatenate([im for im in data['band_1']]).reshape(-1, 75, 75)
    band_2 = np.concatenate([im for im in data['band_2']]).reshape(-1, 75, 75)
    image = np.stack([band_1, band_2], axis=1)
    images = torch.from_numpy(image).float()
    angles = torch.from_numpy(np.array(data['inc_angle'])).float()

    if data_type == 'test':
        return data['id'], images, angles
    else:
        targets = torch.from_numpy(data['is_iceberg'].values)
        dataset = tnt.dataset.TensorDataset([images, targets])
        return dataset, angles


def augmentation(x, max_shift=2):
    _, _, height, width = x.size()

    h_shift, w_shift = np.random.randint(-max_shift, max_shift + 1, size=2)
    source_height_slice = slice(max(0, h_shift), h_shift + height)
    source_width_slice = slice(max(0, w_shift), w_shift + width)
    target_height_slice = slice(max(0, -h_shift), -h_shift + height)
    target_width_slice = slice(max(0, -w_shift), -w_shift + width)

    shifted_image = torch.zeros(*x.size())
    shifted_image[:, :, source_height_slice, source_width_slice] = x[:, :, target_height_slice, target_width_slice]
    return shifted_image.float()


def get_iterator(mode, datas):
    if mode:
        dataset, angles = load_data('train', datas)
    else:
        dataset, angles = load_data('val', datas)
    return dataset.parallel(batch_size=8, num_workers=4, shuffle=mode)
