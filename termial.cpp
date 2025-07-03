#include "termial.h"
#include "ui_termial.h"
// #include "CheckBoxUpdater.h"
#include "Entity/channeldmr.h"
#include <QMessageBox>

#ifdef Q_OS_WIN
#include <windows.h>
void setDTRRTS(HANDLE hPort, bool dtr, bool rts) {
    EscapeCommFunction(hPort, dtr ? SETDTR : CLRDTR);
    EscapeCommFunction(hPort, rts ? SETRTS : CLRRTS);
}
#endif

termial::termial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::termial)
    , retransmissionTimer0x40(new QTimer(this))
    , retransmissionTimer0x41(new QTimer(this))
    , retransmissionTimer0x43(new QTimer(this))
    , retransmissionTimer0x44(new QTimer(this))
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    readySend40ChannelList = new QList<channel>();
    readySend41ChannelList = new QList<channel>();
    readySend43ChannelList = new QList<DMR>();
    readySend44ChannelList = new QList<DMR>();

    readBtn_busy = false;
    sendBtn_busy = false;

    initArt();
    initSerialportComboBox();
    initPushBtnState();

    initModelsAndViews(); // 初始化模型和视图

    initLoad(); // 初始化进度条
    initLanguageComboBox();
    initConnect();  // 信号and槽初始化
    switchLanguage(0);
    ui->channelMaxNum_spinBox->setValue(10);
}

// 清理函数
void termial::clearAllCommandLists() {
    readySend40ChannelList->clear();
    readySend41ChannelList->clear();
    readySend43ChannelList->clear();
    readySend44ChannelList->clear();

    // 重置所有重试计数器
    retryCount0x40 = 0;
    retryCount0x41 = 0;
    retryCount0x43 = 0;
    retryCount0x44 = 0;
}
/**
 *  重置按钮UI
 */
void termial::resetOperationState() {
    ui->send_btn->setText(tr("发送"));
    ui->read_btn->setText(tr("读取"));
    ui->checkAll_pushButton->setEnabled(true);
    ui->checkNotAll_pushButton->setEnabled(true);
}

/**
 *  用于停止定时器
 *  例子：调用方法stopTimerSafe(timer0x40);
 */
inline void stopTimerSafe(QTimer* timer) {
    if(timer && timer->isActive()) {
        timer->stop();
    }
}

/**
 *  UI
 *  切换翻译
 *  @param  翻译文件在资源文件夹下的名字
 */
void termial::loadingLanguage(QString langName){
    if (!translator.load(langName, "://language/")) {
        debug("查找翻译文件失败");
    }
    qApp->installTranslator(&translator); // 如果加载成功，安装新翻译器
    ui->retranslateUi(this); // 更新界面
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
 *  当串口连接按钮被点击时
 */
void termial::serialportLinkBtn_clicked(){
    if(serialportLinkBtn_state == false){   // 未连接状态时点击
        serialPortTool.initSerialport(currentSerialportInfo,currentSerialport);  // 初始化串口连接
        // 打开串口
        if(!currentSerialport.open(QIODevice::ReadWrite)){
            debug("没有成功打开串口")<< currentSerialport.errorString();
            QMessageBox::warning(this, tr("警告") , tr("没有成功打开串口,") + currentSerialport.errorString());
            return;
        }


        debug("连接 DTR: ")<<currentSerialport.isDataTerminalReady();
        debug("连接 RTS: ")<<currentSerialport.isRequestToSend();

        ui->save_pushButton->setEnabled(true);
        ui->open_pushButton->setEnabled(true);
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->serialport_comboBox->setEnabled(false);
        ui->serialportFlash_pushButton->setEnabled(false);

        ui->serialportLink_pushButton->setText(tr("断开"));
        connectionName = "串口";
        ui->language_comboBox->setEnabled(false);   // 语言框不可在连接状态下更改，不然会出bug
    }else{
        if (currentSerialport.isOpen()) {
            // currentSerialport.setRequestToSend(true);
            // currentSerialport.setDataTerminalReady(true);
            // currentSerialport.flush();
            currentSerialport.close();
        }
        // 取消定时器
        stopTimerSafe(retransmissionTimer0x40);
        stopTimerSafe(retransmissionTimer0x41);
        stopTimerSafe(retransmissionTimer0x43);
        stopTimerSafe(retransmissionTimer0x44);

        ui->save_pushButton->setEnabled(false);
        ui->open_pushButton->setEnabled(false);
        ui->checkAll_pushButton->setEnabled(false);
        ui->checkNotAll_pushButton->setEnabled(false);
        ui->serialport_comboBox->setEnabled(true);
        ui->serialportFlash_pushButton->setEnabled(true);

        ui->serialportLink_pushButton->setText(tr("连接"));
        ui->send_btn->setText(tr("发送"));
        connectionName = "";
        ui->language_comboBox->setEnabled(true);
    }
    serialportLinkBtn_state = !serialportLinkBtn_state; // 点击后更改按钮状态

}

/**
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
}

/**
 *  当串口下拉框发生变化时
 */
 void termial::serialportComboBox_currentIndexChanged(int index){
    currentSerialportInfo = serialPortList[index];
    debug(currentSerialportInfo.portName());
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

    channel newChannel;
    DMR newDmr;

    // 判断数据是否合法
    QByteArray dataPacket;
    // dataPacket = tool.parsePackets(data);
    dataPacket = tool.parsePacketsPlus(data);   // 保证获取到有效数据包,并将有效数据存到dataPacket,若无有效数据 返回的是""
    if(dataPacket.isEmpty() || dataPacket == ""){
        return;
    }


    if(static_cast<unsigned char>(dataPacket[5])!=0x47){
        debug("判断数据合法性结束\n\t")<<dataPacket.toHex(' ');
    }

    // 判断传回来的是什么命令
    switch(dataPacket[5]){
    case 0x40:
        newChannel.radioWriteResponseToObj(dataPacket); // 将dataPacket转化为Channel对象
        serialHandleCommand0x40(newChannel);    //
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
        debug("0x44chTypes - ")<<(int)dataPacket[20];
        serialHandleCommand0x44(newDmr);
        break;
    }
}

/**
 *  串口
 *  设备回复 0x40
 *  channel写
 */
void termial::serialHandleCommand0x40(channel& /*newChannel*/){
    retryCount0x40 = 0;  // 收到响应，重置计数器
    // 关闭定时器
    stopTimerSafe(retransmissionTimer0x40);

    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    // 检查是否还有待发送命令
    if(!readySend40ChannelList->isEmpty()){
        // 获取下一个命令
        serialPortTool.takeFirst40ListWrite(channelWrite,readySend40ChannelList,currentSerialport);
        retransmissionTimer0x40->start(200);
    } else {
        // 所有命令发送完成
        debug("0x40 写操作命令全部发送完成");

        // 清除相关状态
        readySend40ChannelList->clear();

        if(readySend40ChannelList->isEmpty() && !readySend43ChannelList->isEmpty()){
            serialPortTool.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentSerialport);
            retransmissionTimer0x43->start(200);
        }
    }
}

