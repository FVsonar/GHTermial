#include "stlip.h"

STLIP::STLIP(QObject *parent)
    : QObject{parent}
{}

quint8 STLIP::getStartBit1() const
{
    return startBit1;
}

void STLIP::setStartBit1(quint8 newStartBit1)
{
    startBit1 = newStartBit1;
}

quint8 STLIP::getStartBit2() const
{
    return startBit2;
}

void STLIP::setStartBit2(quint8 newStartBit2)
{
    startBit2 = newStartBit2;
}

quint8 STLIP::getStartBit3() const
{
    return startBit3;
}

void STLIP::setStartBit3(quint8 newStartBit3)
{
    startBit3 = newStartBit3;
}

quint8 STLIP::getStartBit4() const
{
    return startBit4;
}

void STLIP::setStartBit4(quint8 newStartBit4)
{
    startBit4 = newStartBit4;
}

quint8 STLIP::getSize() const
{
    return size;
}

void STLIP::setSize(quint8 newSize)
{
    size = newSize;
}

quint8 STLIP::getSplip() const
{
    return splip;
}

void STLIP::setSplip(quint8 newSplip)
{
    splip = newSplip;
}

quint8 STLIP::getCommand() const
{
    return command;
}

void STLIP::setCommand(quint8 newCommand)
{
    command = newCommand;
}

quint8 STLIP::getCrcHigh() const
{
    return crcHigh;
}

void STLIP::setCrcHigh(quint8 newCrcHigh)
{
    crcHigh = newCrcHigh;
}

quint8 STLIP::getCrcLow() const
{
    return crcLow;
}

void STLIP::setCrcLow(quint8 newCrcLow)
{
    crcLow = newCrcLow;
}


uint16_t STLIP::CRC16Check(unsigned char *buf, unsigned char len)
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
