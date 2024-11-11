#ifndef AUTOCONN_H
#define AUTOCONN_H

#include <QObject>
#include <QTimer>
class AutoConn  : public QObject
{
    Q_OBJECT
public:

    explicit AutoConn(QObject *parent = nullptr);

    // 表示连接是否成功的成员变量
    bool m_isConnecSuccess;

private:

    // 获取可用的串口名称
    void GetSerialPortNames(void);

    QStringList nameSerialPort; // 保存可用的串口名称
    quint8 m_count; // 用于计数的变量
    QTimer m_pTimer;    // 发送定时器，用于控制发送数据的定时
    QTimer m_rTimer;    // 接收定时器，用于控制接收数据的定时
    quint8 m_connstate; // 连接状态变量，表示当前的连接状态

private slots:
    // 定时器超时处理函数
    void handleTimeout(void);
    // 检查设备连接状态
    void checkDevice(void);

public slots:
    // 开始连接设备
    void startConnDevive(void);
    // 获取当前连接状态
    quint8 getconnState(void);

};

#endif // AUTOCONN_H
