#include "termial.h"
#include "ui_termial.h"
// #include "CheckBoxUpdater.h"
#include "Entity/channeldmr.h"
#include "DAO/channeldmr_dao.h"
#include "DAO/channel_dao.h"
#include "DAO/dmr_dao.h"
#include "DAO/tuner_dao.h"


termial::termial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::termial)
    , retransmissionTimer0x40(new QTimer(this))
    , retransmissionTimer0x41(new QTimer(this))
    , retransmissionTimer0x43(new QTimer(this))
    , retransmissionTimer0x44(new QTimer(this))
    , tcpRetransmissionTimer0x40(new QTimer(this))
    , tcpRetransmissionTimer0x41(new QTimer(this))
    , tcpRetransmissionTimer0x43(new QTimer(this))
    , tcpRetransmissionTimer0x44(new QTimer(this))
    , tunerRetransmissionTimer0x46(new QTimer(this))
    , tunerRetransmissionTimer0x47(new QTimer(this))
    , tunerRetransmissionTimer0x48(new QTimer(this))
    , heartbeatTimer(new QTimer(this))
{
    ui->setupUi(this);

    initArt();
    initSerialportComboBox();
    initPushBtnState();
    initViewTableHaed();
    initViewTable1000Col(); // 生成1000空白行
    initLoad(); // 初始化进度条
    initLanguageComboBox();
    initTunerSwtRadioBtn();
    tuner_v.forTheCurrentFocus(); // 初始化天调同步定时器
    tcpServer = new QTcpServer;
    initConnect();  // 信号and槽初始化

}

termial::~termial()
{
    // 清空复选框列表的所有指针
    qDeleteAll(checkBoxPrtList);
    checkBoxPrtList.clear();
    // 清空vfoa下拉框带来的所有指针
    qDeleteAll(vfoaComboBoxPtrList);
    vfoaComboBoxPtrList.clear();
    // 清空vfob下拉框带来的所有指针
    qDeleteAll(vfobComboBoxPtrList);
    vfobComboBoxPtrList.clear();
    // 清空发射亚音下拉框列表中的所有指针
    qDeleteAll(EmitYayinComboBoxPtrList);
    EmitYayinComboBoxPtrList.clear();
    // 清空接收亚音下拉框列表中的所有指针
    qDeleteAll(ReceiveYayinComboBoxPtrList);
    ReceiveYayinComboBoxPtrList.clear();
    // 清空dmr callType下拉框列表中的所有指针
    qDeleteAll(callTypeComboBoxPtrList);
    callTypeComboBoxPtrList.clear();
    // 清空dmr txCc数字选择列表中的所有指针
    qDeleteAll(txCcSpinBoxPtrList);
    txCcSpinBoxPtrList.clear();
    // 清空dmr rxCc数字选择列表中的所有指针
    qDeleteAll(rxCcSpinBoxPtrList);
    rxCcSpinBoxPtrList.clear();
    // 清空dmr slot数字选择列表中的所有指针
    qDeleteAll(slotSpinBoxPtrList);
    slotSpinBoxPtrList.clear();
    // 清空dmr chType下拉框列表中的所有指针
    qDeleteAll(chTypeComboBoxPtrList);
    chTypeComboBoxPtrList.clear();
    // 清空dmr rxCtcss下拉框列表中的所有指针
    qDeleteAll(rxCtcssComboBoxPtrList);
    rxCtcssComboBoxPtrList.clear();
    // 清空dmr txCtcss下拉框列表中的所有指针
    qDeleteAll(txCtcssComboBoxPtrList);
    txCtcssComboBoxPtrList.clear();
    // 清空dmr sqlevel下拉框列表中的所有指针
    qDeleteAll(sqlevelSpinBoxPtrList);
    sqlevelSpinBoxPtrList.clear();
    // 清空dmr spkgain下拉框列表中的所有指针
    qDeleteAll(spkgainSpinBoxPtrList);
    spkgainSpinBoxPtrList.clear();
    // 清空dmr rxGain下拉框列表中的所有指针
    qDeleteAll(rxGainSpinBoxPtrList);
    rxGainSpinBoxPtrList.clear();
    // 清空dmr enScr下拉框列表中的所有指针
    qDeleteAll(enScrComboBoxPtrList);
    enScrComboBoxPtrList.clear();
    // 清空dmr bsMode下拉框列表中的所有指针
    qDeleteAll(bsModeComboBoxPtrList);
    bsModeComboBoxPtrList.clear();

    delete swtBtnGroup; // 清理单选框组指针

    readySend40ChannelList.clear();
    readySend41ChannelList.clear();
    readySend43ChannelList.clear();
    readySend44ChannelList.clear();

    /* 串口 */
    if(retransmissionTimer0x40->isActive()){
        retransmissionTimer0x40->stop();
    }
    if(retransmissionTimer0x41->isActive()){
        retransmissionTimer0x41->stop();
    }
    if(retransmissionTimer0x43->isActive()){
        retransmissionTimer0x43->stop();
    }
    if(retransmissionTimer0x44->isActive()){
        retransmissionTimer0x44->stop();
    }
    /* tcp */
    if(tcpRetransmissionTimer0x40->isActive()){
        tcpRetransmissionTimer0x40->stop();
    }
    if(tcpRetransmissionTimer0x41->isActive()){
        tcpRetransmissionTimer0x41->stop();
    }
    if(tcpRetransmissionTimer0x43->isActive()){
        tcpRetransmissionTimer0x43->stop();
    }
    if(tcpRetransmissionTimer0x44->isActive()){
        tcpRetransmissionTimer0x44->stop();
    }

    // currentSerialport.setDataTerminalReady(false);
    // currentSerialport.setRequestToSend(false);

    disconnect(&currentSerialport, &QSerialPort::readyRead, this, &termial::currentSerialport_readyRead);

    // 等待一段时间，确保信号生效
    QThread::msleep(100);

    if(currentSerialport.isOpen()){
        currentSerialport.close();  // 关闭串口
    }


    delete ui;

}


// 辅助函数


/**
 *  UI
 *  切换翻译
 *  @param  翻译文件在资源文件夹下的名字
 */
void termial::loadingLanguage(QString langName){
    if (!translator.load(langName, "://")) {
        debug("查找翻译文件失败");
    }
    qApp->installTranslator(&translator); // 如果加载成功，安装新翻译器
    // ui->retranslateUi(this); // 更新界面
}

/**
 *  异步加载翻译文件
 *  @param  翻译文件在资源文件夹下的名字
 */
void termial::loadLanguageAsync(const QString &langName) {
    QFuture<void> future = QtConcurrent::run(std::bind(&termial::loadingLanguage, this, langName));
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this, [this, watcher] {
        ui->retranslateUi(this); // 更新界面
        watcher->deleteLater();
    });
    watcher->setFuture(future);
}

/**
 *  天调发送辅助函数
 *  @return bool    true发送成功 false发送失败
 */
bool termial::tunerSend(QByteArray data){
    if(connectionName == "" || connectionName.isEmpty()){
        QMessageBox::warning(this, tr("警告") , tr("未连接串口或TCP!"));
        return false;
    }
    if(connectionName == "串口"){
        debug("使用串口连接");
        currentSerialport.write(data);
    }
    if(connectionName == "TCP"){
        if(tcpSocketList.isEmpty() || tcpSocketList.count() == 0){
            return false;
        }
        currentClient = getCurrentClientInfo();
        currentClient.getSocket()->write(data);
    }
    return true;
}



/**
 *  串口
 *  设备回复 0x40
 *  channel写
 */
void termial::serialHandleCommand0x40(channel& newChannel){

    // 判断回复的数据能否对应发送的命令
    // if(newChannel.getChannelID() != channelWrite.getChannelID()){
    //     debug("0x40 非当前要读取的数据,等待超时重发 newChannel:")<<newChannel.getChannelID() << " , channelWrite:" << channelWrite.getChannelID();
    //     return;
    // }

    // 关闭定时器
    if (retransmissionTimer0x40->isActive()) {
        retransmissionTimer0x40->stop();
    }

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend40ChannelList.isEmpty()){
        debug("写操作命令全部发送完成");
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->send_btn->setText(tr("发送"));
        return;
    }

    // 获取40列表中第一个命令,发送后删除对应命令
    serialPortTool.takeFirst40ListWrite(channelWrite,readySend40ChannelList,currentSerialport);

    // 启动定时器，等待200毫秒，超时重发
    retransmissionTimer0x40->start(200);
}

/**
 *  串口
 *  设备回复 0x41
 *  channel读
 */
void termial::serialHandleCommand0x41(channel& newChannel){
    int newRow = newChannel.getChannelID();

    // 判断回复的是否为当前要读取的数据
    // if(newChannel.getChannelID() != channelRead.getChannelID()){
    //     debug("0x41 非当前要读取的数据,等待超时重发 newChannel:")<<newChannel.getChannelID() << " , channelRead:" << channelRead.getChannelID();
    //     return;
    // }

    viewUpdate(newRow,newChannel);

    // 关闭定时器
    if (retransmissionTimer0x41->isActive()) {
        retransmissionTimer0x41->stop();
    }

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend41ChannelList.isEmpty()){
        debug("串口 0x41 全部发送完成");
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->read_btn->setText(tr("读取"));
        return;
    }

    // 获取41列表中第一个命令,发送后删除对应命令
    serialPortTool.takeFirst41ListWrite(channelRead,readySend41ChannelList,currentSerialport);

    // 启动定时器，等待50毫秒，超时重发
    retransmissionTimer0x41->start(100);
}

/**
 *  串口
 *  设备回复 0x43
 *  DMR写
 */
void termial::serialHandleCommand0x43(DMR& newDmr){
    // 判断回复是否为当前要数据的数据
    // if(newDmr.getChannelID() != dmrWrite.getChannelID()){
    //     debug("0x43 非当前要读取的数据,等待超时重发 newDmr:")<<newDmr.getChannelID() << " , dmrWrite:" << dmrWrite.getChannelID();
    //     return;
    // }

    if(retransmissionTimer0x43->isActive()){
        retransmissionTimer0x43->stop();
    }

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend43ChannelList.isEmpty()){
        debug("dmr命令List发送完毕");
        return;
    }

    serialPortTool.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentSerialport);

    retransmissionTimer0x43->start(200);
}

/**
 *  串口
 *  设备回复 0x44
 *  DMR读
 */
void termial::serialHandleCommand0x44(DMR& newDmr){
    /* dmr读取 */
    // if(newDmr.getChannelID() != dmrRead.getChannelID()){
    //     debug("串口 0x44 非当前要读取的数据,等待超时重发 newDmr:")<<newDmr.getChannelID() << " , dmrRead:" << dmrRead.getChannelID();
    //     return;
    // }

    int newRow = newDmr.getChannelID();
    viewUpdateDmr(newRow,newDmr);

    // 暂停定时器
    if(retransmissionTimer0x44->isActive()){
        retransmissionTimer0x44->stop();
    }

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend44ChannelList.isEmpty()){
        debug("串口 0x44 发送完毕");
        return;
    }

    serialPortTool.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentSerialport);

    // 启动定时器
    retransmissionTimer0x44->start(100);
}

/**
 *  tcp
 *  设备回复 0x40
 *  channel写
 */
void termial::handleCommand0x40(channel& newChannel){
    // 判断回复的数据能否对应发送的命令
    // if(newChannel.getChannelID() != channelWrite.getChannelID()){
    //     debug("非之前发送的数据,等待超时重发:")<<newChannel.getChannelID();
    //     return;
    // }

    // 关闭定时器
    if (tcpRetransmissionTimer0x40->isActive()) {
        tcpRetransmissionTimer0x40->stop();
    }

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend40ChannelList.isEmpty()){
        debug("tcp 0x40 全部发送完成");
        heartbeatTimer->start();
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->send_btn->setText(tr("发送"));
        return;
    }

    // 获得当前下拉框选择的IP 端口 客户端套接字
    currentClient = getCurrentClientInfo();
    // 获取40列表中第一个命令,发送后删除对应命令
    tcpTools.takeFirst40ListWrite(channelWrite,readySend40ChannelList,currentClient);

    // 启动定时器，等待50毫秒，超时重发
    tcpRetransmissionTimer0x40->start(200);
}

/**
 *  tcp
 *  设备回复 0x41
 *  channel读
 */
void termial::handleCommand0x41(channel& newChannel){
    // 判断回复的是否为当前要读取的数据
    // if(newChannel.getChannelID() != channelRead.getChannelID()){
    //     debug("非当前要读取的数据,等待超时重发")<<newChannel.getChannelID()<<channelRead.getChannelID();
    //     return;
    // }

    tcpRetransmissionTimer0x41->stop();

    int newRow = newChannel.getChannelID();
    viewUpdate(newRow,newChannel);  // 显示到UI

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend41ChannelList.isEmpty()){
        debug("tcp 0x41 全部发送完成");
        heartbeatTimer->start();
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->read_btn->setText(tr("读取"));
        return;
    }

    // 获得当前下拉框选择的IP 端口 客户端套接字
    currentClient = getCurrentClientInfo();
    // 获取41列表中第一个命令,发送后删除对应命令
    tcpTools.takeFirst41ListWrite(channelRead,readySend41ChannelList,currentClient);


    // 启动定时器，等待50毫秒，超时重发
    tcpRetransmissionTimer0x41->start(200);
}

