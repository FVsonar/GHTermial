#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <QObject>

class BaseController : public QObject {
    Q_OBJECT

public:
    explicit BaseController(QObject *parent = nullptr);

    // 初始化控制器
    virtual void initialize() = 0;
    // 处理业务逻辑
    virtual void processData() = 0;
    // 清理资源
    virtual void cleanup() = 0;

signals:
    // 数据更新信号
    void dataUpdated();
    // 错误处理信号
    void errorOccurred(const QString &message);

protected:
    // 数据验证方法
    bool validateData(const QVariant &data);
};

#endif // BASE_CONTROLLER_H