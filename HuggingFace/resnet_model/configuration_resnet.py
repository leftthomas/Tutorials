from transformers import PretrainedConfig
from typing import List


class ResnetConfig(PretrainedConfig):
    model_type = 'resnet'
    def __init__(self, block_type='bottleneck', layers: List[int] = [3, 4, 6, 3], num_classes: int = 1000, **kwargs):
        if block_type not in ['basic', 'bottleneck']:
            raise ValueError(f"`block` must be 'basic' or bottleneck', got {block_type}.")
        self.block_type = block_type
        self.layers = layers
        self.num_classes = num_classes
        super().__init__(**kwargs)
