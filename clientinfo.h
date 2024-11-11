#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QObject>
#include <QTcpSocket>

class ClientInfo : public QObject
{
    Q_OBJECT
public:
    explicit ClientInfo(QObject *parent = nullptr);

    // 拷贝构造函数
    ClientInfo(const ClientInfo &other) :
        socket(other.socket),
        ip(other.ip),
        port(other.port){}

    // 移动构造函数
    ClientInfo(ClientInfo &&other) noexcept :
        socket(other.socket),
        ip(std::move(other.ip)),
        port(other.port) {
        other.socket = nullptr;
    }

    // 拷贝赋值运算符
    ClientInfo& operator=(const ClientInfo &other) {
        if (this != &other) {
            socket = other.socket;
            ip = other.ip;
            port = other.port;
        }
        return *this;
    }

    // 移动赋值运算符
    ClientInfo& operator=(ClientInfo &&other) noexcept {
        if (this != &other) {
            socket = other.socket;
            ip = std::move(other.ip);
            port = other.port;
            other.socket = nullptr;
        }
        return *this;
    }


    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *newSocket);

    QString getIp() const;
    void setIp(const QString &newIp);

    quint16 getPort() const;
    void setPort(quint16 newPort);

private:
    QTcpSocket *socket;
    QString ip;
    quint16 port;

};

#endif // CLIENTINFO_H
