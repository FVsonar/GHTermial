#ifndef DMR_SERVICE_H
#define DMR_SERVICE_H

#include <QObject>
#include "Entity/dmr.h"
#include "Tools/tools.h"

class Dmr_Service : public QObject
{
    Q_OBJECT
private:
    Tools tool;
public:
    explicit Dmr_Service(QObject *parent = nullptr);

    QByteArray build0x43(DMR &dmr);
    QByteArray build0x44(DMR &dmr);

signals:
};

#endif // DMR_SERVICE_H
