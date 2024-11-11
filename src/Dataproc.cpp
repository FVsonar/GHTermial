#include "Dataproc.h"
#include <qjsondocument.h>
#include <QJsonObject>

#include <QDebug>
#include <Serial/Manager.h>
#include <Misc/Utilities.h>

using namespace Serial;
static DataProc *INSTANCE = nullptr;

DataProc::DataProc(QObject *parent) : QObject{parent}
{
    // Read received data automatically
    auto dm = Manager::getInstance();
    connect(dm, &Manager::dataReceived, this, &DataProc::onDataReceived);

    // 间隔发送
    m_sendTimer.setInterval(150);
    m_sendTimer.setTimerType(Qt::PreciseTimer);
    connect(&m_sendTimer, &QTimer::timeout, this, &DataProc::onSendInterval);

    // 间隔读取
    m_readTimer.setInterval(150);
    m_readTimer.setTimerType(Qt::PreciseTimer);
    connect(&m_readTimer, &QTimer::timeout, this, &DataProc::onGetInterval);

    m_isReading = false;
    m_isSending = false;
    m_isUIGetted = false;
    m_ReadLock = false;
    m_realRWcount = READ_CHANNEL_MAX_COUNT;
    for(quint16 rw_index=0;rw_index<100;rw_index++)
    {
         m_needRWList[rw_index] = 1;
    }


#ifdef QT_DEBUG
    m_isDebugMode = true;
#else
    m_isDebugMode = false;
#endif

}

DataProc::~DataProc()
{

}

/**
 * Returns the only instance of the class
 */
DataProc *DataProc::getInstance()
{
    if (INSTANCE == nullptr)
        INSTANCE = new DataProc;

    return INSTANCE;
}


/*********************************************************************************
 * 发送相关
*********************************************************************************/


/**
 * @函数功能: 获取发送的字节数
 * @输入参数: 无
 * @返 回 值: 无
 * @说    明: 无
 */
quint16 DataProc::getSendCount(void)
{

    return  m_sendPro;
}


quint16 DataProc::getReadCount(void)
{

    return  m_readPro;
}


void DataProc::stopLoad(void)
{
    m_isReading = false;
    m_isSending = false;
    m_isUIGetted = false;
    m_ReadLock = false;

    m_sendCount = 0;
    m_readPro = 0;
    m_BasicAckChannel = 0xFFFF;
    m_DMRAckChannel =0xFFFF;
}

/**
 * @函数功能: 开启发送信道tablemodle Json格式数据
 * @输入参数: 无
 * @返 回 值: 无
 * @说    明: 无
 */
void DataProc::parseTableJsonArry(QString str)
{
    if (false == m_isSending)
    {
        QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
        m_sendArray = jdoc.array();
        m_sendCount = 0;
        m_sendPro = 0;
        m_sendTimer.start();
        m_BasicAckChannel = 0xFFFF;
        m_DMRAckChannel =0xFFFF;
        m_isSending = true;
        m_isReading = false;
    }

}

quint16 DataProc::CheckReceAckOk()
{
    quint16 ret_Value = 0;
    static quint16 check_count = 0;
    static quint16 send_count = 0;
    static quint16 old_channel = 0xFFFF;

    if (m_BasicAckChannel == m_sendCount )
    {
         qInfo() << "BASIC回环正确" ;

         ret_Value = 1;
    }

    if  (m_DMRAckChannel == m_sendCount )
    {
        qInfo() << "DMR回环正确" ;

        ret_Value = 2;
    }

    if(ret_Value == 0)
    {
        check_count++;
    }

    debug("m_sendCount:" << m_sendCount << ",m_DMRAckChannel:" << m_DMRAckChannel << ",m_BasicAckChannel:" << m_BasicAckChannel);
    if((m_DMRAckChannel == m_sendCount) && (m_BasicAckChannel == m_sendCount) && (m_sendCount != old_channel))
    {
        old_channel = m_sendCount;
        qInfo() << "回环正确" ;
        check_count = 0;
        ret_Value = 3;
        send_count ++;
    }else if(check_count >= 5){    //检测3次还没收到应答 直接退出
         qInfo() << "发送超时" << m_sendCount;
         qInfo() << m_DMRAckChannel ;
         check_count = 0;
        // ret_Value = 4;
    }

     if( send_count > m_realRWcount)
     {
         old_channel = 0xff;
         send_count = 0;
     }

    return ret_Value;
}
/**
 * @函数功能: 发送信道tablemodle Json格式数据
 * @输入参数: 无
 * @返 回 值: 无
 * @说    明: 无
 */
