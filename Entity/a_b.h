#ifndef A_B_H
#define A_B_H

#include <QObject>

class A_B : public QObject
{
    Q_OBJECT
public:
    explicit A_B(QObject *parent = nullptr);
    quint8 getStartBit1() const;
    void setStartBit1(quint8 newStartBit1);
    quint8 getStartBit2() const;
    void setStartBit2(quint8 newStartBit2);
    quint8 getStartBit3() const;
    void setStartBit3(quint8 newStartBit3);
    quint8 getStartBit4() const;
    void setStartBit4(quint8 newStartBit4);
    quint8 getSize() const;
    void setSize(quint8 newSize);
    quint8 getCommand() const;
    void setCommand(quint8 newCommand);
    quint8 getAb() const;
    void setAb(quint8 newAb);
    quint8 getCrcHigh() const;
    void setCrcHigh(quint8 newCrcHigh);
    quint8 getCrcLow() const;
    void setCrcLow(quint8 newCrcLow);


    uint16_t CRC16Check(unsigned char *buf, unsigned char len);
    QByteArray addCrc();
    void datatoAb(QByteArray);
    QByteArray abToData(A_B);

private:
    quint8 startBit1;
    quint8 startBit2;
    quint8 startBit3;
    quint8 startBit4;
    quint8 size;
    quint8 command;
    quint8 ab;   // ab频切换 0:A频  1:B频   2：A=B频
    quint8 crcHigh;
    quint8 crcLow;
signals:
};

#endif // A_B_H
