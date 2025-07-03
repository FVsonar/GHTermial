#include "channel.h"
#include <QDebug>

channel::channel(QObject *parent)
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
    vfoaMode = 0;
    vfobMode = 0;
    vfoaFrequency1 = 0;
    vfoaFrequency2 = 0;
    vfoaFrequency3 = 0;
    vfoaFrequency4 = 0;
    vfobFrequency1 = 0;
    vfobFrequency2 = 0;
    vfobFrequency3 = 0;
    vfobFrequency4 = 0;
    emitYayin = 0;
    receiveYayin = 0;
    channelName = "RENAME";
    crcHigh = 0;
    crcLow = 0;
}
/* 析构 */
channel::~channel(){

}
channel::channel(const channel &other)
    : QObject(other.parent()) // 复制父对象
{
    startBit1 = other.startBit1;
    startBit2 = other.startBit2;
    startBit3 = other.startBit3;
    startBit4 = other.startBit4;
    size = other.size;
    command = other.command;
    channelHigh = other.channelHigh;
    channelLow = other.channelLow;
    vfoaMode = other.vfoaMode;
    vfobMode = other.vfobMode;
    vfoaFrequency1 = other.vfoaFrequency1;
    vfoaFrequency2 = other.vfoaFrequency2;
    vfoaFrequency3 = other.vfoaFrequency3;
    vfoaFrequency4 = other.vfoaFrequency4;
    vfobFrequency1 = other.vfobFrequency1;
    vfobFrequency2 = other.vfobFrequency2;
    vfobFrequency3 = other.vfobFrequency3;
    vfobFrequency4 = other.vfobFrequency4;
    emitYayin = other.emitYayin;
    receiveYayin = other.receiveYayin;
    channelName = other.channelName; // QByteArray 的复制
    crcHigh = other.crcHigh;
    crcLow = other.crcLow;
}

// 拷贝赋值运算符实现
channel& channel::operator=(const channel &other)
{
    if (this != &other) {
        startBit1 = other.startBit1;
        startBit2 = other.startBit2;
        startBit3 = other.startBit3;
        startBit4 = other.startBit4;
        size = other.size;
        command = other.command;
        channelHigh = other.channelHigh;
        channelLow = other.channelLow;
        vfoaMode = other.vfoaMode;
        vfobMode = other.vfobMode;
        vfoaFrequency1 = other.vfoaFrequency1;
        vfoaFrequency2 = other.vfoaFrequency2;
        vfoaFrequency3 = other.vfoaFrequency3;
        vfoaFrequency4 = other.vfoaFrequency4;
        vfobFrequency1 = other.vfobFrequency1;
        vfobFrequency2 = other.vfobFrequency2;
        vfobFrequency3 = other.vfobFrequency3;
        vfobFrequency4 = other.vfobFrequency4;
        emitYayin = other.emitYayin;
        receiveYayin = other.receiveYayin;
        channelName = other.channelName; // QByteArray 的复制
        crcHigh = other.crcHigh;
        crcLow = other.crcLow;
    }
    return *this;
}

quint8 channel::getStartBit1() const
{
    return startBit1;
}

void channel::setStartBit1(quint8 newStartBit1)
{
    startBit1 = newStartBit1;
}

quint8 channel::getStartBit2() const
{
    return startBit2;
}

void channel::setStartBit2(quint8 newStartBit2)
{
    startBit2 = newStartBit2;
}

quint8 channel::getStartBit3() const
{
    return startBit3;
}

void channel::setStartBit3(quint8 newStartBit3)
{
    startBit3 = newStartBit3;
}

quint8 channel::getStartBit4() const
{
    return startBit4;
}

void channel::setStartBit4(quint8 newStartBit4)
{
    startBit4 = newStartBit4;
}

quint8 channel::getSize() const
{
    return size;
}

void channel::setSize(quint8 newSize)
{
    size = newSize;
}