void DataProc::onSendInterval(void)
{
    static quint16 send_type = 0;
    static quint16 real_SendCount = 0;
    if(!Manager::getInstance()->connected())  // 还要加上超时退出
     {
        m_sendTimer.stop();
    }
    get_realneedsentcount();

    if ((m_sendCount < m_sendArray.size() && (real_SendCount < m_realRWcount) )&& m_isSending)
    {
        quint16 ack_num=0;
        quint16 is_Checked;

      //  jsValue = item_object.value("CHECKED");
        is_Checked = m_needRWList[m_sendCount];
        if(is_Checked)
        {
            ack_num = CheckReceAckOk();
            send_type = (1 == ack_num)? 1: 0;

            if (3 <= ack_num)
            {
                  m_sendCount ++;
                  real_SendCount++;
                   m_readPro = real_SendCount *100 /  (m_realRWcount);
                  if ((m_sendCount >= m_sendArray.size()) || (real_SendCount >= m_realRWcount))
                  {
                      return;
                  }
            }
            QJsonObject item_object = m_sendArray.at(m_sendCount).toObject();

            QJsonValue jsValue;
            QString itemStr;
            quint32 temp_Freq;

                m_DMR_SendBuff[0] = m_dmr.ch_index;

                jsValue = item_object.value(m_type[0]);
              //  qInfo() << "ch_index" << jsValue.toInt();
                m_dmr.ch_index = (quint16)jsValue.toInt();
                m_DMR_SendBuff[0] = m_dmr.ch_index;

                jsValue = item_object.value(m_type[1]);
              //  qInfo() << "call_format" << jsValue.toInt();
                m_dmr.call_format = (quint16)jsValue.toInt();
                m_DMR_SendBuff[1] = m_dmr.call_format;

                jsValue = item_object.value(m_type[2]);
               // qInfo() << "txcc" << jsValue.toInt();
                m_dmr.txcc = (quint16)jsValue.toInt();
                m_DMR_SendBuff[2] = m_dmr.txcc;

                jsValue = item_object.value(m_type[3]);
               // qInfo() << "rxcc" << jsValue.toInt();
                m_dmr.rxcc = (quint16)jsValue.toInt();
                m_DMR_SendBuff[3] = m_dmr.rxcc;

                jsValue = item_object.value(m_type[4]);
            //    qInfo() << "slot_num" << jsValue.toInt();
                m_dmr.slot_num = (quint16)jsValue.toInt();
                m_DMR_SendBuff[4] = m_dmr.slot_num;

                jsValue = item_object.value(m_type[5]);
                itemStr = jsValue.toString();
             //   qInfo() << "call_id_dec" << (quint32)itemStr.toInt();
                m_dmr.call_id_dec = (quint32)itemStr.toInt();
                Dec2Hex(&m_DMR_SendBuff[5],4,m_dmr.call_id_dec);


                jsValue = item_object.value(m_type[6]);
                itemStr = jsValue.toString();
              //  qInfo() << "own_id_dec" << (quint32)itemStr.toInt();
                m_dmr.own_id_dec = (quint32)itemStr.toInt();
                Dec2Hex(&m_DMR_SendBuff[9],4, m_dmr.own_id_dec);

                jsValue = item_object.value(m_type[7]);
              //  qInfo() << "ch_type" << jsValue.toInt();
                m_dmr.ch_type = (quint16)jsValue.toInt();
                m_dmr.ch_type = m_dmr.ch_type? 0 : 1; //做一下反向
                m_DMR_SendBuff[13] = m_dmr.ch_type;


                jsValue = item_object.value(m_type[8]);
              //  qInfo() << "rxctcss" << jsValue.toInt();
                m_dmr.rxctcss = (quint16)jsValue.toInt();
                m_DMR_SendBuff[14] = m_dmr.rxctcss;

                jsValue = item_object.value(m_type[9]);
              //  qInfo() << "txctcss" << jsValue.toInt();
                m_dmr.txctcss = (quint16)jsValue.toInt();
                m_DMR_SendBuff[15] = m_dmr.txctcss;

                jsValue = item_object.value(m_type[10]);
              //  qInfo() << "sql" << jsValue.toInt();
                m_dmr.sqlevel = (quint16)jsValue.toInt();
                m_DMR_SendBuff[16] = m_dmr.sqlevel;

                jsValue = item_object.value(m_type[11]);
               // qInfo() << "spk" << jsValue.toInt();
                m_dmr.spkgain = (quint16)jsValue.toInt();
                m_DMR_SendBuff[17] = m_dmr.spkgain;

                m_dmr.dmrexist = (quint16)1;
                m_DMR_SendBuff[18] = m_dmr.dmrexist;

                jsValue = item_object.value(m_type[12]);
              //  qInfo() << "rxgain" << jsValue.toInt();
                m_dmr.dmod_gain = (quint16)jsValue.toInt();
                m_DMR_SendBuff[19] = m_dmr.dmod_gain;


                jsValue = item_object.value(m_type[13]);
               // qInfo() << "scren" << jsValue.toInt();
                m_dmr.scr_en = (quint16)jsValue.toInt();
                m_DMR_SendBuff[20] = m_dmr.scr_en;

                jsValue = item_object.value(m_type[14]);
                itemStr = jsValue.toString();
               // qInfo() << "Scr_seed" << jsValue.toString();
                if (itemStr.toInt() > 65535)
                {
                    m_dmr.scr_seed = 0xFF;
                }
                else
                {
                    m_dmr.scr_seed = (quint16)itemStr.toInt();
                }
                m_DMR_SendBuff[21] = (m_dmr.scr_seed >> 8 & 0xFF);
                m_DMR_SendBuff[22] = m_dmr.scr_seed;

                jsValue = item_object.value(m_type[15]);
              //  qInfo() << "bsmode" << jsValue.toInt();
                m_dmr.ch_bs_mode = (quint16)jsValue.toInt();
                m_DMR_SendBuff[23] = m_dmr.ch_bs_mode;

                m_dmr.validat = (quint16)1;
                m_DMR_SendBuff[24] = m_dmr.validat;

                 jsValue = item_object.value(m_BasicType[0]);
                 m_Basic_SendBuff[0] = (quint16)jsValue.toInt();

                 jsValue = item_object.value(m_BasicType[1]);
                 m_Basic_SendBuff[1] = (quint16)jsValue.toInt();

                 jsValue = item_object.value(m_BasicType[2]);
                 m_Basic_SendBuff[2] = (quint16)jsValue.toInt();

                 jsValue = item_object.value(m_BasicType[3]);
                 itemStr = jsValue.toString();
              //   qInfo() << "call_id_dec" << (quint32)itemStr.toInt();
                 temp_Freq = (quint32)itemStr.toInt();
                 Dec2Hex(&m_Basic_SendBuff[3],4,temp_Freq);

                 jsValue = item_object.value(m_BasicType[4]);
                 itemStr = jsValue.toString();
              //   qInfo() << "call_id_dec" << (quint32)itemStr.toInt();
                 temp_Freq = (quint32)itemStr.toInt();
                 Dec2Hex(&m_Basic_SendBuff[7],4,temp_Freq);

                 jsValue = item_object.value(m_BasicType[5]);
                 m_Basic_SendBuff[11] = (quint16)jsValue.toInt();

                 jsValue = item_object.value(m_BasicType[6]);
                 m_Basic_SendBuff[12] = (quint16)jsValue.toInt();

                 jsValue = item_object.value(m_BasicType[7]);
                 itemStr = jsValue.toString();
                 QByteArray tempArray = itemStr.toLatin1();
                 qstrncpy((char*)&m_Basic_SendBuff[13],tempArray.constData(),12);


            if (send_type == 0)
            {
                PackData(CMD_SETCHANNEL,25);
            }else
            {
                 PackData(CMD_DMRSETCHANNEL,25);
            }

        }
        else
        {
            m_sendCount++;
        }
        m_sendPro = m_sendCount *100 /  m_sendArray.size();
     //   qInfo() << "已发送数据" << m_sendCount;
     //   qInfo() << "sended progrss" << m_sendPro;
    }
    else
    {
        m_sendCount = 0;
        real_SendCount = 0;
        m_sendPro = 100;
        m_sendTimer.stop();
        m_isSending = false;


      //  qInfo() << "发送完成" << m_sendCount;
    }
}