/**
 *  tcp
 *  设备回复 0x43
 *  dmr写
 */
void termial::handleCommand0x43(DMR& newDmr){
    // if(newDmr.getCallID() != dmrWrite.getCallID()){
    //     debug("非之前发送的数据")<<newDmr.getCallID();
    //     return;
    // }

    if(tcpRetransmissionTimer0x43->isActive()){
        tcpRetransmissionTimer0x43->stop();
    }

    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend44ChannelList.isEmpty()){
        debug("tcp 0x43 全部发送完成");
        heartbeatTimer->start();    // 开启心跳包
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->send_btn->setText(tr("发送"));
        return;
    }

    debug("进入case 0x43,开始发送第一条list数据");
    currentClient = getCurrentClientInfo();
    tcpTools.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentClient);   // 发送List中的第一条数据

    // 启动定时器
    tcpRetransmissionTimer0x43->start(200);
}

/**
 *  tcp
 *  设备回复 0x44
 *  dmr读取
 */
void termial::handleCommand0x44(DMR& newDmr){
    // 按段回复的是否为当前要读取的数据
    // if(newDmr.getChannelID() != dmrRead.getChannelID()){
    //     debug("非当前要读取的数据,等待超时重发") << newDmr.getChannelID() <<dmrRead.getChannelID();
    //     return;
    // }

    int newRow = newDmr.getChannelID();
    viewUpdateDmr(newRow,newDmr);

    if(tcpRetransmissionTimer0x44->isActive()){
        tcpRetransmissionTimer0x44->stop();
    }

    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(readySend44ChannelList.isEmpty()){
        debug("44命令发送完毕");
        heartbeatTimer->start();    // 开启心跳包
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->read_btn->setText(tr("读取"));
        return;
    }

    currentClient = getCurrentClientInfo();
    tcpTools.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentClient);

    // 启动定时器
    tcpRetransmissionTimer0x44->start(100);
}

/**
 *  设备回复  0x46
 *  天调调谐指令
 */
void termial::handleCommand0x46(TUNER newTuner){
    switch(newTuner.getTuningMode()){
    case 0x00:
        ui->tunerCurrentModel_label->setText("自动调谐");
        break;
    case 0x01:
        ui->tunerCurrentModel_label->setText("手动调谐");
        break;
    case 0x03:
        ui->tunerCurrentModel_label->setText("关闭调谐");
        break;
    }
    // swtBtnGroup->button(newTuner.getTuningMode())->setChecked(true);
    double value = ((double)newTuner.getSwtv())/10;
    // ui->swtValue_doubleSpinBox->setValue(value);
    ui->swtValue_label->setText(QString::number(value));
    ui->swr_horizontalSlider->setValue(newTuner.getSwtv());
    // 关闭天调定时器
    if(tunerRetransmissionTimer0x46->isActive()){
        tunerRetransmissionTimer0x46->stop();
    }
    ui->SWT_pushButton->setText(tr("驻波调谐"));
}

/**
 *  设备回复  0x47
 *  天调同步
 */
void termial::handleCommand0x47(TUNER newTuner){
    // swtBtnGroup->button(newTuner.getTuningMode())->setChecked(true);
    switch(newTuner.getTuningMode()){
    case 0x00:
        ui->tunerCurrentModel_label->setText("自动调谐");
        break;
    case 0x01:
        ui->tunerCurrentModel_label->setText("手动调谐");
        break;
    case 0x03:
        ui->tunerCurrentModel_label->setText("关闭调谐");
        break;
    }
    double value = ((double)newTuner.getSwtv())/10;
    // ui->swtValue_doubleSpinBox->setValue(value);
    debug("((double)newTuner.getSwtv())/10:")<<value;
    ui->swtValue_label->setText(QString::number(value));
    ui->swr_horizontalSlider->setValue(newTuner.getSwtv());
    // ui->voltage_label->setText(QString::number(newTuner.getVoltage())+"V");
    double vv = (double)newTuner.getVoltage()/10;
    ui->voltage_lcdNumber->display(vv);

    // 关闭天调超时重发
    if(tunerRetransmissionTimer0x47->isActive()){
        tunerRetransmissionTimer0x47->stop();
    }
}

/**
 *  设备回复  0x48
 *  天调校准指令
 */
void termial::handleCommand0x48(TUNER newTuner){
    ui->PPc_label->setText(QString::number(newTuner.getPpcv()));
    ui->Swc_label->setText(QString::number(newTuner.getSwcv()));
    ui->Vc_label->setText(QString::number(newTuner.getVcv()));

    // ui->Vc_horizontalSlider->setValue(newTuner.getVcv());
    // ui->Swc_horizontalSlider->setValue(newTuner.getSwcv());
    // ui->PPc_horizontalSlider->setValue(newTuner.getPpcv());

    // 关闭天调定时器
    if(tunerRetransmissionTimer0x48->isActive()){
        tunerRetransmissionTimer0x48->stop();
    }
    ui->ATC_pushButton->setText(tr("天调校准"));
}

/**
 *  UI
 *  添加单条数据UI占位显示
 *  将一行数据添加到UI表格
 *  @value int row 所在行
 */
void termial::viewAddData(int row){
    /* 复选框 */
    QCheckBox *checkBox = new QCheckBox;
    checkBox->setChecked(false); // 设置复选框状态
    checkBox->setStyleSheet("margin-left:5%;"); // 居中显示
    ui->viewTable_tableWidget->setCellWidget(row, 0, checkBox); // 设置复选框到第0列
    checkBoxPrtList.append(checkBox);   // 方便反转和释放空间

    /* 信道号 */
    QTableWidgetItem* chId = new QTableWidgetItem(QString::number(row));
    chId->setFlags(chId->flags() & ~Qt::ItemIsEditable);    // 设置不可修改
    chId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter); // 水平垂直居中
    ui->viewTable_tableWidget->setItem(row,1,chId);  // 信道号

    /* name */
    QTableWidgetItem* chName = new QTableWidgetItem();
    chName->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter); // 水平垂直居中
    ui->viewTable_tableWidget->setItem(row,2,chName);    // name

    /* VFOA频率 */
    QTableWidgetItem* VFOAfreq = new QTableWidgetItem();
    VFOAfreq->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter); // 水平垂直居中
    ui->viewTable_tableWidget->setItem(row,3,VFOAfreq);  // VFOA频率

    /* VFOB频率 */
    QTableWidgetItem* VFOBfreq = new QTableWidgetItem();
    VFOBfreq->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter); // 水平垂直居中
    ui->viewTable_tableWidget->setItem(row,4,VFOBfreq); // VFOB频率

    /* VFOA模式 */
    // 设置为下拉框
    QComboBox *vfoaComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,5,vfoaComboBoxPtr);   // VFOA模式
    vfoaComboBoxPtrList.append(vfoaComboBoxPtr);    // 放入指针集合，方便释放空间

    /* VFOB模式 */
    QComboBox *vfobComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,6,vfobComboBoxPtr);   // VFOB模式
    vfobComboBoxPtrList.append(vfobComboBoxPtr);    // 放入指针集合，方便释放空间

    /* 发射亚音 */
    QComboBox *EmitYayinComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,7,EmitYayinComboBoxPtr);   // 显示
    EmitYayinComboBoxPtrList.append(EmitYayinComboBoxPtr);  // 等待被释放

    /* 接收亚音 */
    QComboBox *ReceiveYayinComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,8,ReceiveYayinComboBoxPtr);
    ReceiveYayinComboBoxPtrList.append(ReceiveYayinComboBoxPtr);

    /* Call_Format / CALL_TYPE */
    QComboBox *callTypeComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,9,callTypeComboBoxPtr);    // 显示
    callTypeComboBoxPtrList.append(callTypeComboBoxPtr);    // 放入指针集合
    callTypeComboBoxPtr->setEnabled(false);

    /* TX_CC */
    QSpinBox *txCcSpinBoxPtr = new QSpinBox;
    ui->viewTable_tableWidget->setCellWidget(row, 10, txCcSpinBoxPtr);
    txCcSpinBoxPtrList.append(txCcSpinBoxPtr);  // 方便二次使用
    txCcSpinBoxPtr->setEnabled(false);

    /* RX_CC */
    QSpinBox *rxCcSpinBoxPtr = new QSpinBox;
    ui->viewTable_tableWidget->setCellWidget(row, 11, rxCcSpinBoxPtr);
    rxCcSpinBoxPtrList.append(rxCcSpinBoxPtr);  // 方便二次使用
    rxCcSpinBoxPtr->setEnabled(false);

    /* SLOT */
    QSpinBox *slotSpinBoxPtr = new QSpinBox;
    ui->viewTable_tableWidget->setCellWidget(row, 12, slotSpinBoxPtr);
    slotSpinBoxPtrList.append(slotSpinBoxPtr);  // 方便二次使用
    slotSpinBoxPtr->setEnabled(false);

    /* CALL_ID */
    QTableWidgetItem* dmrCallId = new QTableWidgetItem();
    dmrCallId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    ui->viewTable_tableWidget->setItem(row,13,dmrCallId);
    dmrCallId->setFlags(dmrCallId->flags() & ~Qt::ItemIsEditable);

    /* Own_id */
    QTableWidgetItem* dmrOwnId = new QTableWidgetItem();
    dmrOwnId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    ui->viewTable_tableWidget->setItem(row,14,dmrOwnId);
    dmrOwnId->setFlags(dmrCallId->flags() & ~Qt::ItemIsEditable);

    /* CH_TYPE */
    QComboBox *chTypeComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,15,chTypeComboBoxPtr);
    chTypeComboBoxPtrList.append(chTypeComboBoxPtr);
    chTypeComboBoxPtr->setEnabled(false);

    /* RX_CTCSS */
    QComboBox *rxCtcssComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,16,rxCtcssComboBoxPtr);
    rxCtcssComboBoxPtrList.append(rxCtcssComboBoxPtr);
    rxCtcssComboBoxPtr->setEnabled(false);

    // TX_CTCSS
    QComboBox *txCtcssComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,17,txCtcssComboBoxPtr);
    txCtcssComboBoxPtrList.append(txCtcssComboBoxPtr);
    txCtcssComboBoxPtr->setEnabled(false);

    // SQL / Sqlevel
    QSpinBox *sqlevelSpinBox = new QSpinBox;
    ui->viewTable_tableWidget->setCellWidget(row, 18, sqlevelSpinBox);
    sqlevelSpinBoxPtrList.append(sqlevelSpinBox);  // 方便二次使用
    sqlevelSpinBox->setEnabled(false);

    // SPK / spkgain
    QSpinBox *spkgainSpinBox = new QSpinBox;
    // 在 QTableWidget 中指定的位置添加 QSpinBox
    ui->viewTable_tableWidget->setCellWidget(row, 19, spkgainSpinBox);
    spkgainSpinBoxPtrList.append(spkgainSpinBox);  // 方便二次使用
    spkgainSpinBox->setEnabled(false);

    // RX_GAIN / dmod_gain
    QSpinBox *rxGainSpinBox = new QSpinBox;
    // 在 QTableWidget 中指定的位置添加 QSpinBox
    ui->viewTable_tableWidget->setCellWidget(row, 20, rxGainSpinBox);
    rxGainSpinBoxPtrList.append(rxGainSpinBox);  // 方便二次使用
    rxGainSpinBox->setEnabled(false);

    // ENCRY / scr_en
    QComboBox *enScrComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,21,enScrComboBoxPtr);
    enScrComboBoxPtrList.append(enScrComboBoxPtr);
    enScrComboBoxPtr->setEnabled(false);

    // SEED / scr_seed
    QTableWidgetItem* dmrSEED = new QTableWidgetItem();
    dmrSEED->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    ui->viewTable_tableWidget->setItem(row,22,dmrSEED);
    dmrSEED->setFlags(dmrSEED->flags() & ~Qt::ItemIsEditable);

    // BSMODE / ch_bs_mode
    QComboBox *bsModeComboBoxPtr = new QComboBox;
    ui->viewTable_tableWidget->setCellWidget(row,23,bsModeComboBoxPtr);
    bsModeComboBoxPtrList.append(bsModeComboBoxPtr);
    bsModeComboBoxPtr->setEnabled(false);
}



/**
 *  UI
 *  单条UI修改
 *  将一行channel数据进行修改
 *  @value int row 所在行
 *  @value channel& newChannel 一条数据源
 */