/**
 *  串口
 *  设备回复 0x41
 *  channel读
 */
void termial::serialHandleCommand0x41(channel& newChannel){
    retryCount0x41 = 0;
    viewUpdate(newChannel.getChannelID(),newChannel);

    stopTimerSafe(retransmissionTimer0x41);

    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(!readySend41ChannelList->isEmpty()){
        // 获取下一个命令
        serialPortTool.takeFirst41ListWrite(channelRead,readySend41ChannelList,currentSerialport);
        retransmissionTimer0x41->start(200);
    } else {
        // 所有命令发送完成
        debug("0x41 读操作命令全部发送完成");

        // 清除相关状态
        readySend41ChannelList->clear();

        // 只有在处理完所有0x41命令后才开始0x44命令
        if(readySend41ChannelList->isEmpty() && !readySend44ChannelList->isEmpty()){
            serialPortTool.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentSerialport);
            retransmissionTimer0x44->start(200);
        }
    }
}

/**
 *  串口
 *  设备回复 0x43
 *  DMR写
 */
void termial::serialHandleCommand0x43(DMR& /*newDmr*/){
    retryCount0x43 = 0;
    stopTimerSafe(retransmissionTimer0x43);

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(!readySend43ChannelList->isEmpty()){
        // 获取下一个命令
        serialPortTool.takeFirst43ListWrite(dmrWrite,readySend43ChannelList,currentSerialport);
        retransmissionTimer0x43->start(200);
    } else {
        // 所有命令发送完成
        debug("0x43 写操作命令全部发送完成");
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->send_btn->setText(tr("发送"));
        sendBtn_busy = false;

        // 清除相关状态
        readySend43ChannelList->clear();
    }
}

/**
 *  串口
 *  设备回复 0x44
 *  DMR读
 */
void termial::serialHandleCommand0x44(DMR& newDmr){
    retryCount0x44 = 0;
    int newRow = newDmr.getChannelID();
    viewUpdateDmr(newRow,newDmr);

    stopTimerSafe(retransmissionTimer0x44);

    // 更新进度条
    ui->load_progressBar->setValue(ui->load_progressBar->value()+1);

    if(!readySend44ChannelList->isEmpty()){
        // 获取下一个命令
        serialPortTool.takeFirst44ListWrite(dmrRead,readySend44ChannelList,currentSerialport);
        retransmissionTimer0x44->start(200);
    } else {
        // 所有命令发送完成
        debug("0x44 读操作命令全部发送完成");
        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);
        ui->read_btn->setText(tr("读取"));
        readBtn_busy = false;

        // 清除相关状态
        readySend44ChannelList->clear();
    }
}

/**
 *  0x40 定时器
 *  重发串口写命令
 */
 void termial::onTimeout0x40() {
    if(retryCount0x40 >= 3) {
        debug("0x40 命令已达到最大重试次数(3次)，跳过此命令");
        retryCount0x40 = 0;  // 重置计数器
        stopTimerSafe(retransmissionTimer0x40);

        // 处理下一条命令
        if(!readySend40ChannelList->isEmpty()) {
            serialPortTool.takeFirst40ListWrite(channelWrite, readySend40ChannelList, currentSerialport);
            retransmissionTimer0x40->start(200);
        }
        return;
    }

    QByteArray data = channelWrite.prepareWritePacketWithCRC();
    debug("0x40 超时重发(尝试次数:" << retryCount0x40+1 << "):\n") << data.toHex(' ');
    currentSerialport.write(data);
    retryCount0x40++;
}

/**
 *  0x41 定时器
 *  重发串口读请求
*/
void termial::onTimeout0x41() {
    if(retryCount0x41 >= 3) {
        debug("0x41 命令已达到最大重试次数(3次)，跳过此命令");
        retryCount0x41 = 0;
        stopTimerSafe(retransmissionTimer0x41);

        if(!readySend41ChannelList->isEmpty()) {
            serialPortTool.takeFirst41ListWrite(channelRead, readySend41ChannelList, currentSerialport);
            retransmissionTimer0x41->start(200);
        }
        return;
    }

    QByteArray data = channelRead.preparePacketWithCRC();
    debug("0x41 超时重发(尝试次数:" << retryCount0x41+1 << "):\n") << data.toHex(' ');
    currentSerialport.write(data);
    retryCount0x41++;
}

/**
 *  0x43 写命令
 *  重发串口写请求
 */
