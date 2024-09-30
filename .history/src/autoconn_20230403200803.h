#ifndef AUTOCONN_H
#define AUTOCONN_H

#include <QObject>
#include <QTimer>
class AutoConn  : public QObject
{
    Q_OBJECT
public:

 explicit AutoConn(QObject *parent = nullptr);

private:
    void GetSerialPortNames(void);

private slots:
    void handleTimeout(void);
    void checkDevice(void);

public slots:
    void startConnDevive(void);
    quint8 getconnState(void);
private:
    QStringList nameSerialPort;
    quint8 m_count;
    QTimer m_pTimer;
    QTimer m_rTimer;
    quint8 m_connstate;
public:
    bool m_isConnecSuccess;


};

#endif // AUTOCONN_H
