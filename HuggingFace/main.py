from torchvision.models.resnet import resnet18
from resnet_model.configuration_resnet import ResnetConfig
from resnet_model.modeling_resnet import ResnetModelForImageClassification


ResnetConfig.register_for_auto_class()
ResnetModelForImageClassification.register_for_auto_class('AutoModelForImageClassification')

resnet18_config = ResnetConfig(block_type='basic', layers=[2, 2, 2, 2], num_classes=1000)
resnet18_config.save_pretrained('resnet18')
resnet18_model = ResnetModelForImageClassification(resnet18_config)
resnet18_model.model.load_state_dict(resnet18(pretrained=True).state_dict())
resnet18_model.save_pretrained('resnet18')