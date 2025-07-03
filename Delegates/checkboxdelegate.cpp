#include "checkboxdelegate.h"
#include <QCheckBox>
#include <QApplication>
#include <QPainter>
#include <QStyleOptionButton>

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

// 禁用原生编辑器创建
QWidget *CheckBoxDelegate::createEditor(QWidget *, const QStyleOptionViewItem &,
                                        const QModelIndex &) const {
    return nullptr; // 返回空指针禁用默认编辑器
}

void CheckBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    bool value = index.model()->data(index, Qt::EditRole).toBool();
    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
    checkBox->setChecked(value);
}

void CheckBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const {
    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
    model->setData(index, checkBox->isChecked() ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
}



bool CheckBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &/*option*/,
                                   const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        // 获取当前状态（使用CheckStateRole）
        Qt::CheckState state = static_cast<Qt::CheckState>(
            model->data(index, Qt::CheckStateRole).toInt());

        // 切换状态
        Qt::CheckState newState = (state == Qt::Checked) ?
                                      Qt::Unchecked : Qt::Checked;

        // 使用EditRole确保触发数据变更信号
        model->setData(index, newState, Qt::CheckStateRole);
        return true;
    }
    return false;
}
