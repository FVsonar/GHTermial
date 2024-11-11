#include "clientinfo.h"

ClientInfo::ClientInfo(QObject *parent)
    : QObject{parent}
{}

QTcpSocket *ClientInfo::getSocket() const
{
    return socket;
}

void ClientInfo::setSocket(QTcpSocket *newSocket)
{
    socket = newSocket;
}

QString ClientInfo::getIp() const
{
    return ip;
}

void ClientInfo::setIp(const QString &newIp)
{
    ip = newIp;
}

quint16 ClientInfo::getPort() const
{
    return port;
}

void ClientInfo::setPort(quint16 newPort)
{
    port = newPort;
}
