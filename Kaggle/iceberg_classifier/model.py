import torch.nn.functional as F
from torch import nn

from capsulelayer import CapsuleConv2d, CapsuleLinear


class CapsuleNet(nn.Module):
    def __init__(self):
        super(CapsuleNet, self).__init__()
        self.features = nn.Sequential(
            CapsuleConv2d(in_channels=2, out_channels=32, kernel_size=3, in_length=1, out_length=8, stride=1,
                          padding=1),
            CapsuleConv2d(in_channels=32, out_channels=32, kernel_size=3, in_length=8, out_length=8, stride=2,
                          padding=1),
            CapsuleConv2d(in_channels=32, out_channels=64, kernel_size=3, in_length=8, out_length=16, stride=1,
                          padding=1),
            CapsuleConv2d(in_channels=64, out_channels=64, kernel_size=3, in_length=16, out_length=16, stride=2,
                          padding=1),
            CapsuleConv2d(in_channels=64, out_channels=128, kernel_size=3, in_length=16, out_length=16, stride=1,
                          padding=1),
            CapsuleConv2d(in_channels=128, out_channels=128, kernel_size=3, in_length=16, out_length=16, stride=2,
                          padding=1),
            CapsuleConv2d(in_channels=128, out_channels=128, kernel_size=3, in_length=16, out_length=16, stride=2,
                          padding=1),
            CapsuleConv2d(in_channels=128, out_channels=128, kernel_size=3, in_length=16, out_length=16, stride=2,
                          padding=1),
        )
        self.classifier = CapsuleLinear(in_capsules=3 * 3 * 128 // 16, out_capsules=2, in_length=16, out_length=16)

    def forward(self, x):
        out = self.features(x)

        out = out.view(*out.size()[:2], -1)
        out = out.transpose(-1, -2)
        out = out.contiguous().view(out.size(0), -1, 16)

        out = self.classifier(out)
        classes = out.norm(p=2, dim=-1)
        classes = F.softmax(classes, dim=-1)
        return classes
