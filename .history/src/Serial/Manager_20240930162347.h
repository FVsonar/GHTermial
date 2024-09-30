/*
 * Copyright (c) 2020-2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SERIAL_MANAGER_H
#define SERIAL_MANAGER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QStringList>
#include <QtSerialPort>

namespace Serial
{
class Manager : public QObject
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(QString portName
               READ portName
               NOTIFY portChanged)
    Q_PROPERTY(bool connected
               READ connected
               NOTIFY connectedChanged)
    Q_PROPERTY(bool configurationOk
               READ configurationOk
               NOTIFY portIndexChanged)
    Q_PROPERTY(quint8 portIndex
               READ portIndex
               WRITE setPortIndex
               NOTIFY portIndexChanged)
    Q_PROPERTY(quint8 parityIndex
               READ parityIndex
               WRITE setParity
               NOTIFY parityChanged)
    Q_PROPERTY(quint8 dataBitsIndex
               READ dataBitsIndex
               WRITE setDataBits
               NOTIFY dataBitsChanged)
    Q_PROPERTY(quint8 stopBitsIndex
               READ stopBitsIndex
               WRITE setStopBits
               NOTIFY stopBitsChanged)
    Q_PROPERTY(quint8 flowControlIndex
               READ flowControlIndex
               WRITE setFlowControl
               NOTIFY flowControlChanged)
    Q_PROPERTY(quint8 baudRateIndex
               READ baudRateIndex
               WRITE setBaudRateIndex
               NOTIFY baudRateIndexChanged)
    Q_PROPERTY(qint32 baudRate
               READ baudRate
               WRITE setBaudRate
               NOTIFY baudRateChanged)
    Q_PROPERTY(QStringList portList
               READ portList
               NOTIFY availablePortsChanged)
    Q_PROPERTY(QStringList parityList
               READ parityList
               CONSTANT)
    Q_PROPERTY(QStringList baudRateList
               READ baudRateList
               NOTIFY baudRateListChanged)
    Q_PROPERTY(QStringList dataBitsList
               READ dataBitsList
               CONSTANT)
    Q_PROPERTY(QStringList stopBitsList
               READ stopBitsList
               CONSTANT)
    Q_PROPERTY(QStringList flowControlList
               READ flowControlList
               CONSTANT)
    // clang-format on

signals:
    /**
    * @brief 发送数据的函数
    *
    * 此函数负责通过串行端口发送数据。它可能包含处理数据发送的逻辑，
    * 包括错误检查和重传机制。具体实现应确保数据被正确地发送。
    */
    void tx();

    /**
    * @brief 接收数据的函数
    *
    * 此函数用于处理通过串行端口接收到的数据。它可能包含解析接收到的数据，
    * 以及错误检测的逻辑。具体实现应能正确地处理接收到的数据。
    */
    void rx();

    /**
    * @brief 连接关闭时的回调函数
    *
    * 当串行端口连接关闭时，此函数将被调用。它可以用于执行一些清理工作，
    * 比如重置状态标志或通知用户连接已关闭。
    */
    void closed();

    /**
    * @brief 端口更改时的回调函数
    *
    * 当串行端口设置发生更改时，此函数将被调用。它可以用于更新端口设置，
    * 或者通知用户设置已更改。
    */
    void portChanged();

    /**
    * @brief 奇偶校验更改时的回调函数
    *
    * 当串行端口的奇偶校验设置发生更改时，此函数将被调用。它可以用于更新奇偶校验设置，
    * 或者通知用户设置已更改。
    */
    void parityChanged();

    /**
    * @brief 波特率更改时的回调函数
    *
    * 当串行端口的波特率设置发生更改时，此函数将被调用。它可以用于更新波特率设置，
    * 或者通知用户设置已更改。
    */
    void baudRateChanged();

    /**
    * @brief 数据位数更改时的回调函数
    *
    * 当串行端口的数据位数设置发生更改时，此函数将被调用。它可以用于更新数据位数设置，
    * 或者通知用户设置已更改。
    */
    void dataBitsChanged();

    /**
    * @brief 停止位数更改时的回调函数
    *
    * 当串行端口的停止位数设置发生更改时，此函数将被调用。它可以用于更新停止位数设置，
    * 或者通知用户设置已更改。
    */
    void stopBitsChanged();

    /**
    * @brief 连接状态更改时的回调函数
    *
    * 当串行端口的连接状态发生更改时，此函数将被调用。它可以用于更新连接状态，
    * 或者通知用户连接状态已更改。
    */
    void connectedChanged();

    /**
    * @brief 端口索引更改时的回调函数
    *
    * 当串行端口的索引发生更改时，此函数将被调用。它可以用于更新端口索引，
    * 或者通知用户索引已更改。
    */
    void portIndexChanged();

    /**
    * @brief 流控制设置更改时的回调函数
    *
    * 当串行端口的流控制设置发生更改时，此函数将被调用。它可以用于更新流控制设置，
    * 或者通知用户设置已更改。
    */
    void flowControlChanged();

    /**
    * @brief 波特率列表更改时的回调函数
    *
    * 当串行端口可用的波特率列表发生更改时，此函数将被调用。它可以用于更新波特率列表，
    * 或者通知用户列表已更改。
    */
    void baudRateListChanged();

    /**
    * @brief 波特率索引更改时的回调函数
    *
    * 当串行端口的当前波特率索引发生更改时，此函数将被调用。它可以用于更新波特率索引，
    * 或者通知用户索引已更改。
    */
    void baudRateIndexChanged();

    /**
    * @brief 可用端口列表更改时的回调函数
    *
    * 当串行端口可用的端口列表发生更改时，此函数将被调用。它可以用于更新可用端口列表，
    * 或者通知用户列表已更改。
    */
    void availablePortsChanged();

    /**
    * @brief 发送数据时的信号
    *
    * 当有数据通过串行端口发送时，此函数将被调用。它可以用于记录发送的数据量，
    * 或者触发其他相关的操作。
    *
    * @param data 被发送的数据
    */
    void dataSent(const QByteArray &data);

    /**
    * @brief 连接错误时的信号
    *
    * 当串行端口连接发生错误时，此函数将被调用。它可以用于记录错误，
    * 或者通知用户连接错误的详细信息。
    *
    * @param name 错误的名称或描述
    */
    void connectionError(const QString &name);

    /**
    * @brief 接收数据时的信号
    *
    * 当有数据通过串行端口接收时，此函数将被调用。它可以用于处理接收到的数据，
    * 包括解析和错误检测。
    *
    * @param data 接收到的数据
    */
    void dataReceived(const QByteArray &data);