void DataProc::sendCheckDevice(void)
{

     PackData(CMD_VERIFY,3);

}
void DataProc::PackData(quint16 cmd,int len)
{

    QByteArray tx_buff;

    switch(cmd)
    {

        case CMD_VERIFY:
        tx_buff.append(0x04); //包长
        tx_buff.append(0x27); //命令码
        tx_buff.append(char(0x00)); //状态
        break;
        case CMD_SETCHANNEL: //设置信道
        tx_buff.append(len+3); //包长
        tx_buff.append(0x40); //命令码
        //tx_buff.append((char*)&m_dmr, sizeof(dmr_mem_t)); // 不能直接这么发送 结构体字体对齐问题
        tx_buff.append((char*)&m_Basic_SendBuff,len);
        break;

        case CMD_GETCHANNEL:  //读取信道
        tx_buff.append(len+3); //包长
        tx_buff.append(0x41); //命令码
        tx_buff.append(m_sendCount);
        break;
        case CMD_ENCHANNEL:  //设能信道
        tx_buff.append(0x04); //包长
        tx_buff.append(0x42); //命令码
        tx_buff.append(0x01); //状态

        break;
        case CMD_DMRSETCHANNEL:
            tx_buff.append(len+3); //包长
            tx_buff.append(0x43); //命令码
            //tx_buff.append((char*)&m_dmr, sizeof(dmr_mem_t)); // 不能直接这么发送 结构体字体对齐问题
            tx_buff.append((char*)&m_DMR_SendBuff,len);
            break;
        case CMD_DMRGETCHANNEL:
            tx_buff.append(len+3); //包长
            tx_buff.append(0x44); //命令码
            tx_buff.append(m_sendCount);
            break;
        default: break;

    }
    SendData(tx_buff);

}


