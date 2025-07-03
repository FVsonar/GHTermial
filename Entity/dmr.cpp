#include "dmr.h"

DMR::DMR(QObject *parent)
    : QObject{parent}
{
    startBit1 = 0xA5;
    startBit2 = 0xA5;
    startBit3 = 0xA5;
    startBit4 = 0xA5;
    size = 0;
    command = 0;
    channelHigh = 0;
    channelLow = 0;

    callFormat = 0;
    txCc = 0;
    rxCc = 0;
    slot = 0;

    callId1 = 0;
    callId2 = 0;
    callId3 = 0;
    callId4 = 0;

    ownId1 = 0;
    ownId2 = 0;
    ownId3 = 0;
    ownId4 = 0;

    chType = 0;

    rxCtcss = 0;
    txCtcss = 0;

    sqlevel = 0;
    spkgain = 0;
    dmrexist = 1;
    dmodGain = 0;
    scrEn = 0;

    scrSeed1 = 0;
    scrSeed2 = 0;

    chBsMode = 0;
    validat = 1;

    crcHigh = 0;
    crcLow = 0;
}

DMR::~DMR()
{

}
// 拷贝构造函数
DMR::DMR(const DMR &other): QObject(other.parent()), // 调用基类拷贝构造函数
    startBit1(other.startBit1),
    startBit2(other.startBit2),
    startBit3(other.startBit3),
    startBit4(other.startBit4),
    size(other.size),
    command(other.command),
    channelHigh(other.channelHigh),
    channelLow(other.channelLow),
    callFormat(other.callFormat),
    txCc(other.txCc),
    rxCc(other.rxCc),
    slot(other.slot),
    callId1(other.callId1),
    callId2(other.callId2),
    callId3(other.callId3),
    callId4(other.callId4),
    ownId1(other.ownId1),
    ownId2(other.ownId2),
    ownId3(other.ownId3),
    ownId4(other.ownId4),
    chType(other.chType),
    rxCtcss(other.rxCtcss),
    txCtcss(other.txCtcss),
    sqlevel(other.sqlevel),
    spkgain(other.spkgain),
    dmrexist(other.dmrexist),
    dmodGain(other.dmodGain),
    scrEn(other.scrEn),
    scrSeed1(other.scrSeed1),
    scrSeed2(other.scrSeed2),
    chBsMode(other.chBsMode),
    validat(other.validat),
    crcHigh(other.crcHigh),
    crcLow(other.crcLow),
    channelID(other.channelID),
    callID(other.callID),
    ownID(other.ownID),
    scrSend(other.scrSend)
{

}

DMR &DMR::operator=(const DMR &other)
{
    if (this != &other) { // 自我赋值检查
        // 复制所有成员变量
        startBit1 = other.startBit1;
        startBit2 = other.startBit2;
        startBit3 = other.startBit3;
        startBit4 = other.startBit4;
        size = other.size;
        command = other.command;
        channelHigh = other.channelHigh;
        channelLow = other.channelLow;
        callFormat = other.callFormat;
        txCc = other.txCc;
        rxCc = other.rxCc;
        slot = other.slot;
        callId1 = other.callId1;
        callId2 = other.callId2;
        callId3 = other.callId3;
        callId4 = other.callId4;
        ownId1 = other.ownId1;
        ownId2 = other.ownId2;
        ownId3 = other.ownId3;
        ownId4 = other.ownId4;
        chType = other.chType;
        rxCtcss = other.rxCtcss;
        txCtcss = other.txCtcss;
        sqlevel = other.sqlevel;
        spkgain = other.spkgain;
        dmrexist = other.dmrexist;
        dmodGain = other.dmodGain;
        scrEn = other.scrEn;
        scrSeed1 = other.scrSeed1;
        scrSeed2 = other.scrSeed2;
        chBsMode = other.chBsMode;
        validat = other.validat;
        crcHigh = other.crcHigh;
        crcLow = other.crcLow;
        channelID = other.channelID;
        callID = other.callID;
        ownID = other.ownID;
        scrSend = other.scrSend;
    }
    return *this;
}



quint8 DMR::getStartBit1() const
{
    return startBit1;
}

void DMR::setStartBit1(quint8 newStartBit1)
{
    startBit1 = newStartBit1;
}

quint8 DMR::getStartBit2() const
{
    return startBit2;
}

void DMR::setStartBit2(quint8 newStartBit2)
{
    startBit2 = newStartBit2;
}

quint8 DMR::getStartBit3() const
{
    return startBit3;
}

void DMR::setStartBit3(quint8 newStartBit3)
{
    startBit3 = newStartBit3;
}

quint8 DMR::getStartBit4() const
{
    return startBit4;
}

void DMR::setStartBit4(quint8 newStartBit4)
{
    startBit4 = newStartBit4;
}

