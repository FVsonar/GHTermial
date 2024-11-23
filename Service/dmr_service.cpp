#include "dmr_service.h"

Dmr_Service::Dmr_Service(QObject *parent)
    : QObject{parent}
{}

QByteArray Dmr_Service::build0x43(DMR& dmr)
{
    QByteArray packet;

    packet.append(dmr.getSize());
    packet.append(dmr.getCommand());

    packet.append(dmr.getChannelHigh());
    packet.append(dmr.getChannelLow());

    packet.append(dmr.getCallFormat());

    packet.append(dmr.getTxCc());
    packet.append(dmr.getRxCc());

    packet.append(dmr.getSlot());

    packet.append(dmr.getCallId1());
    packet.append(dmr.getCallId2());
    packet.append(dmr.getCallId3());
    packet.append(dmr.getCallId4());

    packet.append(dmr.getOwnId1());
    packet.append(dmr.getOwnId2());
    packet.append(dmr.getOwnId3());
    packet.append(dmr.getOwnId4());

    packet.append(dmr.getChType());

    packet.append(dmr.getRxCtcss());
    packet.append(dmr.getTxCtcss());

    packet.append(dmr.getSqlevel());
    packet.append(dmr.getSpkgain());
    packet.append(dmr.getDmrexist());
    packet.append(dmr.getDmodGain());

    packet.append(dmr.getScrEn());
    packet.append(dmr.getScrSeed1());
    packet.append(dmr.getScrSeed2());

    packet.append(dmr.getChBsMode());
    packet.append(dmr.getValidat());

    tool.addCrc(packet);
    tool.addHead(packet);

    return packet;
}

QByteArray Dmr_Service::build0x44(DMR& dmr)
{
    QByteArray packet;

    packet.append(dmr.getSize());
    packet.append(dmr.getCommand());
    packet.append(dmr.getChannelHigh());
    packet.append(dmr.getChannelLow());

    tool.addCrc(packet);
    tool.addHead(packet);

    return packet;
}
