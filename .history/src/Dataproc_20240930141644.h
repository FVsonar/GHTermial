#ifndef DATAPROC_H
#define DATAPROC_H
#include <QObject>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>

#define PROTOCAL_BUFFER_SIZE 255
#define READ_CHANNEL_MAX_COUNT  100 //实际数字加一


// 定义DMR内存结构体，用于存储频道相关配置信息
struct dmr_mem_t
{
    quint8 ch_index;  // 频道索引，用于标识特定的频道
    quint8 call_format;  // 呼叫格式，定义了通信的方式或类型
    quint8 txcc;  // 发射色彩码，用于确定发射时的逻辑信道
    quint8 rxcc;  // 接收色彩码，用于确定接收时的逻辑信道
    quint8 slot_num;  // 时隙号，用于区分在同一载波上的不同时间片
    quint32 call_id_dec;  // 呼叫ID，用于标识一次特定的呼叫
    quint32 own_id_dec;  // 本机ID，用于标识当前设备的身份
    quint8 ch_type;  // 频道类型，区分不同服务或功能的频道
    quint8 rxctcss;  // 接收CTCSS码，用于亚音频静噪系统的频率
    quint8 txctcss;  // 发射CTCSS码，用于亚音频静噪系统的频率
    quint8 sqlevel;  // 静噪电平，用于设置接收信号的最低电平阈值
    quint8 spkgain;  // 扬声器增益，用于调节设备输出音量
    quint8 dmrexist;  // DMR存在性标志，用于指示DMR信号是否存在
    quint8 dmod_gain;  // DMR模式增益，用于调节DMR信号的接收增益
    quint8 scr_en;  // 语音加密使能，用于指示是否启用语音加密功能
    quint16 scr_seed;  // 语音加密种子，用于加密和解密语音信息
    quint8 ch_bs_mode;  // 频道工作模式，区分基站模式或直通模式
    quint8 validat;  // 验证标志，用于指示配置信息是否有效
};

class DataProc : public QObject
{
    Q_OBJECT
public:
    static DataProc *getInstance(); // 获取本类的单例对象

/**
 * @brief 检查设备状态
 *
 * 本函数用于发送检查请求，以验证设备的当前状态是否正常。
 * 它不返回任何结果，但可能触发进一步的操作或警报，具体取决于设备的状态。
 */
void sendCheckDevice(void);

/**
 * @brief 验证设备身份
 *
 * 本函数用于验证设备的身份，确保其合法性。这对于防止未授权访问和确保系统安全至关重要。
 *
 * @return true 设备身份验证成功
 * @return false 设备身份验证失败
 */
bool deviceVerify(void);

private:
    explicit DataProc(QObject *parent = nullptr); // 构造方法
    ~DataProc(); // 析构函数

private:
    /**
    * 检查接收的数据包是否包含正确的结束标志。
    *
    * @return 返回一个quint8类型的值，表示检查的结果。0表示结束标志错误，1表示结束标志正确。
    */
    quint8 CheckReceAckOk(void);

    /**
    * 计算CRC16校验码。
    *
    * @param buf 指向待计算校验码的数据缓冲区的指针。
    * @param len 数据缓冲区的长度。
    * @return 返回计算得到的CRC16校验码值。
    */
    uint16_t CRC16Check(unsigned char *buf, unsigned char len);

    /**
    * 解析接收到的数据，获取指令。
    *
    * @param temp_buf 临时缓冲区，用于存储接收到的数据。
    * @param size 缓冲区中数据的大小。
    */
    void Protocal_Get_Command(uint8_t* temp_buf, uint8_t size);

    /**
    * 准备数据包并发送。
    *
    * @param cmd 数据包的命令码。
    * @param len 数据包中数据的长度。
    */
    void PackData(quint8 cmd, int len);

    /**
    * 发送数据包。
    *
    * @param buff 包含待发送数据的缓冲区。
    */
    void SendData(QByteArray &buff);

    /**
    * 将十六进制表示的数字转换为十进制。
    *
    * @param buf 包含十六进制数字的缓冲区。
    * @param len 缓冲区中数据的长度。
    * @return 返回转换后的十进制数值。
    */
    ulong Hex2Dec(uint8_t* buf, uint8_t len);

