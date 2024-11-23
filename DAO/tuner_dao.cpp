#include "tuner_dao.h"

TUNER_DAO::TUNER_DAO(QObject *parent)
    : QObject{parent}
{}

TUNER TUNER_DAO::getTuner()
{
    return tuner;
}

TUNER TUNER_DAO::dataToObj0x46(QByteArray data)
{
    tuner.setStartBit1(data[0]);
    tuner.setStartBit2(data[1]);
    tuner.setStartBit3(data[2]);
    tuner.setStartBit4(data[3]);

    tuner.setSize(data[4]);

    tuner.setCommand(data[5]);

    tuner.setTuningMode(data[6]);

    tuner.setSwtv(data[7]);

    tuner.setCrcHigh(data[8]);
    tuner.setCrcLow(data[9]);

    return tuner;
}

TUNER TUNER_DAO::dataToObj0x47(QByteArray data)
{
    tuner.setStartBit1(data[0]);
    tuner.setStartBit2(data[1]);
    tuner.setStartBit3(data[2]);
    tuner.setStartBit4(data[3]);

    tuner.setSize(data[4]);

    tuner.setCommand(data[5]);

    tuner.setTuningMode(data[6]);

    tuner.setSwtv(data[7]);

    tuner.setVoltage(data[8]);

    tuner.setCrcHigh(data[9]);
    tuner.setCrcLow(data[10]);

    return tuner;
}

TUNER TUNER_DAO::dataToObj0x48(QByteArray data)
{
    tuner.setStartBit1(data[0]);
    tuner.setStartBit2(data[1]);
    tuner.setStartBit3(data[2]);
    tuner.setStartBit4(data[3]);

    tuner.setSize(data[4]);

    tuner.setCommand(data[5]);

    tuner.setPpcv(data[6]);
    tuner.setSwcv(data[7]);
    tuner.setVcv(data[8]);

    tuner.setCrcHigh(data[9]);
    tuner.setCrcLow(data[10]);

    return tuner;
}
