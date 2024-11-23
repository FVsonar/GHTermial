#ifndef CHANNEL_SERVICE_H
#define CHANNEL_SERVICE_H

#include <QObject>
#include "Tools/tools.h"
#include "Entity/channel.h"

class Channel_Service : public QObject
{
    Q_OBJECT
private:
    Tools tool;
public:
    explicit Channel_Service(QObject *parent = nullptr);

    QByteArray build0x40(channel& cl);
    QByteArray build0x41(channel& cl);
signals:
};

#endif // CHANNEL_SERVICE_H