public:
    /**
    * @brief 获取Manager类的单例实例
    *
    * 该函数用于获取Manager类的单例实例，确保在整个应用程序中只存在一个Manager对象。
    * 这对于需要集中管理或控制的系统资源特别有用。
    *
    * @return Manager* 返回Manager类的单例实例指针
    */
    static Manager *getInstance();

    /**
    * @brief 检查串口是否已连接
    *
    * 该函数用于检查当前串口的状态，是否已经成功连接。
    *
    * @return bool 如果串口已连接，则返回true；否则返回false。
    */
    bool connected() const;

    /**
    * @brief 获取串口名称
    *
    * 该函数用于获取当前配置的串口的名称。
    *
    * @return QString 返回串口的名称。
    */
    QString portName() const;

    /**
    * @brief 获取串口对象
    *
    * 该函数用于获取当前配置的串口对象。
    *
    * @return QSerialPort* 返回QSerialPort对象的指针。
    */
    QSerialPort *port() const;

    /**
    * @brief 检查配置是否正确
    *
    * 该函数用于检查当前串口的配置是否正确，确保所有必要的设置都已正确配置。
    *
    * @return bool 如果配置正确，则返回true；否则返回false。
    */
    bool configurationOk() const;

    /**
    * @brief 获取串口索引
    *
    * 该函数用于获取当前配置的串口索引，这是一个内部使用的索引值。
    *
    * @return quint8 返回串口索引值。
    */
    quint8 portIndex() const;

    /**
    * @brief 获取奇偶校验索引
    *
    * 该函数用于获取当前配置的奇偶校验设置的索引值。
    *
    * @return quint8 返回奇偶校验设置的索引值。
    */
    quint8 parityIndex() const;

    /**
    * @brief 获取显示模式
    *
    * 该函数用于获取当前的显示模式设置。
    *
    * @return quint8 返回显示模式设置的值。
    */
    quint8 displayMode() const;

    /**
    * @brief 获取波特率索引
    *
    * 该函数用于获取当前配置的波特率设置的索引值。
    *
    * @return quint8 返回波特率设置的索引值。
    */
    quint8 baudRateIndex() const;

    /**
    * @brief 获取数据位索引
    *
    * 该函数用于获取当前配置的数据位设置的索引值。
    *
    * @return quint8 返回数据位设置的索引值。
    */
    quint8 dataBitsIndex() const;

    /**
    * @brief 获取停止位索引
    *
    * 该函数用于获取当前配置的停止位设置的索引值。
    *
    * @return quint8 返回停止位设置的索引值。
    */
    quint8 stopBitsIndex() const;

    /**
    * @brief 获取流控制索引
    *
    * 该函数用于获取当前配置的流控制设置的索引值。
    *
    * @return quint8 返回流控制设置的索引值。
    */
    quint8 flowControlIndex() const;

    /**
    * @brief 获取串口列表
    *
    * 该函数用于获取系统中可用串口的列表。
    *
    * @return QStringList 返回可用串口的名称列表。
    */
    QStringList portList() const;

    /**
    * @brief 获取奇偶校验列表
    *
    * 该函数用于获取支持的奇偶校验设置的列表。
    *
    * @return QStringList 返回奇偶校验设置的列表。
    */
    QStringList parityList() const;

    /**
    * @brief 获取波特率列表
    *
    * 该函数用于获取支持的波特率设置的列表。
    *
    * @return QStringList 返回波特率设置的列表。
    */
    QStringList baudRateList() const;

    /**
    * @brief 获取数据位列表
    *
    * 该函数用于获取支持的数据位设置的列表。
    *
    * @return QStringList 返回数据位设置的列表。
    */
    QStringList dataBitsList() const;

    /**
    * @brief 获取停止位列表
    *
    * 该函数用于获取支持的停止位设置的列表。
    *
    * @return QStringList 返回停止位设置的列表。
    */
    QStringList stopBitsList() const;

    /**
    * @brief 获取流控制列表
    *
    * 该函数用于获取支持的流控制设置的列表。
    *
    * @return QStringList 返回流控制设置的列表。
    */
    QStringList flowControlList() const;

    /**
    * @brief 获取波特率
    *
    * 该函数用于获取当前配置的波特率值。
    *
    * @return qint32 返回当前配置的波特率值。
    */
    qint32 baudRate() const;

    /**
    * @brief 获取奇偶校验设置
    *
    * 该函数用于获取当前配置的奇偶校验设置。
    *
    * @return QSerialPort::Parity 返回奇偶校验设置。
    */
    QSerialPort::Parity parity() const;

    /**
    * @brief 获取数据位设置
    *
    * 该函数用于获取当前配置的数据位设置。
    *
    * @return QSerialPort::DataBits 返回数据位设置。
    */
    QSerialPort::DataBits dataBits() const;

    /**
    * @brief 获取停止位设置
    *
    * 该函数用于获取当前配置的停止位设置。
    *
    * @return QSerialPort::StopBits 返回停止位设置。
    */
    QSerialPort::StopBits stopBits() const;

    /**
    * @brief 获取流控制设置
    *
    * 该函数用于获取当前配置的流控制设置。
    *
    * @return QSerialPort::FlowControl 返回流控制设置。
    */
    QSerialPort::FlowControl flowControl() const;

    /**
    * @brief 向串口写入数据
    *
    * 该函数用于向串口写入数据，是Q_INVOKABLE的，可以在QML中调用。
    *
    * @param data 要写入的数据，类型为QByteArray。
    * @return qint64 返回写入的数据字节数。
    */
    Q_INVOKABLE qint64 writeData(const QByteArray &data);

public slots:
    void connectDevice();
    void disconnectDevice();
    void toggleConnection();
    void setBaudRate(const qint32 rate);
    void setBaudRateIndex(const int index);
    void setParity(const quint8 parityIndex);
    void setPortIndex(const quint8 portIndex);
    void setDataBits(const quint8 dataBitsIndex);
    void setStopBits(const quint8 stopBitsIndex);
    void setFlowControl(const quint8 flowControlIndex);

private slots:
    void onDataReceived();
    void refreshSerialDevices();
    void handleError(QSerialPort::SerialPortError error);

private:
    Manager();
    ~Manager();
    QList<QSerialPortInfo> validPorts() const;

private:
    QSerialPort *m_port;

    QTimer m_refreshTimer;

    qint32 m_baudRate;
    QSettings m_settings;
    QSerialPort::Parity m_parity;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::FlowControl m_flowControl;

    quint8 m_portIndex;
    quint8 m_parityIndex;
    quint8 m_dataBitsIndex;
    quint8 m_stopBitsIndex;
    quint8 m_baudRateIndex;
    quint8 m_flowControlIndex;

    QStringList m_portList;
};
}

#endif
