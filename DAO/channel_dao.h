#ifndef CHANNEL_DAO_H
#define CHANNEL_DAO_H

#include <QObject>
#include "Entity/channel.h"

class Channel_DAO : public QObject
{
    Q_OBJECT
private:
    channel cl;
public:
    explicit Channel_DAO(QObject *parent = nullptr);

    channel dataToObj0x40(QByteArray data);
    channel dataToObj0x41(QByteArray data);
signals:
};

#endif // CHANNEL_DAO_H
