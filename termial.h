#ifndef TERMIAL_H
#define TERMIAL_H

#include <QList>
#include <QHash>
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <QPointer>
#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QFile>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QSpinBox>
#include <QTranslator>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrentRun>

#include "Entity/channel.h"
#include "Tools/serialporttools.h"
#include "clientinfo.h"
#include "Tools/tcptools.h"
#include "Entity/dmr.h"


#define debug(x) qDebug().noquote()<<QTime::currentTime()<<"termial:["<<__LINE__<<"]"<<__FUNCTION__<<"()"<<x

QT_BEGIN_NAMESPACE
namespace Ui {
class termial;
}
QT_END_NAMESPACE

class termial : public QWidget
{
    Q_OBJECT

public:
    termial(QWidget *parent = nullptr);
    ~termial();

    const int CHANNEL_NAME_SIZE = 12;
    const int HOW_LONG_HEARTBEAT = 8000; // 多久发一次心跳包
    const int MAX_TIMEOUT_MUN = 3;
    int currentErrorMun = 0;


public slots:
    void serialportComboBox_currentIndexChanged(int index);    // 当串口选择下拉框发生变化时
    void serialportLinkBtn_clicked();   // 当连接按钮被点击时
    void currentSerialport_readyRead();
    void readBtn_clicked();
    void sendBtn_clicked();

    void tcpOpenBtn_clicked();

    void onTimeout0x40();
    void onTimeout0x41();

    void checkAllBtn_clicked();
    void saveBtn_clicked();
    void openBtn_clicked();
    void channelNumLineEdit_returnPressed();
    // void scanSerialPort_timeout();
    void checkAllNotBtn_clicked();
    // void scanNetworkInterfaces();
    void tcpServerNewConnection();
    void tcpSocket_readyRead();
    void tcpReadBtn_clicked();
    void tcpSendBtn_clicked();
    void tcpOnTimeout0x40();
    void tcpOnTimeout0x41();



    void heartbeat_outtime();
    void onTimeout0x44();
    void onTimeout0x43();
    void tcpOnTimeout0x43();
    void tcpOnTimeout0x44();
    // void scanSerialPort_timeout();
    void serialportFlashBtn_clicked();

private:
    Ui::termial *ui;
    Tools tool;
    SerialPort serialPortTool;
    TcpTools tcpTools;

    QTranslator translator; // 翻译

    /* 串口定时器 超时重发 */
    QTimer *retransmissionTimer0x40;   // 0x40
    QTimer *retransmissionTimer0x41;    // 0x41
    QTimer *retransmissionTimer0x43;    // 0x43
    QTimer *retransmissionTimer0x44;    // 0x44
    /* tcp定时器 超时重发 */
    QTimer *tcpRetransmissionTimer0x40;
    QTimer *tcpRetransmissionTimer0x41;
    QTimer *tcpRetransmissionTimer0x43;
    QTimer *tcpRetransmissionTimer0x44;

    QTimer *heartbeatTimer; // 心跳包定时器 超时发送心跳包

    channel channelWrite;   // 0x40 信道数据对象
    channel channelRead;    // 0x41 信道数据对象
    DMR dmrWrite;           // 0x43 DMR数据对象
    DMR dmrRead;            // 0x44 DMR数据对象

    /* 表格列 列表 */
    QVector<QCheckBox*> checkBoxPrtList;            // 储存下拉框list 用于全选/全不选 释放空间
    QList<QComboBox*> vfoaComboBoxPtrList;          // vfoa模式下拉框list 用于释放空间
    QList<QComboBox*> vfobComboBoxPtrList;          // vfoab模式下拉框list 用于释放空间
    QList<QComboBox*> EmitYayinComboBoxPtrList;     // 发射亚音下拉框list 用于释放空间
    QList<QComboBox*> ReceiveYayinComboBoxPtrList;  // 发射亚音下拉框list 用于释放空间
    QList<QComboBox*> callTypeComboBoxPtrList;      // DMR的call_type下拉框list
    QList<QSpinBox*> txCcSpinBoxPtrList;            // DMR的TX_CC数字选择框list
    QList<QSpinBox*> rxCcSpinBoxPtrList;            // DMR的RX_CC数字选择框list
    QList<QSpinBox*> slotSpinBoxPtrList;            // DMR的slot数字选择框list
    QList<QComboBox*> chTypeComboBoxPtrList;        // DMR的CH_TYPE下拉框list
    QList<QComboBox*> rxCtcssComboBoxPtrList;       // DMR的RX_CTCSS下拉框list
    QList<QComboBox*> txCtcssComboBoxPtrList;       // DMR的RX_CTCSS下拉框list
    QList<QSpinBox*> sqlevelSpinBoxPtrList;         // DMR的sqlevel数字选择框list
    QList<QSpinBox*> spkgainSpinBoxPtrList;         // DMR的spkgain
    QList<QSpinBox*> rxGainSpinBoxPtrList;          // DMR的dmod_gain
    QList<QComboBox*> enScrComboBoxPtrList;         // DMR scr_en 0不加密 1加密
    QList<QComboBox*> bsModeComboBoxPtrList;        // DMR ch_bs_mode 0~1
    /* 表格 勾选 */
    QList<channel> readySend40ChannelList;  // 所有被勾选的Channel对象    0x40的newChannelList
    QList<channel> readySend41ChannelList;  // 所有被勾选的Channel对象    0x41的newChannelList
    QList<DMR> readySend43ChannelList;      // 储存表格中所有被勾选的DMR对象    0x43的newDMRList
    QList<DMR> readySend44ChannelList;      // 储存表格中所有被勾选的DMR对象    0x44的newDMRList

