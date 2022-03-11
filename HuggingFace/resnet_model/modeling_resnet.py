from transformers import PreTrainedModel
from torchvision.models.resnet import ResNet, Bottleneck, BasicBlock
import torch.nn.functional as F
from .configuration_resnet import ResnetConfig


BLOCK_MAPPING = {'basic': BasicBlock, 'bottleneck': Bottleneck}


class ResnetModelForImageClassification(PreTrainedModel):
    config_class = ResnetConfig
    def __init__(self, config):
        super().__init__(config)
        block_layer = BLOCK_MAPPING[config.block_type]
        self.model = ResNet(block_layer, config.layers, config.num_classes)

    def forward(self, tensor, labels=None):
        logits = self.model(tensor)
        if labels is not None:
            loss = F.cross_entropy(logits, labels)
            return {'loss': loss, 'logits': logits}
        return {'logits': logits}
