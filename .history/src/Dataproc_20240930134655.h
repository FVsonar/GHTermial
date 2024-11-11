#ifndef DATAPROC_H
#define DATAPROC_H
#include <QObject>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>

#define PROTOCAL_BUFFER_SIZE 255
#define READ_CHANNEL_MAX_COUNT  100 //实际数字加一


struct dmr_mem_t
{
    quint8 ch_index;  //与q900 结构体不同 需要加入inxex
    quint8 call_format;
    quint8 txcc;
    quint8 rxcc;
    quint8 slot_num;
    quint32 call_id_dec;
    quint32 own_id_dec;
    quint8 ch_type;
    quint8 rxctcss;
    quint8 txctcss;
    quint8 sqlevel;
    quint8 spkgain;
    quint8 dmrexist;
    quint8 dmod_gain;
    quint8 scr_en;
    quint16 scr_seed;
    quint8 ch_bs_mode;
    quint8 validat;
};

class DataProc : public QObject
{
    Q_OBJECT
public:
    static DataProc *getInstance(); // 获取本类的单例对象

private:
    explicit DataProc(QObject *parent = nullptr); // 构造方法
    ~DataProc(); // 析构函数

private:
    quint8 CheckReceAckOk(void);

    uint16_t CRC16Check(unsigned char *buf, unsigned char len);
    void Protocal_Get_Command(uint8_t* temp_buf,uint8_t size);
    void PackData(quint8 cmd,int len);
    void SendData(QByteArray &buff);
    ulong Hex2Dec(uint8_t* buf,uint8_t len );
    void Dec2Hex(uint8_t* buf,uint8_t len,volatile uint32_t dec);
    void getChannelBasicParam(const uint8_t* channel_buf);
    void getChannelDMRParam(const uint8_t* channel_buf);
    QString JsonToQstring(QJsonObject jsonObject);
    void get_realneedsentcount(void);

public:
    void sendCheckDevice(void);
    bool deviceVerify(void);
signals:

private slots:
    void onSendInterval();
    void onGetInterval();

public slots:
    void onDataReceived(const QByteArray &buff);
    void parseTableJsonArry(QString str);  //写信道开始
    quint8 getSendCount(void);
    quint8 getReadCount(void);
    void loadChannelParamater();         //读信道开始
     QString getJsonArrayFromByte();//uint8_t* channel_buf
    void stopLoad();

    void setReadWriteList(quint8 index, bool state);
    quint8 getDebugMode(void)
    {
        return m_isDebugMode;
    }
private:
    enum FRAME_STATE
    {
        F_HEAD,
        F_LEN,
        F_DATA
    };

    enum CMD_Label
    {
        CMD_PTT_PRESS = 0,
        CMD_PTT_RELEASE,  //PTT 释放 ,FM发送 接收关闭都是同一个命令
        CMD_FM_TX_ON ,
    //    CMD_FM_TX_MUSIC 暂时不用
        CMD_FM_ON,

        CMD_FM_RX_UP,
        CMD_FM_RX_DOWN,
        CMD_VERIFY,  //认证命令
        CMD_CW,
        CMD_SPECTRUM,
        CMD_FREQ_SET,
        CMD_MODE_SET,
        CMD_STAT_REQ,
        CMD_POWER_DOWN,
        CMD_SVOL_SET,
        CMD_HVOL_SET,
        CMD_MIC_SET,
        CMD_CMP_SET,
        CMD_BAS_SET,
        CMD_TRB_SET,
        CMD_RFG_SET,
        CMD_IFG_SET,
        CMD_SQL_SET,
        CMD_AGC_SET,
        CMD_AMP_SET,
        CMD_FILTER_SET,
        CMD_NR_SET,
        CMD_NB_SET,
        CMD_VFO_SET,
        CMD_SPLIT_SET,
        CMD_BAND_SET,
        CMD_NR_VALUE_SET,
        CMD_NB_VALUE_SET,
        CMD_PEAK_VALUE_SET,
        CMD_TUNER_SET,
        CMD_SPEC_SPAN_SET,
        CMD_SPEC_REF_SET,
        CMD_SPEC_SPEED_SET,
        CMD_SPEC_MODE_SET,
        CMD_CTSS_SET,   //哑音频率
        CMD_MODLE,   //设备类型
        CMD_POWER_PERCENT,
        CMD_RIT,
        CMD_XIT,
        CMD_LVOICE_TIME,
        CMD_POWER_LEVEL,
        CMD_METERS,
        CMD_PARAM_UPDATE,
        CMD_KEY_TYPE,
        CMD_SIDETONE_VOLUME,
        CMD_SIDETONE_FREQ,
        CMD_TRX_DELAY,
        CMD_CW_TRAINING,
        CMD_KEY_SPEED,
        CMD_AUDIO_SOURCE,
        CMD_CW_DECODE,
        CMD_CW_THRESHOLD,
        CMD_SETCHANNEL,  //信道设置
        CMD_GETCHANNEL,  //信道读取
        CMD_ENCHANNEL,  //信道开启 关闭
        CMD_DMRSETCHANNEL, //DMR信道设置
        CMD_DMRGETCHANNEL, // DMR 信道数据读取
        CMD_ALL,
        CMD_NONE
    };

    const QString m_type[16] ={"CHANNEL", "CALL_TYPE", "TX_CC", "RX_CC","SLOT", "CALL_ID", "OWN_ID", "CH_TYPE", "RX_CTCSS", "TX_CTCSS", "SQL","SPK" ,"RX_GAIN","ENCRY", "SEED", "BSMODE" };
    const QString m_BasicType[10]  = {"CHANNEL","VFA_MODE","VFB_MODE","VFA_FREQ","VFB_FREQ","T_CTCSS","R_CTCSS","NAME","A_B","SPLIT"};

    quint8 m_Parse_Buff[PROTOCAL_BUFFER_SIZE];  //命令解析buff
    quint8 m_DMR_SendBuff[PROTOCAL_BUFFER_SIZE];  //DMR tempbuff
    quint8 m_Basic_SendBuff[PROTOCAL_BUFFER_SIZE]; //Basic tempbuff
    qint16 m_stateMachine;                   //协议处理状态机
    quint16 m_recNum;
    quint16 m_rxLen;
    quint8 m_headCount;                     //包头A5计数
    quint8 m_command;
    QByteArray m_dataBuffer;
    QByteArray m_txDataBuffer;
    dmr_mem_t m_dmr;
    QJsonArray m_sendArray;
    QTimer m_sendTimer;
    quint16 m_sendCount;  //已经发送帧数
    quint8 m_sendPro;  //发送进度
    bool m_isSending;


    quint8 m_needRWList[100];
    QTimer m_readTimer;
    bool m_isReading;
    bool m_ReadLock;
    bool m_isUIGetted;
    quint8 m_readPro;  //读取进度
    QJsonObject m_ChannelParamObject;

    quint8 m_realRWcount;

    quint8 m_DMRAckChannel;
    quint8 m_BasicAckChannel;

    bool m_isDeviceVerifyOk;
    bool m_isDebugMode;
};

#endif // DATAPROC_H
