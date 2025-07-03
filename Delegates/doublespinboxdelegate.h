// doublespinboxdelegate.h
#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include <QStyledItemDelegate>

class DoubleSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    DoubleSpinBoxDelegate(double min, double max, double step, int decimals, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    // 可选：自定义显示文本（例如添加 "Hz" 单位）
    QString displayText(const QVariant &value, const QLocale &locale) const override;

private:
    double m_min;
    double m_max;
    double m_step;
    int m_decimals;
};

#endif // DOUBLESPINBOXDELEGATE_H