quint8 channel::getCommand() const
{
    return command;
}

void channel::setCommand(quint8 newCommand)
{
    command = newCommand;
}

quint8 channel::getChannelHigh() const
{
    return channelHigh;
}

void channel::setChannelHigh(quint8 newChannelHigh)
{
    channelHigh = newChannelHigh;
}

quint8 channel::getChannelLow() const
{
    return channelLow;
}

void channel::setChannelLow(quint8 newChannelLow)
{
    channelLow = newChannelLow;
}

quint8 channel::getVfoaMode() const
{
    return vfoaMode;
}

void channel::setVfoaMode(quint8 newVfoaMode)
{
    vfoaMode = newVfoaMode;
}

quint8 channel::getVfobMode() const
{
    return vfobMode;
}

void channel::setVfobMode(quint8 newVfobMode)
{
    vfobMode = newVfobMode;
}


quint8 channel::getEmitYayin() const
{
    return emitYayin;
}

void channel::setEmitYayin(quint8 newEmitYayin)
{
    emitYayin = newEmitYayin;
}

quint8 channel::getReceiveYayin() const
{
    return receiveYayin;
}

void channel::setReceiveYayin(quint8 newReceiveYayin)
{
    receiveYayin = newReceiveYayin;
}

QByteArray channel::getChannelName() const
{
    return channelName;
}

void channel::setChannelName(const QByteArray &newChannelName)
{
    channelName = newChannelName;
}

quint8 channel::getCrcHigh() const
{
    return crcHigh;
}

void channel::setCrcHigh(quint8 newCrcHigh)
{
    crcHigh = newCrcHigh;
}

quint8 channel::getCrcLow() const
{
    return crcLow;
}

