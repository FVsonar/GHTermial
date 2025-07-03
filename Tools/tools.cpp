#include "tools.h"
#include <QDebug>
#include <QJsonDocument>
#include <QFile>

/**
 * CRC16校验类
 * 实现CRC16/CCITT-FALSE校验算法
 * 用于验证数据的完整性，常用于通信协议中
 */
class CRC16Checker {
public:
    /**
     * 计算CRC16校验值
     * @param buf 待校验的数据缓冲区
     * @param len 数据长度
     * @return 计算得到的CRC16校验值
     */
    static uint16_t CRC16Check(unsigned char *buf, unsigned char len);
};

/**
 * CRC16校验实现
 * 使用CRC16/CCITT-FALSE算法计算校验值
 * 多项式：0x1021，初始值：0xFFFF
 * @param buf 待校验的数据缓冲区
 * @param len 数据长度
 * @return 计算得到的CRC16校验值
 */
uint16_t CRC16Checker::CRC16Check(unsigned char *buf, unsigned char len) {
    unsigned char  i, j;
    uint16_t uncrcReg = 0xFFFF;
    int16_t uncur;
    for (i = 0; i < len; i++) {
        uncur = buf[i] << 8;
        for (j = 0; j < 8; j++) {
            if ((int16_t)(uncrcReg ^ uncur) < 0) {
                uncrcReg = (uncrcReg << 1) ^ 0x1021;
            } else {
                uncrcReg <<= 1;
            }
            uncur <<= 1;
        }
    }
    return uncrcReg;
}

/**
 * Tools类构造函数
 * @param parent 父对象指针，用于Qt对象树管理
 */
Tools::Tools(QObject *parent)
    : QObject{parent}
{}

/**
* 函数名称: CRC16Check
* 功能描述: CRC16循环冗余校验
* 备注：校验模式为CRC16/CCITT-FALSE
* @param    buf 要校验的数据;
* @param    len 要校验的数据的长度
* @return   uint16_t 校验值
*/
uint16_t Tools::CRC16Check(unsigned char *buf, unsigned char len) {
    return CRC16Checker::CRC16Check(buf, len);
}


/**
 * 数据校验
 * 校验数据包是否符合规范，包括：
 * 1. 包头校验（4字节A5）
 * 2. 长度校验
 * 3. CRC16校验
 * @param data 待校验的数据
 * @return bool 校验通过返回true，否则返回false
 */
bool Tools::checkData(QByteArray data)
{
    // 包头校验
    for(int i = 0; i < 4; i++){
        if(static_cast<unsigned char>(data[i]) != 0xA5){
            qDebug() << "包头错误，位置：" << i << "，期望值：0xA5，实际值：" << QString::number(static_cast<unsigned char>(data[i]), 16);
            return false;
        }
    }

    // 长度校验
    if(static_cast<unsigned char>(data[4]) != data.size()-5){
        qDebug() << "长度错误，期望值：" << static_cast<unsigned char>(data[4]) << "，实际值：" << data.size()-5;
        return false;
    }

    // 计算CRC16值
    uint16_t dataPartCrc = CRC16Check(reinterpret_cast<unsigned char*>(data.data() + 4), data.size() - 6);

    char a = dataPartCrc >> 8;
    char b = dataPartCrc;

    char c = data[data.size()-2];
    char d = data[data.size()-1];

    if(a!=c || b!=d){
        qDebug() << "CRC错误，期望值：" << QString::number(dataPartCrc, 16) << "，实际值：" << QString::number((static_cast<uint16_t>(c) << 8) | d, 16);
        return false;
    }

    return true;

}

/**
 *  比较CRC
 *  @param  QByteArray  data    完整的命令(包含包头和CRC)从这个数据中提取数据跟crc比较
 *  @param  uint16_t    crc
 *  @return bool    true相等    false不等于
 */
