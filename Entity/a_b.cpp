#include "a_b.h"

A_B::A_B(QObject *parent)
    : QObject{parent}
{}

quint8 A_B::getStartBit1() const
{
    return startBit1;
}

void A_B::setStartBit1(quint8 newStartBit1)
{
    startBit1 = newStartBit1;
}

quint8 A_B::getStartBit2() const
{
    return startBit2;
}

void A_B::setStartBit2(quint8 newStartBit2)
{
    startBit2 = newStartBit2;
}

quint8 A_B::getStartBit3() const
{
    return startBit3;
}

void A_B::setStartBit3(quint8 newStartBit3)
{
    startBit3 = newStartBit3;
}

quint8 A_B::getStartBit4() const
{
    return startBit4;
}

void A_B::setStartBit4(quint8 newStartBit4)
{
    startBit4 = newStartBit4;
}

quint8 A_B::getSize() const
{
    return size;
}

void A_B::setSize(quint8 newSize)
{
    size = newSize;
}

quint8 A_B::getCommand() const
{
    return command;
}

void A_B::setCommand(quint8 newCommand)
{
    command = newCommand;
}

quint8 A_B::getAb() const
{
    return ab;
}

void A_B::setAb(quint8 newAb)
{
    ab = newAb;
}

quint8 A_B::getCrcHigh() const
{
    return crcHigh;
}

void A_B::setCrcHigh(quint8 newCrcHigh)
{
    crcHigh = newCrcHigh;
}

quint8 A_B::getCrcLow() const
{
    return crcLow;
}

void A_B::setCrcLow(quint8 newCrcLow)
{
    crcLow = newCrcLow;
}

uint16_t A_B::CRC16Check(unsigned char *buf, unsigned char len)
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
 *  返回完全组合好的，包含包头、大小、命令、特殊位、CRC的QByteArray命令
 */
QByteArray A_B::addCrc()
{
    QByteArray packet;

    packet.append(this->getSize());

    packet.append(this->getCommand());

    packet.append(this->getAb());

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

void A_B::datatoAb(QByteArray data)
{
    this->setStartBit1(data[0]);
    this->setStartBit2(data[1]);
    this->setStartBit3(data[2]);
    this->setStartBit4(data[3]);

    this->setSize(data[4]);

    this->setCommand(data[5]);

    this->setAb(data[6]);

    // 获取crc
    this->setCrcHigh(data[size-2]);
    this->setCrcLow(data[size-1]);
}