    /* 串口 */
    QList<QSerialPortInfo> serialPortList;      // 所有串口QSerialPortInfo对象的列表
    QList<QSerialPortInfo> loadSerialPortList;  // 上次的串口列表
    QSerialPortInfo currentSerialportInfo;      // 串口下拉框当前选中的QSerialPortInfo对象
    QSerialPort currentSerialport;              // 当前使用的串口

    /* 状态 */
    bool isAllSet=false;                    // 是否全选 -1全不选 0有选
    bool orAllSet=false;                    // 是否为 全选/全不选 状态
    bool serialportLinkBtn_state = false;   // 串口连接按钮 未连接-false 连接-true 默认false
    bool tcpOpenBtn_state = false;          // TCP连接按钮 未连接-false 连接-true 默认false
    bool vfoaModeIsDmr = false; // vfoa模式是否为DMR 控制DMR是否可修改
    bool vfobModeIsDmr = false; // vfob模式是否为DMR 控制DMR是否可修改

    /* TCP */
    QTcpServer *tcpServer;
    QList<ClientInfo> tcpSocketList;    // 所有已连接的客户端
    ClientInfo currentClient;   // 下拉框当前选中的客户端  通过getCurrentClientInfo更新

    /* 初始化函数 */
    void initSerialportComboBox();
    void initPushBtnState();
    void initViewTableHaed();
    void initViewTable1000Col();    // 生产1000空白行
    void initLoad();
    void initConnect();
    void initLanguageComboBox();
    void initArt();

    /* vfo 模式发生改变 */
    void vfoaComboBoxIndexChanged(int row, int index);
    void vfobComboBoxIndexChanged(int row, int index);
    void updateDmrWidgetsState(int row);
    /* tcp 处理回复数据 */
    void handleCommand0x40(channel &newChannel);
    void handleCommand0x41(channel &newChannel);
    void handleCommand0x43(DMR &newDmr);
    void handleCommand0x44(DMR &newDmr);
    /* 串口 处理回复数据 */
    void serialHandleCommand0x40(channel &newChannel);
    void serialHandleCommand0x41(channel &newChannel);
    void serialHandleCommand0x43(DMR &newDmr);
    void serialHandleCommand0x44(DMR &newDmr);

    /* 辅助函数 */

    /**
    *   UI
    *   读取该行数据为channel对象
    *   @value  行号
    *   @return channel 对象
    */
    channel rowReadDataToChannel(int row);   // 读取该行所有数据

    /**
    *  UI  json
    *  让用户选择保存位置,返回路径
    *  @value QWidget *parent  父窗口,用来指定位置
    *  @value const QString &filter    文件过滤器,用;;分隔
    *  @return QString filePath    返回选择的文件路径
    */
    QString getUserSaveLocation(QWidget *parent, const QString &filter);

    /**
    *   UI  json
    *   将json数据保存到文件
    *   @value const QJsonObject& obj   json数据对象
    *   @value const QString& filePath  保存的文件路径
    *   @return bool 是否保存成功
    */
    bool saveQJsonObjectToFile(const QJsonObject &obj, const QString &filePath);

    /**
    *  UI  json
    *  让用户选择保存位置,返回路径
    *  @value QWidget *parent  父窗口,用来指定位置
    *  @value const QString &filter    文件过滤器,用;;分隔
    *  @return QString filePath    返回选择的文件路径
    */
    void getAllCheckedRowsToList(QList<channel> &readySendChannelList);

    /**
    *   设置所有复选框状态
    */
    void setAllCheckedState(bool state);

    /**
    *   UI
    *   获得当前下拉框选择的IP 端口
    *   @return   ClientInfo    返回获取到下拉框选择的ClientInfo自定义对象
    */
    ClientInfo getCurrentClientInfo();

    /**
    *   UI
    *   单条UI修改
    *   将一行channel数据进行修改
    *   @value int row 所在行
    *   @value channel& newChannel 一条数据源
    */
    void viewUpdate(int row, channel &newChannel);

    /**
    *  UI
    *  单条UI修改
    *  将一行dmr数据进行修改
    *  @param  int row 所在行
    *  @param  DMR& newDMR 一条数据源
    */
    void viewUpdateDmr(int row, DMR &newDMR);

    /**
    *  UI
    *  添加单条数据UI占位显示
    *  将一行数据添加到UI表格
    *  @value int row 所在行
    */
    void viewAddData(int row);

    /**
    *  UI
    *  读取该行数据为DMR对象
    *  @param  int row 行号
    *  @return DMR 对象
    */
    DMR rowReadDataToDmr(int row);

    /**
    *  UI
    *  辅助函数
    *  遍历所有复选框,将勾选的行加入List<DMR>
    *  @param   QList<DMR> &readySendDmrList    存放位置
    */
    void getAllCheckedRowsToListDmr(QList<DMR> &readySendDmrList);

    /**
    *  槽函数
    *  语言切换
    *  当语言下拉框发生变化时
    *  @param  int index   下拉框选择
    */
    void switchLanguage(int index);

    /**
    *  UI
    *  切换翻译
    *  @param  翻译文件在资源文件夹下的名字
    */
    void loadingLanguage(QString langName);

    /**
    *  异步加载翻译文件
    *  @param  翻译文件在资源文件夹下的名字
    */
    void loadLanguageAsync(const QString &langName);

};
#endif // TERMIAL_H