void termial::viewUpdate(int row, channel &newChannel){
    // 复选框
    QCheckBox *checkBox = checkBoxPrtList[row];
    checkBox->setChecked(false); // 设置复选框状态

    // 信道号
    QTableWidgetItem* chId = ui->viewTable_tableWidget->item(row, 1);
    chId->setText(QString::number(newChannel.getChannelID()));

    // name
    /* 使name不显示\0位 */
    QByteArray temp= newChannel.getChannelName();
    QByteArray name;
    for(auto i = temp.begin(); i != temp.end(); ++i){
        if(*i != '\0'){
            name.append(*i);
        }
    }
    QTableWidgetItem* chName = ui->viewTable_tableWidget->item(row, 2);
    chName->setText(name);

    // vfoa频率
    QTableWidgetItem* VFOAfreq = ui->viewTable_tableWidget->item(row, 3);
    VFOAfreq->setText(QString::number(newChannel.getVfoaFrequency()));

    // vfob频率
    QTableWidgetItem* VFOBfreq = ui->viewTable_tableWidget->item(row, 4);
    VFOBfreq->setText(QString::number(newChannel.getVfobFrequency()));

    // vfoa模式
    QComboBox *vfoaComboBoxPtr = vfoaComboBoxPtrList[row];
    if(vfoaComboBoxPtr->count()==0)
        tool.setVfoComboBoxPtr(vfoaComboBoxPtr);
    connect(vfoaComboBoxPtr,QOverload<int>::of(&QComboBox::currentIndexChanged),this, [this, row](int index) {
        vfoaComboBoxIndexChanged(row, index);
    });// 当模式下拉框变化时
    vfoaComboBoxPtr->setCurrentIndex(newChannel.getVfoaMode());

    // vfob模式
    QComboBox *vfobComboBoxPtr = vfobComboBoxPtrList[row];
    if(vfobComboBoxPtr->count()==0)
        tool.setVfoComboBoxPtr(vfobComboBoxPtr);
    connect(vfobComboBoxPtr,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[this, row](int index) {
        vfobComboBoxIndexChanged(row, index);
    }); // 当模式下拉框变化时
    vfobComboBoxPtr->setCurrentIndex(newChannel.getVfobMode());

    // 发射亚音
    QComboBox *emitYayin = EmitYayinComboBoxPtrList[row];
    if(emitYayin->count()==0)
        tool.setYayinComboBoxPtr(emitYayin);  // 给下拉框添加数据
    emitYayin->setCurrentIndex(newChannel.getEmitYayin());

    // 接收亚音
    QComboBox *receiveYayin = ReceiveYayinComboBoxPtrList[row];
    if(receiveYayin->count()==0)
        tool.setYayinComboBoxPtr(receiveYayin);   // 给下拉框添加数据
    receiveYayin->setCurrentIndex(newChannel.getReceiveYayin());
}

/**
 *  UI
 *  单条UI修改
 *  将一行dmr数据进行修改
 *  @param  int row 所在行
 *  @param  DMR& newDMR 一条数据源
 */
void termial::viewUpdateDmr(int row,DMR& newDMR){


    // call_format / callType
    QComboBox *callTypeComboBoxPtr = callTypeComboBoxPtrList[row];
    if(callTypeComboBoxPtr->count()==0){
        callTypeComboBoxPtr->addItem("Single");
        callTypeComboBoxPtr->addItem("Group");
        callTypeComboBoxPtr->addItem("All");
    }
    callTypeComboBoxPtr->setCurrentIndex(newDMR.getCallFormat());

    // Tx_cc
    QSpinBox* txCcSpinBoxPtr = txCcSpinBoxPtrList[row];
    txCcSpinBoxPtr->setMinimum(0);
    txCcSpinBoxPtr->setMaximum(15);
    txCcSpinBoxPtr->setValue(newDMR.getTxCc());

    // Rx_cc
    QSpinBox* rxCcSpinBoxPtr = rxCcSpinBoxPtrList[row];
    rxCcSpinBoxPtr->setMinimum(0);
    rxCcSpinBoxPtr->setMaximum(15);
    rxCcSpinBoxPtr->setValue(newDMR.getRxCc());

    // slot
    QSpinBox* slotSpinBoxPtr = slotSpinBoxPtrList[row];
    slotSpinBoxPtr->setMinimum(1);
    slotSpinBoxPtr->setMaximum(2);
    slotSpinBoxPtr->setValue(newDMR.getSlot());

    // call_id
    QTableWidgetItem* callId = ui->viewTable_tableWidget->item(row,13);
    callId->setText(QString::number(newDMR.getCallID()));

    // own_id
    QTableWidgetItem* ownId = ui->viewTable_tableWidget->item(row,14);
    ownId->setText(QString::number(newDMR.getOwnID()));

    // ch_type
    QComboBox* chTypeComboBoxPtr = chTypeComboBoxPtrList[row];
    if(chTypeComboBoxPtr->count()==0){
        chTypeComboBoxPtr->addItem("DFM");
        chTypeComboBoxPtr->addItem("DMR");
    }
    chTypeComboBoxPtr->setCurrentIndex(0); // 0~1
    chTypeComboBoxPtr->setCurrentIndex(newDMR.getChType());

    // Rx_ctcss
    QComboBox* rxCtcssComboBoxPtr = rxCtcssComboBoxPtrList[row];
    if(rxCtcssComboBoxPtr->count()==0)
        tool.setRxTxCtcssComboBoxPtr(rxCtcssComboBoxPtr);
    rxCtcssComboBoxPtr->setCurrentIndex(newDMR.getRxCtcss());

    // Tx_ctcss
    QComboBox* txCtcssComboBoxPtr = txCtcssComboBoxPtrList[row];
    if(txCtcssComboBoxPtr->count()==0)
        tool.setRxTxCtcssComboBoxPtr(txCtcssComboBoxPtr);
    txCtcssComboBoxPtr->setCurrentIndex(newDMR.getTxCtcss());

    // sqlevel
    QSpinBox* sqlevelSpinBox = sqlevelSpinBoxPtrList[row];
    sqlevelSpinBox->setMinimum(1);
    sqlevelSpinBox->setMaximum(5);
    sqlevelSpinBox->setValue(newDMR.getSqlevel());

    // spkgain
    QSpinBox* spkgainSpinBox = spkgainSpinBoxPtrList[row];
    spkgainSpinBox->setMinimum(0);
    spkgainSpinBox->setMaximum(10);
    spkgainSpinBox->setValue(newDMR.getSpkgain());

    // RX_GAIN / dmod_gain
    QSpinBox* rxGainSpinBox = rxGainSpinBoxPtrList[row];
    rxGainSpinBox->setMinimum(0);
    rxGainSpinBox->setMaximum(95);
    rxGainSpinBox->setValue(newDMR.getDmodGain());

    // scr_en
    QComboBox* enScrComboBoxPtr = enScrComboBoxPtrList[row];
    if(enScrComboBoxPtr->count()==0){
        enScrComboBoxPtr->addItem("不加密");
        enScrComboBoxPtr->addItem("加密");
    }
    enScrComboBoxPtr->setCurrentIndex(newDMR.getScrEn());

    // scr_send
    QTableWidgetItem* scrSend = ui->viewTable_tableWidget->item(row,22);
    scrSend->setText(QString::number(newDMR.getScrSend()));

    // ch_bs_mode
    QComboBox* bsModeComboBoxPtr = bsModeComboBoxPtrList[row];
    if(bsModeComboBoxPtr->count()==0){
        bsModeComboBoxPtr->addItem("BS");
        bsModeComboBoxPtr->addItem("MS");
    }
    bsModeComboBoxPtr->setCurrentIndex(newDMR.getChBsMode());
}

/**
 *  UI
*   读取该行数据为channel对象
*   @value  行号
*   @return channel 对象
*/
channel termial::rowReadDataToChannel(int row){
    channel rowChannel;   // channel对象
    unsigned short channelValue;  // 存放信道号

    // 读取该行的数据
    for (int col = 0; col < ui->viewTable_tableWidget->columnCount(); ++col) {
        QTableWidgetItem *cellItem = nullptr;
        QComboBox *comboBox = nullptr;

        switch(col){
        case 0:
            // checkBox = qobject_cast<QCheckBox*>(ui->viewTable_tableWidget->cellWidget(row, col));
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            cellItem = ui->viewTable_tableWidget->item(row, col);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            comboBox = qobject_cast<QComboBox*>(ui->viewTable_tableWidget->cellWidget(row, col));
            break;
        }

        // 将本行数据放入channel对象
        switch(col){
        case 0:
            /* 复选框 */
            break;
        case 1:
        {
            // 信道号，将它拆分成两个1字节数据
            channelValue = cellItem->text().toUInt();

            rowChannel.setChannelHigh(static_cast<unsigned char>((channelValue >> 8) & 0xFF));
            rowChannel.setChannelLow(static_cast<unsigned char>(channelValue & 0xFF));
        }
        break;
        case 2:
        {
            // 信道名称
            QByteArray temp = cellItem->text().toUtf8();
            // 判断输入是否超过11字节，若超过直接截断
            if(temp.length()>11){
                temp = temp.left(11);
            }
            // 不足12字节的位置补0
            while(temp.length()<12){
                temp.append('\0');
            }

            rowChannel.setChannelName(temp);
        }
        break;
        case 3:
        {   // vfoa频率
            unsigned long long temp = cellItem->text().toLongLong();
            if(temp>4294967295){
                unsigned int vfaFreq = 300003000;
                rowChannel.setVfoaFrequency1(static_cast<unsigned char>((vfaFreq >> 24) & 0xFF));
                rowChannel.setVfoaFrequency2(static_cast<unsigned char>((vfaFreq >> 16) & 0xFF));
                rowChannel.setVfoaFrequency3(static_cast<unsigned char>((vfaFreq >> 8) & 0xFF));
                rowChannel.setVfoaFrequency4(static_cast<unsigned char>(vfaFreq & 0xFF));
                break;
            }
            // VFA_FREQ vfoa频率，拆分为4个1字节数据
            unsigned int vfaFreq = cellItem->text().toUInt();
            rowChannel.setVfoaFrequency1(static_cast<unsigned char>((vfaFreq >> 24) & 0xFF));
            rowChannel.setVfoaFrequency2(static_cast<unsigned char>((vfaFreq >> 16) & 0xFF));
            rowChannel.setVfoaFrequency3(static_cast<unsigned char>((vfaFreq >> 8) & 0xFF));
            rowChannel.setVfoaFrequency4(static_cast<unsigned char>(vfaFreq & 0xFF));
        }
        break;
        case 4:
        {   // vfob频率
            unsigned long long temp = cellItem->text().toLongLong();
            if(temp>4294967295){
                unsigned int vfbFreq = 300003000;
                rowChannel.setVfoaFrequency1(static_cast<unsigned char>((vfbFreq >> 24) & 0xFF));
                rowChannel.setVfoaFrequency2(static_cast<unsigned char>((vfbFreq >> 16) & 0xFF));
                rowChannel.setVfoaFrequency3(static_cast<unsigned char>((vfbFreq >> 8) & 0xFF));
                rowChannel.setVfoaFrequency4(static_cast<unsigned char>(vfbFreq & 0xFF));
                break;
            }
            // VFB_FREQ vfob频率，拆分为4个1字节数据
            unsigned int vfbFreq = cellItem->text().toUInt();
            rowChannel.setVfobFrequency1(static_cast<unsigned char>((vfbFreq >> 24) & 0xFF));
            rowChannel.setVfobFrequency2(static_cast<unsigned char>((vfbFreq >> 16) & 0xFF));
            rowChannel.setVfobFrequency3(static_cast<unsigned char>((vfbFreq >> 8) & 0xFF));
            rowChannel.setVfobFrequency4(static_cast<unsigned char>(vfbFreq & 0xFF));
        }
        break;
        case 5:
        {
            // VFA_MODE vfoa模式
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index); // 下拉框的索引与模式编码一致
                rowChannel.setVfoaMode(mode);
            }
        }
        break;
        case 6:
            // VFB_MODE vfob模式
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowChannel.setVfobMode(mode);
            }
            break;
        case 7:
            // T_CTCSS 发送亚音
            if(comboBox){
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowChannel.setEmitYayin(mode);
            }
            break;
        case 8:
            // R_CTCSS 接收亚音
            if(comboBox){
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowChannel.setReceiveYayin(mode);
            }
            break;
        }
    }
    return rowChannel;
}

/**
 *  UI
 *  读取该行数据为DMR对象
 *  @param  int row 行号
 *  @return DMR 对象
 */
