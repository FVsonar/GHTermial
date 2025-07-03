#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QDockWidget>
#include <memory>

namespace GHTerminal {

class ChannelModel;
class SerialService;
class ConfigManager;
class Logger;
class ChannelWidget;
class SettingsDialog;

namespace Ui {
class MainWindow;
}

/**
 * @brief 主窗口
 * 
 * 应用程序的主界面，负责整体布局和功能协调
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    /**
     * @brief 初始化主窗口
     * @return 初始化是否成功
     */
    bool initialize();

    /**
     * @brief 设置信道模型
     * @param model 信道模型
     */
    void setChannelModel(ChannelModel *model);

    /**
     * @brief 设置串口服务
     * @param service 串口服务
     */
    void setSerialService(SerialService *service);

    /**
     * @brief 设置配置管理器
     * @param configManager 配置管理器
     */
    void setConfigManager(ConfigManager *configManager);

    /**
     * @brief 设置日志管理器
     * @param logger 日志管理器
     */
    void setLogger(Logger *logger);

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    // 文件菜单
    void onNewProject();
    void onOpenProject();
    void onSaveProject();
    void onSaveProjectAs();
    void onExportData();
    void onImportData();
    void onExit();

    // 编辑菜单
    void onUndo();
    void onRedo();
    void onCut();
    void onCopy();
    void onPaste();
    void onDelete();
    void onSelectAll();

    // 视图菜单
    void onShowToolbar();
    void onShowStatusbar();
    void onShowChannelPanel();
    void onShowLogPanel();
    void onFullscreen();

    // 通信菜单
    void onConnect();
    void onDisconnect();
    void onRefreshPorts();
    void onReadChannels();
    void onWriteChannels();
    void onReadDMR();
    void onWriteDMR();

    // 工具菜单
    void onSettings();
    void onTerminal();
    void onCalculator();
    void onAbout();

    // 帮助菜单
    void onHelp();
    void onAboutQt();

    // 状态栏
    void onConnectionStatusChanged(const QString &status);
    void onDataReceived(const QByteArray &data);
    void onDataSent(const QByteArray &data);
    void onErrorOccurred(const QString &error);

    // 其他
    void onChannelModelChanged();
    void onUpdateWindowTitle();

private:
    void setupUi();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupDockWidgets();
    void setupActions();
    void setupConnections();
    void setupShortcuts();
    void loadSettings();
    void saveSettings();
    void updateActions();
    void updateWindowTitle();
    void showStatusMessage(const QString &message, int timeout = 5000);

private:
    std::unique_ptr<Ui::MainWindow> ui;
    
    // 核心组件
    ChannelModel *m_channelModel;
    SerialService *m_serialService;
    ConfigManager *m_configManager;
    Logger *m_logger;
    
    // UI组件
    ChannelWidget *m_channelWidget;
    SettingsDialog *m_settingsDialog;
    QTableView *m_channelTableView;
    
    // 菜单和工具栏
    QMenuBar *m_menuBar;
    QToolBar *m_toolBar;
    QStatusBar *m_statusBar;
    
    // 停靠窗口
    QDockWidget *m_channelDock;
    QDockWidget *m_logDock;
    
    // 动作
    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_exitAction;
    QAction *m_connectAction;
    QAction *m_disconnectAction;
    QAction *m_readAction;
    QAction *m_writeAction;
    QAction *m_settingsAction;
    
    // 状态
    QString m_currentProjectFile;
    bool m_isModified;
};

} // namespace GHTerminal 