void termial::onTimeout0x43() {
    if(retryCount0x43 >= 3) {
        debug("0x43 命令已达到最大重试次数(3次)，跳过此命令");
        retryCount0x43 = 0;
        stopTimerSafe(retransmissionTimer0x43);

        if(!readySend43ChannelList->isEmpty()) {
            serialPortTool.takeFirst43ListWrite(dmrWrite, readySend43ChannelList, currentSerialport);
            retransmissionTimer0x43->start(200);
        }
        return;
    }

    QByteArray data = dmrWrite.buildWriteData();
    debug("0x43 超时重发(尝试次数:" << retryCount0x43+1 << "):\n") << data.toHex(' ');
    currentSerialport.write(data);
    retryCount0x43++;
}

/**
 *  0x44 读命令
 *  重发串口写请求
 */
void termial::onTimeout0x44() {
    if(retryCount0x44 >= 3) {
        debug("0x44 命令已达到最大重试次数(3次)，跳过此命令");
        retryCount0x44 = 0;
        stopTimerSafe(retransmissionTimer0x44);

        if(!readySend44ChannelList->isEmpty()) {
            serialPortTool.takeFirst44ListWrite(dmrRead, readySend44ChannelList, currentSerialport);
            retransmissionTimer0x44->start(200);
        }
        return;
    }

    QByteArray data = dmrRead.buildReadData();
    debug("0x44 超时重发(尝试次数:" << retryCount0x44+1 << "):\n") << data.toHex(' ');
    currentSerialport.write(data);
    retryCount0x44++;
}

/*  UI操作  */

/**
 *  UI
 *  单条UI修改
 *  将一行channel数据进行修改
 *  @value int row 所在行
 *  @value channel& newChannel 一条数据源
 */
void termial::viewUpdate(int row, channel &newChannel) {
    if (row < 0 || row >= model->rowCount()) return;

    model->blockSignals(true);

    // 信道号 (第1列)
    model->setData(model->index(row, 1), newChannel.getChannelID());

    // 名称处理 (第2列)
    QByteArray name = newChannel.getChannelName();
    name.replace('\0', "");
    model->setData(model->index(row, 2), QString::fromUtf8(name));

    // VFOA频率 (第3列)
    model->setData(model->index(row, 3), newChannel.getVfoaFrequency());

    // VFOB频率 (第4列)
    model->setData(model->index(row, 4), newChannel.getVfobFrequency());

    // VFOA模式 (第5列)
    int vfoaModeIndex = newChannel.getVfoaMode();
    model->setData(model->index(row, 5), vfoaModeIndex, Qt::EditRole); // 存储 index
    model->setData(model->index(row, 5), vfoModes.value(vfoaModeIndex, ""), Qt::DisplayRole); // 显示文本

    // VFOB模式 (第6列)
    int vfobModeIndex = newChannel.getVfobMode();
    model->setData(model->index(row, 6), vfobModeIndex, Qt::EditRole); // 存储 index
    model->setData(model->index(row, 6), vfoModes.value(vfobModeIndex, ""), Qt::DisplayRole); // 显示文本

    // 发射亚音 (第7列)
    model->setData(model->index(row, 7), newChannel.getEmitYayin(),Qt::EditRole);
    model->setData(model->index(row, 7), yayinModes.value(newChannel.getEmitYayin()),Qt::DisplayRole);


    // 接收亚音 (第8列)
    model->setData(model->index(row, 8), newChannel.getReceiveYayin());
    model->setData(model->index(row, 8), yayinModes.value(newChannel.getReceiveYayin()),Qt::DisplayRole);

    model->blockSignals(false);
    emit model->dataChanged(model->index(row, 0), model->index(row, 8));
}

/**
 *  UI
 *  单条UI修改
 *  将一行dmr数据进行修改
 *  @param  int row 所在行
 *  @param  DMR& newDMR 一条数据源
 */
void termial::viewUpdateDmr(int row,DMR& newDMR){
    // 批量更新前禁用信号
    model->blockSignals(true);

    // 呼叫类型 (第9列)
    model->setData(model->index(row, 9), newDMR.getCallFormat());
    model->setData(model->index(row,9),callTypes.value(newDMR.getCallFormat()),Qt::DisplayRole);

    // Tx_cc (第10列)
    model->setData(model->index(row, 10), newDMR.getTxCc());

    // Rx_cc (第11列)
    model->setData(model->index(row, 11), newDMR.getRxCc());

    // 时隙 (第12列)
    model->setData(model->index(row, 12), newDMR.getSlot());

    // 呼叫ID (第13列)
    model->setData(model->index(row, 13), newDMR.getCallID());

    // Own ID (第14列)
    model->setData(model->index(row, 14), newDMR.getOwnID());

    // 信道类型 (第15列)
    model->setData(model->index(row, 15), newDMR.getChType(), Qt::EditRole); // 存储原始值
    model->setData(model->index(row, 15), chTypes.value(newDMR.getChType()), Qt::DisplayRole); // 显示文本
    debug("chTypes - ")<<newDMR.getChType();

    // Rx Ctcss (第16列)
    model->setData(model->index(row, 16), newDMR.getRxCtcss(), Qt::EditRole); // 存储原始值
    model->setData(model->index(row, 16), dmrYayinModes.value(newDMR.getRxCtcss()), Qt::DisplayRole); // 显示文本


    // Tx Ctcss (第17列)
    model->setData(model->index(row, 17), newDMR.getTxCtcss(), Qt::EditRole); // 存储原始值
    model->setData(model->index(row, 17), dmrYayinModes.value(newDMR.getTxCtcss()), Qt::DisplayRole); // 显示文本

    // SQL等级 (第18列)
    model->setData(model->index(row, 18), newDMR.getSqlevel());
    QStandardItem* sqlItem = model->item(row, 18);
    if(sqlItem){
        sqlItem->setFlags(sqlItem->flags() & ~Qt::ItemIsEditable);
    }

    // 启用信号
    model->blockSignals(false);

    // 通知视图更新这些行
    emit model->dataChanged(model->index(row, 9),
                            model->index(row, 23));
}

