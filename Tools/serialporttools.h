#ifndef SERIALPORTTOOLS_H
#define SERIALPORTTOOLS_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "Entity/channel.h"
#include "Entity/dmr.h"
#include "Service/channel_service.h"
#include "Service/dmr_service.h"

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);


    // 返回一个初始化后的Serialport
    void initSerialport(QSerialPortInfo &currentSerialportInfo,QSerialPort &currentSerialport);

    void readOne(channel &newChannel, QSerialPort &currentSerialport);
    void sendOneReadData(QSerialPort &currentSerialport);
    void takeFirst40ListWrite(channel &channelWrite, QList<channel> *readySend40ChannelList, QSerialPort &currentSerialport);
    void takeFirst41ListWrite(channel &channelRead, QList<channel> *readySend41ChannelList, QSerialPort &currentSerialport);
    void takeFirst43ListWrite(DMR &dmr, QList<DMR> *readySend43ChannelList, QSerialPort &currentSerialport);
    void takeFirst44ListWrite(DMR &dmr, QList<DMR> *readySend44ChannelList, QSerialPort &currentSerialport);


    bool serialPortReadyRead(QByteArray &data, channel &lastChannel, QSerialPort &currentSerialport);
private:
    Channel_Service channel_service;
    Dmr_Service dmr_service;


signals:
};

#endif // SERIALPORTTOOLS_H
