#include "comboboxdelegate.h"
#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(const QStringList &items, QObject *parent)
    : QStyledItemDelegate(parent), m_items(items)
{
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &/*option*/,
                                        const QModelIndex &/*index*/) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItems(m_items);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int currentIndex = comboBox->currentIndex(); // 获取当前选中索引
    model->setData(index, currentIndex, Qt::EditRole);  // 存储索引
    model->setData(index, comboBox->currentText(), Qt::DisplayRole); // 存储文本
}
