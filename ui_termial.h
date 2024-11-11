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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_termial
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *data;
    QVBoxLayout *verticalLayout_2;
    QWidget *tools;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *checkAll_pushButton;
    QPushButton *checkNotAll_pushButton;
    QLineEdit *channelNum_lineEdit;
    QProgressBar *load_progressBar;
    QTableWidget *viewTable_tableWidget;
    QFrame *line_4;
    QWidget *control;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QComboBox *language_comboBox;
    QFrame *line_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *save_pushButton;
    QPushButton *open_pushButton;
    QFrame *line;
    QLabel *label_4;
    QLabel *label_7;
    QLineEdit *IPLocal_lineEdit;
    QLabel *label_8;
    QLineEdit *tcpPort_lineEdit;
    QPushButton *tcpOpen_pushButton;
    QLabel *label_9;
    QComboBox *connectedDevices_comboBox;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *tcpSend_pushButton;
    QPushButton *tcpRead_pushButton;
    QFrame *line_3;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *serialport_comboBox;
    QPushButton *serialportFlash_pushButton;
    QPushButton *serialportLink_pushButton;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *send_pushButton;
    QPushButton *read_pushButton;

    void setupUi(QWidget *termial)
    {
        if (termial->objectName().isEmpty())
            termial->setObjectName("termial");
        termial->resize(1125, 664);
#if QT_CONFIG(tooltip)
        termial->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        termial->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(termial);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        data = new QWidget(termial);
        data->setObjectName("data");
        verticalLayout_2 = new QVBoxLayout(data);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tools = new QWidget(data);
        tools->setObjectName("tools");
        horizontalLayout_2 = new QHBoxLayout(tools);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        checkAll_pushButton = new QPushButton(tools);
        checkAll_pushButton->setObjectName("checkAll_pushButton");

        horizontalLayout_2->addWidget(checkAll_pushButton);

        checkNotAll_pushButton = new QPushButton(tools);
        checkNotAll_pushButton->setObjectName("checkNotAll_pushButton");

        horizontalLayout_2->addWidget(checkNotAll_pushButton);

        channelNum_lineEdit = new QLineEdit(tools);
        channelNum_lineEdit->setObjectName("channelNum_lineEdit");

        horizontalLayout_2->addWidget(channelNum_lineEdit);

        load_progressBar = new QProgressBar(tools);
        load_progressBar->setObjectName("load_progressBar");
        load_progressBar->setValue(24);

        horizontalLayout_2->addWidget(load_progressBar);


        verticalLayout_2->addWidget(tools);

        viewTable_tableWidget = new QTableWidget(data);
        viewTable_tableWidget->setObjectName("viewTable_tableWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(viewTable_tableWidget->sizePolicy().hasHeightForWidth());
        viewTable_tableWidget->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(viewTable_tableWidget);


        horizontalLayout->addWidget(data);

        line_4 = new QFrame(termial);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::VLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_4);

        control = new QWidget(termial);
        control->setObjectName("control");
        verticalLayout_3 = new QVBoxLayout(control);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(control);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        language_comboBox = new QComboBox(control);
        language_comboBox->setObjectName("language_comboBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(language_comboBox->sizePolicy().hasHeightForWidth());
        language_comboBox->setSizePolicy(sizePolicy2);
        language_comboBox->setMinimumSize(QSize(150, 0));

        verticalLayout_3->addWidget(language_comboBox);

        line_2 = new QFrame(control);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_2);

        label_2 = new QLabel(control);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        save_pushButton = new QPushButton(control);
        save_pushButton->setObjectName("save_pushButton");
        sizePolicy2.setHeightForWidth(save_pushButton->sizePolicy().hasHeightForWidth());
        save_pushButton->setSizePolicy(sizePolicy2);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        save_pushButton->setIcon(icon);

        horizontalLayout_3->addWidget(save_pushButton);

        open_pushButton = new QPushButton(control);
        open_pushButton->setObjectName("open_pushButton");
        sizePolicy2.setHeightForWidth(open_pushButton->sizePolicy().hasHeightForWidth());
        open_pushButton->setSizePolicy(sizePolicy2);
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs));
        open_pushButton->setIcon(icon1);

        horizontalLayout_3->addWidget(open_pushButton);


        verticalLayout_3->addLayout(horizontalLayout_3);

        line = new QFrame(control);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line);

        label_4 = new QLabel(control);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        label_7 = new QLabel(control);
        label_7->setObjectName("label_7");
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label_7);

        IPLocal_lineEdit = new QLineEdit(control);
        IPLocal_lineEdit->setObjectName("IPLocal_lineEdit");
        sizePolicy2.setHeightForWidth(IPLocal_lineEdit->sizePolicy().hasHeightForWidth());
        IPLocal_lineEdit->setSizePolicy(sizePolicy2);
