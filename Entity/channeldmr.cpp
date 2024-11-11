#include "channeldmr.h"


ChannelDmr::ChannelDmr()
{}

quint8 ChannelDmr::getChannelHigh() const
{
    return channelHigh;
}

void ChannelDmr::setChannelHigh(quint8 newChannelHigh)
{
    channelHigh = newChannelHigh;
}

quint8 ChannelDmr::getChannelLow() const
{
    return channelLow;
}

void ChannelDmr::setChannelLow(quint8 newChannelLow)
{
    channelLow = newChannelLow;
}

QByteArray ChannelDmr::getChannelName() const
{
    return channelName;
}

void ChannelDmr::setChannelName(const QByteArray &newChannelName)
{
    channelName = newChannelName;
}

quint32 ChannelDmr::getVfoaFrequency() const
{
    return vfoaFrequency;
}

void ChannelDmr::setVfoaFrequency(quint32 newVfoaFrequency)
{
    vfoaFrequency = newVfoaFrequency;
}

quint8 ChannelDmr::getVfoaFrequency1() const
{
    return vfoaFrequency1;
}

void ChannelDmr::setVfoaFrequency1(quint8 newVfoaFrequency1)
{
    vfoaFrequency1 = newVfoaFrequency1;
}

quint8 ChannelDmr::getVfoaFrequency2() const
{
    return vfoaFrequency2;
}

void ChannelDmr::setVfoaFrequency2(quint8 newVfoaFrequency2)
{
    vfoaFrequency2 = newVfoaFrequency2;
}

quint8 ChannelDmr::getVfoaFrequency3() const
{
    return vfoaFrequency3;
}

void ChannelDmr::setVfoaFrequency3(quint8 newVfoaFrequency3)
{
    vfoaFrequency3 = newVfoaFrequency3;
}

quint8 ChannelDmr::getVfoaFrequency4() const
{
    return vfoaFrequency4;
}

void ChannelDmr::setVfoaFrequency4(quint8 newVfoaFrequency4)
{
    vfoaFrequency4 = newVfoaFrequency4;
}

quint32 ChannelDmr::getVfobFrequency() const
{
    return vfobFrequency;
}

void ChannelDmr::setVfobFrequency(quint32 newVfobFrequency)
{
    vfobFrequency = newVfobFrequency;
}

quint8 ChannelDmr::getVfobFrequency1() const
{
    return vfobFrequency1;
}

void ChannelDmr::setVfobFrequency1(quint8 newVfobFrequency1)
{
    vfobFrequency1 = newVfobFrequency1;
}

quint8 ChannelDmr::getVfobFrequency2() const
{
    return vfobFrequency2;
}

void ChannelDmr::setVfobFrequency2(quint8 newVfobFrequency2)
{
    vfobFrequency2 = newVfobFrequency2;
}

quint8 ChannelDmr::getVfobFrequency3() const
{
    return vfobFrequency3;
}

void ChannelDmr::setVfobFrequency3(quint8 newVfobFrequency3)
{
    vfobFrequency3 = newVfobFrequency3;
}

quint8 ChannelDmr::getVfobFrequency4() const
{
    return vfobFrequency4;
}

void ChannelDmr::setVfobFrequency4(quint8 newVfobFrequency4)
{
    vfobFrequency4 = newVfobFrequency4;
}

quint8 ChannelDmr::getVfoaMode() const
{
    return vfoaMode;
}

void ChannelDmr::setVfoaMode(quint8 newVfoaMode)
{
    vfoaMode = newVfoaMode;
}

quint8 ChannelDmr::getVfobMode() const
{
    return vfobMode;
}

void ChannelDmr::setVfobMode(quint8 newVfobMode)
{
    vfobMode = newVfobMode;
}

quint8 ChannelDmr::getEmitYayin() const
{
    return emitYayin;
}

void ChannelDmr::setEmitYayin(quint8 newEmitYayin)
{
    emitYayin = newEmitYayin;
}

quint8 ChannelDmr::getReceiveYayin() const
{
    return receiveYayin;
}

void ChannelDmr::setReceiveYayin(quint8 newReceiveYayin)
{
    receiveYayin = newReceiveYayin;
}

quint8 ChannelDmr::getCallFormat() const
{
    return callFormat;
}

void ChannelDmr::setCallFormat(quint8 newCallFormat)
{
    callFormat = newCallFormat;
}

quint8 ChannelDmr::getTxCc() const
{
    return txCc;
}

void ChannelDmr::setTxCc(quint8 newTxCc)
{
    txCc = newTxCc;
}