/**
 *  UI
*   读取该行数据为channel对象
*   @value  行号
*   @return channel 对象
*/
channel termial::rowReadDataToChannel(int row) {
    channel rowChannel;
    unsigned short channelValue;

    // 读取复选框状态 (第0列)
    // Qt::CheckState checkState = static_cast<Qt::CheckState>(model->data(model->index(row, 0), Qt::CheckStateRole).toInt());
    // 如果需要可以使用: bool isChecked = (checkState == Qt::Checked);

    // 信道号 (第1列)
    channelValue = model->data(model->index(row, 1)).toUInt();
    rowChannel.setChannelHigh(static_cast<unsigned char>((channelValue >> 8) & 0xFF));
    rowChannel.setChannelLow(static_cast<unsigned char>(channelValue & 0xFF));
    // 信道名称 (第2列)
    QByteArray temp = model->data(model->index(row, 2)).toString().toUtf8();
    if(temp.length() > 11) {
        temp = temp.left(11);
    }
    while(temp.length() < 12) {
        temp.append('\0');
    }
    rowChannel.setChannelName(temp);

    // VFOA频率 (第3列)
    unsigned long long vfoaFreq = model->data(model->index(row, 3)).toULongLong();
    if(vfoaFreq > 4294967295) {
        vfoaFreq = 300003000;
    }
    rowChannel.setVfoaFrequency1(static_cast<unsigned char>((vfoaFreq >> 24) & 0xFF));
    rowChannel.setVfoaFrequency2(static_cast<unsigned char>((vfoaFreq >> 16) & 0xFF));
    rowChannel.setVfoaFrequency3(static_cast<unsigned char>((vfoaFreq >> 8) & 0xFF));
    rowChannel.setVfoaFrequency4(static_cast<unsigned char>(vfoaFreq & 0xFF));

    // VFOB频率 (第4列)
    unsigned long long vfobFreq = model->data(model->index(row, 4)).toULongLong();
    if(vfobFreq > 4294967295) {
        vfobFreq = 300003000;
    }
    rowChannel.setVfobFrequency1(static_cast<unsigned char>((vfobFreq >> 24) & 0xFF));
    rowChannel.setVfobFrequency2(static_cast<unsigned char>((vfobFreq >> 16) & 0xFF));
    rowChannel.setVfobFrequency3(static_cast<unsigned char>((vfobFreq >> 8) & 0xFF));
    rowChannel.setVfobFrequency4(static_cast<unsigned char>(vfobFreq & 0xFF));

    // VFOA模式 (第5列)
    unsigned char vfoaMode = static_cast<unsigned char>(vfoModes.indexOf(model->data(model->index(row, 5)).toString()));
    rowChannel.setVfoaMode(vfoaMode);

    // VFOB模式 (第6列)
    unsigned char vfobMode = static_cast<unsigned char>(vfoModes.indexOf(model->data(model->index(row, 6)).toString()));
    rowChannel.setVfobMode(vfobMode);

    int emitIndex = yayinModes.indexOf(model->data(model->index(row, 7)).toString());
    if (emitIndex < 0 || emitIndex >= yayinModes.size()) {
        emitIndex = 0; // 默认值
    }
    rowChannel.setEmitYayin(static_cast<unsigned char>(emitIndex));

    // 接收亚音 (第8列)
    int receiveIndex = yayinModes.indexOf(model->data(model->index(row, 8)).toString());
    if (receiveIndex < 0 || receiveIndex >= yayinModes.size()) {
        receiveIndex = 0; // 默认值
    }
    rowChannel.setReceiveYayin(static_cast<unsigned char>(receiveIndex));

    return rowChannel;
}

/**
 *  UI
 *  读取该行数据为DMR对象
 *  @param  int row 行号
 *  @return DMR 对象
 */
DMR termial::rowReadDataToDmr(int row) {
    DMR rowDmr;
    unsigned short channelValue;

    // 信道号 (第1列)
    channelValue = model->data(model->index(row, 1)).toUInt();
    rowDmr.setChannelHigh(static_cast<unsigned char>((channelValue >> 8) & 0xFF));
    rowDmr.setChannelLow(static_cast<unsigned char>(channelValue & 0xFF));

    // 呼叫类型 (第9列)
    unsigned char callFormat = callTypes.indexOf(model->data(model->index(row, 9)).toString());
    rowDmr.setCallFormat(callFormat);

    // Tx_cc (第10列)
    unsigned char txCc = static_cast<unsigned char>(model->data(model->index(row, 10)).toUInt());
    rowDmr.setTxCc(txCc);

    // Rx_cc (第11列)
    unsigned char rxCc = static_cast<unsigned char>(model->data(model->index(row, 11)).toUInt());
    rowDmr.setRxCc(rxCc);

    // 时隙 (第12列)
    unsigned char slot = static_cast<unsigned char>(model->data(model->index(row, 12)).toUInt());
    rowDmr.setSlot(slot);

    // 呼叫ID (第13列)
    unsigned long long callId = model->data(model->index(row, 13)).toULongLong();
    if(callId > 16777214) callId = 0;
    rowDmr.setCallID(static_cast<unsigned int>(callId));

    // Own ID (第14列)
    unsigned long long ownId = model->data(model->index(row, 14)).toULongLong();
    if(ownId > 16777214) ownId = 0;
    rowDmr.setOwnID(static_cast<unsigned int>(ownId));

    // 信道类型 (第15列)
    unsigned char chType = chTypes.indexOf(model->data(model->index(row, 15)).toString());
    rowDmr.setChType(chType);

    // Rx Ctcss (第16列)
    unsigned char rxCtcss = dmrYayinModes.indexOf(model->data(model->index(row,16)).toString());
    rowDmr.setRxCtcss(rxCtcss);

    // Tx Ctcss (第17列)
    unsigned char txCtcss = dmrYayinModes.indexOf(model->data(model->index(row,17)).toString());
    rowDmr.setTxCtcss(txCtcss);

    // SQL等级 (第18列)
    unsigned char sqlevel = static_cast<unsigned char>(model->data(model->index(row, 18)).toUInt());
    rowDmr.setSqlevel(sqlevel);

    return rowDmr;
}

