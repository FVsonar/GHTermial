#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>

class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckBoxDelegate(QObject *parent = nullptr);

    // 必须重写的虚函数
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;


    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index);
};

#endif // CHECKBOXDELEGATE_H
