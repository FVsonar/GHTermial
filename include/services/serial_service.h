#pragma once

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QQueue>
#include <QMutex>
#include <memory>

namespace GHTerminal {

struct SerialConfig {
    QString portName;
    int baudRate;
    int dataBits;
    QString parity;
    QString stopBits;
    QString flowControl;
    
    SerialConfig() : baudRate(9600), dataBits(8) {}
};

struct SerialCommand {
    QByteArray data;
    int timeout;
    int retryCount;
    std::function<void(const QByteArray&)> callback;
    std::function<void(const QString&)> errorCallback;
    
    SerialCommand() : timeout(5000), retryCount(3) {}
};

/**
 * @brief 串口通信服务
 * 
 * 提供串口连接、数据发送接收和命令队列管理
 */
class SerialService : public QObject
{
    Q_OBJECT

public:
    explicit SerialService(QObject *parent = nullptr);
    ~SerialService() override;

    /**
     * @brief 获取可用串口列表
     * @return 串口信息列表
     */
    QList<QSerialPortInfo> availablePorts() const;

    /**
     * @brief 连接串口
     * @param config 串口配置
     * @return 连接是否成功
     */
    bool connect(const SerialConfig &config);

    /**
     * @brief 断开连接
     */
    void disconnect();

    /**
     * @brief 检查是否已连接
     * @return 是否已连接
     */
    bool isConnected() const;

    /**
     * @brief 发送数据
     * @param data 要发送的数据
     * @return 发送是否成功
     */
    bool sendData(const QByteArray &data);

    /**
     * @brief 发送命令
     * @param command 命令数据
     * @param callback 成功回调
     * @param errorCallback 错误回调
     * @param timeout 超时时间(ms)
     * @param retryCount 重试次数
     */
    void sendCommand(const QByteArray &command,
                    std::function<void(const QByteArray&)> callback = nullptr,
                    std::function<void(const QString&)> errorCallback = nullptr,
                    int timeout = 5000,
                    int retryCount = 3);

    /**
     * @brief 清空命令队列
     */
    void clearCommandQueue();

    /**
     * @brief 获取当前串口配置
     * @return 串口配置
     */
    SerialConfig currentConfig() const;

    /**
     * @brief 设置接收超时
     * @param timeout 超时时间(ms)
     */
    void setReceiveTimeout(int timeout);

    /**
     * @brief 获取接收超时
     * @return 超时时间(ms)
     */
    int receiveTimeout() const;

    /**
     * @brief 启用/禁用自动重连
     * @param enable 是否启用
     */
    void setAutoReconnect(bool enable);

    /**
     * @brief 获取自动重连状态
     * @return 是否启用自动重连
     */
    bool autoReconnect() const;

    /**
     * @brief 获取连接状态
     * @return 连接状态字符串
     */
    QString connectionStatus() const;

    /**
     * @brief 获取错误信息
     * @return 错误信息
     */
    QString errorString() const;

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);
    void errorOccurred(const QString &error);
    void connectionStatusChanged(const QString &status);

private slots:
    void onSerialPortError(QSerialPort::SerialPortError error);
    void onDataReceived();
    void onCommandTimeout();
    void onReconnectTimer();

private:
    void processCommandQueue();
    void sendNextCommand();
    void handleCommandResponse(const QByteArray &response);
    void handleCommandError(const QString &error);
    void startReconnectTimer();
    void stopReconnectTimer();

private:
    std::unique_ptr<QSerialPort> m_serialPort;
    SerialConfig m_config;
    bool m_isConnected;
    bool m_autoReconnect;
    int m_receiveTimeout;
    
    QQueue<SerialCommand> m_commandQueue;
    SerialCommand m_currentCommand;
    QTimer m_commandTimer;
    QTimer m_reconnectTimer;
    QMutex m_mutex;
    
    int m_retryCount;
    QString m_lastError;
};

} // namespace GHTerminal 