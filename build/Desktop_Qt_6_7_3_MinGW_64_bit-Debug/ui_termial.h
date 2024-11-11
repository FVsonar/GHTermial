/********************************************************************************
** Form generated from reading UI file 'termial.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TERMIAL_H
#define UI_TERMIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_termial
{
public:
    QGroupBox *groupBox_2;
    QPushButton *save_pushButton;
    QPushButton *open_pushButton;
    QGroupBox *groupBox_4;
    QLabel *label_3;
    QLineEdit *tcpPort_lineEdit;
    QPushButton *tcpOpen_pushButton;
    QLabel *label_5;
    QComboBox *connectedDevices_comboBox;
    QLabel *label_6;
    QPushButton *tcpSend_pushButton;
    QPushButton *tcpRead_pushButton;
    QLineEdit *IPLocal_lineEdit;
    QGroupBox *groupBox_5;
    QTableWidget *viewTable_tableWidget;
    QProgressBar *load_progressBar;
    QLabel *label_4;
    QLineEdit *channelNum_lineEdit;
    QPushButton *checkAll_pushButton;
    QPushButton *checkNotAll_pushButton;
    QGroupBox *groupBox;
    QComboBox *serialport_comboBox;
    QPushButton *serialportLink_pushButton;
    QPushButton *send_pushButton;
    QPushButton *read_pushButton;
    QTextEdit *debug;

    void setupUi(QWidget *termial)
    {
        if (termial->objectName().isEmpty())
            termial->setObjectName("termial");
        termial->resize(1200, 800);
        groupBox_2 = new QGroupBox(termial);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(930, 0, 261, 71));
        save_pushButton = new QPushButton(groupBox_2);
        save_pushButton->setObjectName("save_pushButton");
        save_pushButton->setGeometry(QRect(140, 20, 93, 41));
        open_pushButton = new QPushButton(groupBox_2);
        open_pushButton->setObjectName("open_pushButton");
        open_pushButton->setGeometry(QRect(30, 20, 91, 41));
        groupBox_4 = new QGroupBox(termial);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(930, 80, 261, 311));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 70, 91, 31));
        tcpPort_lineEdit = new QLineEdit(groupBox_4);
        tcpPort_lineEdit->setObjectName("tcpPort_lineEdit");
        tcpPort_lineEdit->setGeometry(QRect(130, 70, 101, 31));
        tcpOpen_pushButton = new QPushButton(groupBox_4);
        tcpOpen_pushButton->setObjectName("tcpOpen_pushButton");
        tcpOpen_pushButton->setGeometry(QRect(30, 110, 201, 41));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 160, 81, 31));
        connectedDevices_comboBox = new QComboBox(groupBox_4);
        connectedDevices_comboBox->setObjectName("connectedDevices_comboBox");
        connectedDevices_comboBox->setGeometry(QRect(30, 200, 201, 25));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(28, 30, 61, 31));
        tcpSend_pushButton = new QPushButton(groupBox_4);
        tcpSend_pushButton->setObjectName("tcpSend_pushButton");
        tcpSend_pushButton->setGeometry(QRect(30, 247, 91, 41));
        tcpRead_pushButton = new QPushButton(groupBox_4);
        tcpRead_pushButton->setObjectName("tcpRead_pushButton");
        tcpRead_pushButton->setGeometry(QRect(140, 247, 93, 41));
        IPLocal_lineEdit = new QLineEdit(groupBox_4);
        IPLocal_lineEdit->setObjectName("IPLocal_lineEdit");
        IPLocal_lineEdit->setGeometry(QRect(92, 30, 141, 31));
        groupBox_5 = new QGroupBox(termial);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(10, 0, 911, 791));
        viewTable_tableWidget = new QTableWidget(groupBox_5);
        viewTable_tableWidget->setObjectName("viewTable_tableWidget");
        viewTable_tableWidget->setGeometry(QRect(10, 70, 891, 711));
        load_progressBar = new QProgressBar(groupBox_5);
        load_progressBar->setObjectName("load_progressBar");
        load_progressBar->setGeometry(QRect(80, 20, 341, 31));
        load_progressBar->setValue(24);
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 20, 51, 31));
        channelNum_lineEdit = new QLineEdit(groupBox_5);
        channelNum_lineEdit->setObjectName("channelNum_lineEdit");
        channelNum_lineEdit->setGeometry(QRect(430, 20, 239, 31));
        checkAll_pushButton = new QPushButton(groupBox_5);
        checkAll_pushButton->setObjectName("checkAll_pushButton");
        checkAll_pushButton->setGeometry(QRect(690, 17, 93, 41));
        checkNotAll_pushButton = new QPushButton(groupBox_5);
        checkNotAll_pushButton->setObjectName("checkNotAll_pushButton");
        checkNotAll_pushButton->setGeometry(QRect(800, 17, 93, 41));
        groupBox = new QGroupBox(termial);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(930, 400, 261, 201));
        serialport_comboBox = new QComboBox(groupBox);
        serialport_comboBox->setObjectName("serialport_comboBox");
        serialport_comboBox->setGeometry(QRect(30, 30, 200, 31));
        serialport_comboBox->setMinimumSize(QSize(200, 0));
        serialport_comboBox->setMaximumSize(QSize(200, 16777215));
        serialport_comboBox->setSizeIncrement(QSize(210, 0));
        serialportLink_pushButton = new QPushButton(groupBox);
        serialportLink_pushButton->setObjectName("serialportLink_pushButton");
        serialportLink_pushButton->setGeometry(QRect(30, 80, 201, 41));
        send_pushButton = new QPushButton(groupBox);
        send_pushButton->setObjectName("send_pushButton");
        send_pushButton->setGeometry(QRect(30, 140, 91, 41));
        read_pushButton = new QPushButton(groupBox);
        read_pushButton->setObjectName("read_pushButton");
        read_pushButton->setGeometry(QRect(140, 140, 91, 41));
        debug = new QTextEdit(termial);
        debug->setObjectName("debug");
        debug->setGeometry(QRect(930, 600, 261, 191));

        retranslateUi(termial);

        QMetaObject::connectSlotsByName(termial);
    } // setupUi

    void retranslateUi(QWidget *termial)
    {
        termial->setWindowTitle(QCoreApplication::translate("termial", "termial", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("termial", "\346\226\207\344\273\266", nullptr));
        save_pushButton->setText(QCoreApplication::translate("termial", "\344\277\235\345\255\230", nullptr));
        open_pushButton->setText(QCoreApplication::translate("termial", "\346\211\223\345\274\200", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("termial", "\347\275\221\347\273\234\350\277\236\346\216\245", nullptr));
        label_3->setText(QCoreApplication::translate("termial", "TCP\347\233\221\345\220\254\347\253\257\345\217\243", nullptr));
        tcpPort_lineEdit->setText(QCoreApplication::translate("termial", "8080", nullptr));
        tcpOpen_pushButton->setText(QCoreApplication::translate("termial", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
        label_5->setText(QCoreApplication::translate("termial", "\345\267\262\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        label_6->setText(QCoreApplication::translate("termial", "\346\234\254\346\234\272\345\234\260\345\235\200", nullptr));
        tcpSend_pushButton->setText(QCoreApplication::translate("termial", "\345\217\221\351\200\201", nullptr));
        tcpRead_pushButton->setText(QCoreApplication::translate("termial", "\350\257\273\345\217\226", nullptr));
        IPLocal_lineEdit->setText(QCoreApplication::translate("termial", "192.168.1.68", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("termial", "\346\225\260\346\215\256", nullptr));
        label_4->setText(QCoreApplication::translate("termial", "\350\277\233\345\272\246:", nullptr));
        channelNum_lineEdit->setPlaceholderText(QCoreApplication::translate("termial", "\350\267\263\350\275\254Channel", nullptr));
        checkAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\351\200\211", nullptr));
        checkNotAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\344\270\215\351\200\211", nullptr));
        groupBox->setTitle(QCoreApplication::translate("termial", "\344\270\262\345\217\243\350\277\236\346\216\245", nullptr));
        serialportLink_pushButton->setText(QCoreApplication::translate("termial", "\350\277\236\346\216\245", nullptr));
        send_pushButton->setText(QCoreApplication::translate("termial", "\345\217\221\351\200\201", nullptr));
        read_pushButton->setText(QCoreApplication::translate("termial", "\350\257\273\345\217\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class termial: public Ui_termial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERMIAL_H
