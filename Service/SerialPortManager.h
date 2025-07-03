#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QList>

class SerialPortManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortManager(QObject *parent = nullptr);
    ~SerialPortManager();

    bool openPort(const QSerialPortInfo &info);
    void closePort();
    bool isOpen() const;
    void writeData(const QByteArray &data);
    void setDTR(bool set);
    void setRTS(bool set);
    QSerialPort* getSerialPort();

signals:
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &error);
    void portOpened();
    void portClosed();

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort serialPort;
};

#endif // SERIALPORTMANAGER_H 