bool Tools::compareCRC(QByteArray data){

    // 确保数据长度至少为 7 字节（包头 4 字节 + 包长 1 字节 + 命令位 1 字节 + CRC 2 字节）
    if (data.size() < 7) {
        qDebug() << "数据长度不足，最小长度：7，实际长度：" << data.size();
        return false;
    }

    // 获取包长
    uint8_t packetLength = static_cast<uint8_t>(data[4]);

    // 计算有效数据部分的长度
    int validDataLength = 1 + packetLength -2; // 包长 + 命令位 数据段 - CRC

    // 确保数据长度足够
    if (data.size() < 6 + validDataLength) {
        return false;
    }

    // 计算 CRC16 值
    uint16_t calculatedCRC = CRC16Check(reinterpret_cast<unsigned char*>(data.data() + 4), static_cast<unsigned char>(validDataLength));

    // 提取数据中的 CRC 值
    uint8_t crcH = static_cast<uint8_t>(data[data.size() - 2]);
    uint8_t crcL = static_cast<uint8_t>(data[data.size() - 1]);
    uint16_t receivedCRC = (static_cast<uint16_t>(crcH) << 8) | crcL;

    // 比较 CRC 值
    if (calculatedCRC == receivedCRC) {
        return true;
    } else {
        qDebug() << "CRC校验失败，计算值：" << QString::number(calculatedCRC, 16) << "，接收值：" << QString::number(receivedCRC, 16);
        return false;
    }

}

/**
 * 解析数据包
 * 从原始数据中提取符合规范的数据包，包括：
 * 1. 查找包头位置
 * 2. 验证包长度
 * 3. 校验CRC
 * @param data 原始数据
 * @return QByteArray 解析成功返回有效数据包，失败返回空数据包
 */
QByteArray Tools::parsePackets(QByteArray data) {
    //包头位置
    int phIndex =  data.indexOf("\xA5\xA5\xA5\xA5");
    if(phIndex == -1){
        // qDebug()<<"没找到包头"<<data.toHex(' ');
        return QByteArray();
    }
    if(data.size()<phIndex+5){
        // qDebug()<<"没有包长"<<data.toHex(' ');
        return QByteArray();
    }

    // 包长位置
    int plIndex = phIndex+4;
    // 包长
    int pl = data[plIndex];
    // 包含包头和本身的包长
    int pkpl = 5+pl;

    if(data.size() < phIndex + pkpl){
        // qDebug()<<"包长度不对"<<data.toHex(' ');
        return QByteArray();
    }

    QByteArray newData = data.mid(phIndex,phIndex+pkpl);
    if(!compareCRC(newData)){
        // qDebug()<<"crc校验失败"<<data.toHex(' ');
    }
    return newData;
}

/**
 *  当数据分段到达时 使用此方法获得完整数据
 */
/**
 * 分段数据包解析
 * 处理可能分段的网络数据，包括：
 * 1. 将新数据追加到缓冲区
 * 2. 查找完整数据包
 * 3. 校验CRC
 * 4. 移除已处理数据
 * @param data 新接收到的数据
 * @return QByteArray 解析成功返回有效数据包，失败返回空数据包
 */
QByteArray Tools::parsePacketsPlus(QByteArray data){

    // 将新接收到的数据添加到缓冲区
    buffer.append(data);

    while (true) {
        // 查找包头位置
        int phIndex = buffer.indexOf("\xA5\xA5\xA5\xA5");
        if (phIndex == -1) {
            // 没找到包头，跳出循环
            break;
        }

        // 如果包头后面的数据不足，则继续等待更多数据
        if (buffer.size() < phIndex + 5) {
            break;
        }

        // 包长位置
        int plIndex = phIndex + 4;
        // 包长
        int pl = static_cast<unsigned char>(buffer[plIndex]);
        // 包含包头和本身的包长
        int pkpl = 5 + pl;

        // 如果数据不足以构成一个完整的数据包，则继续等待更多数据
        if (buffer.size() < phIndex + pkpl) {
            break;
        }

        // 提取完整的数据包
        QByteArray newData = buffer.mid(phIndex, pkpl);
        qDebug()<<"完整数据包(crc未校验)："<<newData.toHex(' ');
        // 校验CRC
        if (!compareCRC(newData)) {
            qDebug() << "crc校验失败" << buffer.toHex(' ');
            // 如果CRC校验失败，丢弃当前数据包并继续处理剩余数据
            buffer.remove(0, pkpl);
            continue;
        }

        // 移除已处理的数据包
        buffer.remove(0, pkpl);

        if(static_cast<unsigned char>(newData[5]) != 0x47){
            qDebug() << "返回解析出来的数据包:" << newData.toHex(' ');
        }
        // 返回解析出来的数据包
        return newData;
    }
    return QByteArray();
}

