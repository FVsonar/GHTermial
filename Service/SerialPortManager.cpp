#include "SerialPortManager.h"
#include <QDebug>

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject(parent)
{
    connect(&serialPort, &QSerialPort::readyRead, this, &SerialPortManager::handleReadyRead);
    connect(&serialPort, &QSerialPort::errorOccurred, this, &SerialPortManager::handleError);
}

SerialPortManager::~SerialPortManager()
{
    closePort();
}

bool SerialPortManager::openPort(const QSerialPortInfo &info)
{
    if (serialPort.isOpen())
        serialPort.close();
    serialPort.setPort(info);
    if (serialPort.open(QIODevice::ReadWrite)) {
        emit portOpened();
        return true;
    } else {
        emit errorOccurred(serialPort.errorString());
        return false;
    }
}

void SerialPortManager::closePort()
{
    if (serialPort.isOpen()) {
        serialPort.close();
        emit portClosed();
    }
}

bool SerialPortManager::isOpen() const
{
    return serialPort.isOpen();
}

void SerialPortManager::writeData(const QByteArray &data)
{
    if (serialPort.isOpen()) {
        serialPort.write(data);
    }
}

void SerialPortManager::setDTR(bool set)
{
    if (serialPort.isOpen()) {
        serialPort.setDataTerminalReady(set);
    }
}

void SerialPortManager::setRTS(bool set)
{
    if (serialPort.isOpen()) {
        serialPort.setRequestToSend(set);
    }
}

QSerialPort* SerialPortManager::getSerialPort()
{
    return &serialPort;
}

void SerialPortManager::handleReadyRead()
{
    QByteArray data = serialPort.readAll();
    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}

void SerialPortManager::handleError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        emit errorOccurred(serialPort.errorString());
    }
} 