DMR termial::rowReadDataToDmr(int row){
    DMR rowDmr;
    unsigned short channelValue;  // 存放信道号

    // 读取该行的数据
    for (int col = 0; col < ui->viewTable_tableWidget->columnCount(); ++col) {
        QTableWidgetItem *cellItem = nullptr;
        QComboBox *comboBox = nullptr;
        QSpinBox *spinBox = nullptr;

        switch (col) {
        case 1:
        case 13:
        case 14:
        case 22:
            cellItem = ui->viewTable_tableWidget->item(row, col);
            break;
        case 9:
        case 15:
        case 16:
        case 17:
        case 21:
        case 23:
            comboBox = qobject_cast<QComboBox*>(ui->viewTable_tableWidget->cellWidget(row, col));
            break;
        case 10:
        case 11:
        case 12:
        case 18:
        case 19:
        case 20:
            spinBox = qobject_cast<QSpinBox*>(ui->viewTable_tableWidget->cellWidget(row, col));
            break;
        default:
            break;
        }

        switch (col) {
        case 1: {
            if (cellItem) {
                // 信道号，将它拆分成两个1字节数据
                channelValue = cellItem->text().toUInt();
                rowDmr.setChannelHigh(static_cast<unsigned char>((channelValue >> 8) & 0xFF));
                rowDmr.setChannelLow(static_cast<unsigned char>(channelValue & 0xFF));
            }
            break;
        }
        case 9: {
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setCallFormat(mode);
            }
            break;
        }
        case 10: {
            if (spinBox) {
                int data = spinBox->value();
                unsigned char mode = static_cast<unsigned char>(data);
                rowDmr.setTxCc(mode);
            }
            break;
        }
        case 11: {
            if (spinBox) {
                int index = spinBox->value();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setRxCc(mode);
            }
            break;
        }
        case 12: {
            if (spinBox) {
                int index = spinBox->value();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setSlot(mode);
            }
            break;
        }
        case 13: {
            if (cellItem) {
                unsigned long long temp = cellItem->text().toLongLong();
                if (temp > 16777214) {
                    rowDmr.setCallID(0);
                } else {
                    unsigned int callid = cellItem->text().toUInt();
                    rowDmr.setCallID(callid);
                }
            }
            break;
        }
        case 14: {
            if (cellItem) {
                unsigned long long temp = cellItem->text().toLongLong();
                if (temp > 16777214) {
                    rowDmr.setOwnID(0);
                } else {
                    unsigned int ownid = cellItem->text().toUInt();
                    rowDmr.setOwnID(ownid);
                }
            }
            break;
        }
        case 15: {
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setChType(mode);
            }
            break;
        }
        case 16: {
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setRxCtcss(mode);
            }
            break;
        }
        case 17: {
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setTxCtcss(mode);
            }
            break;
        }
        case 18: {
            if (spinBox) {
                int index = spinBox->value();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setSqlevel(mode);
            }
            break;
        }
        case 19: {
            if (spinBox) {
                int index = spinBox->value();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setSpkgain(mode);
            }
            break;
        }
        case 20: {
            if (spinBox) {
                int index = spinBox->value();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setDmodGain(mode);
            }
            break;
        }
        case 21: {
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setScrEn(mode);
            }
            break;
        }
        case 22: {
            if (cellItem) {
                unsigned long long temp = cellItem->text().toLongLong();
                if (temp > 65535) {
                    rowDmr.setScrSend(0);
                } else {
                    unsigned short mode = static_cast<unsigned short>(cellItem->text().toUShort());
                    rowDmr.setScrSend(mode);
                }
            }
            break;
        }
        case 23: {
            if (comboBox) {
                int index = comboBox->currentIndex();
                unsigned char mode = static_cast<unsigned char>(index);
                rowDmr.setChBsMode(mode);
            }
            break;
        }
        default:
            break;
        }
    }
    return rowDmr;
}

/**
 *  UI
 *  辅助函数
 *  修改DMR状态
 */
void termial::updateDmrWidgetsState(int row) {
    bool isDmr = vfoaModeIsDmr || vfobModeIsDmr;
    if (isDmr) {
        callTypeComboBoxPtrList[row]->setEnabled(true);
        txCcSpinBoxPtrList[row]->setEnabled(true);
        rxCcSpinBoxPtrList[row]->setEnabled(true);
        slotSpinBoxPtrList[row]->setEnabled(true);
        QTableWidgetItem* callid = ui->viewTable_tableWidget->item(row, 13);
        if (callid) {
            callid->setFlags(callid->flags() | Qt::ItemIsEditable);
        }
        QTableWidgetItem* ownid = ui->viewTable_tableWidget->item(row, 14);
        if (ownid) {
            ownid->setFlags(ownid->flags() | Qt::ItemIsEditable);
        }
        chTypeComboBoxPtrList[row]->setEnabled(true);
        rxCtcssComboBoxPtrList[row]->setEnabled(true);
        txCtcssComboBoxPtrList[row]->setEnabled(true);
        sqlevelSpinBoxPtrList[row]->setEnabled(true);
        spkgainSpinBoxPtrList[row]->setEnabled(true);
        rxGainSpinBoxPtrList[row]->setEnabled(true);
        enScrComboBoxPtrList[row]->setEnabled(true);
        QTableWidgetItem* srcsend = ui->viewTable_tableWidget->item(row, 22);
        if (srcsend) {
            srcsend->setFlags(srcsend->flags() | Qt::ItemIsEditable);
        }
        bsModeComboBoxPtrList[row]->setEnabled(true);
    } else {
        callTypeComboBoxPtrList[row]->setEnabled(false);
        txCcSpinBoxPtrList[row]->setEnabled(false);
        rxCcSpinBoxPtrList[row]->setEnabled(false);
        slotSpinBoxPtrList[row]->setEnabled(false);
        QTableWidgetItem* callid = ui->viewTable_tableWidget->item(row, 13);
        if (callid) {
            callid->setFlags(callid->flags() & ~Qt::ItemIsEditable);
        }
        QTableWidgetItem* ownid = ui->viewTable_tableWidget->item(row, 14);
        if (ownid) {
            ownid->setFlags(ownid->flags() & ~Qt::ItemIsEditable);
        }
        chTypeComboBoxPtrList[row]->setEnabled(false);
        rxCtcssComboBoxPtrList[row]->setEnabled(false);
        txCtcssComboBoxPtrList[row]->setEnabled(false);
        sqlevelSpinBoxPtrList[row]->setEnabled(false);
        spkgainSpinBoxPtrList[row]->setEnabled(false);
        rxGainSpinBoxPtrList[row]->setEnabled(false);
        enScrComboBoxPtrList[row]->setEnabled(false);
        QTableWidgetItem* srcsend = ui->viewTable_tableWidget->item(row, 22);
        if (srcsend) {
            srcsend->setFlags(srcsend->flags() & ~Qt::ItemIsEditable);
        }
        bsModeComboBoxPtrList[row]->setEnabled(false);
    }
}

/**
 *  UI
 *  辅助函数
 *  遍历所有复选框,将勾选行加入List<channel>
 */
void termial::getAllCheckedRowsToList(QList<channel> &readySendChannelList){
    for(int i = 0; i < ui->viewTable_tableWidget->rowCount(); i++){
        // 复选框所在的列号
        int checkBoxColumn = 0;
        // 获取该行的复选框
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(ui->viewTable_tableWidget->cellWidget(i, checkBoxColumn));
        if(checkBox && checkBox->isChecked()){
            channel rowChannel = rowReadDataToChannel(i);
            readySendChannelList.append(rowChannel);
        }
    }
}

/**
 *  UI
 *  辅助函数
 *  遍历所有复选框,将勾选的行加入List<DMR>
 */
void termial::getAllCheckedRowsToListDmr(QList<DMR> &readySendDmrList){
    for(int i = 0; i < ui->viewTable_tableWidget->rowCount(); i++){
        // 复选框所在的列号
        int checkBoxColumn = 0;
        // 获取该行的复选框
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(ui->viewTable_tableWidget->cellWidget(i, checkBoxColumn));
        if(checkBox && checkBox->isChecked()){
            DMR rowDmr = rowReadDataToDmr(i);
            readySendDmrList.append(rowDmr);
        }
    }
}

/**
 *  UI  json
 *  让用户选择保存位置,返回路径
 *  @value QWidget *parent  父窗口,用来指定位置
 *  @value const QString &filter    文件过滤器,用;;分隔
 *  @return QString filePath    返回选择的文件路径
 */
QString termial::getUserSaveLocation(QWidget *parent, const QString &filter) {
    // 显示文件保存对话框
    QString filePath = QFileDialog::getSaveFileName(parent,tr("保存文件"),"",filter);

    return filePath;
}

/**
 *  UI  json
*   将json数据保存到文件
*   @value const QJsonObject& obj   json数据对象
*   @value const QString& filePath  保存的文件路径
*   @return bool 是否保存成功
*/
bool termial::saveQJsonObjectToFile(const QJsonObject& obj, const QString& filePath) {
    QJsonDocument doc(obj);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson());
        file.close();
        return true;
    }
    return false;
}


/**
 *  UI
 *  获得当前下拉框选择的IP 端口
 *  @return   ClientInfo    返回获取到下拉框选择的ClientInfo自定义对象
 */
ClientInfo termial::getCurrentClientInfo(){
    QString selectedClient = ui->connectedDevices_comboBox->currentText();
    ClientInfo currentClient;
    for (const ClientInfo& client : tcpSocketList) {
        if (client.getIp() + ":" + QString::number(client.getPort()) == selectedClient) {
            currentClient = client;
        }
    }
    return currentClient;
}



// 初始化
/**
 *  初始化connect
 */
void termial::initConnect(){

    /* 语言切换 */
    connect(ui->language_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this,&termial::switchLanguage);
    /* 页切换时 */
    connect(ui->tabWidget, QOverload<int>::of(&QTabWidget::currentChanged), this, &termial::tabWidgetSwitch);
    /* 发送/读取 按钮点击时 */
    connect(ui->send_btn, &QPushButton::clicked, this, &termial::send_clicked);
    connect(ui->read_btn, &QPushButton::clicked, this, &termial::read_clicked);

    // 串口有数据可读时触发
    connect(&currentSerialport, &QSerialPort::readyRead, this, &termial::currentSerialport_readyRead);
    // 串口下拉框发生变化时
    connect(ui->serialport_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &termial::serialportComboBox_currentIndexChanged);
    /* 串口按钮 */
    connect(ui->serialportLink_pushButton, &QPushButton::clicked, this, &termial::serialportLinkBtn_clicked); // 串口连接按钮点击时

    /* 串口 定时器超时信号 */
    connect(retransmissionTimer0x40, &QTimer::timeout, this, &termial::onTimeout0x40);
    connect(retransmissionTimer0x41, &QTimer::timeout, this, &termial::onTimeout0x41);
    connect(retransmissionTimer0x43, &QTimer::timeout, this, &termial::onTimeout0x43);
    connect(retransmissionTimer0x44, &QTimer::timeout, this, &termial::onTimeout0x44);
    /* tcp 定时器超时信号 */
    connect(tcpRetransmissionTimer0x40, &QTimer::timeout, this, &termial::tcpOnTimeout0x40);
    connect(tcpRetransmissionTimer0x41, &QTimer::timeout, this, &termial::tcpOnTimeout0x41);
    connect(tcpRetransmissionTimer0x43, &QTimer::timeout, this, &termial::tcpOnTimeout0x43);
    connect(tcpRetransmissionTimer0x44, &QTimer::timeout, this, &termial::tcpOnTimeout0x44);
    /* 天调 定时器超时信号 */
    connect(tunerRetransmissionTimer0x46, &QTimer::timeout, this, &termial::tunerOnTimer0x46);
    connect(tunerRetransmissionTimer0x47, &QTimer::timeout, this, &termial::tunerOnTimer0x47);
    connect(tunerRetransmissionTimer0x48, &QTimer::timeout, this, &termial::tunerOnTimer0x48);

    /* TCP按钮 */
    connect(ui->tcpOpen_pushButton, &QPushButton::clicked, this, &termial::tcpOpenBtn_clicked);


    // 监听单行文本框的回车按下事件
    connect(ui->channelNum_lineEdit, &QLineEdit::returnPressed, this, &termial::channelNumLineEdit_returnPressed);
    // 监听全选按钮点击事件
    connect(ui->checkAll_pushButton, &QPushButton::clicked, this, &termial::checkAllBtn_clicked);
    // 监听全不选按钮点击事件
    connect(ui->checkNotAll_pushButton, &QPushButton::clicked, this, &termial::checkAllNotBtn_clicked);

    // 监听保存为json点击事件
    connect(ui->save_pushButton, &QPushButton::clicked, this, &termial::saveBtn_clicked);
    // 监听打开按钮点击事件
    connect(ui->open_pushButton, &QPushButton::clicked, this, &termial::openBtn_clicked);
    // 监听串口刷新按钮点击事件
    connect(ui->serialportFlash_pushButton, &QPushButton::clicked, this, &termial::serialportFlashBtn_clicked);

    /* 天调 */
    connect(ui->SWT_pushButton, &QPushButton::clicked, this, &termial::swtBtn_clicked);
    // connect(ui->TUNER_synchronous_pushButton, &QPushButton::clicked,this, &termial::TUNER_synchronousBtn_clicked);
    connect(ui->ATC_pushButton, &QPushButton::clicked, this, &termial::ATCbtn_clicked);
    // 滑块变动
    connect(ui->Swc_horizontalSlider,&QSlider::valueChanged,this,&termial::swcHorizontalSlier_valueChanged);
    connect(ui->PPc_horizontalSlider,&QSlider::valueChanged,this,&termial::ppcHorizontalSlier_valueChanged);
    connect(ui->Vc_horizontalSlider, &QSlider::valueChanged,this,&termial::vcHorizontalSlier_valueChanged);
    //
    connect(ui->Vcv_spinBox, &QSpinBox::valueChanged,this,&termial::vcvSpinBox_valueChanged);
    connect(ui->PPcv_spinBox, &QSpinBox::valueChanged,this,&termial::ppcvSpinBox_valueChanged);
    connect(ui->Swcv_spinBox, &QSpinBox::valueChanged,this,&termial::swcvSpinBox_valueChanged);
    //
    connect(ui->swtValue_doubleSpinBox, &QDoubleSpinBox::valueChanged, this,&termial::swtDoubleSpinBox_valueChanged);
    connect(ui->swtValue_dial, &QDial::valueChanged,this, &termial::swtDial_valueChanged);
}