void DataProc::SendData(QByteArray &buff)
{

    quint16 tx_crcData;
    quint16 crc_Len;

    // Check conditions
    if (buff.isEmpty() || !Manager::getInstance()->connected())
        return;


    m_txDataBuffer.clear();
    // 添加包头
    m_txDataBuffer.append(0xA5);
    m_txDataBuffer.append(0xA5);
    m_txDataBuffer.append(0xA5);
    m_txDataBuffer.append(0xA5);

    // 添加帧数据
    m_txDataBuffer.append(buff);

    // 添加CRC校验码
    crc_Len = m_txDataBuffer.size()-4;
    tx_crcData = CRC16Check((unsigned char *)(m_txDataBuffer.mid(4,crc_Len).data()),crc_Len);

    m_txDataBuffer.append(tx_crcData >> 8);
    m_txDataBuffer.append(tx_crcData);

   // 串口发送数据
    // Write data to device
    Manager::getInstance()->writeData(m_txDataBuffer);
}



// 不会产生换行符
QString DataProc::JsonToQstring(QJsonObject jsonObject)
{
    QJsonDocument document;
    document.setObject(jsonObject);
    QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
    QString simpjson_str(simpbyte_array);

    return simpjson_str;
}


/*********************************************************************************
 * 接收数据处理
*********************************************************************************/

/**
 * @函数功能: 返回信道参数给qml
 * @输入参数: 无
 * @返 回 值: 无
 * @说    明: 无
 */
QString DataProc::getJsonArrayFromByte()
{
    QString retString;
    QJsonObject object;   //构造两个QJsonObject并插值
    retString = "NONE";

//测试用
     //QString tempString;
//     tempString = "1234"
//    object.insert(m_type[0], tempString);
//    retString = QString(QJsonDocument(object).toJson());
    if(m_ReadLock == true )
    {
        retString = JsonToQstring(m_ChannelParamObject);
       //  qInfo() << "Retstring ：" << retString;
        m_ReadLock = false;
        m_isUIGetted = true;
    }
    return retString;
}

/**
 * @函数功能: 获取接收到的数据和长度 顺序命令没有按照顺序 所以需要转换
 * @输入参数: 无
 * @返 回 值: 无
 * @说    明: 无
 */