quint8 ChannelDmr::getRxCc() const
{
    return rxCc;
}

void ChannelDmr::setRxCc(quint8 newRxCc)
{
    rxCc = newRxCc;
}

quint8 ChannelDmr::getSlot() const
{
    return slot;
}

void ChannelDmr::setSlot(quint8 newSlot)
{
    slot = newSlot;
}

quint8 ChannelDmr::getCallId1() const
{
    return callId1;
}

void ChannelDmr::setCallId1(quint8 newCallId1)
{
    callId1 = newCallId1;
}

quint8 ChannelDmr::getCallId2() const
{
    return callId2;
}

void ChannelDmr::setCallId2(quint8 newCallId2)
{
    callId2 = newCallId2;
}

quint8 ChannelDmr::getCallId3() const
{
    return callId3;
}

void ChannelDmr::setCallId3(quint8 newCallId3)
{
    callId3 = newCallId3;
}

quint8 ChannelDmr::getCallId4() const
{
    return callId4;
}

void ChannelDmr::setCallId4(quint8 newCallId4)
{
    callId4 = newCallId4;
}

quint8 ChannelDmr::getOwnId1() const
{
    return ownId1;
}

void ChannelDmr::setOwnId1(quint8 newOwnId1)
{
    ownId1 = newOwnId1;
}

quint8 ChannelDmr::getOwnId2() const
{
    return ownId2;
}

void ChannelDmr::setOwnId2(quint8 newOwnId2)
{
    ownId2 = newOwnId2;
}

quint8 ChannelDmr::getOwnId3() const
{
    return ownId3;
}

void ChannelDmr::setOwnId3(quint8 newOwnId3)
{
    ownId3 = newOwnId3;
}

quint8 ChannelDmr::getOwnId4() const
{
    return ownId4;
}

void ChannelDmr::setOwnId4(quint8 newOwnId4)
{
    ownId4 = newOwnId4;
}

quint8 ChannelDmr::getChType() const
{
    return chType;
}

void ChannelDmr::setChType(quint8 newChType)
{
    chType = newChType;
}

quint8 ChannelDmr::getRxCtcss() const
{
    return rxCtcss;
}

void ChannelDmr::setRxCtcss(quint8 newRxCtcss)
{
    rxCtcss = newRxCtcss;
}

quint8 ChannelDmr::getTxCtcss() const
{
    return txCtcss;
}

void ChannelDmr::setTxCtcss(quint8 newTxCtcss)
{
    txCtcss = newTxCtcss;
}

quint8 ChannelDmr::getSqlevel() const
{
    return sqlevel;
}

void ChannelDmr::setSqlevel(quint8 newSqlevel)
{
    sqlevel = newSqlevel;
}

quint8 ChannelDmr::getSpkgain() const
{
    return spkgain;
}

void ChannelDmr::setSpkgain(quint8 newSpkgain)
{
    spkgain = newSpkgain;
}

quint8 ChannelDmr::getDmodGain() const
{
    return dmodGain;
}

void ChannelDmr::setDmodGain(quint8 newDmodGain)
{
    dmodGain = newDmodGain;
}

quint8 ChannelDmr::getScrEn() const
{
    return scrEn;
}

void ChannelDmr::setScrEn(quint8 newScrEn)
{
    scrEn = newScrEn;
}

quint8 ChannelDmr::getScrSeed1() const
{
    return scrSeed1;
}

void ChannelDmr::setScrSeed1(quint8 newScrSeed1)
{
    scrSeed1 = newScrSeed1;
}

quint8 ChannelDmr::getScrSeed2() const
{
    return scrSeed2;
}

void ChannelDmr::setScrSeed2(quint8 newScrSeed2)
{
    scrSeed2 = newScrSeed2;
}

quint8 ChannelDmr::getChBsMode() const
{
    return chBsMode;
}

void ChannelDmr::setChBsMode(quint8 newChBsMode)
{
    chBsMode = newChBsMode;
}

unsigned short ChannelDmr::getChannelID()
{
    return (getChannelHigh() << 8 ) | getChannelLow();
}

/**
 *  组合channel对象和dmr对象为本类对象
 *  @param  channel
 *  @param  DMR
 *  @return ChannelDmr
 */