/**
 *  初始化语言下拉框
 */
void termial::initLanguageComboBox(){
    ui->language_comboBox->addItem("中文");
    ui->language_comboBox->addItem("English");
    ui->language_comboBox->addItem("Français");
    ui->language_comboBox->addItem("بالعربية");
    ui->language_comboBox->addItem("deutsch");
    ui->language_comboBox->addItem("日本語");
    ui->language_comboBox->addItem("Português");
    ui->language_comboBox->addItem("Русский язык");
    ui->language_comboBox->addItem("Español");
    ui->language_comboBox->addItem("हिंदी भाषा");
}

/**
 *  初始化天调驻波调谐 单选框
 */
void termial::initTunerSwtRadioBtn(){
    swtBtnGroup = new QButtonGroup;
    swtBtnGroup->addButton(ui->auto_radioButton,0);
    swtBtnGroup->addButton(ui->start_radioButton,1);
    swtBtnGroup->addButton(ui->close_radioButton,3);
    swtBtnGroup->button(0)->setChecked(true);
}

/**
 *  初始化
 *  初始化美术
 *  包括图标,背景等
 */
void termial::initArt()
{
    // 图标
    this->setWindowIcon(QIcon("://GHTermial.ico"));
    ui->swr_horizontalSlider->setEnabled(false);

    // ui->viewTable_tableWidget->setStyleSheet("background-color:darkgray");
    // this->setStyleSheet("background-color:darkgray");
    // ui->control->setStyleSheet("background-color:#330019");
    // ui->tools->setStyleSheet("background-color:#C0C0C0");
    // ui->data->setStyleSheet("background-color:#C0C0C0");
    // ui->viewTable_tableWidget->setStyleSheet("background-color:#D5CFCF");
    // ui->viewTable_tableWidget->setStyleSheet("border:none;");
}

/**
*   初始化表格的行列头
*/
void termial::initViewTableHaed(){

    ui->viewTable_tableWidget->setColumnCount(24);
    QStringList tableCplumnHeader;

    tool.setTableHeader(tableCplumnHeader); // 初始化表头

    ui->viewTable_tableWidget->setHorizontalHeaderLabels(tableCplumnHeader);    // 设置水平头部
    debug("初始化表格的行列头");

}

/**
 *  UI
 *  提前生成1000空白行
 */
void termial::initViewTable1000Col(){
    // 清除所有行
    ui->viewTable_tableWidget->clearContents();
    ui->viewTable_tableWidget->setRowCount(0);

    // 取消行头显示
    ui->viewTable_tableWidget->verticalHeader()->setVisible(false);
    // 一次性设置行数
    ui->viewTable_tableWidget->setRowCount(1000);

    ui->viewTable_tableWidget->setUpdatesEnabled(false); // 关闭自动更新
    debug("开始生成:")<<QTime::currentTime();
    /* 生成1000行占位 */
    for(int i = 0; i < ui->viewTable_tableWidget->rowCount(); i++){
        viewAddData(i);
    }
    debug("生成完毕:")<<QTime::currentTime();
    // 在添加完所有数据之后，调整列宽
    ui->viewTable_tableWidget->resizeColumnsToContents();
    ui->viewTable_tableWidget->setUpdatesEnabled(true); // 重新启用自动更新
    ui->viewTable_tableWidget->viewport()->update(); // 强制更新视图
}

/**
 *  UI
*   初始化按钮状态
*/
void termial::initPushBtnState(){
    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);
    debug("初始化按钮状态");
}


/**
*   串口下拉框
*/
void termial::initSerialportComboBox(){

    ui->serialport_comboBox->clear();
    serialPortList.clear();
    //通过QSerialPortInfo查找可用串口
    bool first=true;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->serialport_comboBox->addItem(info.portName());
        serialPortList.append(info);

        // 默认选择第一个串口
        if(first && !info.isNull()){
            currentSerialportInfo = info;
            first = false;
        }
    }
    debug("初始化串口下拉框");
}

/**
 *  UI
 *  初始化进度条
 */
void termial::initLoad(){
    ui->load_progressBar->setOrientation(Qt::Horizontal);  // 水平方向
    ui->load_progressBar->setMaximum(2000);
    ui->load_progressBar->setMinimum(0);
    ui->load_progressBar->setValue(0);
}

// 槽函数
/**
 *
 */
void termial::vcvSpinBox_valueChanged(int value){
    ui->Vc_horizontalSlider->setValue(value);
}
void termial::swcvSpinBox_valueChanged(int value){
    ui->Swc_horizontalSlider->setValue(value);
}
void termial::ppcvSpinBox_valueChanged(int value){
    ui->PPc_horizontalSlider->setValue(value);
}
void termial::swtDial_valueChanged(int value){
    double v = (double)value / 10;
    ui->swtValue_doubleSpinBox->setValue(v);

}
void termial::swtDoubleSpinBox_valueChanged(double value){
    value = value*10;
    ui->swtValue_dial->setValue(value);
}

/**
 *  当swc滑块发生变化时
 */
void termial::swcHorizontalSlier_valueChanged(int value){
    ui->Swcv_spinBox->setValue(value);
}
/**
 *   当ppc滑块发生变化时
 */
void termial::ppcHorizontalSlier_valueChanged(int value){
    ui->PPcv_spinBox->setValue(value);
}
/**
 *
 */
void termial::vcHorizontalSlier_valueChanged(int value){
    ui->Vcv_spinBox->setValue(value);
}

/**
 *  槽函数
 *  0x46 驻波调谐按钮被点击
 *  传递被选中的单选框下标和驻波调谐值
 *  0~2         1.0~14.0
 */
void termial::swtBtn_clicked(){
    if(ui->SWT_pushButton->text() == tr("驻波调谐")){
        QByteArray data = tuner_v.swtBtn_clicked(swtBtnGroup->checkedId(), ui->swtValue_doubleSpinBox->value());
        if(tunerSend(data) == false){
            ui->SWT_pushButton->setText(tr("驻波调谐"));
            return;
        }
        //0x46启动定时器
        tunerRetransmissionTimer0x46->start(500);
    }else{
        ui->SWT_pushButton->setText(tr("驻波调谐"));
        if(tunerRetransmissionTimer0x46->isActive()){
            tunerRetransmissionTimer0x46->stop();
        }

    }
}

/**
 *  槽函数
 *  0x47
 *  天调同步按钮点击时
 */
void termial::TUNER_synchronousBtn_clicked(){
    // if(ui->TUNER_synchronous_pushButton->text() == tr("天调同步")){
    //     QByteArray data = tuner_v.TUNER_synchronousBtn_clicked();
    //     if(tunerSend(data) == false){
    //         ui->TUNER_synchronous_pushButton->setText(tr("天调同步"));
    //         return;
    //     }
    //     // 0x47启动定时器
    //     tunerRetransmissionTimer0x47->start(100);
    //     ui->TUNER_synchronous_pushButton->setText(tr("定时同步中..."));

    //     /* 启动定时 天调同步 */
    //     if(!(connectionName == "" || connectionName.isEmpty())){
    //         connect(&tuner_v,&TUNER_view::onTimerOut0x47,this,&termial::onTimerout0x47);
    //     }
    // }else{
    //     if(tunerRetransmissionTimer0x47->isActive()){
    //         tunerRetransmissionTimer0x47->stop();
    //     }
    //     disconnect(&tuner_v,&TUNER_view::onTimerOut0x47,this,&termial::onTimerout0x47);
    //     ui->TUNER_synchronous_pushButton->setText(tr("天调同步"));
    // }
    QByteArray data = tuner_v.TUNER_synchronousBtn_clicked();
    tunerSend(data);
    // 0x47启动定时器
    tunerRetransmissionTimer0x47->start(100);
    // ui->TUNER_synchronous_pushButton->setText(tr("定时同步中..."));

    /* 启动定时 天调同步 */
    if(!(connectionName == "" || connectionName.isEmpty())){
        connect(&tuner_v,&TUNER_view::onTimerOut0x47,this,&termial::onTimerout0x47);
    }
}

/**
 *  槽函数
 *  0x48
 *  天调校准按钮点击时
 */
void termial::ATCbtn_clicked(){
    if(ui->ATC_pushButton->text() == tr("天调校准")){
        // 99是-100 0是-1 100是0 200是100
        // int ppcv = ui->PPcv_spinBox->value();
        // int swcv = ui->Swcv_spinBox->value();
        // int vcv = ui->Vcv_spinBox->value();

        int ppcv2 = ui->PPc_horizontalSlider->value();
        int swcv2 = ui->Swc_horizontalSlider->value();
        int vcv2 = ui->Vc_horizontalSlider->value();

        // ppcv = (ppcv < 0) ? (-ppcv)-1 : ppcv + 100;
        // swcv = (swcv < 0) ? (-swcv)-1 : swcv + 100;
        // vcv  = (vcv  < 0) ? (-vcv)-1  : vcv  + 100;

        ppcv2 = (ppcv2 < 0) ? (-ppcv2)-1 : ppcv2 + 100;
        swcv2 = (swcv2 < 0) ? (-swcv2)-1 : swcv2 + 100;
        vcv2  = (vcv2  < 0) ? (-vcv2)-1  : vcv2  + 100;

        // debug("ppcv")<<ppcv<<",swcv"<<swcv<<",vcv"<<vcv;
        debug("ppcv2")<<ppcv2<<",swcv2"<<swcv2<<",vcv2"<<vcv2;

        // QByteArray data = tuner_v.ATCbtn_clicked(ppcv,swcv,vcv);
        QByteArray data = tuner_v.ATCbtn_clicked(ppcv2,swcv2,vcv2);
        if(tunerSend(data) == false){
            ui->ATC_pushButton->setText(tr("天调校准"));
            return;
        }
        // 0x48启动定时器
        tunerRetransmissionTimer0x48->start(100);
        ui->ATC_pushButton->setText(tr("正在等待回复..."));
    }else{
        if(tunerRetransmissionTimer0x48->isActive()){
            tunerRetransmissionTimer0x48->stop();
        }
        ui->ATC_pushButton->setText(tr("天调校准"));
    }
}

/**
 *  槽函数
 *  串口刷新按钮点击事件
 */
void termial::serialportFlashBtn_clicked(){
    disconnect(ui->serialport_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &termial::serialportComboBox_currentIndexChanged);
    ui->serialport_comboBox->clear();
    serialPortList.clear();
    //通过QSerialPortInfo查找可用串口
    bool first=true;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->serialport_comboBox->addItem(info.portName());
        serialPortList.append(info);

        // 默认选择第一个串口
        if(first && !info.isNull()){
            currentSerialportInfo = info;
            first = false;
        }
    }
    connect(ui->serialport_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &termial::serialportComboBox_currentIndexChanged);
}

/**
 *  槽函数
 *  语言切换
 *  当语言下拉框发生变化时
 *  @param  int index   下拉框选择
 */
void termial::switchLanguage(int index){
    qApp->removeTranslator(&translator); // 移除旧的翻译器
    switch(index){
    case 0:
        loadLanguageAsync("lang_Chinese.qm");
        break;
    case 1:
        loadLanguageAsync("lang_English.qm");
        break;
    case 2:
        loadLanguageAsync("lang_French.qm");
        break;
    case 3:
        loadLanguageAsync("lang_Arabic.qm");
        break;
    case 4:
        loadLanguageAsync("lang_German.qm");
        break;
    case 5:
        loadLanguageAsync("lang_Japanese.qm");
        break;
    case 6:
        loadLanguageAsync("lang_Portuguese.qm");
        break;
    case 7:
        loadLanguageAsync("lang_Russian.qm");
        break;
    case 8:
        loadLanguageAsync("lang_Spanish.qm");
        break;
    case 9:
        loadLanguageAsync("lang_Hindi.qm");
        break;
    default:
        debug("未知语言选项:")<<index;
        loadLanguageAsync("lang_English.qm");
        break;
    }
}