#if QT_CONFIG(tooltip)
        IPLocal_lineEdit->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        verticalLayout_3->addWidget(IPLocal_lineEdit);

        label_8 = new QLabel(control);
        label_8->setObjectName("label_8");
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label_8);

        tcpPort_lineEdit = new QLineEdit(control);
        tcpPort_lineEdit->setObjectName("tcpPort_lineEdit");
        sizePolicy2.setHeightForWidth(tcpPort_lineEdit->sizePolicy().hasHeightForWidth());
        tcpPort_lineEdit->setSizePolicy(sizePolicy2);
#if QT_CONFIG(tooltip)
        tcpPort_lineEdit->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        verticalLayout_3->addWidget(tcpPort_lineEdit);

        tcpOpen_pushButton = new QPushButton(control);
        tcpOpen_pushButton->setObjectName("tcpOpen_pushButton");
        sizePolicy2.setHeightForWidth(tcpOpen_pushButton->sizePolicy().hasHeightForWidth());
        tcpOpen_pushButton->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(tcpOpen_pushButton);

        label_9 = new QLabel(control);
        label_9->setObjectName("label_9");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(label_9);

        connectedDevices_comboBox = new QComboBox(control);
        connectedDevices_comboBox->setObjectName("connectedDevices_comboBox");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(connectedDevices_comboBox->sizePolicy().hasHeightForWidth());
        connectedDevices_comboBox->setSizePolicy(sizePolicy4);
#if QT_CONFIG(tooltip)
        connectedDevices_comboBox->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        verticalLayout_3->addWidget(connectedDevices_comboBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        tcpSend_pushButton = new QPushButton(control);
        tcpSend_pushButton->setObjectName("tcpSend_pushButton");
        sizePolicy4.setHeightForWidth(tcpSend_pushButton->sizePolicy().hasHeightForWidth());
        tcpSend_pushButton->setSizePolicy(sizePolicy4);
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::MailSend));
        tcpSend_pushButton->setIcon(icon2);

        horizontalLayout_4->addWidget(tcpSend_pushButton);

        tcpRead_pushButton = new QPushButton(control);
        tcpRead_pushButton->setObjectName("tcpRead_pushButton");
        sizePolicy4.setHeightForWidth(tcpRead_pushButton->sizePolicy().hasHeightForWidth());
        tcpRead_pushButton->setSizePolicy(sizePolicy4);
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::SystemSearch));
        tcpRead_pushButton->setIcon(icon3);

        horizontalLayout_4->addWidget(tcpRead_pushButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        line_3 = new QFrame(control);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_3);

        label_10 = new QLabel(control);
        label_10->setObjectName("label_10");
        sizePolicy3.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy3);
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        serialport_comboBox = new QComboBox(control);
        serialport_comboBox->setObjectName("serialport_comboBox");
        serialport_comboBox->setEnabled(true);
        sizePolicy4.setHeightForWidth(serialport_comboBox->sizePolicy().hasHeightForWidth());
        serialport_comboBox->setSizePolicy(sizePolicy4);
        serialport_comboBox->setMinimumSize(QSize(0, 0));
        serialport_comboBox->setMaximumSize(QSize(16777215, 16777215));
        serialport_comboBox->setSizeIncrement(QSize(210, 0));
