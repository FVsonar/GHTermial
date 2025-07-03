#include "channel_controller.h"

ChannelController::ChannelController(ChannelModel *model, QObject *parent) :
    BaseController(parent),
    channelModel(model)
{
}

void ChannelController::initialize()
{
    // 初始化控制器逻辑
    connect(channelModel, &ChannelModel::dataChanged, this, &ChannelController::onModelDataChanged);
    // 初始化数据
    channelModel->initialize();
}

void ChannelController::processData()
{
    // 处理业务逻辑
    QList<Channel> channels = channelModel->getChannels();
    // 更新UI
    emit dataProcessed(channels);
}

void ChannelController::cleanup()
{
    // 清理资源
    channelModel->clear();
}

void ChannelController::addChannel(const Channel &channel)
{
    // 添加信道逻辑
    channelModel->addChannel(channel);
    // 更新UI
    emit channelAdded(channel);
}

void ChannelController::removeChannel(int index)
{
    // 删除信道逻辑
    channelModel->removeChannel(index);
    // 更新UI
    emit channelRemoved(index);
}

void ChannelController::updateChannel(int index, const Channel &channel)
{
    // 更新信道逻辑
    channelModel->updateChannel(index, channel);
    // 更新UI
    emit channelUpdated(index, channel);
}