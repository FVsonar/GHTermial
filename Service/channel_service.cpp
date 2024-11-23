#include "channel_service.h"

Channel_Service::Channel_Service(QObject *parent)
    : QObject{parent}
{}

QByteArray Channel_Service::build0x40(channel& cl)
{
    QByteArray data;

    data.append(cl.getSize());

    data.append(cl.getCommand());

    data.append(cl.getChannelHigh());
    data.append(cl.getChannelLow());

    data.append(cl.getVfoaMode());
    data.append(cl.getVfobMode());

    data.append(cl.getVfoaFrequency1());
    data.append(cl.getVfoaFrequency2());
    data.append(cl.getVfoaFrequency3());
    data.append(cl.getVfoaFrequency4());
    data.append(cl.getVfobFrequency1());
    data.append(cl.getVfobFrequency2());
    data.append(cl.getVfobFrequency3());
    data.append(cl.getVfobFrequency4());

    data.append(cl.getEmitYayin());
    data.append(cl.getReceiveYayin());

    tool.addCrc(data);
    tool.addHead(data);

    return data;
}

QByteArray Channel_Service::build0x41(channel& cl)
{
    QByteArray data;

    data.append(cl.getSize());

    data.append(cl.getCommand());

    data.append(cl.getChannelHigh());
    data.append(cl.getChannelLow());

    tool.addCrc(data);
    tool.addHead(data);

    return data;
}