void DataProc::loadChannelParamater()
{
    if (false == m_isReading)
    {
        m_sendCount = 0;
        m_readPro = 0;
        m_readTimer.start();
        m_BasicAckChannel = 0xFFFF;
        m_DMRAckChannel =0xFFFF;
        m_isSending = false;
        m_isReading = true;
        m_isUIGetted = false;
        m_ReadLock = false;
        qInfo() << "读取信道" ;
    }

}

void DataProc::setReadWriteList(quint16 index, bool state)
{
   m_needRWList[index] = state;
}

void DataProc::get_realneedsentcount(void)
{
    quint16 count = 0;
    quint16 i;
    for(i = 0; i< 1000;i++)
    {
        if(m_needRWList[i])
        {
            count++;
        }

    }
    m_realRWcount = count;

}

void DataProc::onGetInterval(void)
{
    static quint16 get_type = 0;
    static quint16 real_count = 0;
    quint16 get_count = READ_CHANNEL_MAX_COUNT; // 根据实际值更改

    if (!Manager::getInstance()->connected()) { // 检查连接状态
        m_readTimer.stop();
        return;
    }

    get_realneedsentcount();

    if (m_sendCount < get_count && real_count < m_realRWcount && m_isReading) {
        quint16 ack_num = 0;
        quint16 is_Checked = m_needRWList[m_sendCount];

        if (is_Checked) {
            if (!m_ReadLock) {
                ack_num = CheckReceAckOk();
                get_type = (ack_num == 1) ? 1 : 0;

                if (ack_num >= 3) {
                    if (ack_num == 3) {
                        m_ReadLock = true; // 等待QML读取数据
                    }
                }

                if (m_isUIGetted) {
                    m_sendCount++;
                    real_count++;
                    m_readPro = real_count * 100 / m_realRWcount;
                    m_isUIGetted = false;
                }

                if (m_sendCount >= get_count || real_count >= m_realRWcount) {
                    return;
                }

                if (ack_num <= 2) {
                    PackData(((get_type == 0) ? CMD_GETCHANNEL : CMD_DMRGETCHANNEL), 1);
                }
            }
        } else {
            m_sendCount++;
            m_readPro = m_sendCount * 100 / get_count;
        }
    } else {
        m_sendCount = 0;
        real_count = 0;
        m_readPro = 100;
        m_readTimer.stop();
        m_isReading = false;
        m_isUIGetted = false;
        m_ReadLock = false;
    }
}


void DataProc::getChannelBasicParam(const uint8_t* channel_buf)
{
    QString tempString;
    // QString retString;
    int tempNum;
    tempString = "1234";

    //CHANNEL
    m_ChannelParamObject.insert(m_BasicType[0], channel_buf[0]);

    //VFA_MODE
    m_ChannelParamObject.insert(m_BasicType[1],channel_buf[1]);

    //VFB_MODE
    m_ChannelParamObject.insert(m_BasicType[2],channel_buf[2]);

    //VFA_FREQ
    tempNum = Hex2Dec((uint8_t*)(channel_buf+3),4);
    tempString = QString::number(tempNum);
    m_ChannelParamObject.insert(m_BasicType[3], tempString);

    //VFB_FREQ
    tempNum = Hex2Dec((uint8_t*)(channel_buf+7),4);
    tempString = QString::number(tempNum);
    m_ChannelParamObject.insert(m_BasicType[4], tempString);

    //T_CTCSS
    m_ChannelParamObject.insert(m_BasicType[5], channel_buf[11]);

    //R_CTCSS
    m_ChannelParamObject.insert(m_BasicType[6], channel_buf[12]);

    // NAME 解决乱码问题
    QByteArray array;
    if (channel_buf + 13 + 12 <= channel_buf + 13 + 12) {
        array = QByteArray(reinterpret_cast<const char*>(channel_buf + 13), 12);
        tempString = QString::fromUtf8(array);
        m_ChannelParamObject.insert(m_BasicType[7], tempString);
    } else {
        debug("错误：name缓冲区大小无效");
    }

    //A_B
    m_ChannelParamObject.insert(m_BasicType[8], 1);

    //SPLIT
    m_ChannelParamObject.insert(m_BasicType[9], 1);

}

