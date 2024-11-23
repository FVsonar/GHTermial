#ifndef DMR_DAO_H
#define DMR_DAO_H

#include <QObject>
#include "Entity/dmr.h"

class Dmr_DAO : public QObject
{
    Q_OBJECT
private:
    DMR dmr;
public:
    explicit Dmr_DAO(QObject *parent = nullptr);

    DMR dataToObj0x43(QByteArray data);
    DMR dataToObj0x44(QByteArray data);

signals:
};

#endif // DMR_DAO_H
