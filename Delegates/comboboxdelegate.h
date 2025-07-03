#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QStringList>

class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(const QStringList &items,
                              QObject *parent = nullptr);

    // 必须重写的虚函数
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

private:
    QStringList m_items;
};

#endif // COMBOBOXDELEGATE_H
