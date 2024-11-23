#include "dmr_dao.h"

Dmr_DAO::Dmr_DAO(QObject *parent)
    : QObject{parent}
{}

DMR Dmr_DAO::dataToObj0x43(QByteArray data)
{
    dmr.setStartBit1(data[0]);
    dmr.setStartBit2(data[1]);
    dmr.setStartBit3(data[2]);
    dmr.setStartBit4(data[3]);

    dmr.setSize(data[4]);

    dmr.setCommand(data[5]);

    dmr.setChannelHigh(data[6]);
    dmr.setChannelLow(data[7]);

    dmr.setCallFormat(data[8]);

    dmr.setTxCc(data[9]);
    dmr.setRxCc(data[10]);

    dmr.setSlot(data[11]);

    dmr.setCallId1(data[12]);
    dmr.setCallId2(data[13]);
    dmr.setCallId3(data[14]);
    dmr.setCallId4(data[15]);

    dmr.setOwnId1(data[16]);
    dmr.setOwnId2(data[17]);
    dmr.setOwnId3(data[18]);
    dmr.setOwnId4(data[19]);

    dmr.setChType(data[20]);

    dmr.setRxCtcss(data[21]);
    dmr.setTxCtcss(data[22]);

    dmr.setSqlevel(data[23]);
    dmr.setSpkgain(data[24]);
    dmr.setDmrexist(data[25]);
    dmr.setDmodGain(data[26]);
    dmr.setScrEn(data[27]);

    dmr.setScrSeed1(data[28]);
    dmr.setScrSeed2(data[29]);

    dmr.setChBsMode(data[30]);
    dmr.setValidat(data[31]);

    dmr.setCrcHigh(data[32]);
    dmr.setCrcLow(data[33]);

    return dmr;
}

DMR Dmr_DAO::dataToObj0x44(QByteArray data)
{
    dmr.setStartBit1(data[0]);
    dmr.setStartBit2(data[1]);
    dmr.setStartBit3(data[2]);
    dmr.setStartBit4(data[3]);

    dmr.setSize(data[4]);

    dmr.setCommand(data[5]);

    dmr.setChannelHigh(data[6]);
    dmr.setChannelLow(data[7]);

    dmr.setCallFormat(data[8]);

    dmr.setTxCc(data[9]);
    dmr.setRxCc(data[10]);

    dmr.setSlot(data[11]);

    dmr.setCallId1(data[12]);
    dmr.setCallId2(data[13]);
    dmr.setCallId3(data[14]);
    dmr.setCallId4(data[15]);

    dmr.setOwnId1(data[16]);
    dmr.setOwnId2(data[17]);
    dmr.setOwnId3(data[18]);
    dmr.setOwnId4(data[19]);

    dmr.setChType(data[20]);

    dmr.setRxCtcss(data[21]);
    dmr.setTxCtcss(data[22]);

    dmr.setSqlevel(data[23]);
    dmr.setSpkgain(data[24]);
    dmr.setDmrexist(data[25]);
    dmr.setDmodGain(data[26]);
    dmr.setScrEn(data[27]);

    dmr.setScrSeed1(data[28]);
    dmr.setScrSeed2(data[29]);

    dmr.setChBsMode(data[30]);
    dmr.setValidat(data[31]);

    dmr.setCrcHigh(data[32]);
    dmr.setCrcLow(data[33]);

    return dmr;
}