quint8 DMR::getSize() const
{
    return size;
}

void DMR::setSize(quint8 newSize)
{
    size = newSize;
}

quint8 DMR::getCommand() const
{
    return command;
}

void DMR::setCommand(quint8 newCommand)
{
    command = newCommand;
}

quint8 DMR::getChannelHigh() const
{
    return channelHigh;
}

void DMR::setChannelHigh(quint8 newChannelHigh)
{
    channelHigh = newChannelHigh;
}

quint8 DMR::getChannelLow() const
{
    return channelLow;
}

void DMR::setChannelLow(quint8 newChannelLow)
{
    channelLow = newChannelLow;
}

quint8 DMR::getCallFormat() const
{
    return callFormat;
}

void DMR::setCallFormat(quint8 newCallFormat)
{
    callFormat = newCallFormat;
}

quint8 DMR::getTxCc() const
{
    return txCc;
}

void DMR::setTxCc(quint8 newTxCc)
{
    txCc = newTxCc;
}

quint8 DMR::getRxCc() const
{
    return rxCc;
}

void DMR::setRxCc(quint8 newRxCc)
{
    rxCc = newRxCc;
}

quint8 DMR::getSlot() const
{
    return slot;
}

void DMR::setSlot(quint8 newSlot)
{
    slot = newSlot;
}

quint8 DMR::getCallId1() const
{
    return callId1;
}

void DMR::setCallId1(quint8 newCallId1)
{
    callId1 = newCallId1;
}

quint8 DMR::getCallId2() const
{
    return callId2;
}

void DMR::setCallId2(quint8 newCallId2)
{
    callId2 = newCallId2;
}

quint8 DMR::getCallId3() const
{
    return callId3;
}

void DMR::setCallId3(quint8 newCallId3)
{
    callId3 = newCallId3;
}

quint8 DMR::getCallId4() const
{
    return callId4;
}

void DMR::setCallId4(quint8 newCallId4)
{
    callId4 = newCallId4;
}

quint8 DMR::getOwnId1() const
{
    return ownId1;
}

void DMR::setOwnId1(quint8 newOwnId1)
{
    ownId1 = newOwnId1;
}

quint8 DMR::getOwnId2() const
{
    return ownId2;
}

void DMR::setOwnId2(quint8 newOwnId2)
{
    ownId2 = newOwnId2;
}

quint8 DMR::getOwnId3() const
{
    return ownId3;
}

void DMR::setOwnId3(quint8 newOwnId3)
{
    ownId3 = newOwnId3;
}

quint8 DMR::getOwnId4() const
{
    return ownId4;
}

void DMR::setOwnId4(quint8 newOwnId4)
{
    ownId4 = newOwnId4;
}

quint8 DMR::getChType() const
{
    return chType;
}

void DMR::setChType(quint8 newChType)
{
    chType = newChType;
}

quint8 DMR::getRxCtcss() const
{
    return rxCtcss;
}

void DMR::setRxCtcss(quint8 newRxCtcss)
{
    rxCtcss = newRxCtcss;
}

quint8 DMR::getTxCtcss() const
{
    return txCtcss;
}

void DMR::setTxCtcss(quint8 newTxCtcss)
{
    txCtcss = newTxCtcss;
}

quint8 DMR::getSqlevel() const
{
    return sqlevel;
}

void DMR::setSqlevel(quint8 newSqlevel)
{
    sqlevel = newSqlevel;
}

quint8 DMR::getSpkgain() const
{
    return spkgain;
}

void DMR::setSpkgain(quint8 newSpkgain)
{
    spkgain = newSpkgain;
}

quint8 DMR::getDmrexist() const
{
    return dmrexist;
}

void DMR::setDmrexist(quint8 newDmrexist)
{
    dmrexist = newDmrexist;
}

quint8 DMR::getDmodGain() const
{
    return dmodGain;
}

void DMR::setDmodGain(quint8 newDmodGain)
{
    dmodGain = newDmodGain;
}

quint8 DMR::getScrEn() const
{
    return scrEn;
}

void DMR::setScrEn(quint8 newScrEn)
{
    scrEn = newScrEn;
}

quint8 DMR::getScrSeed1() const
{
    return scrSeed1;
}

void DMR::setScrSeed1(quint8 newScrSeed1)
{
    scrSeed1 = newScrSeed1;
}

quint8 DMR::getScrSeed2() const
{
    return scrSeed2;
}

void DMR::setScrSeed2(quint8 newScrSeed2)
{
    scrSeed2 = newScrSeed2;
}

quint8 DMR::getChBsMode() const
{
    return chBsMode;
}

void DMR::setChBsMode(quint8 newChBsMode)
{
    chBsMode = newChBsMode;
}

quint8 DMR::getValidat() const
{
    return validat;
}

void DMR::setValidat(quint8 newValidat)
{
    validat = newValidat;
}

