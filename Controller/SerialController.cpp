#include "SerialController.h"

SerialController::SerialController(QObject *parent) : QObject(parent)
{
    currentSerialport = new QSerialPort(this);
    retransmissionTimer0x40 = new QTimer(this);
    retransmissionTimer0x41 = new QTimer(this);
    retransmissionTimer0x43 = new QTimer(this);
    retransmissionTimer0x44 = new QTimer(this);
}

void SerialController::handleCommand0x40(channel& newChannel){
    retryCount0x40 = 0;
    stopTimerSafe(retransmissionTimer0x40);
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);
    if(!readySend40ChannelList->isEmpty()){
        serialPortTool.takeFirst40ListWrite(channelWrite,readySend40ChannelList,currentSerialport);
        retransmissionTimer0x40->start(200);
    } else {
        debug("0x40 写操作命令全部发送完成");
        readySend40ChannelList->clear();
        if(readySend40ChannelList->isEmpty() && !readySend43ChannelList->isEmpty()){
            serialPortTool.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentSerialport);
            retransmissionTimer0x43->start(200);
        }
    }
}
{
    // 实现0x40命令处理逻辑
}

void SerialController::handleCommand0x41(channel& newChannel){
    retryCount0x41 = 0;
    viewUpdate(newChannel.getChannelID(),newChannel);
    stopTimerSafe(retransmissionTimer0x41);
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);
    if(!readySend41ChannelList->isEmpty()){
        serialPortTool.takeFirst41ListWrite(channelRead,readySend41ChannelList,currentSerialport);
        retransmissionTimer0x41->start(200);
    } else {
        debug("0x41 读操作命令全部发送完成");
        readySend41ChannelList->clear();
        if(readySend41ChannelList->isEmpty() && !readySend44ChannelList->isEmpty()){
            serialPortTool.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentSerialport);
            retransmissionTimer0x44->start(200);
        }
    }
}
{
    // 实现0x41命令处理逻辑
}

void SerialController::handleCommand0x43(DMR& newDmr){
    retryCount0x43 = 0;
    stopTimerSafe(retransmissionTimer0x43);
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);
    if(!readySend43ChannelList->isEmpty()){
        serialPortTool.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentSerialport);
        retransmissionTimer0x43->start(200);
    } else {
        debug("0x43 写操作命令全部发送完成");
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->send_btn->setText(tr("发送"));
        ui->send_btn->setToolTip(tr("发送信道数据到设备"));
        sendBtn_busy = false;
        readySend43ChannelList->clear();
    }
}
{
    // 实现0x43命令处理逻辑
}

void SerialController::handleCommand0x44(DMR& newDmr){
    retryCount0x44 = 0;
    int newRow = newDmr.getChannelID();
    viewUpdateDmr(newRow,newDmr);
    stopTimerSafe(retransmissionTimer0x44);
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);
    if(!readySend44ChannelList->isEmpty()){
        serialPortTool.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentSerialport);
        retransmissionTimer0x44->start(200);
    } else {
        debug("0x44 读操作命令全部发送完成");
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->read_btn->setText(tr("读取"));
        ui->read_btn->setToolTip(tr("从设备读取信道数据"));
        readBtn_busy = false;
        readySend44ChannelList->clear();
    }
}
{
    // 实现0x44命令处理逻辑
}