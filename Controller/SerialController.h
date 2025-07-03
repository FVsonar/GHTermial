#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>
#include "Entity/channel.h"
#include "Entity/dmr.h"
#include "Tools/serialporttools.h"

class SerialController : public QObject
{
    Q_OBJECT

public:
    explicit SerialController(QObject *parent = nullptr);

    void handleCommand0x40(channel& newChannel);
    void handleCommand0x41(channel& newChannel);
    void handleCommand0x43(DMR& newDmr);
    void handleCommand0x44(DMR& newDmr);

private:
    QSerialPort *currentSerialport;
    QTimer *retransmissionTimer0x40;
    QTimer *retransmissionTimer0x41;
    QTimer *retransmissionTimer0x43;
    QTimer *retransmissionTimer0x44;
    SerialPortTools serialPortTool;
};

#endif // SERIALCONTROLLER_H