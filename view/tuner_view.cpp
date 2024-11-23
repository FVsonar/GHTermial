#include "tuner_view.h"
#include "Entity/tuner.h"
#include <QDebug>

TUNER_view::TUNER_view(QObject *parent)
    : QObject{parent}
    , tunerSyncTimer(new QTimer(this))

{

}

TUNER_view::~TUNER_view()
{

}

/**
 *  槽函数
 *  0x46 被点击时
 *  天调调谐按钮
 */
QByteArray TUNER_view::swtBtn_clicked(int index,double value){
    TUNER tuner;

    tuner.setSize(5);
    tuner.setCommand(0x46);
    tuner.setTuningMode(index);
    int v = (int)(value*10);
    tuner.setSwtv(v);
    QByteArray data = tuner.build0x46();

    debug("0x46 要发送数据:")<<data.toHex(' ');
    return data;
}

/**
 *  槽函数
 *  0x47 被点击时
 *  天调同步按钮
 */
QByteArray TUNER_view::TUNER_synchronousBtn_clicked(){
    TUNER tuner;
    tuner.setSize(3);
    tuner.setCommand(0x47);
    QByteArray data = tuner.build0x47();

    debug("0x47 要发送数据:")<<data.toHex(' ');
    return data;
}

/**
 *  槽函数
 *  0x48 被点击时
 *  天调校准按钮
 */
QByteArray TUNER_view::ATCbtn_clicked(int ppcv,int swcv,int vcv){
    TUNER tuner;
    tuner.setSize(6);
    tuner.setCommand(0x48);
    tuner.setPpcv(ppcv);
    tuner.setSwcv(swcv);
    tuner.setVcv(vcv);
    QByteArray data = tuner.build0x48();

    debug("0x48 要发送数据:")<<data.toHex(' ');
    return data;
}
/**
 *  当焦点为本页时
 */
void TUNER_view::forTheCurrentFocus(){
    debug("天调页为焦点");
    tunerSyncTimer->setInterval(500);
    tunerSyncTimer->start();
    connect(tunerSyncTimer,&QTimer::timeout,this,&TUNER_view::timerout0x47);
}
/**
 *  天调同步 定时发送
 */
void TUNER_view::timerout0x47(){
    TUNER tuner;
    tuner.setSize(3);
    tuner.setCommand(0x47);
    QByteArray data = tuner.build0x47();

    emit onTimerOut0x47(data);
}

void TUNER_view::setTimerout0x47(bool state){
    if(state == false){
        if(tunerSyncTimer->isActive())
            tunerSyncTimer->stop();
        return;
    }
    if(state){
        tunerSyncTimer->start(500);
    }
}