void channel::setCrcLow(quint8 newCrcLow)
{
    crcLow = newCrcLow;
}
/**
*   组装信道写频数据包为QByteArray
*   @return QByteArray 组装好的数据包
*/
QByteArray channel::toWriteFrequencyData()
{
    QByteArray data;

    data.append(this->getStartBit1());
    data.append(this->getStartBit2());
    data.append(this->getStartBit3());
    data.append(this->getStartBit4());

    data.append(this->getSize());

    data.append(this->getCommand());

    data.append(this->getChannelHigh());
    data.append(this->getChannelLow());

    data.append(this->getVfoaMode());
    data.append(this->getVfobMode());

    data.append(this->getVfoaFrequency1());
    data.append(this->getVfoaFrequency2());
    data.append(this->getVfoaFrequency3());
    data.append(this->getVfoaFrequency4());
    data.append(this->getVfobFrequency1());
    data.append(this->getVfobFrequency2());
    data.append(this->getVfobFrequency3());
    data.append(this->getVfobFrequency4());

    data.append(this->getEmitYayin());
    data.append(this->getReceiveYayin());

    data.append(this->getCrcHigh());
    data.append(this->getCrcLow());

    return data;
}
/**
*   将电台写频回复的数据包写入到对象中
*   @value data 接收的数据
*/
void channel::radioWriteResponseToObj(QByteArray data){

    this->setStartBit1(data[0]);
    this->setStartBit2(data[1]);
    this->setStartBit3(data[2]);
    this->setStartBit4(data[3]);

    this->setSize(data[4]);

    this->setCommand(data[5]);

    this->setChannelHigh(data[6]);
    this->setChannelLow(data[7]);

    this->setVfoaMode(data[8]);
    this->setVfobMode(data[9]);

    // 获取VFOA频率
    this->setVfoaFrequency1(data[10]);
    this->setVfoaFrequency2(data[11]);
    this->setVfoaFrequency3(data[12]);
    this->setVfoaFrequency4(data[13]);
    // 获取VFOB频率
    this->setVfobFrequency1(data[14]);
    this->setVfobFrequency2(data[15]);
    this->setVfobFrequency3(data[16]);
    this->setVfobFrequency4(data[17]);
    // 亚音
    this->setEmitYayin(data[18]);
    this->setReceiveYayin(data[19]);

    // 获取信道名字
    int size = data.size();
    QByteArray name;
    name.resize((size-2)-20);
    int j = 0;
    for(int i = 20 ; i < (size-2) ; i++,j++){
        name[j] = data[i];
    }
    this->setChannelName(name);

    // 获取crc
    this->setCrcHigh(data[size-2]);
    this->setCrcLow(data[size-1]);
}
/**
*   打包电台读取命令
*   @return QByteArray 返回打包好的命令数据包
*/
QByteArray channel::toReadFrequencyData(){
    QByteArray data;

    data = this->preparePacketWithCRC();    //添加CRC校验

    data.append(this->getSize());

    data.append(this->getCommand());

    data.append(this->getChannelHigh());
    data.append(this->getChannelLow());

    data.prepend(this->getStartBit4());
    data.prepend(this->getStartBit3());
    data.prepend(this->getStartBit2());
    data.prepend(this->getStartBit1());


    return data;
}
/**
 *  0x41
*   将读取命令带来的回复数据包拆分到类
*   @value QByteArray data 回复数据包
*/
void channel::radioReadResponseToObj(QByteArray data){
    this->setStartBit1(data[0]);
    this->setStartBit2(data[1]);
    this->setStartBit3(data[2]);
    this->setStartBit4(data[3]);

    this->setSize(data[4]);

    this->setCommand(data[5]);

    this->setChannelHigh(data[6]);
    this->setChannelLow(data[7]);

    this->setVfoaMode(data[8]);
    this->setVfobMode(data[9]);

    this->setVfoaFrequency1(data[10]);
    this->setVfoaFrequency2(data[11]);
    this->setVfoaFrequency3(data[12]);
    this->setVfoaFrequency4(data[13]);

    this->setVfobFrequency1(data[14]);
    this->setVfobFrequency2(data[15]);
    this->setVfobFrequency3(data[16]);
    this->setVfobFrequency4(data[17]);
    this->setEmitYayin(data[18]);
    this->setReceiveYayin(data[19]);
    // 获取信道名字
    int size = data.size();

    QByteArray name;
    name.resize((size-2)-20);
    int j = 0;
    for(int i = 20 ; i < (size-2) ; i++,j++){
        name[j] = data[i];
    }
    this->setChannelName(name);

    // 获取crc
    this->setCrcHigh(data[size-2]);
    this->setCrcLow(data[size-1]);

}

quint8 channel::getVfoaFrequency1() const
{
    return vfoaFrequency1;
}

void channel::setVfoaFrequency1(quint8 newVfoaFrequency1)
{
    vfoaFrequency1 = newVfoaFrequency1;
}


quint8 channel::getVfoaFrequency2() const
{
    return vfoaFrequency2;
}

void channel::setVfoaFrequency2(quint8 newVfoaFrequency2)
{
    vfoaFrequency2 = newVfoaFrequency2;
}

quint8 channel::getVfoaFrequency3() const
{
    return vfoaFrequency3;
}

void channel::setVfoaFrequency3(quint8 newVfoaFrequency3)
{
    vfoaFrequency3 = newVfoaFrequency3;
}

quint8 channel::getVfoaFrequency4() const
{
    return vfoaFrequency4;
}

void channel::setVfoaFrequency4(quint8 newVfoaFrequency4)
{
    vfoaFrequency4 = newVfoaFrequency4;
}

quint8 channel::getVfobFrequency1() const
{
    return vfobFrequency1;
}

void channel::setVfobFrequency1(quint8 newVfobFrequency1)
{
    vfobFrequency1 = newVfobFrequency1;
}

quint8 channel::getVfobFrequency2() const
{
    return vfobFrequency2;
}