void DataProc::getChannelDMRParam(const uint8_t* channel_buf)
{
    QString tempString;
    int tempNum;
    tempString = "1234";

    //CALL_TYPE
    m_ChannelParamObject.insert(m_type[1], channel_buf[0]);

    //TX_CC
    m_ChannelParamObject.insert(m_type[2], channel_buf[1]);

    //RX_CC
    m_ChannelParamObject.insert(m_type[3], channel_buf[2]);

    //SLOT
    m_ChannelParamObject.insert(m_type[4], channel_buf[3]);

    //CALL_ID
    tempNum = Hex2Dec((uint8_t*)(channel_buf+4),4);
    tempString = QString::number(tempNum);
    m_ChannelParamObject.insert(m_type[5], tempString);

    //OWN_ID
    tempNum = Hex2Dec((uint8_t*)(channel_buf+8),4);
    tempString = QString::number(tempNum);
    m_ChannelParamObject.insert(m_type[6], tempString);

    //CH_TYPE
    m_ChannelParamObject.insert(m_type[7], channel_buf[12]?0:1);  //读取同发送一样 反向

    //RX_CTCSS
    m_ChannelParamObject.insert(m_type[8], channel_buf[13]);

    //TX_CTCSS
    m_ChannelParamObject.insert(m_type[9], channel_buf[14]);

    //SQL
    m_ChannelParamObject.insert(m_type[10], channel_buf[15]);

    //SPK
    m_ChannelParamObject.insert(m_type[11], channel_buf[16]);

    //dmrexist channel_buf[17]

    //RX_GAIN
    m_ChannelParamObject.insert(m_type[12], channel_buf[18]);

    //ENCRY
    m_ChannelParamObject.insert(m_type[13], channel_buf[19]);

    //SEED
    tempNum = Hex2Dec((uint8_t*)(channel_buf+20),2);
    tempString = QString::number(tempNum);
    m_ChannelParamObject.insert(m_type[14], tempString);

    //BS_MODE
    m_ChannelParamObject.insert(m_type[15], channel_buf[22]);

    //CHECKED
//     m_ChannelParamObject.insert("CHECKED", 1);
}


/*********************************************************************************
 * 串口接收相关
*********************************************************************************/

/**
 * DataProc类的onDataReceived方法
 * 当接收数据时调用此方法处理数据
 * 参数:
 * - buff: 接收到的原始数据数组
*/
void DataProc::onDataReceived(const QByteArray &buff)
{
    quint16 i = 0; // 用于遍历数据数组的索引变量
    qint16 crcData = 0; // 用于存储CRC校验的结果
    //qDebug() << "header receieved:" << buff; // 调试输出，显示接收到的头部数据
    debug("header receieved:" << buff);

    // 遍历接收到的数据数组
    for (i = 0; i < buff.size(); i++)
    {
        // 根据当前的状态机状态处理数据
        switch (m_stateMachine)
        {
            case F_HEAD: // 处于头部检测状态
                if((quint8)buff.data()[i] == 0xA5) // 检测到头部特定字节
                {
                   m_headCount ++; // 计数头部特定字节出现的次数
                }
                if(m_headCount >= 4) // 如果头部特定字节连续出现4次
                {
                    m_stateMachine = F_LEN; // 状态机转移到长度检测状态
                    m_headCount = 0; // 重置头部计数器
                   // qDebug() << "header receieved"; // 调试输出，显示头部接收完成
                }
                memset(m_Parse_Buff,0,PROTOCAL_BUFFER_SIZE); // 清空解析缓冲区
                m_rxLen = 0;     // 重置接收长度计数器
                m_recNum = 0;    // 重置接收数据计数器

                break;
            case F_LEN: // 处于长度检测状态
                if((quint8)buff.data()[i] != 0xA5)  // 防止数据粘包
                {
                    m_Parse_Buff[m_recNum] = (quint8)buff.data()[i]; // 将数据存入解析缓冲区
                    m_recNum ++; // 增加接收数据计数器
                    m_rxLen = (quint8)buff.data()[i] + 1; // 计算接收数据的总长度
                    if((quint8)buff.data()[i] > 0) // 如果接收的数据长度大于0
                    {
                        m_stateMachine = F_DATA; // 状态机转移到数据接收状态
                    }
                }
            break;
            case F_DATA: // 处于数据接收状态
                 m_Parse_Buff[m_recNum] = (quint8)buff.data()[i]; // 将数据存入解析缓冲区
                 m_recNum ++; // 增加接收数据计数器
                if(m_recNum >= m_rxLen) // 如果接收的数据达到预期长度
                {
                    m_recNum = 0; // 重置接收数据计数器

                    crcData = CRC16Check(m_Parse_Buff,m_rxLen-2); // 计算CRC校验
                    if(((quint8)(crcData >> 8) ==  m_Parse_Buff[m_rxLen -2])
                        && (quint8)crcData == m_Parse_Buff[m_rxLen -1])  //m_rxLen = m_recNum + 1
                    {

                        Protocal_Get_Command(m_Parse_Buff,m_rxLen-2); // 解析命令

                        memset(m_Parse_Buff,0,PROTOCAL_BUFFER_SIZE); // 清空解析缓冲区
                        m_stateMachine = F_HEAD; // 状态机回到头部检测状态
                    }
                    else
                    {
                        m_stateMachine = F_HEAD; // 如果CRC校验失败，状态机回到头部检测状态

                    }

                }

            break;
            default : // 如果状态机状态异常
                m_stateMachine = F_HEAD; // 重置状态机到头部检测状态
            break;
        }
    }
}