/**
 *  槽函数
 *  页切换时
 *  @param  int index   页索引,从0开始
 */
void termial::tabWidgetSwitch(int index){
    debug("页面切换->")<<index;
    // 断开所有已有的信号连接
    disconnect(&tuner_v, &TUNER_view::onTimerOut0x47, this, &termial::onTimerout0x47);
    tuner_v.setTimerout0x47(false);

    ui->save_pushButton->setEnabled(false);
    ui->open_pushButton->setEnabled(false);
    ui->send_btn->setEnabled(false);
    ui->read_btn->setEnabled(false);
    switch(index){
    case 0:
        /* 首页 */
        currentPage = tr("首页");
        break;
    case 1:
        /* 编程页 */
        currentPage = tr("编程");
        ui->save_pushButton->setEnabled(true);
        ui->open_pushButton->setEnabled(true);
        ui->send_btn->setEnabled(true);
        ui->read_btn->setEnabled(true);
        break;
    case 2:
        /* 设置页 */
        currentPage = tr("设置");
        break;
    case 3:
        /* 工程模式 */
        currentPage = tr("工程模式");
        break;
    case 4:
        /* 天调页 */
        currentPage = tr("天调");
        if(connectionName == "" || connectionName.isEmpty()){
            QMessageBox::warning(this, tr("警告") , tr("请先连接串口/TCP"));
            ui->tabWidget->setCurrentIndex(0);
            return;
        }
        // 开启天调同步
        tuner_v.setTimerout0x47(true);
        TUNER_synchronousBtn_clicked();
        break;
    }
}

/**
 * 当tcp连接按钮被点击时
 */
void termial::tcpOpenBtn_clicked(){

    if(!tcpOpenBtn_state)
    {   /* 未连接状态被点击 */

        QString ipStr = ui->IPLocal_lineEdit->text();
        quint16 port = ui->tcpPort_lineEdit->text().toUShort();

        // 检查端口号是否在合理范围内
        if (port < 1000 ) {
            debug("错误") << "端口号必须在1到65535之间。";
            return;
        }

        // 检查IP地址是否符合标准格式
        QHostAddress ipAddress(ipStr);
        if (ipAddress.isNull()) {
            debug("错误") << "无效的IP地址：" << ipStr;
            return;
        }

        if(!tcpServer->listen(ipAddress,port)){
            debug("listen失败");
            return;
        }

        // 初始化连接列表
        tcpSocketList.clear();

        // 若有新连接
        connect(tcpServer,&QTcpServer::newConnection,this,&termial::tcpServerNewConnection);

        tcpOpenBtn_state = true;
        ui->tcpOpen_pushButton->setText(tr("关闭服务器"));
        connectionName = "TCP";
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->save_pushButton->setEnabled(true);
        ui->open_pushButton->setEnabled(true);
        ui->serialportLink_pushButton->setEnabled(false);
    }else{  /* 已连接状态点击了按钮 */
        // 停止监听新连接
        tcpServer->close();

        // 关闭定时器
        if(tcpRetransmissionTimer0x40->isActive())
            tcpRetransmissionTimer0x40->stop();
        if(tcpRetransmissionTimer0x41->isActive())
            tcpRetransmissionTimer0x41->stop();
        if(tcpRetransmissionTimer0x43->isActive())
            tcpRetransmissionTimer0x43->stop();
        if(tcpRetransmissionTimer0x44->isActive())
            tcpRetransmissionTimer0x44->stop();
        if(heartbeatTimer->isActive())
            heartbeatTimer->stop();
        if(tunerRetransmissionTimer0x46->isActive())
            tunerRetransmissionTimer0x46->stop();
        if(tunerRetransmissionTimer0x47->isActive())
            tunerRetransmissionTimer0x47->stop();
        if(tunerRetransmissionTimer0x48->isActive())
            tunerRetransmissionTimer0x48->stop();

        // 断开与 newConnection 信号的连接
        disconnect(tcpServer, &QTcpServer::newConnection, this, &termial::tcpServerNewConnection);

        // 遍历当前已连接的客户端列表，逐一断开连接
        while (!tcpSocketList.isEmpty()) {
            ClientInfo &clientInfo = tcpSocketList.first();
            QTcpSocket *socket = clientInfo.getSocket();
            if (socket && socket->isOpen()) {
                socket->disconnectFromHost();
                socket->deleteLater();
            }
            if(!tcpSocketList.isEmpty()){
                tcpSocketList.removeFirst();
            }
        }

        // 关闭心跳定时器
        heartbeatTimer->stop();

        // 清空客户端列表
        tcpSocketList.clear();

        tcpOpenBtn_state = false;
        ui->tcpOpen_pushButton->setText(tr("开启服务器"));
        connectionName = "";
        ui->checkAll_pushButton->setEnabled(false);
        ui->checkNotAll_pushButton->setEnabled(false);
        ui->save_pushButton->setEnabled(false);
        ui->open_pushButton->setEnabled(false);
        ui->serialportLink_pushButton->setEnabled(true);
        ui->read_btn->setText(tr("读取"));
        ui->send_btn->setText(tr("发送"));
    }
}

/**
 *  tcp
 *  有新客户端连接上服务器时
 */
void termial::tcpServerNewConnection(){
    QTcpSocket *newSocket = tcpServer->nextPendingConnection();
    // 获取客户端的IP地址
    QHostAddress clientIP = newSocket->peerAddress();
    // 获取客户端的端口号
    quint16 clientPort = newSocket->peerPort();
    debug("有新客户端连接,IP:")<<clientIP<<" 端口:"<<clientPort;


    ClientInfo clientInfo;
    clientInfo.setIp(clientIP.toString());
    clientInfo.setPort(clientPort);
    clientInfo.setSocket(newSocket);

    // 立即发送一次心跳包,重置客户端连接计时
    heartbeat_outtime();

    // 连接定时器超时信号到发送命令的槽函数
    connect(heartbeatTimer, &QTimer::timeout, this, &termial::heartbeat_outtime);

    // 启动定时器，每HOW_LONG_HEARTBEAT秒超时一次 发送心跳包
    heartbeatTimer->start(HOW_LONG_HEARTBEAT);

    tcpSocketList.append(clientInfo);   // 加入列表

    connect(newSocket,&QTcpSocket::readyRead,this,&termial::tcpSocket_readyRead);

    // 当连接断开时
    connect(newSocket, &QTcpSocket::disconnected,this,[this,newSocket](){
        // 移除客户端信息
        for (auto it = tcpSocketList.cbegin(); it != tcpSocketList.cend(); ++it) {
            if (it->getSocket() == newSocket) {
                tcpSocketList.erase(it);
                break;
            }
        }

        // 更新下拉框
        QHostAddress ip = newSocket->peerAddress();
        quint16 port = newSocket->peerPort();
        ui->connectedDevices_comboBox->removeItem(ui->connectedDevices_comboBox->findText(ip.toString() + ":" + QString::number(port)));
    });

    // 更新下拉框
    ui->connectedDevices_comboBox->addItem(clientIP.toString() + ":" + QString::number(clientPort));
}

/**
 *  tcp
 *  服务器接收到客户端消息时
 *  有数据可读时
 */
void termial::tcpSocket_readyRead(){

    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        debug("错误") << "发送者不是 QTcpSocket。";
        return;
    }

    QByteArray data = socket->readAll(); // 读取所有可用数据
    if(data.isEmpty()){
        debug("没有读取到任何数据,但是触发了tcp有数据可读");
        return;
    }

    // channel newChannel;
    // DMR newDmr;
    // TUNER newTuner;

    // 判断数据是否合法
    QByteArray dataPacket;   // 合法的数据会保存到这个List中
    // dataPacket = tool.parsePackets(data);
    dataPacket = tool.parsePacketsPlus(data);
    if(dataPacket.isEmpty() || dataPacket == ""){
        debug("此次传输没有收到有效数据");
        return;
    }
    debug("data:")<<data.toHex(' ')<<"\ndataPacket:"<<dataPacket.toHex(' ');
    // 判断传回来的是什么命令
    switch(dataPacket[5])
    {
    case 0x40:
        /* 发送 */
    {
            debug("接受到的消息:\n")<<dataPacket.toHex(' ');
            // newChannel.radioWriteResponseToObj(dataPacket);
            channel newChannel = channel_dao.dataToObj0x40(dataPacket);
            handleCommand0x40(newChannel);
    }
        break;
    case 0x41:
        /* 读取 */
    {
            debug("接受到的消息:\n")<<dataPacket.toHex(' ');
            // newChannel.radioReadResponseToObj(dataPacket);
            channel newChannel = channel_dao.dataToObj0x41(dataPacket);
            handleCommand0x41(newChannel);
    }
        break;
    case 0x43:
        /* dmr写 */
    {
            debug("接受到的消息:\n")<<dataPacket.toHex(' ');
            // newDmr.dataToDMR(dataPacket);
            DMR newDmr = dmr_dao.dataToObj0x43(dataPacket);
            handleCommand0x43(newDmr);
    }
        break;
    case 0x44:
        /* dmr读取 */
    {
            debug("接受到的消息:\n")<<dataPacket.toHex(' ');
            // newDmr.dataToDMR(dataPacket);
            DMR newDmr = dmr_dao.dataToObj0x44(dataPacket);
            handleCommand0x44(newDmr);
    }
        break;
    case 0x46:
    {
        debug("接受到的消息:\n")<<dataPacket.toHex(' ');
        // newTuner.dataToObj0x46(dataPacket);
        TUNER newTuner = tuner_dao.dataToObj0x46(dataPacket);
        handleCommand0x46(newTuner);
    }
        break;
    case 0x47:
    {
        debug("接受到的消息:\n")<<dataPacket.toHex(' ');
        // newTuner.dataToObj0x47(dataPacket);
        TUNER newTuner = tuner_dao.dataToObj0x47(dataPacket);
        handleCommand0x47(newTuner);
    }
        break;
    case 0x48:
    {
        debug("接受到的消息:\n")<<dataPacket.toHex(' ');
        // newTuner.dataToObj0x48(dataPacket);
        TUNER newTuner = tuner_dao.dataToObj0x48(dataPacket);
        handleCommand0x48(newTuner);
    }
        break;
    }


}

/**
 *  tcp
 *  读取按钮被点击时
 *  服务器发送消息给下拉框对应的客户端
 */
void termial::tcpReadBtn_clicked(){
    // 关闭心跳包
    if(heartbeatTimer->isActive()){
        heartbeatTimer->stop();
    }
    // 读取所有被选中的列表行
    getAllCheckedRowsToList(readySend41ChannelList);
    getAllCheckedRowsToListDmr(readySend44ChannelList);


    if(readySend41ChannelList.isEmpty()){
        debug("读取所有被选中的列表行时readySend41ChannelList没有数据");
        return;
    }
    if(readySend44ChannelList.isEmpty()){
        debug("读取所有被选中的列表行时readySend44ChannelList没有数据");
        return;
    }

    // 计算进度条
    int loadSend = readySend41ChannelList.count() + readySend44ChannelList.count();
    ui->load_progressBar->setMaximum(loadSend);
    ui->load_progressBar->setValue(0);

    currentClient = getCurrentClientInfo(); // 获得当前下拉框选择的IP 端口 客户端套接字
    tcpTools.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentClient);
    QThread::msleep(10); // 延迟10毫秒,防止粘包
    tcpTools.takeFirst41ListWrite(channelRead,readySend41ChannelList,currentClient);    // 获取41列表中第一个命令,发送后删除对应命令

    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);

    // 启动定时器，等待50毫秒，超时重发
    tcpRetransmissionTimer0x41->start(100);
    tcpRetransmissionTimer0x44->start(100);
}

/**
 *  tcp
 *  发送按钮被点击时
 *  服务器发送给下拉框对应的客户端
 */