#if QT_CONFIG(tooltip)
        serialport_comboBox->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        horizontalLayout_7->addWidget(serialport_comboBox);

        serialportFlash_pushButton = new QPushButton(control);
        serialportFlash_pushButton->setObjectName("serialportFlash_pushButton");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(serialportFlash_pushButton->sizePolicy().hasHeightForWidth());
        serialportFlash_pushButton->setSizePolicy(sizePolicy5);
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::SyncSynchronizing));
        serialportFlash_pushButton->setIcon(icon4);

        horizontalLayout_7->addWidget(serialportFlash_pushButton);


        verticalLayout_3->addLayout(horizontalLayout_7);

        serialportLink_pushButton = new QPushButton(control);
        serialportLink_pushButton->setObjectName("serialportLink_pushButton");
        sizePolicy2.setHeightForWidth(serialportLink_pushButton->sizePolicy().hasHeightForWidth());
        serialportLink_pushButton->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(serialportLink_pushButton);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        send_pushButton = new QPushButton(control);
        send_pushButton->setObjectName("send_pushButton");
        sizePolicy2.setHeightForWidth(send_pushButton->sizePolicy().hasHeightForWidth());
        send_pushButton->setSizePolicy(sizePolicy2);
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSend));
        send_pushButton->setIcon(icon5);

        horizontalLayout_5->addWidget(send_pushButton);

        read_pushButton = new QPushButton(control);
        read_pushButton->setObjectName("read_pushButton");
        sizePolicy2.setHeightForWidth(read_pushButton->sizePolicy().hasHeightForWidth());
        read_pushButton->setSizePolicy(sizePolicy2);
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        read_pushButton->setIcon(icon6);

        horizontalLayout_5->addWidget(read_pushButton);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout->addWidget(control);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(termial);

        QMetaObject::connectSlotsByName(termial);
    } // setupUi

    void retranslateUi(QWidget *termial)
    {
        termial->setWindowTitle(QCoreApplication::translate("termial", "termial", nullptr));
        checkAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\351\200\211", nullptr));
        checkNotAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\344\270\215\351\200\211", nullptr));
        channelNum_lineEdit->setPlaceholderText(QCoreApplication::translate("termial", "\350\267\263\350\275\254Channel", nullptr));
        label->setText(QCoreApplication::translate("termial", "\350\257\255\350\250\200", nullptr));
        label_2->setText(QCoreApplication::translate("termial", "\346\226\207\344\273\266", nullptr));
        save_pushButton->setText(QCoreApplication::translate("termial", "\344\277\235\345\255\230", nullptr));
        open_pushButton->setText(QCoreApplication::translate("termial", "\346\211\223\345\274\200", nullptr));
        label_4->setText(QCoreApplication::translate("termial", "\347\275\221\347\273\234\350\277\236\346\216\245", nullptr));
        label_7->setText(QCoreApplication::translate("termial", "\346\234\254\346\234\272\345\234\260\345\235\200", nullptr));
        IPLocal_lineEdit->setText(QCoreApplication::translate("termial", "192.168.1.68", nullptr));
        label_8->setText(QCoreApplication::translate("termial", "TCP\347\253\257\345\217\243", nullptr));
        tcpPort_lineEdit->setText(QCoreApplication::translate("termial", "8080", nullptr));
        tcpOpen_pushButton->setText(QCoreApplication::translate("termial", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
        label_9->setText(QCoreApplication::translate("termial", "\345\267\262\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        tcpSend_pushButton->setText(QCoreApplication::translate("termial", "\345\217\221\351\200\201", nullptr));
        tcpRead_pushButton->setText(QCoreApplication::translate("termial", "\350\257\273\345\217\226", nullptr));
        label_10->setText(QCoreApplication::translate("termial", "\344\270\262\345\217\243\350\277\236\346\216\245", nullptr));
        serialportFlash_pushButton->setText(QString());
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
