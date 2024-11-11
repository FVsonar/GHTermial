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

    // 保存可用的串口名称
    QStringList nameSerialPort;
    // 用于计数的变量
    quint8 m_count;
    // 发送定时器，用于控制发送数据的定时
    QTimer m_pTimer;
    // 接收定时器，用于控制接收数据的定时
    QTimer m_rTimer;
    // 连接状态变量，表示当前的连接状态
    quint8 m_connstate;

private slots:
    void handleTimeout(void);
    void checkDevice(void);

public slots:
    void startConnDevive(void);
    quint8 getconnState(void);

};

#endif // AUTOCONN_H