/**
 *  UI
 *  辅助函数
 *  修改DMR状态
 */
void termial::updateDmrWidgetsState(int row) {
    bool isDmr = vfoaModeIsDmr || vfobModeIsDmr;

    // 定义DMR相关列的列表
    QList<int> dmrColumns = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

    if (isDmr) {
        // 启用DMR相关列
        for (int col : dmrColumns) {
            // 设置可编辑状态
            model->item(row, col)->setFlags(model->item(row, col)->flags() | Qt::ItemIsEditable);
        }
    } else {
        // 禁用DMR相关列
        for (int col : dmrColumns) {
            // 设置不可编辑状态
            model->item(row, col)->setFlags(model->item(row, col)->flags() & ~Qt::ItemIsEditable);
        }

    }

    // 刷新视图
    ui->tableView->viewport()->update();
}

/**
 *  UI
 *  辅助函数
 *  遍历所有复选框,将勾选行加入List<channel>
 */
void termial::getAllCheckedRowsToList(QList<channel>* list) {
    if (!list) return;
    list->clear();

    for (int row = 0; row < model->rowCount(); ++row) {
        // 正确获取CheckStateRole的状态
        Qt::CheckState state = static_cast<Qt::CheckState>(
            model->data(model->index(row, 0), Qt::CheckStateRole).toInt());

        if (state == Qt::Checked) {
            list->append(rowReadDataToChannel(row));
        }
    }
}

/**
 *  UI
 *  辅助函数
 *  遍历所有复选框,将勾选的行加入List<DMR>
 */
