#pragma once

#include <QObject>
#include <QByteArray>
#include <QString>
#include <functional>

namespace GHTerminal {

/**
 * @brief 协议工具类
 * 
 * 提供Q900协议相关的工具函数
 */
class ProtocolUtils : public QObject
{
    Q_OBJECT

public:
    explicit ProtocolUtils(QObject *parent = nullptr);
    ~ProtocolUtils() override;

    /**
     * @brief 计算CRC校验
     * @param data 数据
     * @return CRC值
     */
    static quint16 calculateCRC(const QByteArray &data);

    /**
     * @brief 验证CRC校验
     * @param data 数据（包含CRC）
     * @return 校验是否通过
     */
    static bool verifyCRC(const QByteArray &data);

    /**
     * @brief 构建命令包
     * @param command 命令字节
     * @param data 数据
     * @return 完整的命令包
     */
    static QByteArray buildCommand(quint8 command, const QByteArray &data = QByteArray());

    /**
     * @brief 解析响应包
     * @param response 响应数据
     * @param command 命令字节（输出）
     * @param data 数据（输出）
     * @return 解析是否成功
     */
    static bool parseResponse(const QByteArray &response, quint8 &command, QByteArray &data);

    /**
     * @brief 构建读取信道命令
     * @param channelId 信道ID
     * @return 命令包
     */
    static QByteArray buildReadChannelCommand(int channelId);

    /**
     * @brief 构建写入信道命令
     * @param channelId 信道ID
     * @param channelData 信道数据
     * @return 命令包
     */
    static QByteArray buildWriteChannelCommand(int channelId, const QByteArray &channelData);

    /**
     * @brief 构建读取DMR命令
     * @return 命令包
     */
    static QByteArray buildReadDMRCommand();

    /**
     * @brief 构建写入DMR命令
     * @param dmrData DMR数据
     * @return 命令包
     */
    static QByteArray buildWriteDMRCommand(const QByteArray &dmrData);

    /**
     * @brief 解析信道数据
     * @param data 原始数据
     * @param channelId 信道ID（输出）
     * @param channelData 信道数据（输出）
     * @return 解析是否成功
     */
    static bool parseChannelData(const QByteArray &data, int &channelId, QByteArray &channelData);

    /**
     * @brief 解析DMR数据
     * @param data 原始数据
     * @param dmrData DMR数据（输出）
     * @return 解析是否成功
     */
    static bool parseDMRData(const QByteArray &data, QByteArray &dmrData);

    /**
     * @brief 检查响应是否成功
     * @param response 响应数据
     * @return 是否成功
     */
    static bool isResponseSuccess(const QByteArray &response);

    /**
     * @brief 获取响应错误信息
     * @param response 响应数据
     * @return 错误信息
     */
    static QString getResponseError(const QByteArray &response);

    /**
     * @brief 转义数据
     * @param data 原始数据
     * @return 转义后的数据
     */
    static QByteArray escapeData(const QByteArray &data);

    /**
     * @brief 反转义数据
     * @param data 转义后的数据
     * @return 原始数据
     */
    static QByteArray unescapeData(const QByteArray &data);

    /**
     * @brief 格式化数据为十六进制字符串
     * @param data 数据
     * @return 十六进制字符串
     */
    static QString toHexString(const QByteArray &data);

    /**
     * @brief 从十六进制字符串解析数据
     * @param hexString 十六进制字符串
     * @return 数据
     */
    static QByteArray fromHexString(const QString &hexString);

    // 协议常量
    static const quint8 STX = 0x02;
    static const quint8 ETX = 0x03;
    static const quint8 ACK = 0x06;
    static const quint8 NAK = 0x15;
    static const quint8 ESC = 0x1B;
    
    // 命令常量
    static const quint8 CMD_READ_CHANNEL = 0x40;
    static const quint8 CMD_WRITE_CHANNEL = 0x41;
    static const quint8 CMD_READ_DMR = 0x43;
    static const quint8 CMD_WRITE_DMR = 0x44;
    static const quint8 CMD_ACK = 0x47;
    static const quint8 CMD_NAK = 0x4E;

private:
    static quint16 crc16(const QByteArray &data);
};

} // namespace GHTerminal 