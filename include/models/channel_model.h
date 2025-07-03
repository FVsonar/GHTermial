#pragma once

#include <QAbstractTableModel>
#include <QVector>
#include <QString>
#include <memory>

namespace GHTerminal {

struct ChannelData {
    int id;
    QString name;
    double frequency;
    QString modulation;
    int power;
    bool enabled;
    QString description;
    
    ChannelData() : id(0), frequency(0.0), power(0), enabled(false) {}
    
    bool operator==(const ChannelData &other) const {
        return id == other.id && name == other.name && 
               frequency == other.frequency && modulation == other.modulation &&
               power == other.power && enabled == other.enabled &&
               description == other.description;
    }
    
    bool operator!=(const ChannelData &other) const {
        return !(*this == other);
    }
};

/**
 * @brief 信道数据模型
 * 
 * 管理信道数据的存储、显示和编辑
 */
class ChannelModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column {
        Id = 0,
        Name,
        Frequency,
        Modulation,
        Power,
        Enabled,
        Description,
        ColumnCount
    };

    explicit ChannelModel(QObject *parent = nullptr);
    ~ChannelModel() override;

    // QAbstractTableModel接口
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief 添加信道
     * @param channel 信道数据
     */
    void addChannel(const ChannelData &channel);

    /**
     * @brief 插入信道
     * @param row 插入位置
     * @param channel 信道数据
     */
    void insertChannel(int row, const ChannelData &channel);

    /**
     * @brief 删除信道
     * @param row 删除位置
     */
    void removeChannel(int row);

    /**
     * @brief 获取信道数据
     * @param row 行号
     * @return 信道数据
     */
    ChannelData getChannel(int row) const;

    /**
     * @brief 设置信道数据
     * @param row 行号
     * @param channel 信道数据
     */
    void setChannel(int row, const ChannelData &channel);

    /**
     * @brief 获取所有信道数据
     * @return 信道数据列表
     */
    QVector<ChannelData> getAllChannels() const;

    /**
     * @brief 设置所有信道数据
     * @param channels 信道数据列表
     */
    void setAllChannels(const QVector<ChannelData> &channels);

    /**
     * @brief 清空所有数据
     */
    void clear();

    /**
     * @brief 查找信道
     * @param id 信道ID
     * @return 行号，未找到返回-1
     */
    int findChannel(int id) const;

    /**
     * @brief 查找信道
     * @param name 信道名称
     * @return 行号，未找到返回-1
     */
    int findChannel(const QString &name) const;

    /**
     * @brief 获取启用的信道数量
     * @return 启用信道数量
     */
    int enabledChannelCount() const;

    /**
     * @brief 获取总信道数量
     * @return 总信道数量
     */
    int totalChannelCount() const;

    /**
     * @brief 检查是否有未保存的更改
     * @return 是否有更改
     */
    bool hasChanges() const;

    /**
     * @brief 标记为已保存
     */
    void markAsSaved();

signals:
    void dataChanged();
    void channelAdded(int row);
    void channelRemoved(int row);
    void channelModified(int row);

private:
    QVector<ChannelData> m_channels;
    bool m_hasChanges;
};

} // namespace GHTerminal 