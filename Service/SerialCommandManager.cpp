#include "SerialCommandManager.h"
#include "SerialPortManager.h"
#include <QDebug>

SerialCommandManager::SerialCommandManager(SerialPortManager* serialManager, QObject *parent)
    : QObject(parent)
    , serialManager(serialManager)
    , retransmissionTimer0x40(new QTimer(this))
    , retransmissionTimer0x41(new QTimer(this))
    , retransmissionTimer0x43(new QTimer(this))
    , retransmissionTimer0x44(new QTimer(this))
    , retryCount0x40(0)
    , retryCount0x41(0)
    , retryCount0x43(0)
    , retryCount0x44(0)
{
    // 连接定时器信号
    connect(retransmissionTimer0x40, &QTimer::timeout, this, &SerialCommandManager::onTimeout0x40);
    connect(retransmissionTimer0x41, &QTimer::timeout, this, &SerialCommandManager::onTimeout0x41);
    connect(retransmissionTimer0x43, &QTimer::timeout, this, &SerialCommandManager::onTimeout0x43);
    connect(retransmissionTimer0x44, &QTimer::timeout, this, &SerialCommandManager::onTimeout0x44);
}

SerialCommandManager::~SerialCommandManager()
{
    stopAllTimers();
}

void SerialCommandManager::sendCommand(const QByteArray &data, int commandType, std::function<void()> onSuccess)
{
    if (!serialManager || !serialManager->isOpen()) {
        qDebug() << "串口未打开，无法发送命令";
        return;
    }

    // 停止对应定时器
    QTimer* timer = getTimerForCommand(commandType);
    stopTimerSafe(timer);

    // 重置重试计数器
    resetRetryCount(commandType);

    // 保存命令数据和回调
    getCurrentCommandForType(commandType) = data;
    getSuccessCallbackForCommand(commandType) = onSuccess;

    // 发送命令
    serialManager->writeData(data);
    qDebug() << QString("发送命令 0x%1:").arg(commandType, 0, 16) << data.toHex(' ');

    // 启动定时器
    timer->start(RETRY_INTERVAL);
}

void SerialCommandManager::stopAllTimers()
{
    stopTimerSafe(retransmissionTimer0x40);
    stopTimerSafe(retransmissionTimer0x41);
    stopTimerSafe(retransmissionTimer0x43);
    stopTimerSafe(retransmissionTimer0x44);
}

void SerialCommandManager::resetRetryCount(int commandType)
{
    getRetryCountForCommand(commandType) = 0;
}

void SerialCommandManager::onTimeout0x40()
{
    if (retryCount0x40 >= MAX_RETRY_COUNT) {
        qDebug() << "0x40 命令已达到最大重试次数(3次)，跳过此命令";
        emit commandMaxRetriesReached(0x40);
        stopTimerSafe(retransmissionTimer0x40);
        return;
    }

    emit commandTimeout(0x40, retryCount0x40 + 1);
    qDebug() << QString("0x40 超时重发(尝试次数:%1):").arg(retryCount0x40 + 1) << currentCommand0x40.toHex(' ');
    
    serialManager->writeData(currentCommand0x40);
    retryCount0x40++;
}

void SerialCommandManager::onTimeout0x41()
{
    if (retryCount0x41 >= MAX_RETRY_COUNT) {
        qDebug() << "0x41 命令已达到最大重试次数(3次)，跳过此命令";
        emit commandMaxRetriesReached(0x41);
        stopTimerSafe(retransmissionTimer0x41);
        return;
    }

    emit commandTimeout(0x41, retryCount0x41 + 1);
    qDebug() << QString("0x41 超时重发(尝试次数:%1):").arg(retryCount0x41 + 1) << currentCommand0x41.toHex(' ');
    
    serialManager->writeData(currentCommand0x41);
    retryCount0x41++;
}

void SerialCommandManager::onTimeout0x43()
{
    if (retryCount0x43 >= MAX_RETRY_COUNT) {
        qDebug() << "0x43 命令已达到最大重试次数(3次)，跳过此命令";
        emit commandMaxRetriesReached(0x43);
        stopTimerSafe(retransmissionTimer0x43);
        return;
    }

    emit commandTimeout(0x43, retryCount0x43 + 1);
    qDebug() << QString("0x43 超时重发(尝试次数:%1):").arg(retryCount0x43 + 1) << currentCommand0x43.toHex(' ');
    
    serialManager->writeData(currentCommand0x43);
    retryCount0x43++;
}

void SerialCommandManager::onTimeout0x44()
{
    if (retryCount0x44 >= MAX_RETRY_COUNT) {
        qDebug() << "0x44 命令已达到最大重试次数(3次)，跳过此命令";
        emit commandMaxRetriesReached(0x44);
        stopTimerSafe(retransmissionTimer0x44);
        return;
    }

    emit commandTimeout(0x44, retryCount0x44 + 1);
    qDebug() << QString("0x44 超时重发(尝试次数:%1):").arg(retryCount0x44 + 1) << currentCommand0x44.toHex(' ');
    
    serialManager->writeData(currentCommand0x44);
    retryCount0x44++;
}

void SerialCommandManager::stopTimerSafe(QTimer* timer)
{
    if (timer && timer->isActive()) {
        timer->stop();
    }
}

QTimer* SerialCommandManager::getTimerForCommand(int commandType)
{
    switch (commandType) {
    case 0x40: return retransmissionTimer0x40;
    case 0x41: return retransmissionTimer0x41;
    case 0x43: return retransmissionTimer0x43;
    case 0x44: return retransmissionTimer0x44;
    default: return nullptr;
    }
}

int& SerialCommandManager::getRetryCountForCommand(int commandType)
{
    switch (commandType) {
    case 0x40: return retryCount0x40;
    case 0x41: return retryCount0x41;
    case 0x43: return retryCount0x43;
    case 0x44: return retryCount0x44;
    default: return retryCount0x40; // 默认返回
    }
}

QByteArray& SerialCommandManager::getCurrentCommandForType(int commandType)
{
    switch (commandType) {
    case 0x40: return currentCommand0x40;
    case 0x41: return currentCommand0x41;
    case 0x43: return currentCommand0x43;
    case 0x44: return currentCommand0x44;
    default: return currentCommand0x40; // 默认返回
    }
}

std::function<void()>& SerialCommandManager::getSuccessCallbackForCommand(int commandType)
{
    switch (commandType) {
    case 0x40: return onSuccess0x40;
    case 0x41: return onSuccess0x41;
    case 0x43: return onSuccess0x43;
    case 0x44: return onSuccess0x44;
    default: return onSuccess0x40; // 默认返回
    }
} 