quint8 DMR::getCrcHigh() const
{
    return crcHigh;
}

void DMR::setCrcHigh(quint8 newCrcHigh)
{
    crcHigh = newCrcHigh;
}

quint8 DMR::getCrcLow() const
{
    return crcLow;
}

void DMR::setCrcLow(quint8 newCrcLow)
{
    crcLow = newCrcLow;
}

unsigned short DMR::getChannelID()
{
    channelID = (getChannelHigh() << 8 ) | getChannelLow();
    return channelID;
}

/**
 *  给命令添加CRC
 */
void DMR::addCrc(QByteArray& packet){

    // 计算CRC CRC校验不含包头不含自身
    uint16_t crc = tool.CRC16Check(reinterpret_cast<unsigned char*>(packet.data()), packet.size());

    // 将CRC高低位分开加入到packet中
    packet.append((crc >> 8) & 0xFF); // CRC高
    packet.append(crc & 0xFF);        // CRC低

}

/**
 *  @param  QByteArray& 给它组装包头
 */
void DMR::addHead(QByteArray& data){
    data.prepend(0xa5);
    data.prepend(0xa5);
    data.prepend(0xa5);
    data.prepend(0xa5);
}

unsigned int DMR::getCallID()
{
    callID = (this->getCallId1() << 24)
             | (this->getCallId2() << 16)
             | (this->getCallId3() << 8)
             | this->getCallId4();
    return callID;
}

void DMR::setCallID(unsigned int newCallID)
{
    this->callId1 = static_cast<char>((newCallID >> 24) & 0xFF);
    this->callId2 = static_cast<char>((newCallID >> 16) & 0xFF);
    this->callId3 = static_cast<char>((newCallID >> 8) & 0xFF);
    this->callId4 = static_cast<char>(newCallID & 0xFF);
    callID = newCallID;
}

/**
 * 弃用，似乎不需要考虑字母+数字的情况
 */
void DMR::setCallID(const QString &input)
{
    unsigned int numericId = 0;

    //  检查输入是否为纯数字
    bool isNumeric = false;
    unsigned int pureNumber = input.toUInt(&isNumeric);

    if (isNumeric) {
        // 纯数字模式：直接使用，但限制范围
        numericId = qBound(1u, pureNumber, 16777215u); // 限制在 1~16777215
    } else {
        // 字母+数字模式：通过哈希转换为数字
        QByteArray bytes = input.toUtf8();
        unsigned int hash = 0;
        for (char c : bytes) {
            hash = (hash * 31) + c; // 简单哈希算法
        }
        numericId = (hash % 16777215) + 1; // 限制范围
    }

    // 存储数字和字节拆分
    this->callID = numericId;
    this->callId1 = static_cast<char>((numericId >> 24) & 0xFF);
    this->callId2 = static_cast<char>((numericId >> 16) & 0xFF);
    this->callId3 = static_cast<char>((numericId >> 8) & 0xFF);
    this->callId4 = static_cast<char>(numericId & 0xFF);
}

unsigned int DMR::getOwnID()
{
    ownID = (this->getOwnId1() << 24)
            | (this->getOwnId2() << 16)
            | (this->getOwnId3() << 8)
            | this->getOwnId4();
    return ownID;
}

void DMR::setOwnID(unsigned int newOwnID)
{
    this->ownId1 = static_cast<char>((newOwnID >> 24) & 0xFF);
    this->ownId2 = static_cast<char>((newOwnID >> 16) & 0xFF);
    this->ownId3 = static_cast<char>((newOwnID >> 8) & 0xFF);
    this->ownId4 = static_cast<char>(newOwnID & 0xFF);
    ownID = newOwnID;
}

unsigned short DMR::getScrSend()
{
    scrSend = (this->getScrSeed1() << 8)
              | this->getScrSeed2();
    return scrSend;
}

void DMR::setScrSend(unsigned short newScrSend)
{
    this->scrSeed1 = static_cast<char>((newScrSend >> 8) & 0xFF);
    this->scrSeed2 = static_cast<char>(newScrSend & 0xFF);
    scrSend = newScrSend;
}

