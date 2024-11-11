#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QComboBox>
#include <QJsonDocument>
#include <QFile>

class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools(QObject *parent = nullptr);

    uint16_t CRC16Check(unsigned char *buf, unsigned char len);
    bool checkData(QByteArray data);
    void setVfoComboBoxPtr(QComboBox *&vfoComboBoxPtr);
    void setYayinComboBoxPtr(QComboBox *&comboBox);
    void setTableHeader(QStringList &tableCplumnHeader);
    bool compareCRC(QByteArray data);
    QByteArray parsePackets(QByteArray data);
    bool saveJsonToFile(const QJsonObject &obj, const QString &filePath);
    void setRxTxCtcssComboBoxPtr(QComboBox *&comboBox);
signals:

private:
    // 缓存区
    QByteArray buffer;
};

#endif // TOOLS_H