void ChannelDmr::buildChannelDmr(channel channelTemp,DMR dmrTemp){
    /* channel */
    this->setChannelHigh(channelTemp.getChannelHigh());
    this->setChannelLow(channelTemp.getChannelLow());

    this->setChannelName(channelTemp.getChannelName());

    this->setVfoaFrequency1(channelTemp.getVfoaFrequency1());
    this->setVfoaFrequency2(channelTemp.getVfoaFrequency2());
    this->setVfoaFrequency3(channelTemp.getVfoaFrequency3());
    this->setVfoaFrequency4(channelTemp.getVfoaFrequency4());

    this->setVfobFrequency1(channelTemp.getVfobFrequency1());
    this->setVfobFrequency2(channelTemp.getVfobFrequency2());
    this->setVfobFrequency3(channelTemp.getVfobFrequency3());
    this->setVfobFrequency4(channelTemp.getVfobFrequency4());

    this->setVfoaMode(channelTemp.getVfoaMode());
    this->setVfobMode(channelTemp.getVfobMode());

    this->setEmitYayin(channelTemp.getEmitYayin());
    this->setReceiveYayin(channelTemp.getReceiveYayin());

    /* dmr */
    this->setCallFormat(dmrTemp.getCallFormat());

    this->setCallId1(dmrTemp.getCallId1());
    this->setCallId2(dmrTemp.getCallId2());
    this->setCallId3(dmrTemp.getCallId3());
    this->setCallId4(dmrTemp.getCallId4());

    this->setOwnId1(dmrTemp.getOwnId1());
    this->setOwnId2(dmrTemp.getOwnId2());
    this->setOwnId3(dmrTemp.getOwnId3());
    this->setOwnId4(dmrTemp.getOwnId4());

    this->setChType(dmrTemp.getChType());

    this->setRxCtcss(dmrTemp.getRxCtcss());
    this->setTxCtcss(dmrTemp.getTxCtcss());

    this->setSqlevel(dmrTemp.getSqlevel());
    this->setSpkgain(dmrTemp.getSpkgain());

    this->setDmodGain(dmrTemp.getDmodGain());
    this->setScrEn(dmrTemp.getScrEn());

    this->setScrSeed1(dmrTemp.getScrSeed1());
    this->setScrSeed2(dmrTemp.getScrSeed2());

    this->setChBsMode(dmrTemp.getChBsMode());
}

/**
 *  返回一行数据转化的json对象
 *  @return  QJsonObject
 */
QJsonObject ChannelDmr::toJSON()
{
    QJsonObject obj;
    /* channel */
    obj["channelHigh"] = this->getChannelHigh();
    obj["channelLow"] = this->getChannelLow();

    obj["channelName"] = QString::fromUtf8(this->getChannelName());

    obj["vfoaFrequency1"] = this->getVfoaFrequency1();
    obj["vfoaFrequency2"] = this->getVfoaFrequency2();
    obj["vfoaFrequency3"] = this->getVfoaFrequency3();
    obj["vfoaFrequency4"] = this->getVfoaFrequency4();

    obj["vfobFrequency1"] = this->getVfobFrequency1();
    obj["vfobFrequency2"] = this->getVfobFrequency2();
    obj["vfobFrequency3"] = this->getVfobFrequency3();
    obj["vfobFrequency4"] = this->getVfobFrequency4();

    obj["vfoaMode"] = this->getVfoaMode();
    obj["vfobMode"] = this->getVfobMode();

    obj["emitYayin"] = this->getEmitYayin();
    obj["receiveYayin"] = this->getReceiveYayin();

    /* dmr */
    obj["callFormat"] = this->getCallFormat();

    obj["txCc"] = this->getTxCc();
    obj["rxCc"] = this->getRxCc();

    obj["slot"] = this->getSlot();

    obj["callId1"] = this->getCallId1();
    obj["callId2"] = this->getCallId2();
    obj["callId3"] = this->getCallId3();
    obj["callId4"] = this->getCallId4();

    obj["ownId1"] = this->getOwnId1();
    obj["ownId2"] = this->getOwnId2();
    obj["ownId3"] = this->getOwnId3();
    obj["ownId4"] = this->getOwnId4();

    obj["chType"] = this->getChType();

    obj["rxCtcss"] = this->getRxCtcss();
    obj["txCtcss"] = this->getTxCtcss();

    obj["sqlevel"] = this->getSqlevel();
    obj["spkgain"] = this->getSpkgain();
    obj["dmodGain"] = this->getDmodGain();
    obj["scrEn"] = this->getScrEn();

    obj["scrSeed1"] = this->getScrSeed1();
    obj["scrSeed2"] = this->getScrSeed2();

    obj["chBsMode"] = this->getChBsMode();

    return obj;
}
