#include "Tools/serialporttools.h"

/**
 * SerialPort类构造函数
 * @param parent 父对象指针，用于Qt对象树管理
 */
SerialPort::SerialPort(QObject *parent)
    : QObject{parent}
{}

/**
 * 初始化串口配置
 * @param currentSerialportInfo 串口信息对象
 * @param currentSerialport 串口对象
 */
void SerialPort::initSerialport(QSerialPortInfo &currentSerialportInfo,QSerialPort &currentSerialport)
{

    currentSerialport.setBaudRate(QSerialPort::Baud115200); // 设置波特率
    currentSerialport.setDataBits(QSerialPort::Data8);     // 设置数据位
    currentSerialport.setParity(QSerialPort::NoParity);    // 设置校验位
    currentSerialport.setStopBits(QSerialPort::OneStop);   // 设置停止位
    // currentSerialport.setFlowControl(QSerialPort::NoFlowControl);  // 禁用自动RTS/CTS控制
    currentSerialport.setFlowControl(QSerialPort::HardwareControl); // 设置流控制
    currentSerialport.setPort(currentSerialportInfo);

}

/**
 * 读取单条频道数据
 * @param newChannel 频道对象
 * @param currentSerialport 串口对象
 */
void SerialPort::readOne(channel &newChannel,QSerialPort &currentSerialport)
{
    QByteArray channel = newChannel.toReadFrequencyData();
    currentSerialport.write(channel);
}

/**
 * 发送读取单条频道数据的命令
 * @param currentSerialport 串口对象
 */
void SerialPort::sendOneReadData(QSerialPort &currentSerialport){

    channel tempChannel;
    tempChannel.setSize(5);
    tempChannel.setChannelHigh(0);
    tempChannel.setChannelLow(0);
    QByteArray data = tempChannel.preparePacketWithCRC();

    currentSerialport.write(data);
}

/**
 * 从发送40列表中取出第一条数据并发送
 * @param channelWrite 频道对象
 * @param readySend40ChannelList 待发送的40列表
 * @param currentSerialport 串口对象
 */
void SerialPort::takeFirst40ListWrite(channel &channelWrite,QList<channel> *readySend40ChannelList,QSerialPort &currentSerialport){
    channelWrite = readySend40ChannelList->takeFirst();
    channelWrite.setCommand(0x40);
    channelWrite.setSize(15+12+2);

    // QByteArray firstData = channelWrite.prepareWritePacketWithCRC();
    QByteArray firstData = channel_service.build0x40(channelWrite);

    currentSerialport.write(firstData);
}

/**
 * 从发送41列表中取出第一条数据并发送
 * @param channelRead 频道对象
 * @param readySend41ChannelList 待发送的41列表
 * @param currentSerialport 串口对象
 */
void SerialPort::takeFirst41ListWrite(channel &channelRead,QList<channel> *readySend41ChannelList,QSerialPort &currentSerialport){
    channelRead = readySend41ChannelList->takeFirst();
    channelRead.setCommand(0x41);
    channelRead.setSize(5);

    // QByteArray firstData = channelRead.preparePacketWithCRC();
    QByteArray firstData = channel_service.build0x41(channelRead);

    currentSerialport.write(firstData);
}

/**
 * 从发送43列表中取出第一条数据并发送
 * @param dmrWrite DMR对象
 * @param readySend43ChannelList 待发送的43列表
 * @param currentSerialport 串口对象
 */
void SerialPort::takeFirst43ListWrite(DMR &dmrWrite, QList<DMR> *readySend43ChannelList, QSerialPort &currentSerialpor){
    dmrWrite = readySend43ChannelList->takeFirst();
    dmrWrite.setCommand(0x43);
    dmrWrite.setSize(29);

    // QByteArray firstData = dmrWrite.buildWriteData();
    QByteArray firstData = dmr_service.build0x43(dmrWrite);
    debug("0x43 发送的数据\n\t")<<firstData.toHex(' ');
    currentSerialpor.write(firstData);
}

/**
 * 从发送44列表中取出第一条数据并发送
 * @param dmrRead DMR对象
 * @param readySend44ChannelList 待发送的44列表
 * @param currentSerialport 串口对象
 */
void SerialPort::takeFirst44ListWrite(DMR &dmrRead, QList<DMR> *readySend44ChannelList, QSerialPort &currentSerialport)
{
    dmrRead = readySend44ChannelList->takeFirst();
    dmrRead.setCommand(0x44);
    dmrRead.setSize(5);

    // QByteArray firstData = dmrRead.buildReadData();
    QByteArray firstData = dmr_service.build0x44(dmrRead);
    debug("发送的数据\n\t")<<firstData.toHex(' ');
    currentSerialport.write(firstData);
}