bool DataProc::deviceVerify(void)
{
    bool ret_value = false;
    if(m_isDeviceVerifyOk)
    {
        ret_value = true;
        m_isDeviceVerifyOk = false;
    }
    else
    {
        ret_value = false;
    }
    return ret_value;
}
/**
 * @函数功能: 获取接收到的数据和长度 顺序命令没有按照顺序 所以需要转换
 * @输入参数: 无
 * @返 回 值: 无
 * @说    明: 无
 */
void DataProc::Protocal_Get_Command(uint8_t* temp_buf,uint8_t size)
{

    switch(temp_buf[1])
         {
           case 1: m_command = (temp_buf[2]==1)?CMD_FM_TX_ON:CMD_NONE; break;
           case 2:
                   switch (temp_buf[2])
                   {
                    case 0 : m_command = CMD_FM_ON; break;
                    case 1 : m_command = CMD_FM_RX_UP; break;
                    case 2 : m_command = CMD_FM_RX_DOWN; break;
                   }
           break;
           case 5: m_command = (temp_buf[2]==1)?CMD_VERIFY:CMD_NONE; break;
           case 7: if(temp_buf[2]==0)
                    m_command  = CMD_PTT_PRESS;
                   else if(temp_buf[2]==1)
                   {
                      m_command  = CMD_PTT_RELEASE;
                   }
               break;
           case 8: m_command = CMD_CW;break;
           case 9: m_command = CMD_FREQ_SET; break;
           case 0x0a: m_command = CMD_MODE_SET; break;
           case 0x0b: m_command = CMD_STAT_REQ; break;
           case 0x0c: m_command = CMD_POWER_DOWN;break;
           case 0x0d: m_command = CMD_SVOL_SET;break;
           case 0x0e: m_command = CMD_HVOL_SET;break;
           case 0x0f: m_command = CMD_MIC_SET;break;
           case 0x10: m_command = CMD_CMP_SET;break;
           case 0x11: m_command = CMD_BAS_SET;break;
           case 0x12: m_command = CMD_TRB_SET;break;
           case 0x13: m_command = CMD_RFG_SET;break;
           case 0x14: m_command = CMD_IFG_SET;break;
           case 0x15: m_command = CMD_SQL_SET;break;
           case 0x16: m_command = CMD_AGC_SET;break;
           case 0x17: m_command = CMD_AMP_SET;break;
           case 0x18: m_command = CMD_FILTER_SET;break;
           case 0x19: m_command = CMD_NR_SET;break;
           case 0x1a: m_command = CMD_NB_SET;break;
           case 0x1b: m_command = CMD_VFO_SET;break;
           case 0x1c: m_command = CMD_SPLIT_SET;break;
           case 0x1d: m_command = CMD_BAND_SET;break;
           case 0x1e: m_command = CMD_NR_VALUE_SET;break;
           case 0x1f: m_command = CMD_NB_VALUE_SET;break;
           case 0x20: m_command = CMD_PEAK_VALUE_SET;break;
           case 0x21: m_command = CMD_TUNER_SET;break;
           case 0x22: m_command = CMD_SPEC_SPAN_SET;break;
           case 0x23: m_command = CMD_SPEC_REF_SET;break;
           case 0x24: m_command = CMD_SPEC_SPEED_SET;break;
           case 0x25: m_command = CMD_SPEC_MODE_SET;break;
           case 0x26: m_command = CMD_CTSS_SET;break;
           case 0x27:
                {
                    m_command = CMD_MODLE;
                    m_isDeviceVerifyOk = true;
                }
                break;
           case 0x28: m_command = CMD_POWER_PERCENT; break;
           case 0x29: m_command = CMD_RIT; break;
           case 0x2A: m_command = CMD_XIT; break;
           case 0x2B: m_command = CMD_LVOICE_TIME; break;
           case 0x2C: m_command = CMD_POWER_LEVEL; break;
           case 0x2D: m_command = CMD_METERS; break;
           case 0x2E: m_command = CMD_PARAM_UPDATE; break;
           case 0x2F: m_command = CMD_KEY_TYPE; break;
           case 0x30: m_command = CMD_SIDETONE_VOLUME; break;
           case 0x31: m_command = CMD_SIDETONE_FREQ; break;
           case 0x32: m_command = CMD_TRX_DELAY; break;
           case 0x33: m_command = CMD_AUDIO_SOURCE; break;
           case 0x34: m_command = CMD_CW_TRAINING; break;
           case 0x35: m_command = CMD_KEY_SPEED; break;
           case 0x36: m_command = CMD_CW_DECODE; break;
           case 0x37: m_command = CMD_CW_THRESHOLD; break;
           case 0x39: m_command = CMD_SPECTRUM; break;
           case 0x40:
            {
                m_command = CMD_SETCHANNEL;
                m_BasicAckChannel = temp_buf[2];
            } break;
           case 0x41:
            {
                m_command = CMD_GETCHANNEL;
                if (size > 20)
                {
                    getChannelBasicParam(temp_buf+2);
                    m_BasicAckChannel = temp_buf[2];
                }
            }break;
           case 0x42: m_command = CMD_ENCHANNEL; break;
           case 0x43:
                {
                    m_command = CMD_DMRSETCHANNEL;
                   m_DMRAckChannel = temp_buf[2];
                }
                break;
           case 0x44:
            {
                m_command = CMD_DMRGETCHANNEL;
                if (size > 20)
                {
                    getChannelDMRParam(temp_buf+3); //不需要CHANNEL字节 已经获取了
                    m_DMRAckChannel = temp_buf[2];
                }
            }
            break;
           default: m_command = CMD_NONE;  break;
         }

}

