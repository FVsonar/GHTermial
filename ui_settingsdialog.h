/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QRadioButton *network_radioButton;
    QRadioButton *SerialPort_radioButton;
    QLabel *label_3;
    QFrame *line;
    QLineEdit *IPLocal_lineEdit;
    QLabel *label_4;
    QLineEdit *tcpPort_lineEdit;
    QFrame *line_2;
    QLabel *label_5;
    QComboBox *serialport_comboBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName("SettingsDialog");
        SettingsDialog->resize(403, 368);
        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(150, 300, 221, 41));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(SettingsDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 10, 69, 19));
        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 81, 21));
        network_radioButton = new QRadioButton(SettingsDialog);
        network_radioButton->setObjectName("network_radioButton");
        network_radioButton->setEnabled(true);
        network_radioButton->setGeometry(QRect(110, 60, 120, 25));
        network_radioButton->setChecked(true);
        SerialPort_radioButton = new QRadioButton(SettingsDialog);
        SerialPort_radioButton->setObjectName("SerialPort_radioButton");
        SerialPort_radioButton->setGeometry(QRect(240, 60, 120, 25));
        label_3 = new QLabel(SettingsDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 120, 69, 21));
        line = new QFrame(SettingsDialog);
        line->setObjectName("line");
        line->setGeometry(QRect(10, 100, 371, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        IPLocal_lineEdit = new QLineEdit(SettingsDialog);
        IPLocal_lineEdit->setObjectName("IPLocal_lineEdit");
        IPLocal_lineEdit->setGeometry(QRect(100, 120, 191, 27));
        label_4 = new QLabel(SettingsDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 170, 69, 21));
        tcpPort_lineEdit = new QLineEdit(SettingsDialog);
        tcpPort_lineEdit->setObjectName("tcpPort_lineEdit");
        tcpPort_lineEdit->setGeometry(QRect(100, 170, 191, 27));
        line_2 = new QFrame(SettingsDialog);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(10, 210, 371, 16));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label_5 = new QLabel(SettingsDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 250, 71, 19));
        serialport_comboBox = new QComboBox(SettingsDialog);
        serialport_comboBox->setObjectName("serialport_comboBox");
        serialport_comboBox->setGeometry(QRect(100, 250, 191, 27));

        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SettingsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SettingsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SettingsDialog", "\351\205\215\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsDialog", "\346\250\241\345\274\217\351\200\211\346\213\251\357\274\232", nullptr));
        network_radioButton->setText(QCoreApplication::translate("SettingsDialog", "\347\275\221\347\273\234", nullptr));
        SerialPort_radioButton->setText(QCoreApplication::translate("SettingsDialog", "\344\270\262\345\217\243", nullptr));
        label_3->setText(QCoreApplication::translate("SettingsDialog", "\346\234\254\345\234\260IP\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("SettingsDialog", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("SettingsDialog", "\344\270\262\345\217\243\351\200\211\346\213\251\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