QString DMR::toString(){
    return
    "startBit:"+QString::number(startBit1,16)+
    " "+QString::number(startBit2,16)+
    " "+QString::number(startBit3,16)+
    " "+QString::number(startBit4,16)+
    " , size:"+QString::number(size,16)+
    " , command:"+QString::number(command,16)+
    " , channel:"+QString::number(channelHigh,16)+
    " "+QString::number(channelLow,16)+
    " , callFormat:"+QString::number(callFormat,16)+
    " , txCc:"+QString::number(txCc,16)+
    " , rxCc:"+QString::number(rxCc,16)+
    " , slot"+QString::number(slot,16)+
    " , callId:"+QString::number(callId1,16)+
    " "+QString::number(callId2,16)+
    " "+QString::number(callId3,16)+
    " "+QString::number(callId4,16)+
    " , ownId"+QString::number(ownId1,16)+
    " "+QString::number(ownId2,16)+
    " "+QString::number(ownId3,16)+
    " "+QString::number(ownId4,16)+
    " , chType:"+QString::number(chType,16)+
    " , rxCtcss:"+QString::number(rxCtcss,16)+
    " , txCtcss:"+QString::number(txCtcss,16)+
    " , sqlevel:"+QString::number(sqlevel,16)+
    " , spkgain:"+QString::number(spkgain,16)+
    " , dmrexist:"+QString::number(dmrexist,16)+
    " , dmodGain:"+QString::number(dmodGain,16)+
    " , scrEn:"+QString::number(scrEn,16)+
    " , scrSeed:"+QString::number(scrSeed1,16)+
    " "+QString::number(scrSeed2,16)+
    " , chBsMode:"+QString::number(chBsMode,16)+
    " , validat:"+QString::number(validat,16)+
    " , crc:"+QString::number(crcHigh,16)+
    " "+QString::number(crcLow,16);
}

/**
 *  数据校验是否合法
 */
bool DMR::verifyReadData(QByteArray data)
{
    return tool.checkData(data);
}

/**
 *  0x44
 *  构建0x44 读取命令
 *  @return QByteArray  返回构建好的命令
 */
QByteArray DMR::buildReadData()
{
    QByteArray packet;

    packet.append(this->getSize());
    packet.append(this->getCommand());
    packet.append(this->getChannelHigh());
    packet.append(this->getChannelLow());

    addCrc(packet);

    addHead(packet);

    return packet;
}

/**
 *  0x43 0x44
 *  这两个命令的电台回复一致
 *  将QByteArray转化为DMR对象
 */
void DMR::dataToDMR(QByteArray data){
    this->setStartBit1(data[0]);
    this->setStartBit2(data[1]);
    this->setStartBit3(data[2]);
    this->setStartBit4(data[3]);

    this->setSize(data[4]);

    this->setCommand(data[5]);

    this->setChannelHigh(data[6]);
    this->setChannelLow(data[7]);

    this->setCallFormat(data[8]);

    this->setTxCc(data[9]);
    this->setRxCc(data[10]);

    this->setSlot(data[11]);

    this->setCallId1(data[12]);
    this->setCallId2(data[13]);
    this->setCallId3(data[14]);
    this->setCallId4(data[15]);

    this->setOwnId1(data[16]);
    this->setOwnId2(data[17]);
    this->setOwnId3(data[18]);
    this->setOwnId4(data[19]);

    this->setChType(data[20]);

    this->setRxCtcss(data[21]);
    this->setTxCtcss(data[22]);

    this->setSqlevel(data[23]);
    this->setSpkgain(data[24]);
    this->setDmrexist(data[25]);
    this->setDmodGain(data[26]);
    this->setScrEn(data[27]);

    this->setScrSeed1(data[28]);
    this->setScrSeed2(data[29]);

    this->setChBsMode(data[30]);
    this->setValidat(data[31]);

    this->setCrcHigh(data[32]);
    this->setCrcLow(data[33]);
}

/**
*   转化为QJsonObject
*   @return QJsonObject
*/
QJsonObject DMR::toJSON()
{
    QJsonObject obj;

    obj["channelHigh"] = this->getChannelHigh();
    obj["channelLow"] = this->getChannelLow();

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


/**
 *  0x43
 *  构建设置(写)DMR信道命令
 *  @return QByteArray  设置构建的命令
 */
QByteArray DMR::buildWriteData(){
    QByteArray packet;

    packet.append(this->getSize());
    packet.append(this->getCommand());

    packet.append(this->getChannelHigh());
    packet.append(this->getChannelLow());

    packet.append(this->getCallFormat());

    packet.append(this->getTxCc());
    packet.append(this->getRxCc());

    packet.append(this->getSlot());

    packet.append(this->getCallId1());
    packet.append(this->getCallId2());
    packet.append(this->getCallId3());
    packet.append(this->getCallId4());

    packet.append(this->getOwnId1());
    packet.append(this->getOwnId2());
    packet.append(this->getOwnId3());
    packet.append(this->getOwnId4());

    packet.append(this->getChType());

    packet.append(this->getRxCtcss());
    packet.append(this->getTxCtcss());

    packet.append(this->getSqlevel());
    packet.append(this->getSpkgain());
    packet.append(this->getDmrexist());
    packet.append(this->getDmodGain());

    packet.append(this->getScrEn());
    packet.append(this->getScrSeed1());
    packet.append(this->getScrSeed2());

    packet.append(this->getChBsMode());
    packet.append(this->getValidat());

    addCrc(packet);

    addHead(packet);

    return packet;

}