/**
 * 弃用
 *  初始化vfo ComboBoxPtr 内容
 */
void Tools::setVfoComboBoxPtr(QComboBox *&vfoComboBoxPtr){
    vfoComboBoxPtr->addItem("USB");    // 0
    vfoComboBoxPtr->addItem("LSB");
    vfoComboBoxPtr->addItem("CWR");
    vfoComboBoxPtr->addItem("CWL");
    vfoComboBoxPtr->addItem("AM");
    vfoComboBoxPtr->addItem("WFM");
    vfoComboBoxPtr->addItem("NFM");
    vfoComboBoxPtr->addItem("DIGI");
    vfoComboBoxPtr->addItem("PKT");
    vfoComboBoxPtr->addItem("DMR");
    vfoComboBoxPtr->addItem("DFM");    // 10
}

/**
 * 弃用
 *  给亚音下拉框添加数据
 */
void Tools::setYayinComboBoxPtr(QComboBox *&comboBox){
    comboBox->addItem("0");
    comboBox->addItem("67.0");
    comboBox->addItem("69.3");
    comboBox->addItem("71.9");
    comboBox->addItem("74.4");
    comboBox->addItem("77.0");
    comboBox->addItem("79.7");
    comboBox->addItem("82.5");
    comboBox->addItem("85.4");
    comboBox->addItem("88.5");
    comboBox->addItem("91.5");
    comboBox->addItem("94.8");
    comboBox->addItem("97.4");
    comboBox->addItem("100.0");
    comboBox->addItem("103.5");
    comboBox->addItem("107.2");
    comboBox->addItem("114.8");
    comboBox->addItem("118.8");
    comboBox->addItem("123.0");
    comboBox->addItem("127.3");
    comboBox->addItem("131.8");
    comboBox->addItem("136.5");
    comboBox->addItem("141.3");
    comboBox->addItem("146.2");
    comboBox->addItem("150.0");
    comboBox->addItem("151.4");
    comboBox->addItem("156.7");
    comboBox->addItem("159.8");
    comboBox->addItem("162.2");
    comboBox->addItem("165.5");
    comboBox->addItem("167.9");
    comboBox->addItem("171.3");
    comboBox->addItem("173.8");
    comboBox->addItem("177.3");
    comboBox->addItem("179.9");
    comboBox->addItem("183.5");
    comboBox->addItem("186.2");
    comboBox->addItem("189.9");
    comboBox->addItem("192.8");
    comboBox->addItem("196.6");
    comboBox->addItem("199.5");
    comboBox->addItem("203.5");
    comboBox->addItem("206.5");
    comboBox->addItem("210.7");
    comboBox->addItem("213.8");
    comboBox->addItem("218.1");
    comboBox->addItem("221.3");
    comboBox->addItem("225.7");
    comboBox->addItem("229.1");
    comboBox->addItem("233.6");
    comboBox->addItem("237.1");
    comboBox->addItem("241.8");
    comboBox->addItem("245.5");
    comboBox->addItem("250.3");
    comboBox->addItem("254.1");
}

/**
 * 弃用
 *  dmr TX/RX_CTCSS
 *  给下拉框添加数据
 */
