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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_termial
{
public:
    QGroupBox *file_groupBox;
    QPushButton *save_pushButton;
    QPushButton *open_pushButton;
    QGroupBox *network_groupBox;
    QLabel *label_3;
    QLineEdit *tcpPort_lineEdit;
    QPushButton *tcpOpen_pushButton;
    QLabel *label_5;
    QComboBox *connectedDevices_comboBox;
    QLabel *label_6;
    QPushButton *tcpSend_pushButton;
    QPushButton *tcpRead_pushButton;
    QLineEdit *IPLocal_lineEdit;
    QGroupBox *data_groupBox;
    QTableWidget *viewTable_tableWidget;
    QProgressBar *load_progressBar;
    QLineEdit *channelNum_lineEdit;
    QPushButton *checkAll_pushButton;
    QPushButton *checkNotAll_pushButton;
    QGroupBox *serialport_groupBox;
    QComboBox *serialport_comboBox;
    QPushButton *serialportLink_pushButton;
    QPushButton *send_pushButton;
    QPushButton *read_pushButton;
    QPushButton *serialportFlash_pushButton;
    QGroupBox *language_groupBox;
    QComboBox *language_comboBox;

    void setupUi(QWidget *termial)
    {
        if (termial->objectName().isEmpty())
            termial->setObjectName("termial");
        termial->resize(1200, 800);
#if QT_CONFIG(tooltip)
        termial->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        file_groupBox = new QGroupBox(termial);
        file_groupBox->setObjectName("file_groupBox");
        file_groupBox->setGeometry(QRect(930, 100, 261, 91));
        save_pushButton = new QPushButton(file_groupBox);
        save_pushButton->setObjectName("save_pushButton");
        save_pushButton->setGeometry(QRect(132, 30, 121, 41));
        open_pushButton = new QPushButton(file_groupBox);
        open_pushButton->setObjectName("open_pushButton");
        open_pushButton->setGeometry(QRect(10, 30, 121, 41));
        network_groupBox = new QGroupBox(termial);
        network_groupBox->setObjectName("network_groupBox");
        network_groupBox->setGeometry(QRect(930, 200, 261, 361));
        label_3 = new QLabel(network_groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 100, 241, 21));
        tcpPort_lineEdit = new QLineEdit(network_groupBox);
        tcpPort_lineEdit->setObjectName("tcpPort_lineEdit");
        tcpPort_lineEdit->setGeometry(QRect(10, 130, 241, 31));
#if QT_CONFIG(tooltip)
        tcpPort_lineEdit->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        tcpOpen_pushButton = new QPushButton(network_groupBox);
        tcpOpen_pushButton->setObjectName("tcpOpen_pushButton");
        tcpOpen_pushButton->setGeometry(QRect(10, 170, 241, 41));
        label_5 = new QLabel(network_groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 220, 241, 31));
        connectedDevices_comboBox = new QComboBox(network_groupBox);
        connectedDevices_comboBox->setObjectName("connectedDevices_comboBox");
        connectedDevices_comboBox->setGeometry(QRect(10, 260, 241, 31));
#if QT_CONFIG(tooltip)
        connectedDevices_comboBox->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        label_6 = new QLabel(network_groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 241, 21));
        tcpSend_pushButton = new QPushButton(network_groupBox);
        tcpSend_pushButton->setObjectName("tcpSend_pushButton");
        tcpSend_pushButton->setGeometry(QRect(10, 300, 121, 41));
        tcpRead_pushButton = new QPushButton(network_groupBox);
        tcpRead_pushButton->setObjectName("tcpRead_pushButton");
        tcpRead_pushButton->setGeometry(QRect(132, 300, 121, 41));
        IPLocal_lineEdit = new QLineEdit(network_groupBox);
        IPLocal_lineEdit->setObjectName("IPLocal_lineEdit");
        IPLocal_lineEdit->setGeometry(QRect(10, 60, 241, 31));
#if QT_CONFIG(tooltip)
        IPLocal_lineEdit->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        data_groupBox = new QGroupBox(termial);
        data_groupBox->setObjectName("data_groupBox");
        data_groupBox->setGeometry(QRect(10, 0, 911, 791));
        viewTable_tableWidget = new QTableWidget(data_groupBox);
        viewTable_tableWidget->setObjectName("viewTable_tableWidget");
        viewTable_tableWidget->setGeometry(QRect(10, 70, 891, 711));
        load_progressBar = new QProgressBar(data_groupBox);
        load_progressBar->setObjectName("load_progressBar");
        load_progressBar->setGeometry(QRect(590, 20, 311, 31));
        load_progressBar->setValue(24);
        channelNum_lineEdit = new QLineEdit(data_groupBox);
        channelNum_lineEdit->setObjectName("channelNum_lineEdit");
        channelNum_lineEdit->setGeometry(QRect(340, 20, 239, 31));
        checkAll_pushButton = new QPushButton(data_groupBox);
        checkAll_pushButton->setObjectName("checkAll_pushButton");
        checkAll_pushButton->setGeometry(QRect(10, 17, 161, 41));
        checkNotAll_pushButton = new QPushButton(data_groupBox);
        checkNotAll_pushButton->setObjectName("checkNotAll_pushButton");
        checkNotAll_pushButton->setGeometry(QRect(170, 17, 161, 41));
        serialport_groupBox = new QGroupBox(termial);
        serialport_groupBox->setObjectName("serialport_groupBox");
        serialport_groupBox->setGeometry(QRect(930, 570, 261, 221));
        serialport_comboBox = new QComboBox(serialport_groupBox);
        serialport_comboBox->setObjectName("serialport_comboBox");
        serialport_comboBox->setEnabled(true);
        serialport_comboBox->setGeometry(QRect(9, 40, 241, 31));
        serialport_comboBox->setMinimumSize(QSize(0, 0));
        serialport_comboBox->setMaximumSize(QSize(16777215, 16777215));
        serialport_comboBox->setSizeIncrement(QSize(210, 0));