void channel::setVfobFrequency2(quint8 newVfobFrequency2)
{
    vfobFrequency2 = newVfobFrequency2;
}

quint8 channel::getVfobFrequency3() const
{
    return vfobFrequency3;
}

void channel::setVfobFrequency3(quint8 newVfobFrequency3)
{
    vfobFrequency3 = newVfobFrequency3;
}


quint8 channel::getVfobFrequency4() const
{
    return vfobFrequency4;
}

void channel::setVfobFrequency4(quint8 newVfobFrequency4)
{
    vfobFrequency4 = newVfobFrequency4;
}

/* CRC校验 */

/**
 *  0x41
*   将数据与CRC校验码粘合，返回QByteArray
*   @return QByteArray 完整信道读命令
*/
QByteArray channel::preparePacketWithCRC()
{
    QByteArray packet;

    packet.append(this->getSize());

    packet.append(this->getCommand());

    packet.append(this->getChannelHigh());
    packet.append(this->getChannelLow());
    // 计算CRC CRC校验不含包头不含自身
    uint16_t crc = CRC16Check(reinterpret_cast<unsigned char*>(packet.data()), packet.size());

    // 将CRC高低位分开加入到packet中
    packet.append((crc >> 8) & 0xFF); // CRC高
    packet.append(crc & 0xFF);        // CRC低

    packet.prepend(this->getStartBit4());
    packet.prepend(this->getStartBit3());
    packet.prepend(this->getStartBit2());
    packet.prepend(this->getStartBit1());

    return packet;
}
/**
 * 0x40
*   添加写命令的CRC
*   @return QByteArray 返回一个无包头组装了CRC的本类数据组
*/
QByteArray channel::prepareWritePacketWithCRC(){
    QByteArray packet;

    packet.append(this->getSize());

    packet.append(this->getCommand());

    packet.append(this->getChannelHigh());
    packet.append(this->getChannelLow());

    packet.append(this->getVfoaMode());
    packet.append(this->getVfobMode());

    packet.append(this->getVfoaFrequency1());
    packet.append(this->getVfoaFrequency2());
    packet.append(this->getVfoaFrequency3());
    packet.append(this->getVfoaFrequency4());

    packet.append(this->getVfobFrequency1());
    packet.append(this->getVfobFrequency2());
    packet.append(this->getVfobFrequency3());
    packet.append(this->getVfobFrequency4());

    packet.append(this->getEmitYayin());
    packet.append(this->getReceiveYayin());

    packet.append(this->getChannelName());

    // 计算CRC CRC校验不含包头不含自身
    uint16_t crc = CRC16Check(reinterpret_cast<unsigned char*>(packet.data()), packet.size());

    // 将CRC高低位分开加入到packet中
    packet.append((crc >> 8) & 0xFF); // CRC高
    packet.append(crc & 0xFF);        // CRC低

    packet.prepend(0xA5);
    packet.prepend(0xA5);
    packet.prepend(0xA5);
    packet.prepend(0xA5);

    return packet;
}

/**
 * 0x0B
 * 添加状态同步命令的CRC
 * @return QByteArray 返回一个组装了CRC的本类数据组
 */
QByteArray channel::addCrc0x0B(){
    QByteArray packet;

    packet.append(this->getSize());

    packet.append(this->getCommand());

    // 计算CRC CRC校验不含包头不含自身
    uint16_t crc = CRC16Check(reinterpret_cast<unsigned char*>(packet.data()), packet.size());

    // 将CRC高低位分开加入到packet中
    packet.append((crc >> 8) & 0xFF); // CRC高
    packet.append(crc & 0xFF);        // CRC低

    packet.prepend(0xA5);
    packet.prepend(0xA5);
    packet.prepend(0xA5);
    packet.prepend(0xA5);

    return packet;
}


unsigned short channel::getChannelID()
{
    channelID = (getChannelHigh() << 8 ) | getChannelLow();
    return channelID;
}