void Tools::setRxTxCtcssComboBoxPtr(QComboBox *&comboBox){
    comboBox->addItem("OFF");
    comboBox->addItem("63.0");
    comboBox->addItem("67.0");
    comboBox->addItem("69.3");
    comboBox->addItem("71.9");
    comboBox->addItem("74.4");
    comboBox->addItem("77.0");
    comboBox->addItem("79.7");
    comboBox->addItem("82.5");
    comboBox->addItem("85.4");
    comboBox->addItem("88.5");
    comboBox->addItem("91.5");
    comboBox->addItem("94.8");
    comboBox->addItem("97.4");
    comboBox->addItem("100.0");
    comboBox->addItem("103.5");
    comboBox->addItem("107.2");
    comboBox->addItem("114.8");
    comboBox->addItem("118.8");
    comboBox->addItem("123.0");
    comboBox->addItem("127.3");
    comboBox->addItem("131.8");
    comboBox->addItem("136.5");
    comboBox->addItem("141.3");
    comboBox->addItem("146.2");
    comboBox->addItem("150.0");
    comboBox->addItem("151.4");
    comboBox->addItem("156.7");
    comboBox->addItem("159.8");
    comboBox->addItem("162.2");
    comboBox->addItem("165.5");
    comboBox->addItem("167.9");
    comboBox->addItem("171.3");
    comboBox->addItem("173.8");
    comboBox->addItem("177.3");
    comboBox->addItem("179.9");
    comboBox->addItem("183.5");
    comboBox->addItem("186.2");
    comboBox->addItem("189.9");
    comboBox->addItem("192.8");
    comboBox->addItem("196.6");
    comboBox->addItem("199.5");
    comboBox->addItem("203.5");
    comboBox->addItem("206.5");
    comboBox->addItem("210.7");
    comboBox->addItem("213.8");
    comboBox->addItem("218.1");
    comboBox->addItem("221.3");
    comboBox->addItem("225.7");
    comboBox->addItem("229.1");
    comboBox->addItem("233.6");
}

/**
 * 弃用
 *  添加表头
 */
void Tools::setTableHeader(QStringList &tableCplumnHeader){
    tableCplumnHeader.append("-");
    tableCplumnHeader.append("CHANNEL");
    tableCplumnHeader.append("  NAME  ");
    tableCplumnHeader.append("VFA_FREQ(Hz)");
    tableCplumnHeader.append("VFB_FREQ(Hz)");
    tableCplumnHeader.append("VFA_MODE");
    tableCplumnHeader.append("VFB_MODE");
    tableCplumnHeader.append(" T_CTCSS ");
    tableCplumnHeader.append(" R_CTCSS ");
    tableCplumnHeader.append("Call_format");
    tableCplumnHeader.append("    Tx_cc    ");
    tableCplumnHeader.append("    Rx_cc    ");
    tableCplumnHeader.append("     slot     ");
    tableCplumnHeader.append("  Call_id  ");
    tableCplumnHeader.append("  Own_id  ");
    tableCplumnHeader.append("Ch_type");
    tableCplumnHeader.append(" Rx_ctcss ");
    tableCplumnHeader.append(" Tx_ctcss ");
    tableCplumnHeader.append("   sqlevel   ");
    tableCplumnHeader.append("   spkgain   ");
    tableCplumnHeader.append("   dmod_gain   ");
    tableCplumnHeader.append("scr_en");
    tableCplumnHeader.append(" scr_send ");
    tableCplumnHeader.append("ch_bs_mode");
}

/**
 *  json
 *  将json对象保存到目标位置为json文件
 *  @param  const QJsonObject& obj  要保存的json数据对象
 *  @param  const QString& filePath 保存位置
 *  @return bool 是否保存成功 true成功 false失败
 */
/**
 * 将JSON对象保存到文件
 * @param obj 要保存的JSON对象
 * @param filePath 文件保存路径
 * @return bool 保存成功返回true，否则返回false
 */
bool Tools::saveJsonToFile(const QJsonObject& obj,const QString& filePath){
    QJsonDocument doc(obj);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson());
        file.close();
        return true;
    }
    return false;
}

/**
 *  给data添加CRC
 */
/**
 * 为数据添加CRC校验码
 * 计算数据的CRC16校验值并将其附加到数据末尾
 * @param data 待处理的数据引用
 */
void Tools::addCrc(QByteArray &data)
{
    // 计算CRC CRC校验不含包头不含自身
    uint16_t crc = CRC16Check(reinterpret_cast<unsigned char*>(data.data()), data.size());

    // 将CRC高低位分开加入到data中
    data.append((crc >> 8) & 0xFF); // CRC高
    data.append(crc & 0xFF);        // CRC低
}
/**
 *  给data添加包头
 */
/**
 * 为数据添加包头
 * 在数据开头添加4字节的A5作为包头标识
 * @param data 待处理的数据引用
 */
void Tools::addHead(QByteArray &data)
{
    data.prepend(0xa5);
    data.prepend(0xa5);
    data.prepend(0xa5);
    data.prepend(0xa5);
}