void termial::tcpSendBtn_clicked(){
    // 关闭心跳包
    if(heartbeatTimer->isActive()){
        heartbeatTimer->stop();
    }

    getAllCheckedRowsToList(readySend40ChannelList);
    getAllCheckedRowsToListDmr(readySend43ChannelList);

    if(readySend40ChannelList.isEmpty()){
        debug("没有选中任何行");
        ui->send_btn->setText(tr("发送"));
        return;
    }
    // 计算进度条
    int loadSend = readySend40ChannelList.count() + readySend43ChannelList.count();
    ui->load_progressBar->setMaximum(loadSend);
    ui->load_progressBar->setValue(0);

    // 发送40 43命令
    currentClient = getCurrentClientInfo(); // 获得当前下拉框选择的IP 端口 客户端套接字
    tcpTools.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentClient);   // 获取43列表中第一个命令,发送后删除对应命令
    QThread::msleep(10);    // 延迟10毫秒防止沾包
    tcpTools.takeFirst40ListWrite(channelWrite,readySend40ChannelList,currentClient);   // 获取40列表中第一个命令,发送后删除对应命令

    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);

    // 启动定时器，等待200毫秒，超时重发
    tcpRetransmissionTimer0x40->start(200);
    tcpRetransmissionTimer0x43->start(200);
}

/**
 *  tcp
 *  0x40
 *  发送超时重发
 */
void termial::tcpOnTimeout0x40(){
    if(heartbeatTimer->isActive())
        heartbeatTimer->stop();
    QByteArray data = channelWrite.prepareWritePacketWithCRC();
    debug("tcp 0x40超时重发: \n") << data.toHex(' ');
    currentClient.getSocket()->write(data);
}

/**
 *  tcp
 *  0x41
 *  读取超时重发
 */
void termial::tcpOnTimeout0x41(){
    if(heartbeatTimer->isActive())
        heartbeatTimer->stop();
    QByteArray data = channelRead.preparePacketWithCRC();
    debug("tcp 0x41超时重发:\n ") << data.toHex(' ');
    currentClient.getSocket()->write(data);

}

/**
 *  tcp
 *  0x43
 *  超时重发
 */
void termial::tcpOnTimeout0x43(){
    if(heartbeatTimer->isActive())
        heartbeatTimer->stop();
    QByteArray data = dmrWrite.buildWriteData();
    debug("tcp 0x43超时重发:\n ")<<data.toHex(' ');
    currentClient.getSocket()->write(data);
}

/**
 *  tcp
 *  0x44 超时重发
 */
void termial::tcpOnTimeout0x44(){
    if(heartbeatTimer->isActive())
        heartbeatTimer->stop();
    QByteArray data = dmrRead.buildReadData();
    debug("tcp 0x44超时重发: \n")<<data.toHex(' ');
    currentClient.getSocket()->write(data);
}

/**
 *  天调
 *  0x46 超时重发
 */
void termial::tunerOnTimer0x46(){
    if(ui->auto_radioButton->isChecked()){
        return;
    }
    if(ui->tunerCurrentModel_label->text() == tr("自动调谐")){
        return;
    }
    if(connectionName == "" || connectionName.isEmpty()){
        QMessageBox::warning(this, tr("警告") , tr("未连接串口或TCP!"));
        if(tunerRetransmissionTimer0x46->isActive())
            tunerRetransmissionTimer0x46->stop();
        return;
    }
    QByteArray data = tuner_v.swtBtn_clicked(swtBtnGroup->checkedId(), ui->swtValue_doubleSpinBox->value());
    if(connectionName == "串口"){
        debug("使用串口连接");
        currentSerialport.write(data);
    }
    if(connectionName == "TCP"){
        if(tcpSocketList.isEmpty() || tcpSocketList.count() == 0){
            return;
        }
        currentClient = getCurrentClientInfo();
        currentClient.getSocket()->write(data);
    }
}
/**
 *  天调
 *  0x47 超时重发
 */
void termial::tunerOnTimer0x47(){
    if(connectionName == "" || connectionName.isEmpty()){
        if(tunerRetransmissionTimer0x47->isActive())
            tunerRetransmissionTimer0x47->stop();
        QMessageBox::warning(this, tr("警告") , tr("未连接串口或TCP!"));
        return;
    }

    QByteArray data = tuner_v.TUNER_synchronousBtn_clicked();
    if(connectionName == "串口"){
        debug("使用串口连接");
        currentSerialport.write(data);
    }
    if(connectionName == "TCP"){
        if(tcpSocketList.isEmpty() || tcpSocketList.count() == 0){
            return;
        }
        currentClient = getCurrentClientInfo();
        currentClient.getSocket()->write(data);
    }
}

/**
 *  天调
 *  0x48 超时重发  ATCbtn_clicked(int ppcv,int swcv,int vcv)
 */
void termial::tunerOnTimer0x48(){
    if(connectionName == "" || connectionName.isEmpty()){
        debug("--4--");
        QMessageBox::warning(this, tr("警告") , tr("未连接串口或TCP!"));
        if(tunerRetransmissionTimer0x48->isActive())
            tunerRetransmissionTimer0x48->stop();
        return;
    }
    // 99是-100 0是-1 100是0 200是100
    // int ppcv = ui->PPcv_spinBox->value();
    // int swcv = ui->Swcv_spinBox->value();
    // int vcv = ui->Vcv_spinBox->value();

    int ppcv2 = ui->PPc_horizontalSlider->value();
    int swcv2 = ui->Swc_horizontalSlider->value();
    int vcv2 = ui->PPc_horizontalSlider->value();

    // ppcv = (ppcv < 0) ? (-ppcv)-1 : ppcv + 100;
    // swcv = (swcv < 0) ? (-swcv)-1 : swcv + 100;
    // vcv  = (vcv  < 0) ? (-vcv)-1  : vcv  + 100;

    ppcv2 = (ppcv2 < 0) ? (-ppcv2)-1 : ppcv2 + 100;
    swcv2 = (swcv2 < 0) ? (-swcv2)-1 : swcv2 + 100;
    vcv2  = (vcv2  < 0) ? (-vcv2)-1  : vcv2  + 100;

    // QByteArray data = tuner_v.ATCbtn_clicked(ppcv,swcv,vcv);
    QByteArray data = tuner_v.ATCbtn_clicked(ppcv2,swcv2,vcv2);
    if(connectionName == "串口"){
        debug("使用串口连接");
        currentSerialport.write(data);
    }
    if(connectionName == "TCP"){
        if(tcpSocketList.isEmpty() || tcpSocketList.count() == 0){
            return;
        }
        currentClient = getCurrentClientInfo();
        currentClient.getSocket()->write(data);
    }
}


/**
 *  当串口下拉框发生变化时
 */
void termial::serialportComboBox_currentIndexChanged(int index){
    currentSerialportInfo = serialPortList[index];
    debug(currentSerialportInfo.portName());
}

/**
 *  UI
*   当串口连接按钮被点击时
*/
void termial::serialportLinkBtn_clicked(){
    if(serialportLinkBtn_state == false){   // 未连接状态时点击了
       serialPortTool.initSerialport(currentSerialportInfo,currentSerialport);  // 初始化串口连接
        // currentSerialport.setRequestToSend(true);   //设置RTS电平
        // currentSerialport.setDataTerminalReady(false);   // 设置DTR电平

        // 打开串口
        if(!currentSerialport.open(QIODevice::ReadWrite)){
            debug("没有成功打开串口")<< currentSerialport.errorString();
            QMessageBox::warning(this, tr("警告") , tr("没有成功打开串口,") + currentSerialport.errorString());
            return;
        }

        ui->save_pushButton->setEnabled(true);
        ui->open_pushButton->setEnabled(true);
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->serialport_comboBox->setEnabled(false);
        ui->tcpOpen_pushButton->setEnabled(false);

        ui->serialportLink_pushButton->setText(tr("断开"));
        connectionName = "串口";
    }else{

        // currentSerialport.setDataTerminalReady(false);
        // currentSerialport.setRequestToSend(false);

        // 等待一段时间，确保信号生效
        QThread::msleep(100);

        if(currentSerialport.isOpen())
            currentSerialport.close();  // 关闭串口

        // 取消定时器
        if (retransmissionTimer0x40->isActive())
            retransmissionTimer0x40->stop();
        if (retransmissionTimer0x41->isActive())
            retransmissionTimer0x41->stop();
        if(retransmissionTimer0x43->isActive())
            retransmissionTimer0x43->stop();
        if(retransmissionTimer0x44->isActive())
            retransmissionTimer0x44->stop();
        if(tunerRetransmissionTimer0x46->isActive())
            tunerRetransmissionTimer0x46->stop();
        if(tunerRetransmissionTimer0x47->isActive())
            tunerRetransmissionTimer0x47->stop();
        if(tunerRetransmissionTimer0x48->isActive())
            tunerRetransmissionTimer0x48->stop();

        ui->save_pushButton->setEnabled(false);
        ui->open_pushButton->setEnabled(false);
        ui->checkAll_pushButton->setEnabled(false);
        ui->checkNotAll_pushButton->setEnabled(false);
        ui->serialport_comboBox->setEnabled(true);
        ui->tcpOpen_pushButton->setEnabled(true);   // 使用串口连接时不可网络连接
        ui->serialportLink_pushButton->setText(tr("连接"));
        ui->read_btn->setText(tr("读取"));
        ui->send_btn->setText(tr("发送"));
        connectionName = "";
    }
    serialportLinkBtn_state = !serialportLinkBtn_state; // 点击后更改按钮状态

}


/**
 *  UI
*   保存为json
*/
void termial::saveBtn_clicked(){
    QVector<channel> saveJsonList;    // 储存表格中所有被勾选的channel对象,等待被保存为json
    QVector<DMR> saveJsonDmrList;

    debug("取所有勾选的channel对象开始");
    // 获取所有勾选的channel对象
    getAllCheckedRowsToList(saveJsonList);
    getAllCheckedRowsToListDmr(saveJsonDmrList);
    debug("获取所有勾选的channel对象结束");

    // 让用户选择保存位置及其文件名
    QString jsonPath = getUserSaveLocation(this, "JSON Files (*.json)");
    debug("选择保存的位置:" + jsonPath);

    QJsonObject channelDmrsObj;
    ChannelDmr channelDmr;

    int size = qMin(saveJsonList.size(), saveJsonDmrList.size());

    for (int i = 0; i < size; ++i) {
        channelDmr.buildChannelDmr(saveJsonList[i],saveJsonDmrList[i]);  // 将channel对象和dmr对象组合成channelDmr对象
        channelDmrsObj[QString::number(channelDmr.getChannelID())] = channelDmr.toJSON();
    }

    if (!saveQJsonObjectToFile(channelDmrsObj, jsonPath)) {
        debug("保存失败");
        return;
    }
}

/**
*   打开json文件 读取到
*/
void termial::openBtn_clicked(){
    QList<DMR> openJsonDmrList;
    QList<channel> openJsonList;    // 将json的数据保存至List

    QString filePath = QFileDialog::getOpenFileName( this,tr("Open JSON File"),"", tr("JSON Files (*.json)"));

    // 打开并读取json文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        debug("文件打开失败");
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        debug("json转化失败") << jsonError.errorString();
        return;
    }
    QJsonObject jsonObject = doc.object();

    for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
        QJsonObject obj = it.value().toObject();

        channel channel;
        channel.setChannelHigh(obj["channelHigh"].toInt());
        channel.setChannelLow(obj["channelLow"].toInt());
        channel.setChannelName(obj["channelName"].toString().toUtf8());
        channel.setEmitYayin(obj["emitYayin"].toInt());
        channel.setReceiveYayin(obj["receiveYayin"].toInt());
        channel.setVfoaFrequency1(obj["vfoaFrequency1"].toInt());
        channel.setVfoaFrequency2(obj["vfoaFrequency2"].toInt());
        channel.setVfoaFrequency3(obj["vfoaFrequency3"].toInt());
        channel.setVfoaFrequency4(obj["vfoaFrequency4"].toInt());
        channel.setVfoaMode(obj["vfoaMode"].toInt());
        channel.setVfobFrequency1(obj["vfobFrequency1"].toInt());
        channel.setVfobFrequency2(obj["vfobFrequency2"].toInt());
        channel.setVfobFrequency3(obj["vfobFrequency3"].toInt());
        channel.setVfobFrequency4(obj["vfobFrequency4"].toInt());
        channel.setVfobMode(obj["vfobMode"].toInt());

        DMR dmr;
        dmr.setChannelHigh(obj["channelHigh"].toInt());
        dmr.setChannelLow(obj["channelLow"].toInt());
        dmr.setCallFormat(obj["callFormat"].toInt());
        dmr.setTxCc(obj["txCc"].toInt());
        dmr.setRxCc(obj["rxCc"].toInt());
        dmr.setCallId1(obj["callId1"].toInt());
        dmr.setCallId2(obj["callId2"].toInt());
        dmr.setCallId3(obj["callId3"].toInt());
        dmr.setCallId4(obj["callId4"].toInt());
        dmr.setOwnId1(obj["ownId1"].toInt());
        dmr.setOwnId2(obj["ownId2"].toInt());
        dmr.setOwnId3(obj["ownId3"].toInt());
        dmr.setOwnId4(obj["ownId4"].toInt());
        dmr.setChType(obj["chType"].toInt());
        dmr.setRxCtcss(obj["rxCtcss"].toInt());
        dmr.setTxCtcss(obj["txCtcss"].toInt());
        dmr.setSqlevel(obj["sqlevel"].toInt());
        dmr.setSpkgain(obj["spkgain"].toInt());
        dmr.setDmodGain(obj["dmodGain"].toInt());
        dmr.setSlot(obj["slot"].toInt());
        dmr.setScrSeed1(obj["scrSeed1"].toInt());
        dmr.setScrSeed2(obj["scrSeed2"].toInt());
        dmr.setScrEn(obj["scrEn"].toInt());
        dmr.setChBsMode(obj["chBsMode"].toInt());

        openJsonList.append(channel);
        openJsonDmrList.append(dmr);
    }
    ui->load_progressBar->setMaximum(openJsonList.count()+openJsonDmrList.count());
    ui->load_progressBar->setValue(0);

    // 遍历openJsonList并将数据添加到UI
    for (channel listChannel : openJsonList) {
        viewUpdate(listChannel.getChannelID(), listChannel);
        ui->load_progressBar->setValue(ui->load_progressBar->value()+1);
    }
    for(DMR listDmr : openJsonDmrList){
        viewUpdateDmr(listDmr.getChannelID(),listDmr);
        ui->load_progressBar->setValue(ui->load_progressBar->value()+1);
    }

}