#if QT_CONFIG(tooltip)
        serialport_comboBox->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        serialportLink_pushButton = new QPushButton(serialport_groupBox);
        serialportLink_pushButton->setObjectName("serialportLink_pushButton");
        serialportLink_pushButton->setGeometry(QRect(10, 110, 241, 41));
        send_pushButton = new QPushButton(serialport_groupBox);
        send_pushButton->setObjectName("send_pushButton");
        send_pushButton->setGeometry(QRect(10, 160, 121, 41));
        read_pushButton = new QPushButton(serialport_groupBox);
        read_pushButton->setObjectName("read_pushButton");
        read_pushButton->setGeometry(QRect(130, 160, 121, 41));
        serialportFlash_pushButton = new QPushButton(serialport_groupBox);
        serialportFlash_pushButton->setObjectName("serialportFlash_pushButton");
        serialportFlash_pushButton->setGeometry(QRect(130, 70, 121, 31));
        language_groupBox = new QGroupBox(termial);
        language_groupBox->setObjectName("language_groupBox");
        language_groupBox->setGeometry(QRect(930, 0, 261, 81));
        language_comboBox = new QComboBox(language_groupBox);
        language_comboBox->setObjectName("language_comboBox");
        language_comboBox->setGeometry(QRect(10, 30, 241, 41));

        retranslateUi(termial);

        QMetaObject::connectSlotsByName(termial);
    } // setupUi

    void retranslateUi(QWidget *termial)
    {
        termial->setWindowTitle(QCoreApplication::translate("termial", "termial", nullptr));
        file_groupBox->setTitle(QCoreApplication::translate("termial", "\346\226\207\344\273\266", nullptr));
        save_pushButton->setText(QCoreApplication::translate("termial", "\344\277\235\345\255\230", nullptr));
        open_pushButton->setText(QCoreApplication::translate("termial", "\346\211\223\345\274\200", nullptr));
        network_groupBox->setTitle(QCoreApplication::translate("termial", "\347\275\221\347\273\234\350\277\236\346\216\245", nullptr));
        label_3->setText(QCoreApplication::translate("termial", "TCP\347\233\221\345\220\254\347\253\257\345\217\243", nullptr));
        tcpPort_lineEdit->setText(QCoreApplication::translate("termial", "8080", nullptr));
        tcpOpen_pushButton->setText(QCoreApplication::translate("termial", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
        label_5->setText(QCoreApplication::translate("termial", "\345\267\262\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        label_6->setText(QCoreApplication::translate("termial", "\346\234\254\346\234\272\345\234\260\345\235\200", nullptr));
        tcpSend_pushButton->setText(QCoreApplication::translate("termial", "\345\217\221\351\200\201", nullptr));
        tcpRead_pushButton->setText(QCoreApplication::translate("termial", "\350\257\273\345\217\226", nullptr));
        IPLocal_lineEdit->setText(QCoreApplication::translate("termial", "192.168.1.68", nullptr));
        data_groupBox->setTitle(QCoreApplication::translate("termial", "\346\225\260\346\215\256", nullptr));
        channelNum_lineEdit->setPlaceholderText(QCoreApplication::translate("termial", "\350\267\263\350\275\254Channel", nullptr));
        checkAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\351\200\211", nullptr));
        checkNotAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\344\270\215\351\200\211", nullptr));
        serialport_groupBox->setTitle(QCoreApplication::translate("termial", "\344\270\262\345\217\243\350\277\236\346\216\245", nullptr));
        serialportLink_pushButton->setText(QCoreApplication::translate("termial", "\350\277\236\346\216\245", nullptr));
        send_pushButton->setText(QCoreApplication::translate("termial", "\345\217\221\351\200\201", nullptr));
        read_pushButton->setText(QCoreApplication::translate("termial", "\350\257\273\345\217\226", nullptr));
        serialportFlash_pushButton->setText(QCoreApplication::translate("termial", "\345\210\267\346\226\260", nullptr));
        language_groupBox->setTitle(QCoreApplication::translate("termial", "\350\257\255\350\250\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class termial: public Ui_termial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERMIAL_H
