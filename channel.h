#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QJsonObject>

#include "dmr.h"
#define debug(x) qDebug()<<"channel:["<<__LINE__<<"]"<<__FUNCTION__<<"()"<<x
class channel : public QObject
{
    Q_OBJECT
public:
    explicit channel(QObject *parent = nullptr);
    ~channel();
    // 拷贝构造函数声明
    channel(const channel &other);

    // 拷贝赋值运算符声明
    channel& operator=(const channel &other);

    quint8 getStartBit1() const;
    void setStartBit1(quint8 newStartBit1);

    quint8 getStartBit2() const;
    void setStartBit2(quint8 newStartBit2);

    quint8 getStartBit3() const;
    void setStartBit3(quint8 newStartBit3);

    quint8 getStartBit4() const;
    void setStartBit4(quint8 newStartBit4);

    quint8 getSize() const;
    void setSize(quint8 newSize);

    quint8 getCommand() const;
    void setCommand(quint8 newCommand);

    quint8 getChannelHigh() const;
    void setChannelHigh(quint8 newChannelHigh);

    quint8 getChannelLow() const;
    void setChannelLow(quint8 newChannelLow);

    quint8 getVfoaMode() const;
    void setVfoaMode(quint8 newVfoaMode);

    quint8 getVfobMode() const;
    void setVfobMode(quint8 newVfobMode);



    quint8 getEmitYayin() const;
    void setEmitYayin(quint8 newEmitYayin);

    quint8 getReceiveYayin() const;
    void setReceiveYayin(quint8 newReceiveYayin);

    QByteArray getChannelName() const;
    void setChannelName(const QByteArray &newChannelName);

    quint8 getCrcHigh() const;
    void setCrcHigh(quint8 newCrcHigh);

    quint8 getCrcLow() const;
    void setCrcLow(quint8 newCrcLow);

    // 将要发送的写入数据打包为QByteArray
    QByteArray toWriteFrequencyData();
    // 将电台写入回复的数据拆分到类中
    void radioWriteResponseToObj(QByteArray);
    // 将要发送的读取命令打包为QByteArray
    QByteArray toReadFrequencyData();
    // 将电台读取回复的数据拆分到类中
    void radioReadResponseToObj(QByteArray);

    quint8 getVfoaFrequency1() const;
    void setVfoaFrequency1(quint8 newVfoaFrequency1);

    quint8 getVfoaFrequency2() const;
    void setVfoaFrequency2(quint8 newVfoaFrequency2);

    quint8 getVfoaFrequency3() const;
    void setVfoaFrequency3(quint8 newVfoaFrequency3);

    quint8 getVfoaFrequency4() const;
    void setVfoaFrequency4(quint8 newVfoaFrequency4);

    quint8 getVfobFrequency1() const;
    void setVfobFrequency1(quint8 newVfobFrequency1);

    quint8 getVfobFrequency2() const;
    void setVfobFrequency2(quint8 newVfobFrequency2);

    quint8 getVfobFrequency3() const;
    void setVfobFrequency3(quint8 newVfobFrequency3);

    quint8 getVfobFrequency4() const;
    void setVfobFrequency4(quint8 newVfobFrequency4);

    QByteArray preparePacketWithCRC();
    uint16_t CRC16Check(unsigned char *buf, unsigned char len);

    QString toString();

    QByteArray prepareWritePacketWithCRC();
    unsigned short getChannelID();

    QJsonObject toJSON();
    quint32 getVfoaFrequency();
    void setVfoaFrequency(quint32 newVfoaFrequency);

    quint32 getVfobFrequency() ;
    void setVfobFrequency(quint32 newVfobFrequency);

    QByteArray addCrc0x0B();
    bool verifyReadData(QByteArray data);
    DMR& getDmr();
    void setDmr(const DMR &newDmr);

private:
    quint8 startBit1;
    quint8 startBit2;
    quint8 startBit3;
    quint8 startBit4;
    quint8 size;
    quint8 command;
    quint8 channelHigh;
    quint8 channelLow;
    quint8 vfoaMode;
    quint8 vfobMode;

    quint32 vfoaFrequency;
    quint8 vfoaFrequency1;
    quint8 vfoaFrequency2;
    quint8 vfoaFrequency3;
    quint8 vfoaFrequency4;

    quint32 vfobFrequency;
    quint8 vfobFrequency1;
    quint8 vfobFrequency2;
    quint8 vfobFrequency3;
    quint8 vfobFrequency4;
    quint8 emitYayin;
    quint8 receiveYayin;
    QByteArray channelName;
    quint8 crcHigh;
    quint8 crcLow;

    DMR dmr;

    unsigned short channelID;
};

#endif // CHANNEL_H