/**
*   转化为QJsonObject
*/
QJsonObject channel::toJSON()
{
    QJsonObject obj;

    obj["startBit1"] = this->getStartBit1();
    obj["startBit2"] = this->getStartBit2();
    obj["startBit3"] = this->getStartBit3();
    obj["startBit4"] = this->getStartBit4();

    obj["size"] = this->getSize();

    obj["command"] = this->getCommand();

    obj["channelHigh"] = this->getChannelHigh();
    obj["channelLow"] = this->getChannelLow();

    obj["vfoaMode"] = this->getVfoaMode();
    obj["vfobMode"] = this->getVfobMode();

    obj["vfoaFrequency1"] = this->getVfoaFrequency1();
    obj["vfoaFrequency2"] = this->getVfoaFrequency2();
    obj["vfoaFrequency3"] = this->getVfoaFrequency3();
    obj["vfoaFrequency4"] = this->getVfoaFrequency4();

    obj["vfobFrequency1"] = this->getVfobFrequency1();
    obj["vfobFrequency2"] = this->getVfobFrequency2();
    obj["vfobFrequency3"] = this->getVfobFrequency3();
    obj["vfobFrequency4"] = this->getVfobFrequency4();

    obj["emitYayin"] = this->getEmitYayin();
    obj["receiveYayin"] = this->getReceiveYayin();

    obj["channelName"] = QString::fromUtf8(this->getChannelName());

    obj["crcHigh"] = this->getCrcHigh();
    obj["crcLow"] = this->getCrcLow();

    return obj;
}

quint32 channel::getVfoaFrequency()
{
    // 重组4字节数据
    vfoaFrequency = (static_cast<uint32_t>(this->getVfoaFrequency1()) << 24) |
                   (static_cast<uint32_t>(this->getVfoaFrequency2()) << 16) |
                   (static_cast<uint32_t>(this->getVfoaFrequency3()) << 8)  |
                   static_cast<uint32_t>(this->getVfoaFrequency4());

    return vfoaFrequency;
}

void channel::setVfoaFrequency(quint32 newVfoaFrequency)
{
    if(newVfoaFrequency > 2000000000 ){
        newVfoaFrequency = 2000000000;
    }
    // 将4字节数据拆分成各个字节
    uint8_t byte4 = static_cast<uint8_t>((newVfoaFrequency >> 24) & 0xFF);
    uint8_t byte3 = static_cast<uint8_t>((newVfoaFrequency >> 16) & 0xFF);
    uint8_t byte2 = static_cast<uint8_t>((newVfoaFrequency >> 8) & 0xFF);
    uint8_t byte1 = static_cast<uint8_t>(newVfoaFrequency & 0xFF);

    this->setVfoaFrequency1(byte1);
    this->setVfoaFrequency2(byte2);
    this->setVfoaFrequency3(byte3);
    this->setVfoaFrequency4(byte4);
}

quint32 channel::getVfobFrequency()
{
    // 重组4字节数据
    vfobFrequency = (static_cast<uint32_t>(this->getVfobFrequency1()) << 24) |
                    (static_cast<uint32_t>(this->getVfobFrequency2()) << 16) |
                    (static_cast<uint32_t>(this->getVfobFrequency3()) << 8)  |
                    static_cast<uint32_t>(this->getVfobFrequency4());

    return vfobFrequency;
}

void channel::setVfobFrequency(quint32 newVfobFrequency)
{
    if(newVfobFrequency > 2000000000 ){
        newVfobFrequency = 2000000000;
    }
    // 将4字节数据拆分成各个字节
    uint8_t byte4 = static_cast<uint8_t>((newVfobFrequency >> 24) & 0xFF);
    uint8_t byte3 = static_cast<uint8_t>((newVfobFrequency >> 16) & 0xFF);
    uint8_t byte2 = static_cast<uint8_t>((newVfobFrequency >> 8) & 0xFF);
    uint8_t byte1 = static_cast<uint8_t>(newVfobFrequency & 0xFF);

    this->setVfobFrequency1(byte1);
    this->setVfobFrequency2(byte2);
    this->setVfobFrequency3(byte3);
    this->setVfobFrequency4(byte4);
}

