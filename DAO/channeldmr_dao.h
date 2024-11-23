#ifndef CHANNELDMR_DAO_H
#define CHANNELDMR_DAO_H

#include <QObject>
#include "Entity/channel.h"
#include "Entity/dmr.h"
#include "Entity/channeldmr.h"

class ChannelDmr_DAO : public QObject
{
    Q_OBJECT
public:
    explicit ChannelDmr_DAO(QObject *parent = nullptr);

    ChannelDmr buildChannelDmr(channel channelTemp, DMR dmrTemp);
signals:
};

#endif // CHANNELDMR_DAO_H
