#ifndef TUNER_DAO_H
#define TUNER_DAO_H

#include <QObject>
#include "Entity/tuner.h"

class TUNER_DAO : public QObject
{
    Q_OBJECT
private:
    TUNER tuner;
public:
    explicit TUNER_DAO(QObject *parent = nullptr);

    TUNER getTuner();
    /* 将命令转为对象 */
    TUNER dataToObj0x46(QByteArray data);
    TUNER dataToObj0x47(QByteArray data);
    TUNER dataToObj0x48(QByteArray data);
signals:
};

#endif // TUNER_DAO_H