    /**
    * 将十进制数转换为十六进制表示，并存储到缓冲区中。
    *
    * @param buf 存储转换结果的缓冲区。
    * @param len 缓冲区的长度。
    * @param dec 待转换的十进制数。
    */
    void Dec2Hex(uint8_t* buf, uint8_t len, volatile uint32_t dec);

    /**
    * 获取通道的基本参数。
    *
    * @param channel_buf 包含通道信息的缓冲区。
    */
    void getChannelBasicParam(const uint8_t* channel_buf);

    /**
    * 获取通道的DMR参数。
    *
    * @param channel_buf 包含通道信息的缓冲区。
    */
    void getChannelDMRParam(const uint8_t* channel_buf);

    /**
    * 将JSON对象转换为QString。
    *
    * @param jsonObject 待转换的JSON对象。
    * @return 返回转换后的QString对象。
    */
    QString JsonToQstring(QJsonObject jsonObject);

    /**
    * 获取实际需要发送的数据包数量。
    *
    * 此函数用于计算并返回实际需要发送的数据包数量，以确保所有必要数据都被正确发送。
    */
    void get_realneedsentcount(void);

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
    // 定义帧状态枚举，用于解析数据帧的各个部分
    enum FRAME_STATE
    {
        F_HEAD,   // 数据帧的头部
        F_LEN,    // 数据帧的长度
        F_DATA    // 数据帧的数据部分
    };

    // 定义命令枚举类型
    enum CMD_Label
    {
        CMD_PTT_PRESS = 0,        // PTT 按下
        CMD_PTT_RELEASE,          // PTT 释放 ,FM发送 接收关闭都是同一个命令
        CMD_FM_TX_ON,             // FM 发送打开
        // CMD_FM_TX_MUSIC 暂时不用
        CMD_FM_ON,                // FM 打开

        CMD_FM_RX_UP,             // FM 接收频率上调
        CMD_FM_RX_DOWN,           // FM 接收频率下调
        CMD_VERIFY,               // 认证命令
        CMD_CW,                   // 无线报
        CMD_SPECTRUM,             // 谱图
        CMD_FREQ_SET,             // 频率设置
        CMD_MODE_SET,             // 模式设置
        CMD_STAT_REQ,             // 状态请求
        CMD_POWER_DOWN,           // 电源关闭
        CMD_SVOL_SET,             // 音量设置
        CMD_HVOL_SET,             // 高音设置
        CMD_MIC_SET,              // 麦克风设置
        CMD_CMP_SET,              // 音频压缩设置
        CMD_BAS_SET,              // 低音设置
        CMD_TRB_SET,              // 中音设置
        CMD_RFG_SET,              // 高频增益设置
        CMD_IFG_SET,              // 中频增益设置
        CMD_SQL_SET,              // 静噪设置
        CMD_AGC_SET,              // 自动增益控制设置
        CMD_AMP_SET,              // 放大器设置
        CMD_FILTER_SET,           // 滤波器设置
        CMD_NR_SET,               // 噪声抑制设置
        CMD_NB_SET,               // 噪声消除设置
        CMD_VFO_SET,              // 频率调谐器设置
        CMD_SPLIT_SET,            // 分频设置
        CMD_BAND_SET,             // 频段设置
        CMD_NR_VALUE_SET,         // 噪声抑制值设置
        CMD_NB_VALUE_SET,         // 噪声消除值设置
        CMD_PEAK_VALUE_SET,       // 峰值设置
        CMD_TUNER_SET,            // 调谐器设置
        CMD_SPEC_SPAN_SET,        // 谱宽设置
        CMD_SPEC_REF_SET,         // 谱参考设置
        CMD_SPEC_SPEED_SET,       // 谱速度设置
        CMD_SPEC_MODE_SET,        // 谱模式设置
        CMD_CTSS_SET,             // 哑音频率设置
        CMD_MODLE,                // 设备类型设置
        CMD_POWER_PERCENT,        // 功率百分比设置
        CMD_RIT,                  // 接收频率偏移
        CMD_XIT,                  // 发送频率偏移
        CMD_LVOICE_TIME,          // 语音时间限制
        CMD_POWER_LEVEL,          // 功率等级设置
        CMD_METERS,               // 仪表显示
        CMD_PARAM_UPDATE,         // 参数更新
        CMD_KEY_TYPE,             // 键盘类型设置
        CMD_SIDETONE_VOLUME,      // 旁音音量设置
        CMD_SIDETONE_FREQ,        // 旁音频率设置
        CMD_TRX_DELAY,            // 收发延迟设置
        CMD_CW_TRAINING,          // 无线报训练模式
        CMD_KEY_SPEED,            // 键速度设置
        CMD_AUDIO_SOURCE,         // 音频源设置
        CMD_CW_DECODE,            // 无线报解码
        CMD_CW_THRESHOLD,         // 无线报阈值设置
        CMD_SETCHANNEL,           // 信道设置
        CMD_GETCHANNEL,           // 信道读取
        CMD_ENCHANNEL,            // 信道开启 关闭
        CMD_DMRSETCHANNEL,        // DMR信道设置
        CMD_DMRGETCHANNEL,        // DMR 信道数据读取
        CMD_ALL,                  // 所有命令
        CMD_NONE                  // 无命令
    };
    // 定义一个字符串数组m_type，用于存储16种不同的类型标识
    const QString m_type[16] ={"CHANNEL", "CALL_TYPE", "TX_CC", "RX_CC","SLOT", "CALL_ID", "OWN_ID", "CH_TYPE", "RX_CTCSS", "TX_CTCSS", "SQL","SPK" ,"RX_GAIN","ENCRY", "SEED", "BSMODE" };

