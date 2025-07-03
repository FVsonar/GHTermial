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
#include <QUdpSocket>
#include <QSpinBox>
#include <QTranslator>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrentRun>
#include <QButtonGroup>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <Delegates/checkboxdelegate.h>
#include <Delegates/comboboxdelegate.h>
#include <Delegates/spinboxdelegate.h>


#include "Entity/channel.h"
#include "Entity/dmr.h"

#include "Tools/serialporttools.h"

#include "Service/channel_service.h"
#include "Service/dmr_service.h"

#include "DAO/channel_dao.h"
#include "DAO/dmr_dao.h"

#include "Service/SerialPortManager.h"
#include "Service/SerialCommandManager.h"

#ifndef debug
#define debug(x) qDebug().noquote()<<QTime::currentTime()<<"termial:["<<__LINE__<<"]"<<__FUNCTION__<<"()"<<x
#endif

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
    QString connectionName;  // 储存是TCP连接还是串口连接
    const QStringList vfoModes = {"USB" , "LSB" , "CWR" , "CWL" , "AM" , "WFM" , "NFM" , "DIGI" , "PKT" , "DMR" };//DFM模式在ch_type中
    const QStringList yayinModes = {"0","67.0","69.3","71.9","74.4","77.0","79.7","82.5","85.4","88.5","91.5","94.8","97.4","100.0",
                                    "103.5","107.2","110.9","114.8","118.8","123.0","127.3","131.8","136.5","141.3","146.2","150.0",
                                    "151.4","156.7","159.8","162.2","165.5","167.9","171.3","173.8","177.3","179.9","183.5","186.2",
                                    "189.9","192.8","196.6","199.5","203.5","206.5","210.7","213.8","218.1","221.3","225.7","229.1",
                                    "233.6","237.1","241.8","245.5","250.3","254.1"};
    const QStringList dmrYayinModes = {"0","63.0","67.0","69.3","71.9","74.4","77.0","79.7","82.5","85.4","88.5","91.5","94.8","97.4","100.0",
                                       "103.5","107.2","110.9","114.8","118.8","123.0","127.3","131.8","136.5","141.3","146.2","150.0",
                                       "151.4","156.7","159.8","162.2","165.5","167.9","171.3","173.8","177.3","179.9","183.5","186.2",
                                       "189.9","192.8","196.6","199.5","203.5","206.5","210.7","213.8","218.1","221.3","225.7","229.1",
                                       "233.6"};
    const QStringList callTypes = {"Single", "Group", "All"};
    const QStringList chTypes = {"DFM", "DMR"};

    bool tunerSend(QByteArray data);
    void setNumCheckedState(int value);
    void channelMaxNumSpinBox_valueChanged(int value);
    void handleAllCommandsCompleted_channel();
    void initializeTableRows(int start, int count);
signals:

protected:
    QPoint m_dragPosition;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void serialportComboBox_currentIndexChanged(int index);    // 当串口选择下拉框发生变化时
    void serialportLinkBtn_clicked();   // 当连接按钮被点击时
    void readBtn_clicked();
    void sendBtn_clicked();

    void checkAllBtn_clicked();
    void saveBtn_clicked();
    void openBtn_clicked();
    void channelNumLineEdit_returnPressed();
    // void scanSerialPort_timeout();
    void checkAllNotBtn_clicked();
    // void scanNetworkInterfaces();

    // void scanSerialPort_timeout();
    void serialportFlashBtn_clicked();

    void tabWidgetSwitch(int index);

private slots:

    void send_clicked();
    void read_clicked();

    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

public:
    Ui::termial *ui;

    QByteArray lastSentData;
    int sendCount = 0;
    int lx10 = 0;

    Tools tool;
    SerialPort serialPortTool;

    Channel_Service channel_service;
    Dmr_Service dmr_service;

    Channel_DAO channel_dao;
    Dmr_DAO dmr_dao;

    QTranslator translator; // 翻译

    QString currentPage;    // 当前所在页名称,可当pageIndex使用

    bool readBtn_busy;  // 读取按钮的状态 是否正在读取 在：true 不在：false
    bool sendBtn_busy;  // 发送按钮的状态 是否正在发送 在：true 不在：false



    channel channelWrite;   // 0x40 信道数据对象
    channel channelRead;    // 0x41 信道数据对象
    DMR dmrWrite;           // 0x43 DMR数据对象
    DMR dmrRead;            // 0x44 DMR数据对象


    /* 表格 勾选 */
    QList<channel>* readySend40ChannelList;  // 所有被勾选的Channel对象    0x40的newChannelList
    QList<channel>* readySend41ChannelList;  // 所有被勾选的Channel对象    0x41的newChannelList
    QList<DMR>* readySend43ChannelList;      // 储存表格中所有被勾选的DMR对象    0x43的newDMRList
    QList<DMR>* readySend44ChannelList;      // 储存表格中所有被勾选的DMR对象    0x44的newDMRList

    /* 串口 */
    QList<QSerialPortInfo> serialPortList;      // 所有串口QSerialPortInfo对象的列表
    QList<QSerialPortInfo> loadSerialPortList;  // 上次的串口列表
    QSerialPortInfo currentSerialportInfo;      // 串口下拉框当前选中的QSerialPortInfo对象

    /* 状态 */
    bool isAllSet=false;                    // 是否全选 -1全不选 0有选
    bool orAllSet=false;                    // 是否为 全选/全不选 状态
    bool serialportLinkBtn_state = false;   // 串口连接按钮 未连接-false 连接-true 默认false

    bool vfoaModeIsDmr = false; // vfoa模式是否为DMR 控制DMR是否可修改
    bool vfobModeIsDmr = false; // vfob模式是否为DMR 控制DMR是否可修改



    QStandardItemModel *model; // 数据模型
    // 委托指针
    CheckBoxDelegate *checkBoxDelegate;
    ComboBoxDelegate *vfoModeDelegate;
    ComboBoxDelegate *yayinDelegate;
    ComboBoxDelegate *dmrYayinDelegate;
    ComboBoxDelegate *callTypeDelegate;
    SpinBoxDelegate *ccDelegate;    // DMR的色码
    SpinBoxDelegate *slotDelegate;  // 时隙的数字选择框
    SpinBoxDelegate *idDelegate;    // call_id own_id的数字选择框
    ComboBoxDelegate *chTypeDelegate;   // 信号类型下拉选择框


    /* 初始化函数 */
    void initSerialportComboBox();
    void initPushBtnState();
    void initViewTableHaed();
    void initViewTable1000Col();    // 生产1000空白行
    void initLoad();
    void initConnect();
    void initLanguageComboBox();
    void initArt();

    void initModelsAndViews(); // 初始化模型和视图
    // 初始化表格视图
    void initTableView();

    /* vfo 模式发生改变 */
    void updateDmrWidgetsState(int row);

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
    void getAllCheckedRowsToList(QList<channel>* list);

    /**
    *   设置所有复选框状态
    */
    void setAllCheckedState(bool state);

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
    void getAllCheckedRowsToListDmr(QList<DMR> *readySendDmrList);

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


    void resetOperationState();
    void clearAllCommandLists();

private:
    SerialPortManager* serialPortManager = nullptr;
    SerialCommandManager* serialCommandManager = nullptr;
};
#endif // TERMIAL_H
