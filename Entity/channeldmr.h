#ifndef CHANNELDMR_H
#define CHANNELDMR_H

#include <QObject>
#include <QJsonObject>
#include "Entity/channel.h"
#include "Entity/dmr.h"

class ChannelDmr
{

public:
    explicit ChannelDmr();

    quint8 getChannelHigh() const;
    void setChannelHigh(quint8 newChannelHigh);
    quint8 getChannelLow() const;
    void setChannelLow(quint8 newChannelLow);
    QByteArray getChannelName() const;
    void setChannelName(const QByteArray &newChannelName);
    quint32 getVfoaFrequency() const;
    void setVfoaFrequency(quint32 newVfoaFrequency);
    quint8 getVfoaFrequency1() const;
    void setVfoaFrequency1(quint8 newVfoaFrequency1);
    quint8 getVfoaFrequency2() const;
    void setVfoaFrequency2(quint8 newVfoaFrequency2);
    quint8 getVfoaFrequency3() const;
    void setVfoaFrequency3(quint8 newVfoaFrequency3);
    quint8 getVfoaFrequency4() const;
    void setVfoaFrequency4(quint8 newVfoaFrequency4);
    quint32 getVfobFrequency() const;
    void setVfobFrequency(quint32 newVfobFrequency);
    quint8 getVfobFrequency1() const;
    void setVfobFrequency1(quint8 newVfobFrequency1);
    quint8 getVfobFrequency2() const;
    void setVfobFrequency2(quint8 newVfobFrequency2);
    quint8 getVfobFrequency3() const;
    void setVfobFrequency3(quint8 newVfobFrequency3);
    quint8 getVfobFrequency4() const;
    void setVfobFrequency4(quint8 newVfobFrequency4);
    quint8 getVfoaMode() const;
    void setVfoaMode(quint8 newVfoaMode);
    quint8 getVfobMode() const;
    void setVfobMode(quint8 newVfobMode);
    quint8 getEmitYayin() const;
    void setEmitYayin(quint8 newEmitYayin);
    quint8 getReceiveYayin() const;
    void setReceiveYayin(quint8 newReceiveYayin);
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
    unsigned short getChannelID();

    QJsonObject toJSON();
    void buildChannelDmr(channel channelTemp, DMR dmrTemp);

signals:

private:
    /* channel */
    quint8 channelHigh; // channel
    quint8 channelLow;

    QByteArray channelName; // name

    quint32 vfoaFrequency;  // VFOA频率
    quint8 vfoaFrequency1;
    quint8 vfoaFrequency2;
    quint8 vfoaFrequency3;
    quint8 vfoaFrequency4;

    quint32 vfobFrequency;  // VFOB频率
    quint8 vfobFrequency1;
    quint8 vfobFrequency2;
    quint8 vfobFrequency3;
    quint8 vfobFrequency4;

    quint8 vfoaMode;    // VFA_MODE
    quint8 vfobMode;    // VFB_MODE

    quint8 emitYayin;       // T_CTCSS
    quint8 receiveYayin;    // R_CTCSS

    /* dmr */
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

    quint8 dmodGain;

    quint8 scrEn;

    quint8 scrSeed1;
    quint8 scrSeed2;

    quint8 chBsMode;


};

#endif // CHANNELDMR_H
