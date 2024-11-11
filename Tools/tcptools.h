#ifndef TCPTOOLS_H
#define TCPTOOLS_H

#include <QObject>
#include <QTcpSocket>
#include "Entity/channel.h"
#include "Entity/dmr.h"
#include "clientinfo.h"

#define debug(x) qDebug()<<"TcpTools:["<<__LINE__<<"]"<<__FUNCTION__<<"()"<<x

class TcpTools : public QObject
{
    Q_OBJECT
public:
    explicit TcpTools(QObject *parent = nullptr);

    /**
     *  tcp
     *  写命令
     *  发送列表中第一条数据后删除对应数据 ,多次调用可将列表所有数据发送并清空列表
     *  使用此函数之前请更新currentClient
     */
    void takeFirst40ListWrite(channel &channelWrite, QList<channel> &readySend40ChannelList, ClientInfo &currentClient);
    /**
     *  tcp
     *  读命令
     *  发送列表中第一条数据后删除对应数据 ,多次调用可将列表所有数据发送并清空列表
     *  使用此函数之前请更新currentClient
     */
    void takeFirst41ListWrite(channel &channelRead, QList<channel> &readySend41ChannelList, ClientInfo &currentClient);
    /**
     *  tcp
     *  44读命令
     *  发送列表中的第一条命令
     *  使用此函数之前请更新currentClient
     */
    void takeFirst44ListWrite(DMR &dmrRead, QList<DMR> &readySend44ChannelList, ClientInfo &currentClient);
    /**
     *  tcp
     *  43写命令
     *  发送列表中的第一条命令
     *  使用此函数之前请更新currentClient
     */
    void takeFirst43ListWrite(DMR &dmrWrite, QList<DMR> &readySend43ChannelList, ClientInfo &currentClient);
signals:
};

#endif // TCPTOOLS_H
