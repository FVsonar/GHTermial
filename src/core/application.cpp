#include "core/application.h"
#include "core/config_manager.h"
#include "core/logger.h"

#include <QDir>
#include <QStandardPaths>
#include <QTranslator>
#include <QStyleFactory>
#include <QFont>
#include <QApplication>
#include <QDebug>

namespace GHTerminal {

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_configManager(std::make_unique<ConfigManager>(this))
    , m_logger(std::make_unique<Logger>(this))
    , m_translator(std::make_unique<QTranslator>(this))
{
    setupApplicationInfo();
}

Application::~Application() = default;

bool Application::initialize()
{
    try {
        // 设置样式
        setupStyle();
        
        // 设置字体
        setupFont();
        
        // 初始化日志系统
        setupLogging();
        
        // 加载翻译
        loadTranslations();
        
        // 连接信号
        connect(this, &QApplication::aboutToQuit, this, &Application::onAboutToQuit);
        
        return true;
    } catch (const std::exception &e) {
        qCritical() << "Application initialization failed:" << e.what();
        return false;
    }
}

bool Application::setLanguage(const QString &language)
{
    if (m_currentLanguage == language) {
        return true;
    }
    
    // 移除当前翻译
    if (m_translator && !m_translator->isEmpty()) {
        removeTranslator(m_translator.get());
    }
    
    // 加载新翻译
    QString translationPath = QStandardPaths::locate(
        QStandardPaths::AppDataLocation,
        QString("translations/lang_%1.qm").arg(language)
    );
    
    if (translationPath.isEmpty()) {
        // 尝试从资源文件加载
        translationPath = QString(":/translations/lang_%1.qm").arg(language);
    }
    
    if (m_translator->load(translationPath)) {
        installTranslator(m_translator.get());
        m_currentLanguage = language;
        
        // 保存语言设置
        if (m_configManager) {
            m_configManager->setLanguage(language);
        }
        
        return true;
    } else {
        qWarning() << "Failed to load translation:" << translationPath;
        return false;
    }
}

QString Application::currentLanguage() const
{
    return m_currentLanguage;
}

QString Application::version()
{
    return "1.0.0";
}

QString Application::applicationName()
{
    return "GHTerminal";
}

bool Application::event(QEvent *event)
{
    return QApplication::event(event);
}

void Application::onAboutToQuit()
{
    if (m_logger) {
        m_logger->info("Application shutting down", "Application");
    }
    
    if (m_configManager) {
        m_configManager->sync();
    }
}

void Application::setupApplicationInfo()
{
    setApplicationName(applicationName());
    setApplicationVersion(version());
    setOrganizationName("FVsonar");
    setOrganizationDomain("fvsonar.github.io");
    setApplicationDisplayName("GHTerminal - 串口终端工具");
}

void Application::setupStyle()
{
    // 使用Fusion样式作为基础
    setStyle(QStyleFactory::create("Fusion"));
    
    // 应用主题
    if (m_configManager) {
        QString theme = m_configManager->theme();
        if (!theme.isEmpty()) {
            // 这里可以加载自定义样式表
            QString stylePath = QString(":/styles/%1.qss").arg(theme);
            QFile styleFile(stylePath);
            if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
                QString styleSheet = styleFile.readAll();
                setStyleSheet(styleSheet);
            }
        }
    }
}

void Application::setupFont()
{
    QFont font = this->font();
    font.setFamily("Microsoft YaHei");
    font.setPointSize(12);
    setFont(font);
}

void Application::loadTranslations()
{
    // 从配置加载语言设置
    QString language = "zh_CN"; // 默认中文
    if (m_configManager) {
        language = m_configManager->language();
    }
    
    setLanguage(language);
}

void Application::setupLogging()
{
    if (!m_logger) {
        return;
    }
    
    // 获取日志文件路径
    QString logDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/logs";
    QDir().mkpath(logDir);
    
    QString logFile = logDir + "/ghterminal.log";
    
    // 初始化日志系统
    if (!m_logger->initialize(logFile)) {
        qWarning() << "Failed to initialize logger";
        return;
    }
    
    // 设置日志级别
    if (m_configManager) {
        bool enableLogging = m_configManager->enableLogging();
        m_logger->setFileOutput(enableLogging);
    }
    
    m_logger->info("Application initialized", "Application");
}

} // namespace GHTerminal 