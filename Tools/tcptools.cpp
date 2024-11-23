#include "tcptools.h"

TcpTools::TcpTools(QObject *parent)
    : QObject{parent}
{}

/**
 *  tcp
 *  40写命令
 *  发送列表中第一条数据后删除对应数据 ,多次调用可将列表所有数据发送并清空列表
 *  使用此函数之前请使用getCurrentClientInfo更新currentClient
 */
void TcpTools::takeFirst40ListWrite(channel &channelWrite, QList<channel> &readySend40ChannelList, ClientInfo &currentClient)
{
    channelWrite = readySend40ChannelList.takeFirst();
    channelWrite.setCommand(0x40);
    channelWrite.setSize(15+12+2);

    // QByteArray firstData = channelWrite.prepareWritePacketWithCRC();
    QByteArray firstData = channel_service.build0x40(channelWrite);

    debug("40发送数据:")<< firstData.toHex(' ');
    currentClient.getSocket()->write(firstData);
}

/**
 *  tcp
 *  41读命令
 *  发送列表中第一条数据后删除对应数据 ,多次调用可将列表所有数据发送并清空列表
 *  使用此函数之前请使用getCurrentClientInfo更新currentClient
 */
void TcpTools::takeFirst41ListWrite(channel &channelRead, QList<channel> &readySend41ChannelList, ClientInfo &currentClient)
{
    channelRead = readySend41ChannelList.takeFirst();
    channelRead.setCommand(0x41);
    channelRead.setSize(5);


    // QByteArray firstData = channelRead.preparePacketWithCRC();
    QByteArray firstData = channel_service.build0x41(channelRead);

    // 获得当前下拉框选择的IP 端口 客户端套接字
    debug("41发送数据:")<< firstData.toHex(' ');
    currentClient.getSocket()->write(firstData);    // 发送数据包
}

/**
 *  tcp
 *  43写命令
 */
void TcpTools::takeFirst43ListWrite(DMR& dmrWrite,QList<DMR> &readySend43ChannelList, ClientInfo &currentClient){
    dmrWrite = readySend43ChannelList.takeFirst();
    dmrWrite.setCommand(0x43);
    dmrWrite.setSize(29);

    // QByteArray firstData = dmrWrite.buildWriteData();
    QByteArray firstData = dmr_service.build0x43(dmrWrite);

    debug("43发送数据:")<< firstData.toHex(' ');
    currentClient.getSocket()->write(firstData);
}

/**
 *  tcp
 *  44读命令
 *  发送列表中的第一条命令
 */
void TcpTools::takeFirst44ListWrite(DMR& dmrRead,QList<DMR> &readySend44ChannelList, ClientInfo &currentClient){

    dmrRead = readySend44ChannelList.takeFirst();

    dmrRead.setCommand(0x44);
    dmrRead.setSize(5);
    dmrRead.setChannelHigh(dmrRead.getChannelHigh());
    dmrRead.setChannelLow(dmrRead.getChannelLow());

    // QByteArray firstDataDmr = dmrRead.buildReadData();
    QByteArray firstDataDmr = dmr_service.build0x44(dmrRead);

    debug("44发送数据:")<< firstDataDmr.toHex(' ');
    currentClient.getSocket()->write(firstDataDmr); // 发送DMR数据包
}
