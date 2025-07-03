#pragma once

#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <memory>

namespace GHTerminal {

class ConfigManager;
class Logger;

/**
 * @brief 应用程序核心类
 * 
 * 负责应用程序的初始化、配置管理和生命周期管理
 */
class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);
    ~Application() override;

    /**
     * @brief 初始化应用程序
     * @return 初始化是否成功
     */
    bool initialize();

    /**
     * @brief 获取配置管理器
     * @return 配置管理器实例
     */
    ConfigManager* configManager() const { return m_configManager.get(); }

    /**
     * @brief 获取日志管理器
     * @return 日志管理器实例
     */
    Logger* logger() const { return m_logger.get(); }

    /**
     * @brief 设置应用程序语言
     * @param language 语言代码 (zh_CN, en_US, ja_JP)
     * @return 设置是否成功
     */
    bool setLanguage(const QString &language);

    /**
     * @brief 获取当前语言
     * @return 当前语言代码
     */
    QString currentLanguage() const;

    /**
     * @brief 获取应用程序版本
     * @return 版本字符串
     */
    static QString version();

    /**
     * @brief 获取应用程序名称
     * @return 应用程序名称
     */
    static QString applicationName();

protected:
    bool event(QEvent *event) override;

private slots:
    void onAboutToQuit();

private:
    void setupApplicationInfo();
    void setupStyle();
    void setupFont();
    void loadTranslations();
    void setupLogging();

private:
    std::unique_ptr<ConfigManager> m_configManager;
    std::unique_ptr<Logger> m_logger;
    std::unique_ptr<QTranslator> m_translator;
    QString m_currentLanguage;
};

} // namespace GHTerminal 