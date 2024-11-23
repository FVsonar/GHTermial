#ifndef TUNER_VIEW_H
#define TUNER_VIEW_H

#include <QObject>
#include <QTimer>


class TUNER_view : public QObject
{
    Q_OBJECT
public:
    explicit TUNER_view(QObject *parent = nullptr);
    ~TUNER_view();

    void forTheCurrentFocus();


    QByteArray swtBtn_clicked(int index, double value);
    QByteArray TUNER_synchronousBtn_clicked();
    QByteArray ATCbtn_clicked(int ppcv, int swcv, int vcv);

    void setTimerout0x47(bool start);
    void tunerSyncTimerState(bool state);
private:

    QTimer *tunerSyncTimer; // 天线调谐器同步定时器

public slots:   // 槽函数

    void timerout0x47();
private slots:

signals:    // 信号
    void onTimerOut0x47(QByteArray data);
};

#endif // TUNER_VIEW_H
