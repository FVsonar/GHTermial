#include "tools.h"
#include <QDebug>


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
uint16_t Tools::CRC16Check(unsigned char *buf, unsigned char len)
{
    unsigned char  i, j;
    uint16_t uncrcReg = 0xFFFF;
    int16_t uncur;
    for (i = 0; i < len; i++)
    {
        uncur = buf[i] << 8;
        for (j = 0; j < 8; j++)
        {
            if ((int16_t)(uncrcReg ^ uncur) < 0)
            {
                uncrcReg = (uncrcReg << 1) ^ 0x1021;
            }
            else
            {
                uncrcReg <<= 1;
            }
            uncur <<= 1;
        }
    }
    return uncrcReg;
}

/**
 *  数据校验是否正确
 *  检验有无包头 A5 A5 A5 A5
 *  检验包长度
 *  检验CRC是否一致
 *  @param  data    要校验的数据
 */
bool Tools::checkData(QByteArray data)
{
    // 包头校验
    for(int i = 0; i < 4; i++){
        if(static_cast<unsigned char>(data[i]) != 0xA5){
            qDebug("包头错误");
            return false;
        }
    }

    // 长度校验
    if(static_cast<unsigned char>(data[4]) != data.size()-5){
        qDebug("长度错误");
        return false;
    }

    // 提取数据部分
    QByteArray dataPart = data.mid(4, data.size() - 6);
    unsigned char* dataPartData =reinterpret_cast<unsigned char*>(dataPart.data());
    uint16_t dataPartCrc = CRC16Check(dataPartData,dataPart.size());

    char a = dataPartCrc >> 8;
    char b = dataPartCrc;

    char c = data[data.size()-2];
    char d = data[data.size()-1];

    if(a!=c || b!=d){
        qDebug("crc错误");
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

    // 提取有效数据部分
    QByteArray validData = data.mid(4, validDataLength);

    // 计算 CRC16 值
    uint16_t calculatedCRC = CRC16Check(reinterpret_cast<unsigned char*>(validData.data()), static_cast<unsigned char>(validData.size()));

    // 提取数据中的 CRC 值
    uint8_t crcH = static_cast<uint8_t>(data[data.size() - 2]);
    uint8_t crcL = static_cast<uint8_t>(data[data.size() - 1]);
    uint16_t receivedCRC = (static_cast<uint16_t>(crcH) << 8) | crcL;

    // 比较 CRC 值
    if (calculatedCRC == receivedCRC) {
        return true;
    } else {
        return false;
    }

}

/**
 *  解析数据包
 *  @return QByteArray   返回解析出来正确的数据包
 */
QByteArray Tools::parsePackets(QByteArray data) {
    QByteArray newData = "";

    //包头位置
    int phIndex =  data.indexOf("\xA5\xA5\xA5\xA5");
    if(phIndex == -1){
        // qDebug()<<"没找到包头"<<data.toHex(' ');
        return newData;
    }
    if(data.size()<phIndex+5){
        // qDebug()<<"没有包长"<<data.toHex(' ');
        return newData;
    }

    // 包长位置
    int plIndex = phIndex+4;
    // 包长
    int pl = data[plIndex];
    // 包含包头和本身的包长
    int pkpl = 5+pl;

    if(data.size() < phIndex + pkpl){
        // qDebug()<<"包长度不对"<<data.toHex(' ');
        return newData;
    }

    newData = data.mid(phIndex,phIndex+pkpl);
    if(!compareCRC(newData)){
        // qDebug()<<"crc校验失败"<<data.toHex(' ');
    }
    return newData;
}

/**
 *  当数据分段到达时 使用此方法获得完整数据
 */
QByteArray Tools::parsePacketsPlus(QByteArray data){
    // 将新接收到的数据添加到缓冲区
    buffer.append(data);

    QByteArray newData = "";

    while (true) {
        // 查找包头位置
        int phIndex = buffer.indexOf("\xA5\xA5\xA5\xA5");
        if (phIndex == -1) {
            // qDebug() << "没找到包头" << buffer.toHex(' ');
            break;
        }

        // 如果包头后面的数据不足，则继续等待更多数据
        if (buffer.size() < phIndex + 5) {
            // qDebug() << "没有包长" << buffer.toHex(' ');
            break;
        }

        // 包长位置
        int plIndex = phIndex + 4;
        // 包长
        int pl = buffer[plIndex];
        // 包含包头和本身的包长
        int pkpl = 5 + pl;

        // 如果数据不足以构成一个完整的数据包，则继续等待更多数据
        if (buffer.size() < phIndex + pkpl) {
            // qDebug() << "包长度不够,数据可能是分段到达" << buffer.toHex(' ');
            break;
        }

        // 提取完整的数据包
        newData = buffer.mid(phIndex, pkpl);

        // 校验CRC
        if (!compareCRC(newData)) {
            // qDebug() << "crc校验失败" << buffer.toHex(' ');
            // 如果CRC校验失败，可以选择丢弃当前数据包并继续处理剩余数据
            buffer.remove(0, pkpl);
            continue;
        }

        // 移除已处理的数据包
        buffer.remove(0, pkpl);

        if(newData[5]!=0x47){
            qDebug()<<"返回解析出来的数据包:"<<newData.toHex(' ');
        }
        // 返回解析出来的数据包
        return newData;
    }
    return "";
}

/**
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
    comboBox->addItem("110.9");
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
    comboBox->addItem("110.9");
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
 *  添加表头
 */
void Tools::setTableHeader(QStringList &tableCplumnHeader){
    tableCplumnHeader.append("-");
    tableCplumnHeader.append("CHANNEL");
    tableCplumnHeader.append("  NAME  ");
    tableCplumnHeader.append("VFA_FREQ");
    tableCplumnHeader.append("VFB_FREQ");
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
void Tools::addHead(QByteArray &data)
{
    data.prepend(0xa5);
    data.prepend(0xa5);
    data.prepend(0xa5);
    data.prepend(0xa5);
}
