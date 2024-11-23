#ifndef TUNER_SERVICE_H
#define TUNER_SERVICE_H

#include <QObject>
#include "Entity/tuner.h"
#include "Tools/tools.h"

class TUNER_service : public QObject
{
    Q_OBJECT

private:
    Tools tool;
public:
    explicit TUNER_service(QObject *parent = nullptr);

    /* 构建发送命令 */
    QByteArray build0x46(TUNER tuner);
    QByteArray build0x47(TUNER tuner);
    QByteArray build0x48(TUNER tuner);

signals:
};

#endif // TUNER_SERVICE_H
