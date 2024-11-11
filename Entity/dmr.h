#ifndef DMR_H
#define DMR_H

#include <QObject>
#include <QJsonObject>
#include "Tools/tools.h"

class DMR : public QObject
{
    Q_OBJECT
public:
    explicit DMR(QObject *parent = nullptr);
    ~DMR();

    // 拷贝构造函数声明
    DMR(const DMR &other);
    // 拷贝赋值运算符声明
    DMR& operator=(const DMR &other);

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
    quint8 getCallFormat() const;
    void setCallFormat(quint8 newCallFormat);
    quint8 getTxCc() const;
    void setTxCc(quint8 newTxCc);
    quint8 getRxCc() const;
    void setRxCc(quint8 newRxCc);
    quint8 getSlot() const;
    void setSlot(quint8 newSlot);
    quint8 getCallId1() const;
    void setCallId1(quint8 newCallId1);
    quint8 getCallId2() const;
    void setCallId2(quint8 newCallId2);
    quint8 getCallId3() const;
    void setCallId3(quint8 newCallId3);
    quint8 getCallId4() const;
    void setCallId4(quint8 newCallId4);
    quint8 getOwnId1() const;
    void setOwnId1(quint8 newOwnId1);
    quint8 getOwnId2() const;
    void setOwnId2(quint8 newOwnId2);
    quint8 getOwnId3() const;
    void setOwnId3(quint8 newOwnId3);
    quint8 getOwnId4() const;
    void setOwnId4(quint8 newOwnId4);
    quint8 getChType() const;
    void setChType(quint8 newChType);
    quint8 getRxCtcss() const;
    void setRxCtcss(quint8 newRxCtcss);
    quint8 getTxCtcss() const;
    void setTxCtcss(quint8 newTxCtcss);
    quint8 getSqlevel() const;
    void setSqlevel(quint8 newSqlevel);
    quint8 getSpkgain() const;
    void setSpkgain(quint8 newSpkgain);
    quint8 getDmrexist() const;
    void setDmrexist(quint8 newDmrexist);
    quint8 getDmodGain() const;
    void setDmodGain(quint8 newDmodGain);
    quint8 getScrEn() const;
    void setScrEn(quint8 newScrEn);
    quint8 getScrSeed1() const;
    void setScrSeed1(quint8 newScrSeed1);
    quint8 getScrSeed2() const;
    void setScrSeed2(quint8 newScrSeed2);
    quint8 getChBsMode() const;
    void setChBsMode(quint8 newChBsMode);
    quint8 getValidat() const;
    void setValidat(quint8 newValidat);
    quint8 getCrcHigh() const;
    void setCrcHigh(quint8 newCrcHigh);
    quint8 getCrcLow() const;
    void setCrcLow(quint8 newCrcLow);

    unsigned short getChannelID();

    // 构建读取命令
    QByteArray buildReadData();

    void addCrc(QByteArray &packet);

    void dataToDMR(QByteArray data);
    QJsonObject toJSON();
    QByteArray buildWriteData();
    void addHead(QByteArray &data);
    unsigned int getCallID();
    void setCallID(unsigned int newCallID);

    unsigned int getOwnID();
    void setOwnID(unsigned int newOwnID);

    unsigned short getScrSend() ;
    void setScrSend(unsigned short newScrSend);

    QString toString();
    bool verifyReadData(QByteArray data);  // 校验数据是否正确
private:
    Tools tool;

    quint8 startBit1;
    quint8 startBit2;
    quint8 startBit3;
    quint8 startBit4;
    quint8 size;
    quint8 command;
    quint8 channelHigh;
    quint8 channelLow;

    quint8 callFormat;
    quint8 txCc;
    quint8 rxCc;
    quint8 slot;

    quint8 callId1;
    quint8 callId2;
    quint8 callId3;
    quint8 callId4;

    quint8 ownId1;
    quint8 ownId2;
    quint8 ownId3;
    quint8 ownId4;

    quint8 chType;

    quint8 rxCtcss;
    quint8 txCtcss;

    quint8 sqlevel;
    quint8 spkgain;
    quint8 dmrexist;
    quint8 dmodGain;
    quint8 scrEn;

    quint8 scrSeed1;
    quint8 scrSeed2;

    quint8 chBsMode;
    quint8 validat;

    quint8 crcHigh;
    quint8 crcLow;

    unsigned short channelID;
    unsigned int callID;
    unsigned int ownID;
    unsigned short scrSend;
signals:
};

#endif // DMR_H
