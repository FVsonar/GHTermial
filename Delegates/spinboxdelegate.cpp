#include "spinboxdelegate.h"
#include <QSpinBox>

SpinBoxDelegate::SpinBoxDelegate(int min, int max, QObject *parent)
    : QStyledItemDelegate(parent), m_min(min), m_max(max)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/*option*/,
                                       const QModelIndex &/*index*/) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(m_min);
    editor->setMaximum(m_max);
    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor,
                                   QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}