    // 定义一个字符串数组m_BasicType，用于存储10种基本类型标识
    const QString m_BasicType[10]  = {"CHANNEL","VFA_MODE","VFB_MODE","VFA_FREQ","VFB_FREQ","T_CTCSS","R_CTCSS","NAME","A_B","SPLIT"};

    quint8 m_Parse_Buff[PROTOCAL_BUFFER_SIZE];  // 命令解析buff，用于接收和解析协议数据
    quint8 m_DMR_SendBuff[PROTOCAL_BUFFER_SIZE];    // DMR发送缓存，用于临时存储DMR协议数据
    quint8 m_Basic_SendBuff[PROTOCAL_BUFFER_SIZE];  // 基础发送缓存，用于临时存储基础协议数据
    qint16 m_stateMachine;      // 协议处理状态机，用于管理协议解析和处理的状态
    quint16 m_recNum;            // 接收数据序号，用于跟踪接收到的数据帧
    quint16 m_rxLen;             // 接收到的数据长度
    quint8 m_headCount;          // 包头A5计数，用于同步和识别数据包起始
    quint8 m_command;            // 命令码，表示接收到的命令类型
    QByteArray m_dataBuffer;     // 数据缓冲区，用于存储接收到的数据
    QByteArray m_txDataBuffer;   // 发送数据缓冲区，用于存储待发送的数据
    dmr_mem_t m_dmr;             // DMR内存区域，用于存储DMR相关的数据结构
    QJsonArray m_sendArray;      // 发送数组，用于存储待发送的JSON数据
    QTimer m_sendTimer;          // 发送定时器，用于控制数据发送时机
    quint16 m_sendCount;         // 已发送帧数，记录已发送的数据帧数量
    quint8 m_sendPro;            // 发送进度，表示数据发送的完成程度
    bool m_isSending;            // 发送状态标志，指示当前是否正在发送数据

    quint8 m_needRWList[100];   // 需要读写操作的设备列表，用于存储设备索引
    QTimer m_readTimer; // 读取定时器，用于控制读取操作的频率
    bool m_isReading;   // 当前是否正在读取设备状态
    bool m_ReadLock;    // 读取锁，用于防止同时多次读取操作
    bool m_isUIGetted;  // UI是否已经初始化完成
    quint8 m_readPro;   // 读取进度，表示当前读取操作的完成程度
    QJsonObject m_ChannelParamObject;   // 通道参数对象，用于存储设备通道配置信息
    quint8 m_realRWcount;   // 实际读写操作次数，用于统计读写操作的频率
    quint8 m_DMRAckChannel; // DRM确认通道，用于接收DRM相关的确认消息
    quint8 m_BasicAckChannel;   // 基础确认通道，用于接收基础设备状态确认消息
    bool m_isDeviceVerifyOk;    // 设备验证状态，表示设备验证是否通过
    bool m_isDebugMode; // 是否处于调试模式，用于控制调试信息的输出
};

#endif // DATAPROC_H
