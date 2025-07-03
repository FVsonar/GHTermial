#ifndef CHANNEL_CONTROLLER_H
#define CHANNEL_CONTROLLER_H

#include "base_controller.h"
#include "Model/channel_model.h"

class ChannelController : public BaseController {
    Q_OBJECT

public:
    explicit ChannelController(ChannelModel *model, QObject *parent = nullptr);

    // 初始化控制器
    void initialize() override;
    // 处理业务逻辑
    void processData() override;
    // 清理资源
    void cleanup() override;

    // 信道操作
    void addChannel(const Channel &channel);
    void removeChannel(int index);
    void updateChannel(int index, const Channel &channel);

private:
    ChannelModel *channelModel;
};

#endif // CHANNEL_CONTROLLER_H