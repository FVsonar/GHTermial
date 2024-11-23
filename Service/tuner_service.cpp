#include "tuner_service.h"

TUNER_service::TUNER_service(QObject *parent)
    : QObject{parent}
{}

QByteArray TUNER_service::build0x46(TUNER tuner)
{
    QByteArray packet;

    packet.append(tuner.getSize());
    packet.append(tuner.getCommand());
    packet.append(tuner.getTuningMode());
    packet.append(tuner.getSwtv());

    tool.addCrc(packet);
    tool.addHead(packet);

    return packet;
}

QByteArray TUNER_service::build0x47(TUNER tuner)
{
    QByteArray packet;

    packet.append(tuner.getSize());
    packet.append(tuner.getCommand());

    tool.addCrc(packet);
    tool.addHead(packet);

    return packet;
}

QByteArray TUNER_service::build0x48(TUNER tuner)
{
    QByteArray packet;

    packet.append(tuner.getSize());
    packet.append(tuner.getCommand());
    packet.append(tuner.getPpcv());
    packet.append(tuner.getSwcv());
    packet.append(tuner.getVcv());

    tool.addCrc(packet);
    tool.addHead(packet);

    return packet;
}
