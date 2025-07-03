#pragma once

#include <QObject>
#include <QSettings>
#include <QVariant>
#include <QString>
#include <memory>

namespace GHTerminal {

/**
 * @brief 配置管理器
 * 
 * 负责应用程序配置的读取、写入和管理
 */
class ConfigManager : public QObject
{
    Q_OBJECT

public:
    explicit ConfigManager(QObject *parent = nullptr);
    ~ConfigManager() override;

    /**
     * @brief 设置配置值
     * @param key 配置键
     * @param value 配置值
     */
    void setValue(const QString &key, const QVariant &value);

    /**
     * @brief 获取配置值
     * @param key 配置键
     * @param defaultValue 默认值
     * @return 配置值
     */
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

    /**
     * @brief 检查配置是否存在
     * @param key 配置键
     * @return 是否存在
     */
    bool contains(const QString &key) const;

    /**
     * @brief 删除配置
     * @param key 配置键
     */
    void remove(const QString &key);

    /**
     * @brief 清空所有配置
     */
    void clear();

    /**
     * @brief 同步配置到磁盘
     */
    void sync();

    /**
     * @brief 重置为默认配置
     */
    void resetToDefaults();

    // 串口配置
    QString serialPort() const;
    void setSerialPort(const QString &port);
    
    int baudRate() const;
    void setBaudRate(int baudRate);
    
    int dataBits() const;
    void setDataBits(int dataBits);
    
    QString parity() const;
    void setParity(const QString &parity);
    
    QString stopBits() const;
    void setStopBits(const QString &stopBits);
    
    QString flowControl() const;
    void setFlowControl(const QString &flowControl);

    // 界面配置
    QString language() const;
    void setLanguage(const QString &language);
    
    QString theme() const;
    void setTheme(const QString &theme);
    
    bool autoConnect() const;
    void setAutoConnect(bool autoConnect);
    
    bool autoSave() const;
    void setAutoSave(bool autoSave);

    // 通信配置
    int timeout() const;
    void setTimeout(int timeout);
    
    int retryCount() const;
    void setRetryCount(int retryCount);
    
    bool enableLogging() const;
    void setEnableLogging(bool enable);

signals:
    void configChanged(const QString &key, const QVariant &value);

private:
    void loadDefaults();
    QString configFilePath() const;

private:
    std::unique_ptr<QSettings> m_settings;
};

} // namespace GHTerminal 