void termial::getAllCheckedRowsToListDmr(QList<DMR>* readySendDmrList) {
    if (!readySendDmrList) return;

    readySendDmrList->clear();

    for(int i = 0; i < model->rowCount(); i++) {
        // 获取复选框状态
        Qt::CheckState state = static_cast<Qt::CheckState>(model->data(model->index(i, 0), Qt::CheckStateRole).toInt());

        if(state == Qt::Checked) {
            readySendDmrList->append(rowReadDataToDmr(i));
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



/*  初始化  */ 
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


    connect(ui->channelMaxNum_spinBox, SIGNAL(valueChanged(int)), this, SLOT(channelMaxNumSpinBox_valueChanged(int)));


}

/**
 *  初始化语言下拉框
 */
void termial::initLanguageComboBox(){
    ui->language_comboBox->addItem("English");
    ui->language_comboBox->addItem("中文");
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
 *  初始化模型和视图
 *  初始化表格模型和视图,设置表头,设置委托,设置居中对齐,连接信号槽
 */
void termial::initModelsAndViews()
{
    ui->tableView->setModel(model);

    // 初始化各种委托
    checkBoxDelegate = new CheckBoxDelegate(this);  // 复选框委托
    vfoModeDelegate = new ComboBoxDelegate(vfoModes, this); // 多选框委托
    yayinDelegate = new ComboBoxDelegate(yayinModes, this);
    dmrYayinDelegate = new ComboBoxDelegate(dmrYayinModes, this);
    callTypeDelegate = new ComboBoxDelegate(callTypes, this);
    ccDelegate = new SpinBoxDelegate(0, 15, this);    // 色码数字框
    slotDelegate = new SpinBoxDelegate(1,2, this);  // 时隙数字框
    idDelegate = new SpinBoxDelegate(0,16777215,this); // callid和ownid数字框
    chTypeDelegate = new ComboBoxDelegate(chTypes, this);

    // 设置各列委托
    ui->tableView->setItemDelegateForColumn(0, checkBoxDelegate);  // 复选框列
    ui->tableView->setItemDelegateForColumn(5, vfoModeDelegate);   // VFOA模式
    ui->tableView->setItemDelegateForColumn(6, vfoModeDelegate);   // VFOB模式
    ui->tableView->setItemDelegateForColumn(7, yayinDelegate);    // 发射亚音
    ui->tableView->setItemDelegateForColumn(8, yayinDelegate);    // 接收亚音
    ui->tableView->setItemDelegateForColumn(9, callTypeDelegate); // 呼叫类型
    ui->tableView->setItemDelegateForColumn(10, ccDelegate);    // Tx_cc
    ui->tableView->setItemDelegateForColumn(11, ccDelegate);    // Rx_cc
    ui->tableView->setItemDelegateForColumn(12, slotDelegate);   // 时隙
    ui->tableView->setItemDelegateForColumn(13, idDelegate);    // call_id
    ui->tableView->setItemDelegateForColumn(14, idDelegate);    // own_id
    ui->tableView->setItemDelegateForColumn(15, chTypeDelegate);    // DMR 模式选择
    ui->tableView->setItemDelegateForColumn(16, dmrYayinDelegate); // DMR 接收亚音
    ui->tableView->setItemDelegateForColumn(17, dmrYayinDelegate); // DMR 发射亚音


    // 设置所有单元格居中
    for(int row = 0; row < model->rowCount(); ++row) {
        for(int col = 0; col < model->columnCount(); ++col) {
            QStandardItem* item = model->item(row, col);
            if(!item) {
                item = new QStandardItem();
                model->setItem(row, col, item);
            }
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            // 特殊处理复选框列（第0列）
            if(col == 0) {
                item->setCheckable(true);
                item->setText(""); // 清除复选框列的文本
            }
        }
    }

    // 连接复选框被点击时信号
    connect(model, &QStandardItemModel::dataChanged,
            this, &termial::onDataChanged);

    // 初始化表格
    initTableView();
}
/**
 *  初始化表格
 *  初始化表格模型和视图,设置表头,设置委托,设置居中对齐,连接信号槽
 */
void termial::initTableView()
{
    // 禁用自动更新以提高性能
    ui->tableView->setUpdatesEnabled(false);

    // 设置列数和表头
    model->setColumnCount(18); // 根据实际需求调整列数
    model->setHorizontalHeaderLabels({
        "-","    CHANNEL    ","  NAME  ","    VFA_FREQ(Hz)    ","    VFB_FREQ(Hz)    ","    VFA_MODE    ","    VFB_MODE    ",
        "    T_CTCSS    ","    R_CTCSS    ","    call_type    ","    Tx_cc    ","    Rx_cc    ","     slot     ",
        "    Call_id    ","    Own_id    ","    Ch_type    ","    Rx_ctcss    ","    Tx_ctcss    ","    sqlevel    "
    });
    ui->tableView->verticalHeader()->hide();  // 隐藏垂直表头（行号所在的位置）
    // 设置行数
    model->setRowCount(1000);

    // 初始化默认数据
    for (int row = 0; row < 1000; ++row) {
        model->setData(model->index(row, 0), false, Qt::CheckStateRole); // 复选框默认不选中
        model->setData(model->index(row, 1), row); // 信道号
    }

    for (int row = 0; row < model->rowCount(); ++row) {
        // 设置复选框列的初始状态
        QStandardItem* item = new QStandardItem();
        item->setCheckable(true);
        item->setData(Qt::Unchecked, Qt::CheckStateRole); // 初始状态
        model->setItem(row, 0, item);

        // 设置信道号不可更改
        QStandardItem* item2 = model->item(row, 1);  // 第二列
        if (item2) {
            item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
        }


        // 设置所有单元格居中
        for(int col = 0; col < model->columnCount(); ++col) {
            QStandardItem* item = model->item(row, col);
            if(!item) {
                item = new QStandardItem();
                model->setItem(row, col, item);
            }
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            // 特殊处理复选框列（第0列）
            if(col == 0) {
                item->setCheckable(true);
                item->setText(""); // 清除复选框列的文本
            }
        }
    }

    // 启用更新
    ui->tableView->setUpdatesEnabled(true);

    // 调整列宽
    ui->tableView->resizeColumnsToContents();
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

}

/**
 *  UI
*   初始化按钮状态
*/
void termial::initPushBtnState(){
    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);
}




/**
 *  UI
 *  初始化进度条
 */
void termial::initLoad(){
    //设置圆角 border-radius 这里要注意如果设置的圆角大于或等进度条高度的一半，圆角设置无效， 比如进度条的高度为10， 圆然设置为5px或以上就不会起作用
    ui->load_progressBar->setStyleSheet("QProgressBar{text-align:center;\
                                        background-color:#DDDDDD;border: 0px solid #DDDDDD;border-radius:5px;}"
                                        "QProgressBar::chunk{background-color:#05B8CC; border-radius: 5px;}");
    ui->load_progressBar->setOrientation(Qt::Horizontal);  // 水平方向
    ui->load_progressBar->setMaximum(1999);
    ui->load_progressBar->setMinimum(0);
    ui->load_progressBar->setValue(0);
}

/*  槽函数  */ 
/**
 *  用户选择读取到那个位置
 */
void termial::channelMaxNumSpinBox_valueChanged(int value){
    setNumCheckedState(value);
}



/**
 *  数据发生变化时触发
 *  目前的功能有：
 *      1.当vfa_mode vfb_mode为ture时才能设置更改dmr相关列数据，否则禁止修改
 *      2.当ch_type为DFM模式时才能改动Rx_ctcss Tx_ctcss
 */
void termial::onDataChanged(const QModelIndex &topLeft,
                            const QModelIndex &bottomRight,
                            const QVector<int> &roles) {
    Q_UNUSED(roles)

    if ((topLeft.column() <= 15 && bottomRight.column() >= 5) ||
        (topLeft.column() <= 15 && bottomRight.column() >= 15)) {
        for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
            QString vfoaMode = model->data(model->index(row, 5)).toString();
            QString vfobMode = model->data(model->index(row, 6)).toString();
            bool isDmr = (vfoaMode == "DMR") || (vfobMode == "DMR");

            // 修改1：添加默认值处理，当chType为空时默认视为DFM
            QString chType = model->data(model->index(row, 15)).toString();
            bool isDfm = chType.isEmpty() || (chType == "DFM"); // 空值视为DFM

            QList<int> dmrColumns = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

            for (int col : dmrColumns) {
                QStandardItem* item = model->item(row, col);
                if (item) {
                    if (isDmr) {
                        if (col == 16 || col == 17) {
                            bool editable = isDfm;
                            item->setFlags(editable ? (item->flags() | Qt::ItemIsEditable)
                                                    : (item->flags() & ~Qt::ItemIsEditable));
                        } else {
                            if(col != 18)
                                item->setFlags(item->flags() | Qt::ItemIsEditable);
                        }
                    } else {
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    }
                }
            }
        }
    }
}



/**
 *  语言切换
 *  当语言下拉框发生变化时
 *  @param  int index   下拉框选择
 */
void termial::switchLanguage(int index){
    qApp->removeTranslator(&translator); // 移除旧的翻译器
    switch(index){
    case 0:
        loadLanguageAsync("lang_English.qm");
        break;
    case 1:
        loadLanguageAsync("lang_Chinese.qm");
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

    ui->save_pushButton->setEnabled(false);
    ui->open_pushButton->setEnabled(false);
    ui->send_btn->setEnabled(false);
    ui->read_btn->setEnabled(false);
    switch(index){
    case 0:
        /* 编程页 */
        currentPage = tr("编程");
        ui->save_pushButton->setEnabled(true);
        ui->open_pushButton->setEnabled(true);
        ui->send_btn->setEnabled(true);
        ui->read_btn->setEnabled(true);
        break;
    }
}

/**
 *  UI
*   保存为json
*/
void termial::saveBtn_clicked(){
    // 改为使用指针列表
    QList<channel>* saveJsonList = new QList<channel>();
    QList<DMR>* saveJsonDmrList = new QList<DMR>();

    debug("取所有勾选的channel对象开始");
    // 获取所有勾选的channel对象 - 现在传递指针
    getAllCheckedRowsToList(saveJsonList);
    getAllCheckedRowsToListDmr(saveJsonDmrList);
    debug("获取所有勾选的channel对象结束");

    // 让用户选择保存位置及其文件名
    QString jsonPath = getUserSaveLocation(this, "JSON Files (*.json)");
    debug("选择保存的位置:" + jsonPath);

    QJsonObject channelDmrsObj;
    ChannelDmr channelDmr;

    int size = qMin(saveJsonList->size(), saveJsonDmrList->size());

    for (int i = 0; i < size; ++i) {
        channelDmr.buildChannelDmr(saveJsonList->at(i), saveJsonDmrList->at(i));  // 使用指针访问元素
        channelDmrsObj[QString::number(channelDmr.getChannelID())] = channelDmr.toJSON();
    }

    if (!saveQJsonObjectToFile(channelDmrsObj, jsonPath)) {
        debug("保存失败");
    }

    // 释放内存
    delete saveJsonList;
    delete saveJsonDmrList;
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
        debug("json转化失败\n\t") << jsonError.errorString();
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

    // 设置正确的最大值
    ui->load_progressBar->setMaximum(openJsonList.count() + openJsonDmrList.count());
    ui->load_progressBar->setValue(0);

    // 更新进度
    for (int i = 0; i < openJsonList.count(); ++i) {
        viewUpdate(openJsonList[i].getChannelID(), openJsonList[i]);
        ui->load_progressBar->setValue(i+1);
        QCoreApplication::processEvents(); // 确保UI更新
    }

    for (int i = 0; i < openJsonDmrList.count(); ++i) {
        viewUpdateDmr(openJsonDmrList[i].getChannelID(), openJsonDmrList[i]);
        ui->load_progressBar->setValue(openJsonList.count() + i + 1);
        QCoreApplication::processEvents(); // 确保UI更新
    }

}

/**
 *  控制区
 *  当点击读取按钮时
 */
void termial::readBtn_clicked(){
    getAllCheckedRowsToList(readySend41ChannelList);    // 将所有选中行放入List待发送列表
    getAllCheckedRowsToListDmr(readySend44ChannelList);

    readBtn_busy = true;

    if(readySend41ChannelList->isEmpty() && readySend44ChannelList->isEmpty()){
        debug("没有选中任何行");
        ui->read_btn->setText(tr("读取"));
        readBtn_busy = false;
        return;
    }

    retryCount0x41 = 0;  // 开始新命令序列时重置计数器
    retryCount0x44 = 0;

    // 计算进度条
    ui->load_progressBar->setMaximum(readySend41ChannelList->size() + readySend44ChannelList->size());
    ui->load_progressBar->setValue(0);


    // 获取41列表中第一个命令,发送后删除对应命令
    if(!readySend41ChannelList->isEmpty()){
        serialPortTool.takeFirst41ListWrite(channelRead,readySend41ChannelList,currentSerialport);
        // 启动定时器，等待50毫秒，超时重发
        retransmissionTimer0x41->start(200);
    }
}

/**
 *  控制区
 *  点击发送按钮时
 */
void termial::send_clicked(){
     // 若没连接就点击
    if(!currentSerialport.isOpen()){
        QMessageBox::warning(this, tr("警告") , tr("未连接串口!"));
        return;
    }


    if(!sendBtn_busy){
        // 不在发送状态
        ui->send_btn->setText(tr("正在发送.."));
        sendBtn_clicked();
    }else{
        ui->send_btn->setText(tr("发送"));
        if(retransmissionTimer0x40->isActive()){
            retransmissionTimer0x40->stop();
        }
        if(retransmissionTimer0x43->isActive()){
            retransmissionTimer0x43->stop();
        }

        readySend40ChannelList->clear();
        readySend41ChannelList->clear();
        readySend43ChannelList->clear();
        readySend44ChannelList->clear();

        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);

        sendBtn_busy = false;

        ui->load_progressBar->reset();//重置进度条
    }
}
/**
 *  控制区
 *  读取按钮点击时
 */
void termial::read_clicked(){
    getAllCheckedRowsToList(readySend40ChannelList);
    getAllCheckedRowsToList(readySend41ChannelList);
    getAllCheckedRowsToListDmr(readySend43ChannelList);
    getAllCheckedRowsToListDmr(readySend44ChannelList);

    // 若没连接就点击
    if(!currentSerialport.isOpen()){
        QMessageBox::warning(this, tr("警告") , tr("未连接串口!"));
        return;
    }

    // 判断按钮处于什么状态
    if(!readBtn_busy){
        // 不在读取状态
        ui->read_btn->setText(tr("正在读取.."));
        readBtn_clicked();
    }else{  // 再次点击终止发送
        ui->read_btn->setText(tr("读取"));
        if(retransmissionTimer0x41->isActive()){
            retransmissionTimer0x41->stop();
        }
        if(retransmissionTimer0x44->isActive()){
            retransmissionTimer0x44->stop();
        }

        readySend40ChannelList->clear();
        readySend41ChannelList->clear();
        readySend43ChannelList->clear();
        readySend44ChannelList->clear();


        ui->checkAll_pushButton->setEnabled(true);
        ui->checkNotAll_pushButton->setEnabled(true);

        readBtn_busy = false;

        ui->load_progressBar->reset();//重置进度条
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
void termial::setAllCheckedState(bool state) {
    // 设置进度条
    int totalRows = model->rowCount();
    ui->load_progressBar->setMaximum(totalRows);
    ui->load_progressBar->setValue(0);

    // 批量操作前禁用信号
    bool oldState = model->blockSignals(true);

    // 一次设置所有行的复选框状态
    Qt::CheckState checkState = state ? Qt::Checked : Qt::Unchecked;
    for (int i = 0; i < totalRows; ++i) {
        model->item(i, 0)->setCheckState(checkState);

        // 每100行更新一次进度
        if (i % 100 == 0) {
            ui->load_progressBar->setValue(i);
            QCoreApplication::processEvents();
        }
    }

    // 完成进度
    ui->load_progressBar->setValue(totalRows);

    // 恢复信号状态
    model->blockSignals(oldState);

    // 通知视图更新
    emit model->dataChanged(model->index(0, 0),
                            model->index(totalRows - 1, 0));
}

/**
 *  设置到指定数量的复选框状态
 */
void termial::setNumCheckedState(int value) {
    // 确保值在有效范围内
    if (value < 0 || value > model->rowCount()) {
        debug("无效的行数范围:") << value;
        return;
    }

    // 设置进度条
    ui->load_progressBar->setMaximum(value);
    ui->load_progressBar->setValue(0);

    // 批量操作前禁用信号以提高性能
    bool oldState = model->blockSignals(true);

    // 先取消所有选择
    for (int i = 0; i < model->rowCount(); ++i) {
        model->item(i, 0)->setCheckState(Qt::Unchecked);
    }

    // 勾选从0到value-1的行
    for (int i = 0; i < value; ++i) {
        model->item(i, 0)->setCheckState(Qt::Checked);

        // 每100行更新一次进度
        if (i % 100 == 0) {
            ui->load_progressBar->setValue(i);
            QCoreApplication::processEvents(); // 确保UI更新
        }
    }

    // 完成进度
    ui->load_progressBar->setValue(value);

    // 恢复信号状态
    model->blockSignals(oldState);

    // 通知视图更新
    emit model->dataChanged(model->index(0, 0),
                            model->index(model->rowCount() - 1, 0));

    debug("已勾选 0 ~") << value << "行";
}



/**
 *  串口
*   当点击发送按钮时
*   发送第一条数据，后续数据由接收到回复后再发送
*/
void termial::sendBtn_clicked(){
    readySend40ChannelList->clear();
    readySend43ChannelList->clear();

    getAllCheckedRowsToList(readySend40ChannelList);
    getAllCheckedRowsToListDmr(readySend43ChannelList);

    sendBtn_busy = true;

    if(readySend40ChannelList->isEmpty() && readySend43ChannelList->isEmpty()){
        debug("没有选中任何行");
        ui->send_btn->setText(tr("发送"));
        sendBtn_busy = false;
        return;
    }

    retryCount0x40 = 0;  // 开始新命令序列时重置计数器
    retryCount0x43 = 0;

    // 计算进度条
    ui->load_progressBar->setMaximum(readySend40ChannelList->size() + readySend43ChannelList->size());
    ui->load_progressBar->setValue(0);

    // 更新按钮状态
    ui->send_btn->setText(tr("发送中..."));
    ui->checkAll_pushButton->setEnabled(false);
    ui->checkNotAll_pushButton->setEnabled(false);

    // 只发送第一个命令，后续命令由响应处理
    if(!readySend40ChannelList->isEmpty()){
        serialPortTool.takeFirst40ListWrite(channelWrite,readySend40ChannelList,currentSerialport);
        retransmissionTimer0x40->start(200);
    }
}



/**
 * 根据单行文本框内容跳转至对应行数
 */
void termial::channelNumLineEdit_returnPressed() {
    QString text = ui->channelNum_lineEdit->text();
    bool ok;
    int row = text.toInt(&ok);

    if (ok && row >= 0 && row < model->rowCount()) {
        // 清除当前选择
        ui->tableView->selectionModel()->clearSelection();

        // 创建选择范围（整行）
        QItemSelection selection(
            model->index(row, 0),  // 左上角
            model->index(row, model->columnCount() - 1)  // 右下角
            );

        // 设置选择并高亮
        ui->tableView->selectionModel()->select(
            selection,
            QItemSelectionModel::Select | QItemSelectionModel::Rows
            );

        // 滚动到该行
        ui->tableView->scrollTo(
            model->index(row, 0),
            QAbstractItemView::PositionAtCenter
            );

        // 可选：设置焦点
        ui->tableView->setFocus();
    } else {
        // 无效输入处理
        QMessageBox::warning(this,tr("警告"),
                            tr("请输入有效的行号 (0~%1)").arg(model->rowCount() - 1));
    }
}

termial::~termial(){
    readySend40ChannelList->clear();
    readySend41ChannelList->clear();
    readySend43ChannelList->clear();
    readySend44ChannelList->clear();

    // 确保所有定时器停止
    QList<QTimer*> timers = findChildren<QTimer*>();
    for (auto timer : timers) {
        timer->stop();
        timer->deleteLater();
    }

    // 清理串口资源
    if (currentSerialport.isOpen()) {
        currentSerialport.close();
    }

    /* 串口 */
    stopTimerSafe(retransmissionTimer0x40);
    stopTimerSafe(retransmissionTimer0x41);
    stopTimerSafe(retransmissionTimer0x43);
    stopTimerSafe(retransmissionTimer0x44);

    currentSerialport.setDataTerminalReady(false);
    currentSerialport.setRequestToSend(false);

    disconnect(&currentSerialport, &QSerialPort::readyRead, this, &termial::currentSerialport_readyRead);

    // 等待一段时间，确保信号生效
    // QThread::msleep(100);

    if(currentSerialport.isOpen()){
        currentSerialport.close();  // 关闭串口
    }
    delete ui;
}