/**
 *  串口
 *  0x41
*   当点击读取按钮时
*/
void termial::readBtn_clicked(){

    getAllCheckedRowsToList(readySend41ChannelList);    // 将所有选中行放入List待发送列表
    getAllCheckedRowsToListDmr(readySend44ChannelList);

    if(readySend41ChannelList.isEmpty() && readySend44ChannelList.isEmpty()){
        debug("没有选中任何行");
        ui->read_btn->setText(tr("读取"));
        return;
    }

    // 计算进度条
    int loadSend = readySend41ChannelList.size() + readySend44ChannelList.size();
    ui->load_progressBar->setMaximum(loadSend);
    ui->load_progressBar->setValue(0);

    serialPortTool.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentSerialport);
    // 获取41列表中第一个命令,发送后删除对应命令
    serialPortTool.takeFirst41ListWrite(channelRead,readySend41ChannelList,currentSerialport);

    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);

    // 启动定时器，等待50毫秒，超时重发
    retransmissionTimer0x41->start(100);
    // 启动44定时器,等待50ms,超时重发
    retransmissionTimer0x44->start(100);

}

/**
 *  控制区
 *  发送按钮点击时
 */
void termial::send_clicked(){
    if(connectionName == "" || connectionName.isEmpty()){
        if(retransmissionTimer0x40->isActive()){
            retransmissionTimer0x40->stop();
        }
        if(retransmissionTimer0x43->isActive()){
            retransmissionTimer0x43->stop();
        }
        QMessageBox::warning(this, tr("警告") , tr("未连接串口或TCP!"));
        return;
    }
    // 判断走TCP还是串口
    if(ui->send_btn->text() == tr("发送")){
        ui->send_btn->setText("正在发送..");
        if(connectionName == "串口"){
            sendBtn_clicked();
        }
        if(connectionName == "TCP"){
            if(tcpSocketList.isEmpty() || tcpSocketList.count() == 0){
                return;
            }
            tcpSendBtn_clicked();
        }
    }else{
        ui->send_btn->setText(tr("发送"));
        if(retransmissionTimer0x40->isActive()){
            retransmissionTimer0x40->stop();
        }
        if(retransmissionTimer0x43->isActive()){
            retransmissionTimer0x43->stop();
        }

        readySend40ChannelList.clear();
        readySend43ChannelList.clear();

        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
    }
}
/**
 *  控制区
 *  读取按钮点击时
 */
void termial::read_clicked(){
    // 若没连接就点击
    if(connectionName == "" || connectionName.isEmpty()){
        if(retransmissionTimer0x41->isActive()){
            retransmissionTimer0x41->stop();
        }
        if(retransmissionTimer0x44->isActive()){
            retransmissionTimer0x44->stop();
        }
        QMessageBox::warning(this, tr("警告") , tr("未连接串口或TCP!"));
        return;
    }
    // 判断走TCP还是串口
    if(ui->read_btn->text() == tr("读取")){
        ui->read_btn->setText(tr("正在读取.."));
        if(connectionName == "串口"){
            readBtn_clicked();
        }
        if(connectionName == "TCP"){
            if(tcpSocketList.isEmpty() || tcpSocketList.count() == 0){
                return;
            }
            tcpReadBtn_clicked();
        }
    }else{  // 再次点击终止发送
        ui->read_btn->setText(tr("读取"));
        if(retransmissionTimer0x41->isActive()){
            retransmissionTimer0x41->stop();
        }
        if(retransmissionTimer0x44->isActive()){
            retransmissionTimer0x44->stop();
        }

        readySend41ChannelList.clear();
        readySend44ChannelList.clear();

        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
    }
}

/**
 *  UI
*   当全选被点击时
*/
void termial::checkAllBtn_clicked(){
    isAllSet = true;
    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);
    setAllCheckedState(isAllSet);
    ui->checkAll_pushButton->setEnabled(true);
    ui->checkNotAll_pushButton->setEnabled(true);
}

/**
 *  UI
*   当全不选被点击时
*/
void termial::checkAllNotBtn_clicked(){
    isAllSet = false;
    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);
    setAllCheckedState(isAllSet);
    ui->checkAll_pushButton->setEnabled(true);
    ui->checkNotAll_pushButton->setEnabled(true);
}

/**
 * 设置所有复选框状态
 */
void termial::setAllCheckedState(bool state){
    ui->load_progressBar->setMaximum(1000);
    ui->load_progressBar->setValue(0);
    // 确保 checkBoxPrtList 不为空
    if (checkBoxPrtList.isEmpty()) {
        debug("checkBoxPrtList 为空，无法设置状态。");
        return;
    }

    // 设置所有复选框的状态
    for (int i = 0; i < checkBoxPrtList.count(); ++i) {
        if (checkBoxPrtList[i] == nullptr) { // 再次检查是否为 nullptr
            continue;
        }

        if (checkBoxPrtList[i]->checkState() != state) {
            checkBoxPrtList[i]->setChecked(state);
            // 更新进度条
            ui->load_progressBar->setValue(ui->load_progressBar->value()+1);
        }
    }
    ui->load_progressBar->setValue(ui->load_progressBar->maximum());
}

/**
 *  串口
*   当串口有数据可读时
*/
void termial::currentSerialport_readyRead(){

    QByteArray data = currentSerialport.readAll();
    if(data.isEmpty()){
        debug("没有读取到任何数据，但触发了串口有数据可读?");
        return;
    }

    // debug("串口接收到的信息:\n")<<data.toHex(' ');

    channel newChannel;
    DMR newDmr;
    TUNER newTuner;

    // 判断数据是否合法
    QByteArray dataPacket;
    // dataPacket = tool.parsePackets(data);
    dataPacket = tool.parsePacketsPlus(data);   // 保证获取到有效数据包,并将有效数据存到dataPacket,若无有效数据 返回的是""
    if(dataPacket.isEmpty() || dataPacket == ""){
        // debug("此次传输没有收到有效数据");
        return;
    }


    if(dataPacket[5]!=0x47){
        debug("判断数据合法性结束")<<dataPacket.toHex(' ');
    }

    // 判断传回来的是什么命令
    switch(dataPacket[5]){
    case 0x40:
        newChannel.radioWriteResponseToObj(dataPacket);
        serialHandleCommand0x40(newChannel);
        break;
    case 0x41:
        newChannel.radioReadResponseToObj(dataPacket);
        serialHandleCommand0x41(newChannel);
        break;
    case 0x43:
        newDmr.dataToDMR(dataPacket);
        serialHandleCommand0x43(newDmr);
        break;
    case 0x44:
        newDmr.dataToDMR(dataPacket);
        serialHandleCommand0x44(newDmr);
        break;
    case 0x46:
        newTuner.dataToObj0x46(dataPacket);
        handleCommand0x46(newTuner);
        break;
    case 0x47:
        newTuner.dataToObj0x47(dataPacket);
        handleCommand0x47(newTuner);
        break;
    case 0x48:
        newTuner.dataToObj0x48(dataPacket);
        handleCommand0x48(newTuner);
        break;
    }
}

/**
 *  串口
*   当点击发送按钮时
*   发送第一条数据，后续数据由接收到回复后再发送
*/
void termial::sendBtn_clicked(){

    getAllCheckedRowsToList(readySend40ChannelList);
    getAllCheckedRowsToListDmr(readySend43ChannelList);

    if(readySend40ChannelList.isEmpty() && readySend43ChannelList.isEmpty()){
        debug("没有选中任何行");
        ui->send_btn->setText(tr("发送"));
        return;
    }

    // 计算进度条
    int loadSend = readySend40ChannelList.size() + readySend43ChannelList.size();
    ui->load_progressBar->setMaximum(loadSend);
    ui->load_progressBar->setValue(0);

    // 获取列表中第一个命令,发送后删除对应命令
    serialPortTool.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentSerialport);
    serialPortTool.takeFirst40ListWrite(channelWrite,readySend40ChannelList,currentSerialport);

    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);

    // 启动定时器，等待200毫秒，超时重发
    retransmissionTimer0x40->start(200);
    retransmissionTimer0x43->start(200);
}

/**
 *  0x40
*   定时器重发串口写命令
*/
void termial::onTimeout0x40(){
    QByteArray data = channelWrite.prepareWritePacketWithCRC();
    debug("0x40 超时重发:\n")<<data.toHex(' ');
    currentSerialport.write(data);
}

/**
 *  0x41
*   定时器重发串口读请求
*/
void termial::onTimeout0x41() {
    // 重发数据
    QByteArray data = channelRead.preparePacketWithCRC();
    debug("0x41 超时重发:\n")<<data.toHex(' ');
    currentSerialport.write(data);
}

/**
 *  0x43
 *  写命令 超时重发
 */
void termial::onTimeout0x43(){
    QByteArray data = dmrWrite.buildWriteData();
    debug("0x43 超时重发:\n")<<data.toHex(' ');
    currentSerialport.write(data);
}

/**
 *  0x44
 *  读命令 超时重发
 */
void termial::onTimeout0x44(){
    // 重发数据
    QByteArray data = dmrRead.buildReadData();
    debug("0x44 超时重发:\n")<<data.toHex(' ');
    currentSerialport.write(data);
}

/**
 *  0x47
 *  天调同步 定时发送
 */
void termial::onTimerout0x47(QByteArray data){
    if(connectionName == "" || connectionName.isEmpty()){
        QMessageBox::warning(this, tr("警告") , tr("未连接串口或TCP!"));
        // ui->TUNER_synchronous_pushButton->setText(tr("天调同步"));
        disconnect(&tuner_v,&TUNER_view::onTimerOut0x47,this,&termial::onTimerout0x47);
        if(tunerRetransmissionTimer0x47->isActive())
            tunerRetransmissionTimer0x47->stop();
        return;
    }

    if(connectionName == "串口"){
        currentSerialport.write(data);
    }
    if(connectionName == "TCP"){
        if(tcpSocketList.isEmpty() || tcpSocketList.count() == 0){
            return;
        }
        currentClient = getCurrentClientInfo();
        currentClient.getSocket()->write(data);
    }
}

/**
 *  tcp
 *  维持客户端连接的心跳包
 */
void termial::heartbeat_outtime(){
    foreach (ClientInfo info, tcpSocketList) {
        channel temp;
        temp.setSize(3);
        temp.setCommand(0x0B);
        QByteArray data = temp.addCrc0x0B();
        info.getSocket()->write(data);
    }
}

/**
*   根据单行文本框内容跳转至对应行数
*/
void termial::channelNumLineEdit_returnPressed(){
    QString text = ui->channelNum_lineEdit->text();
    bool ok;
    int number = text.toInt(&ok);
    if (ok && number >= 0 && number < ui->viewTable_tableWidget->rowCount() ) {
        QTableWidgetItem *item = ui->viewTable_tableWidget->item(number,1);
        // 高亮选中行
        item->setSelected(true);
        // 滚动到该行
        ui->viewTable_tableWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
    }

}

/**
 *  当 vfoa 下拉框发生变化时
 */
void termial::vfoaComboBoxIndexChanged(int row,int index){

    if (index == 9) {
        vfoaModeIsDmr = true;
    } else {
        vfoaModeIsDmr = false;
    }

    updateDmrWidgetsState(row);
}

/**
 *  当 vfob 下拉框发生变化时
 */
void termial::vfobComboBoxIndexChanged(int row,int index){
    if (index == 9) {
        vfobModeIsDmr = true;
        debug("vfobModeIsDmr = true");
    } else {
        vfobModeIsDmr = false;
    }

    updateDmrWidgetsState(row);
}

void termial::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);

    QSize oldSize = this->size();
    resize(oldSize + QSize(10, 10));
    resize(oldSize);
}