uint16_t channel::CRC16Check(unsigned char *buf, unsigned char len)
{
    unsigned char  i, j;
    uint16_t uncrcReg = 0xFFFF;
    int16_t uncur;
    for (i = 0; i < len; i++)
    {
        uncur = buf[i] << 8;
        for (j = 0; j < 8; j++)
        {
            if ((int16_t)(uncrcReg ^ uncur) < 0)
            {
                uncrcReg = (uncrcReg << 1) ^ 0x1021;
            }
            else
            {
                uncrcReg <<= 1;
            }
            uncur <<= 1;
        }
    }
    return uncrcReg;
}
/**
*   格式化channel类信息
*   @return QString 返回格式化后的本类变量信息
*/
QString channel::toString(){
    return "channel:{"
           + QString::number(this->getStartBit1(),16) + " "
           + QString::number(this->getStartBit2(),16)+ " "
           + QString::number(this->getStartBit3(),16)+ " "
           + QString::number(this->getStartBit4(),16)+ " "
           +"Size{"+ QString::number(this->getSize())+ "} "
           +"Command{"+ QString::number(this->getCommand(),16)+ "} "
           +"Channel{"+ QString::number(this->getChannelHigh(),16)+ " "
           + QString::number(this->getChannelLow(),16)+ "} "
           +"VfoaMode{"+ QString::number(this->getVfoaMode(),16)+ "} "
           +"VfobMode{"+ QString::number(this->getVfobMode(),16)+ "} "
           +"VfoaFrequency{"+ QString::number(this->getVfoaFrequency1(),16)+ " "
           + QString::number(this->getVfoaFrequency2(),16)+ " "
           + QString::number(this->getVfoaFrequency3(),16)+ " "
           + QString::number(this->getVfoaFrequency4(),16)+ "} "
           +"VfobFrequency{"+ QString::number(this->getVfobFrequency1(),16)+ " "
           + QString::number(this->getVfobFrequency2(),16)+ " "
           + QString::number(this->getVfobFrequency3(),16)+ " "
           + QString::number(this->getVfobFrequency4(),16)+ "} "
           +"EmitYayin{"+ QString::number(this->getEmitYayin(),16)+ "} "
           +"ReceiveYayin{"+ QString::number(this->getReceiveYayin(),16)+ "} "
           +"ChannelName{"+ this->getChannelName()+ "} "
           +"Crc{"+ QString::number(this->getCrcHigh(),16)+ " "
           + QString::number(this->getCrcLow(),16) + "} }"
        ;
}

/**
 *  获取@value data中的有效数据
 *  判断4个A5
 *  判断包长
 *  判断CRC
 *  任一未通过 @return false
 */
bool channel::verifyReadData(QByteArray data){
    // 包头校验
    for(int i = 0; i < 4; i++){
        if(static_cast<unsigned char>(data[i]) != 0xA5){
            debug("包头错误");
            return false;
        }
    }

    // 长度校验
    if(static_cast<unsigned char>(data[4]) != data.size()-5){
        debug("长度错误");
        return false;
    }

    // 提取数据部分
    QByteArray dataPart = data.mid(4, data.size() - 6);
    unsigned char* dataPartData =reinterpret_cast<unsigned char*>(dataPart.data());
    uint16_t dataPartCrc = CRC16Check(dataPartData,dataPart.size());

    char a = dataPartCrc >> 8;
    char b = dataPartCrc;

    char c = data[data.size()-2];
    char d = data[data.size()-1];

    if(a!=c || b!=d){
        debug("crc错误");
        return false;
    }

    return true;
}