//****************************************************
//** 函数名称: CRC16Check
//** 输    入: buf 要校验的数据;
//**             len 要校验的数据的长度
//** 输    出: 校验值
//** 功能描述: CRC16循环冗余校验
//** 备注：校验模式为CRC16/CCITT-FALSE，注意变量类型 由于32位单片机和16位 8位单片机位数不同
// 保证数据是16位即可
//*****************************************************/
uint16_t DataProc::CRC16Check(unsigned char *buf, unsigned char len)
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



// 其他

/*
 * @将n个字节16进制数组转化为10进制数
 *
 */
ulong DataProc::Hex2Dec(uint8_t* buf,uint8_t len )
{
    ulong dec =0;
    for(uint8_t i=0;i<len;i++)
    {
       dec |= ((unsigned int)buf[len-i-1]&0xff) <<(i*8);

    }
    return dec;

}


//不管16进制还是10进制 在单片机都可以按字节寻址,例如 一个四字节十进制数 l44000000 在单片机中存储为  D5 9F 80
//所以在这的进制转换其实并没有真正转换进制 实质只是将n个字节的数组存放到能一个空间足够大的数中 或者将一个数存放到数组中
void DataProc::Dec2Hex(uint8_t* buf,uint8_t len,volatile uint32_t dec)
{

    for(uint8_t i=0;i<len;i++)
    {
        buf[len-i-1] = (uint8_t)(dec>>i*8)&0xFF;  //按字节移位  低位放后面
    }

}


