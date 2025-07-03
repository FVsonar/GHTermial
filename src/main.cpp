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

#include <QtQml>
#include <QSysInfo>
#include <QQuickStyle>
#include <QApplication>
#include <QStyleFactory>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QMessageBox>
#include <QDir>
#include <QStandardPaths>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <AppInfo.h>
#include <Misc/Utilities.h>
#include <Serial/Console.h>
#include <Serial/Manager.h>
#include <UI/TerminalWidget.h>
#include <Serial/FileTransmission.h>
#include "JsonUtils.hpp"
#include "Dataproc.h"
#include "qmllanguge.h"
#include "autoconn.h"
#include "core/application.h"
#include "widgets/main_window.h"
#include "models/channel_model.h"
#include "services/serial_service.h"
#include "core/config_manager.h"
#include "core/logger.h"

#ifdef Q_OS_WIN
#    include <windows.h>
#endif

using namespace GHTerminal;

/**
 * @brief Entry-point function of the application
 *
 * @param argc argument count
 * @param argv argument data
 *
 * @return qApp exit code
 */
int main(int argc, char *argv[])
{
    // Fix console output on Windows (https://stackoverflow.com/a/41701133)
    // This code will only execute if the application is started from the comamnd prompt
#ifdef _WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        // Open the console's active buffer
        (void)freopen("CONOUT$", "w", stdout);
        (void)freopen("CONOUT$", "w", stderr);

        // Force print new-line (to avoid printing text over user commands)
        printf("\n");
    }
#endif

    // Set application attributes
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //解决窗口拖拽时闪烁的问题
//#if (QT_VERSION > QT_VERSION_CHECK(5,4,0))
  // QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
  // QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
//#endif
    // Init. application
    Application app(argc, argv);
    app.setApplicationName("GHTerminal");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("FVsonar");
    app.setOrganizationDomain("fvsonar.github.io");
    app.setStyle(QStyleFactory::create("Fusion"));

    // 命令行参数解析
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt串口终端工具 - Q900系列电台通信配置工具");
    parser.addHelpOption();
    parser.addVersionOption();
    
    QCommandLineOption configOption(QStringList() << "c" << "config",
                                   "指定配置文件路径", "config-file");
    parser.addOption(configOption);
    
    QCommandLineOption logOption(QStringList() << "l" << "log",
                                "指定日志文件路径", "log-file");
    parser.addOption(logOption);
    
    QCommandLineOption verboseOption(QStringList() << "v" << "verbose",
                                    "启用详细日志输出");
    parser.addOption(verboseOption);
    
    parser.process(app);

    // Init application modules
    QQmlApplicationEngine engine;
    auto manager = Serial::Manager::getInstance();
    auto console = Serial::Console::getInstance();
    auto utilities = Misc::Utilities::getInstance();
    auto fileTransmission = Serial::FileTransmission::getInstance();
    auto dataProc = DataProc::getInstance();

    JsonUtils jsonUtils;
    AutoConn autoConn;

    // Register custom QML properties
    qmlRegisterType<UI::TerminalWidget>("UI", 1, 0, "TerminalWidget");

    // Configure dark UI
    Misc::Utilities::configureDarkUi();

    //切换为本地语言
    //检测本系统语言自动装载翻译文件
    //使用qt的QLocale这个类，通过这个类来获取系统本地语言环境
    //QTranslator的load方法装载语言包
    //QGuiApplication的实例化对象的installTranslator去实现语言翻译
    QTranslator translator;
    QLocale locale;
    if( locale.language() == QLocale::English ) {
        translator.load(":/en_US.qm");
    }
    else if( locale.language() == QLocale::Chinese ) {
        translator.load(":/zh_CN.qm");
    }
    app.installTranslator(&translator);

    //将QmlLanguage中的所有函数暴露给qml调用
    QmlLanguage qmlLanguage(app, engine);
    engine.rootContext()->setContextProperty("qmlLanguage", &qmlLanguage);

    // Init QML interface
    auto c = engine.rootContext();
    QQuickStyle::setStyle("Fusion");
    c->setContextProperty("Cpp_AppIcon", "qrc" APP_ICON);
    c->setContextProperty("Cpp_Serial_Manager", manager);
    c->setContextProperty("Cpp_Serial_Console", console);
    c->setContextProperty("Cpp_Misc_Utilities", utilities);
    c->setContextProperty("Cpp_DataProc",dataProc);
    c->setContextProperty("Cpp_JsonUtils",&jsonUtils);
    c->setContextProperty("Cpp_AutoConn",&autoConn);

    c->setContextProperty("Cpp_AppName", app.applicationName());
    c->setContextProperty("Cpp_AppVersion", app.applicationVersion());
    c->setContextProperty("Cpp_AppOrganization", app.organizationName());
    c->setContextProperty("Cpp_Serial_FileTransmission", fileTransmission);
    c->setContextProperty("Cpp_AppOrganizationDomain", app.organizationDomain());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    // QML error, exit
    if (engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    // 初始化应用程序
    if (!app.initialize()) {
        QMessageBox::critical(nullptr, "错误", "应用程序初始化失败！");
        return -1;
    }
    
    // 获取日志管理器
    Logger *logger = app.logger();
    if (logger) {
        logger->info("GHTerminal 启动", "Main");
    }
    
    // 创建主窗口
    MainWindow mainWindow;
    
    // 创建核心组件
    auto configManager = std::make_unique<ConfigManager>(&mainWindow);
    auto serialService = std::make_unique<SerialService>(&mainWindow);
    auto channelModel = std::make_unique<ChannelModel>(&mainWindow);
    
    // 设置主窗口组件
    mainWindow.setConfigManager(configManager.get());
    mainWindow.setSerialService(serialService.get());
    mainWindow.setChannelModel(channelModel.get());
    mainWindow.setLogger(logger);
    
    // 初始化主窗口
    if (!mainWindow.initialize()) {
        QMessageBox::critical(&mainWindow, "错误", "主窗口初始化失败！");
        return -1;
    }
    
    // 显示主窗口
    mainWindow.show();
    
    if (logger) {
        logger->info("主窗口已显示", "Main");
    }
    
    // 运行应用程序
    int result = app.exec();
    
    if (logger) {
        logger->info("GHTerminal 退出", "Main");
    }
    
    return result;
}
