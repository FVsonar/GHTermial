#include "channeldmr_dao.h"

ChannelDmr_DAO::ChannelDmr_DAO(QObject *parent)
    : QObject{parent}
{}

ChannelDmr ChannelDmr_DAO::buildChannelDmr(channel channelTemp, DMR dmrTemp)
{
    ChannelDmr channelDmr;
    /* channel */
    channelDmr.setChannelHigh(channelTemp.getChannelHigh());
    channelDmr.setChannelLow(channelTemp.getChannelLow());

    channelDmr.setChannelName(channelTemp.getChannelName());

    channelDmr.setVfoaFrequency1(channelTemp.getVfoaFrequency1());
    channelDmr.setVfoaFrequency2(channelTemp.getVfoaFrequency2());
    channelDmr.setVfoaFrequency3(channelTemp.getVfoaFrequency3());
    channelDmr.setVfoaFrequency4(channelTemp.getVfoaFrequency4());

    channelDmr.setVfobFrequency1(channelTemp.getVfobFrequency1());
    channelDmr.setVfobFrequency2(channelTemp.getVfobFrequency2());
    channelDmr.setVfobFrequency3(channelTemp.getVfobFrequency3());
    channelDmr.setVfobFrequency4(channelTemp.getVfobFrequency4());

    channelDmr.setVfoaMode(channelTemp.getVfoaMode());
    channelDmr.setVfobMode(channelTemp.getVfobMode());

    channelDmr.setEmitYayin(channelTemp.getEmitYayin());
    channelDmr.setReceiveYayin(channelTemp.getReceiveYayin());

    /* dmr */
    channelDmr.setCallFormat(dmrTemp.getCallFormat());

    channelDmr.setCallId1(dmrTemp.getCallId1());
    channelDmr.setCallId2(dmrTemp.getCallId2());
    channelDmr.setCallId3(dmrTemp.getCallId3());
    channelDmr.setCallId4(dmrTemp.getCallId4());

    channelDmr.setOwnId1(dmrTemp.getOwnId1());
    channelDmr.setOwnId2(dmrTemp.getOwnId2());
    channelDmr.setOwnId3(dmrTemp.getOwnId3());
    channelDmr.setOwnId4(dmrTemp.getOwnId4());

    channelDmr.setChType(dmrTemp.getChType());

    channelDmr.setRxCtcss(dmrTemp.getRxCtcss());
    channelDmr.setTxCtcss(dmrTemp.getTxCtcss());

    channelDmr.setSqlevel(dmrTemp.getSqlevel());
    channelDmr.setSpkgain(dmrTemp.getSpkgain());

    channelDmr.setDmodGain(dmrTemp.getDmodGain());
    channelDmr.setScrEn(dmrTemp.getScrEn());

    channelDmr.setScrSeed1(dmrTemp.getScrSeed1());
    channelDmr.setScrSeed2(dmrTemp.getScrSeed2());

    channelDmr.setChBsMode(dmrTemp.getChBsMode());

    return channelDmr;
}
