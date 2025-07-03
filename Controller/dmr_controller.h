#ifndef DMR_CONTROLLER_H
#define DMR_CONTROLLER_H

#include "base_controller.h"
#include "Model/dmr_model.h"

class DMRController : public BaseController {
    Q_OBJECT

public:
    explicit DMRController(DMRModel *model, QObject *parent = nullptr);

    // 初始化控制器
    void initialize() override;
    // 处理业务逻辑
    void processData() override;
    // 清理资源
    void cleanup() override;

    // DMR操作
    void addDMR(const DMR &dmr);
    void removeDMR(int index);
    void updateDMR(int index, const DMR &dmr);

private:
    DMRModel *dmrModel;
};

#endif // DMR_CONTROLLER_H