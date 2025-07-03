// doublespinboxdelegate.cpp
#include "doublespinboxdelegate.h"
#include <QDoubleSpinBox>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(double min, double max, double step, int decimals, QObject *parent)
    : QStyledItemDelegate(parent), m_min(min), m_max(max), m_step(step), m_decimals(decimals)
{
}

QWidget *DoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(m_min);
    editor->setMaximum(m_max);
    editor->setSingleStep(m_step);
    editor->setDecimals(m_decimals);

    return editor;
}

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}

void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    double value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}

void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
// 显示文本
QString DoubleSpinBoxDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);
    return QString("%1").arg(value.toDouble(), 0, 'f', m_decimals);
}
