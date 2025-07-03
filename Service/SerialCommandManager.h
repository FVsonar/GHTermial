#ifndef SERIALCOMMANDMANAGER_H
#define SERIALCOMMANDMANAGER_H

#include <QObject>
#include <QTimer>
#include <QByteArray>
#include <functional>

class SerialPortManager;

class SerialCommandManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialCommandManager(SerialPortManager* serialManager, QObject *parent = nullptr);
    ~SerialCommandManager();

    // 发送命令并设置重发
    void sendCommand(const QByteArray &data, int commandType, std::function<void()> onSuccess = nullptr);
    
    // 停止所有定时器
    void stopAllTimers();
    
    // 重置重试计数器
    void resetRetryCount(int commandType);

signals:
    void commandTimeout(int commandType, int retryCount);
    void commandMaxRetriesReached(int commandType);

private slots:
    void onTimeout0x40();
    void onTimeout0x41();
    void onTimeout0x43();
    void onTimeout0x44();

private:
    static const int MAX_RETRY_COUNT = 3;
    static const int RETRY_INTERVAL = 200; // ms

    SerialPortManager* serialManager;
    
    // 定时器
    QTimer* retransmissionTimer0x40;
    QTimer* retransmissionTimer0x41;
    QTimer* retransmissionTimer0x43;
    QTimer* retransmissionTimer0x44;
    
    // 重试计数器
    int retryCount0x40;
    int retryCount0x41;
    int retryCount0x43;
    int retryCount0x44;
    
    // 当前命令数据
    QByteArray currentCommand0x40;
    QByteArray currentCommand0x41;
    QByteArray currentCommand0x43;
    QByteArray currentCommand0x44;
    
    // 成功回调
    std::function<void()> onSuccess0x40;
    std::function<void()> onSuccess0x41;
    std::function<void()> onSuccess0x43;
    std::function<void()> onSuccess0x44;
    
    void stopTimerSafe(QTimer* timer);
    QTimer* getTimerForCommand(int commandType);
    int& getRetryCountForCommand(int commandType);
    QByteArray& getCurrentCommandForType(int commandType);
    std::function<void()>& getSuccessCallbackForCommand(int commandType);
};

#endif // SERIALCOMMANDMANAGER_H 