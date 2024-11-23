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
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_termial
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QWidget *data;
    QVBoxLayout *verticalLayout_2;
    QWidget *tools;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *checkAll_pushButton;
    QPushButton *checkNotAll_pushButton;
    QLineEdit *channelNum_lineEdit;
    QProgressBar *load_progressBar;
    QTableWidget *viewTable_tableWidget;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_13;
    QLabel *tunerCurrentModel_label;
    QFrame *line_7;
    QRadioButton *auto_radioButton;
    QRadioButton *start_radioButton;
    QRadioButton *close_radioButton;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QLCDNumber *voltage_lcdNumber;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *swtValue_label;
    QGridLayout *gridLayout_2;
    QLabel *label_24;
    QLabel *label_14;
    QLabel *label_23;
    QLabel *label_21;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_19;
    QLabel *label_22;
    QLabel *label_20;
    QLabel *label_27;
    QSlider *swr_horizontalSlider;
    QHBoxLayout *horizontalLayout_16;
    QDial *swtValue_dial;
    QHBoxLayout *horizontalLayout_14;
    QDoubleSpinBox *swtValue_doubleSpinBox;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *SWT_pushButton;
    QFrame *line_6;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLabel *PPc_label;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_28;
    QSlider *PPc_horizontalSlider;
    QSpinBox *PPcv_spinBox;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QLabel *Swc_label;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_29;
    QSlider *Swc_horizontalSlider;
    QSpinBox *Swcv_spinBox;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QLabel *Vc_label;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_30;
    QSlider *Vc_horizontalSlider;
    QSpinBox *Vcv_spinBox;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *ATC_pushButton;
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
    QFrame *line_3;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *serialport_comboBox;
    QPushButton *serialportFlash_pushButton;
    QPushButton *serialportLink_pushButton;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *send_btn;
    QPushButton *read_btn;

    void setupUi(QWidget *termial)
    {
        if (termial->objectName().isEmpty())
            termial->setObjectName("termial");
        termial->resize(804, 781);
#if QT_CONFIG(tooltip)
        termial->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        termial->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(termial);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        tabWidget = new QTabWidget(termial);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName("verticalLayout");
        data = new QWidget(tab);
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
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(viewTable_tableWidget->sizePolicy().hasHeightForWidth());
        viewTable_tableWidget->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(viewTable_tableWidget);


        verticalLayout->addWidget(data);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        gridLayout_3 = new QGridLayout(tab_4);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_13 = new QLabel(tab_4);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_10->addWidget(label_13);

        tunerCurrentModel_label = new QLabel(tab_4);
        tunerCurrentModel_label->setObjectName("tunerCurrentModel_label");
        tunerCurrentModel_label->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_10->addWidget(tunerCurrentModel_label);


        verticalLayout_4->addLayout(horizontalLayout_10);

        line_7 = new QFrame(tab_4);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::HLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_7);

        auto_radioButton = new QRadioButton(tab_4);
        auto_radioButton->setObjectName("auto_radioButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(auto_radioButton->sizePolicy().hasHeightForWidth());
        auto_radioButton->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(auto_radioButton);

        start_radioButton = new QRadioButton(tab_4);
        start_radioButton->setObjectName("start_radioButton");
        sizePolicy2.setHeightForWidth(start_radioButton->sizePolicy().hasHeightForWidth());
        start_radioButton->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(start_radioButton);

        close_radioButton = new QRadioButton(tab_4);
        close_radioButton->setObjectName("close_radioButton");
        sizePolicy2.setHeightForWidth(close_radioButton->sizePolicy().hasHeightForWidth());
        close_radioButton->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(close_radioButton);


        gridLayout_3->addLayout(verticalLayout_4, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_5 = new QLabel(tab_4);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_5);

        voltage_lcdNumber = new QLCDNumber(tab_4);
        voltage_lcdNumber->setObjectName("voltage_lcdNumber");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(voltage_lcdNumber->sizePolicy().hasHeightForWidth());
        voltage_lcdNumber->setSizePolicy(sizePolicy4);
        voltage_lcdNumber->setMinimumSize(QSize(200, 0));

        verticalLayout_5->addWidget(voltage_lcdNumber);


        gridLayout_3->addLayout(verticalLayout_5, 0, 1, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(tab_4);
        label_3->setObjectName("label_3");
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_4->addWidget(label_3);

        swtValue_label = new QLabel(tab_4);
        swtValue_label->setObjectName("swtValue_label");
        sizePolicy3.setHeightForWidth(swtValue_label->sizePolicy().hasHeightForWidth());
        swtValue_label->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(swtValue_label);


        verticalLayout_6->addLayout(horizontalLayout_4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_24 = new QLabel(tab_4);
        label_24->setObjectName("label_24");
        label_24->setStyleSheet(QString::fromUtf8("QLabel#label_24{\n"
"	color:#ff1418\n"
"}"));
        label_24->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_24, 0, 10, 1, 1);

        label_14 = new QLabel(tab_4);
        label_14->setObjectName("label_14");

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        label_23 = new QLabel(tab_4);
        label_23->setObjectName("label_23");
        label_23->setStyleSheet(QString::fromUtf8("QLabel#label_23{\n"
"	color:#ff1418\n"
"}"));
        label_23->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_23, 0, 9, 1, 1);

        label_21 = new QLabel(tab_4);
        label_21->setObjectName("label_21");
        label_21->setStyleSheet(QString::fromUtf8("QLabel#label_21{\n"
"	color:#ff1418\n"
"}"));
        label_21->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_21, 0, 7, 1, 1);

        label_16 = new QLabel(tab_4);
        label_16->setObjectName("label_16");

        gridLayout_2->addWidget(label_16, 0, 2, 1, 1);

        label_15 = new QLabel(tab_4);
        label_15->setObjectName("label_15");

        gridLayout_2->addWidget(label_15, 0, 1, 1, 1);

        label_17 = new QLabel(tab_4);
        label_17->setObjectName("label_17");
        label_17->setStyleSheet(QString::fromUtf8("QLabel#label_17{\n"
"	color:#ff1418\n"
"}"));
        label_17->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_17, 0, 3, 1, 1);

        label_18 = new QLabel(tab_4);
        label_18->setObjectName("label_18");
        label_18->setStyleSheet(QString::fromUtf8("QLabel#label_18{\n"
"	color:#ff1418\n"
"}"));
        label_18->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_18, 0, 4, 1, 1);

        label_25 = new QLabel(tab_4);
        label_25->setObjectName("label_25");
        label_25->setStyleSheet(QString::fromUtf8("QLabel#label_25{\n"
"	color:#ff1418\n"
"}"));
        label_25->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_25, 0, 11, 1, 1);

        label_26 = new QLabel(tab_4);
        label_26->setObjectName("label_26");
        label_26->setStyleSheet(QString::fromUtf8("QLabel#label_26{\n"
"	color:#ff1418\n"
"}"));
        label_26->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_26, 0, 12, 1, 1);

        label_19 = new QLabel(tab_4);
        label_19->setObjectName("label_19");
        label_19->setStyleSheet(QString::fromUtf8("QLabel#label_19{\n"
"	color:#ff1418\n"
"}"));
        label_19->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_19, 0, 5, 1, 1);

        label_22 = new QLabel(tab_4);
        label_22->setObjectName("label_22");
        label_22->setStyleSheet(QString::fromUtf8("QLabel#label_22{\n"
"	color:#ff1418\n"
"}"));
        label_22->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_22, 0, 8, 1, 1);

        label_20 = new QLabel(tab_4);
        label_20->setObjectName("label_20");
        label_20->setStyleSheet(QString::fromUtf8("QLabel#label_20{\n"
"	color:#ff1418\n"
"}"));
        label_20->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_20, 0, 6, 1, 1);

        label_27 = new QLabel(tab_4);
        label_27->setObjectName("label_27");
        label_27->setStyleSheet(QString::fromUtf8("QLabel#label_27{\n"
"	color:#ff1418\n"
"}"));
        label_27->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_2->addWidget(label_27, 0, 13, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);

        swr_horizontalSlider = new QSlider(tab_4);
        swr_horizontalSlider->setObjectName("swr_horizontalSlider");
        swr_horizontalSlider->setMinimum(10);
        swr_horizontalSlider->setMaximum(140);
        swr_horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        swr_horizontalSlider->setTickPosition(QSlider::TickPosition::TicksAbove);

        verticalLayout_6->addWidget(swr_horizontalSlider);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        swtValue_dial = new QDial(tab_4);
        swtValue_dial->setObjectName("swtValue_dial");
        sizePolicy1.setHeightForWidth(swtValue_dial->sizePolicy().hasHeightForWidth());
        swtValue_dial->setSizePolicy(sizePolicy1);
        swtValue_dial->setMinimum(10);
        swtValue_dial->setMaximum(140);
        swtValue_dial->setSliderPosition(10);
        swtValue_dial->setWrapping(false);
        swtValue_dial->setNotchTarget(10.000000000000000);
        swtValue_dial->setNotchesVisible(true);

        horizontalLayout_16->addWidget(swtValue_dial);


        verticalLayout_6->addLayout(horizontalLayout_16);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        swtValue_doubleSpinBox = new QDoubleSpinBox(tab_4);
        swtValue_doubleSpinBox->setObjectName("swtValue_doubleSpinBox");
        sizePolicy3.setHeightForWidth(swtValue_doubleSpinBox->sizePolicy().hasHeightForWidth());
        swtValue_doubleSpinBox->setSizePolicy(sizePolicy3);
        swtValue_doubleSpinBox->setMaximumSize(QSize(100, 16777215));
        swtValue_doubleSpinBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        swtValue_doubleSpinBox->setReadOnly(false);
        swtValue_doubleSpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
        swtValue_doubleSpinBox->setDecimals(1);
        swtValue_doubleSpinBox->setMinimum(1.000000000000000);
        swtValue_doubleSpinBox->setMaximum(14.000000000000000);
        swtValue_doubleSpinBox->setSingleStep(0.100000000000000);

        horizontalLayout_14->addWidget(swtValue_doubleSpinBox);


        verticalLayout_6->addLayout(horizontalLayout_14);


        gridLayout_3->addLayout(verticalLayout_6, 1, 0, 1, 2);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        SWT_pushButton = new QPushButton(tab_4);
        SWT_pushButton->setObjectName("SWT_pushButton");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(SWT_pushButton->sizePolicy().hasHeightForWidth());
        SWT_pushButton->setSizePolicy(sizePolicy5);
        SWT_pushButton->setMinimumSize(QSize(50, 50));

        horizontalLayout_15->addWidget(SWT_pushButton);


        gridLayout_3->addLayout(horizontalLayout_15, 2, 0, 1, 2);

        line_6 = new QFrame(tab_4);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_3->addWidget(line_6, 3, 0, 1, 2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(tab_4);
        label_6->setObjectName("label_6");
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_5->addWidget(label_6);

        PPc_label = new QLabel(tab_4);
        PPc_label->setObjectName("PPc_label");
        sizePolicy.setHeightForWidth(PPc_label->sizePolicy().hasHeightForWidth());
        PPc_label->setSizePolicy(sizePolicy);
        PPc_label->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_5->addWidget(PPc_label);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_28 = new QLabel(tab_4);
        label_28->setObjectName("label_28");

        horizontalLayout_12->addWidget(label_28);

        PPc_horizontalSlider = new QSlider(tab_4);
        PPc_horizontalSlider->setObjectName("PPc_horizontalSlider");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(PPc_horizontalSlider->sizePolicy().hasHeightForWidth());
        PPc_horizontalSlider->setSizePolicy(sizePolicy6);
        PPc_horizontalSlider->setMinimum(-100);
        PPc_horizontalSlider->setMaximum(100);
        PPc_horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        PPc_horizontalSlider->setTickPosition(QSlider::TickPosition::TicksAbove);

        horizontalLayout_12->addWidget(PPc_horizontalSlider);

        PPcv_spinBox = new QSpinBox(tab_4);
        PPcv_spinBox->setObjectName("PPcv_spinBox");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(PPcv_spinBox->sizePolicy().hasHeightForWidth());
        PPcv_spinBox->setSizePolicy(sizePolicy7);
        PPcv_spinBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        PPcv_spinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
        PPcv_spinBox->setMinimum(-100);
        PPcv_spinBox->setMaximum(100);

        horizontalLayout_12->addWidget(PPcv_spinBox);


        verticalLayout_7->addLayout(horizontalLayout_12);


        gridLayout_3->addLayout(verticalLayout_7, 4, 0, 1, 2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_11 = new QLabel(tab_4);
        label_11->setObjectName("label_11");
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_8->addWidget(label_11);

        Swc_label = new QLabel(tab_4);
        Swc_label->setObjectName("Swc_label");
        sizePolicy.setHeightForWidth(Swc_label->sizePolicy().hasHeightForWidth());
        Swc_label->setSizePolicy(sizePolicy);
        Swc_label->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_8->addWidget(Swc_label);


        verticalLayout_8->addLayout(horizontalLayout_8);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_29 = new QLabel(tab_4);
        label_29->setObjectName("label_29");

        horizontalLayout_11->addWidget(label_29);

        Swc_horizontalSlider = new QSlider(tab_4);
        Swc_horizontalSlider->setObjectName("Swc_horizontalSlider");
        sizePolicy6.setHeightForWidth(Swc_horizontalSlider->sizePolicy().hasHeightForWidth());
        Swc_horizontalSlider->setSizePolicy(sizePolicy6);
        Swc_horizontalSlider->setMinimum(-100);
        Swc_horizontalSlider->setMaximum(100);
        Swc_horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        Swc_horizontalSlider->setTickPosition(QSlider::TickPosition::TicksAbove);

        horizontalLayout_11->addWidget(Swc_horizontalSlider);

        Swcv_spinBox = new QSpinBox(tab_4);
        Swcv_spinBox->setObjectName("Swcv_spinBox");
        sizePolicy7.setHeightForWidth(Swcv_spinBox->sizePolicy().hasHeightForWidth());
        Swcv_spinBox->setSizePolicy(sizePolicy7);
        Swcv_spinBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Swcv_spinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
        Swcv_spinBox->setMinimum(-100);
        Swcv_spinBox->setMaximum(100);

        horizontalLayout_11->addWidget(Swcv_spinBox);


        verticalLayout_8->addLayout(horizontalLayout_11);


        gridLayout_3->addLayout(verticalLayout_8, 5, 0, 1, 2);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_12 = new QLabel(tab_4);
        label_12->setObjectName("label_12");
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_9->addWidget(label_12);

        Vc_label = new QLabel(tab_4);
        Vc_label->setObjectName("Vc_label");
        sizePolicy.setHeightForWidth(Vc_label->sizePolicy().hasHeightForWidth());
        Vc_label->setSizePolicy(sizePolicy);
        Vc_label->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_9->addWidget(Vc_label);


        verticalLayout_9->addLayout(horizontalLayout_9);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_30 = new QLabel(tab_4);
        label_30->setObjectName("label_30");

        horizontalLayout_13->addWidget(label_30);

        Vc_horizontalSlider = new QSlider(tab_4);
        Vc_horizontalSlider->setObjectName("Vc_horizontalSlider");
        sizePolicy6.setHeightForWidth(Vc_horizontalSlider->sizePolicy().hasHeightForWidth());
        Vc_horizontalSlider->setSizePolicy(sizePolicy6);
        Vc_horizontalSlider->setMinimum(-100);
        Vc_horizontalSlider->setMaximum(100);
        Vc_horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        Vc_horizontalSlider->setTickPosition(QSlider::TickPosition::TicksAbove);

        horizontalLayout_13->addWidget(Vc_horizontalSlider);

        Vcv_spinBox = new QSpinBox(tab_4);
        Vcv_spinBox->setObjectName("Vcv_spinBox");
        sizePolicy7.setHeightForWidth(Vcv_spinBox->sizePolicy().hasHeightForWidth());
        Vcv_spinBox->setSizePolicy(sizePolicy7);
        Vcv_spinBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Vcv_spinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
        Vcv_spinBox->setMinimum(-100);
        Vcv_spinBox->setMaximum(100);

        horizontalLayout_13->addWidget(Vcv_spinBox);


        verticalLayout_9->addLayout(horizontalLayout_13);


        gridLayout_3->addLayout(verticalLayout_9, 6, 0, 1, 2);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        ATC_pushButton = new QPushButton(tab_4);
        ATC_pushButton->setObjectName("ATC_pushButton");
        sizePolicy5.setHeightForWidth(ATC_pushButton->sizePolicy().hasHeightForWidth());
        ATC_pushButton->setSizePolicy(sizePolicy5);
        ATC_pushButton->setMinimumSize(QSize(50, 50));

        horizontalLayout_17->addWidget(ATC_pushButton);


        gridLayout_3->addLayout(horizontalLayout_17, 7, 0, 1, 2);

        tabWidget->addTab(tab_4, QString());

        horizontalLayout->addWidget(tabWidget);

        line_4 = new QFrame(termial);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::VLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout->addWidget(line_4);

        control = new QWidget(termial);
        control->setObjectName("control");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(control->sizePolicy().hasHeightForWidth());
        control->setSizePolicy(sizePolicy8);
        control->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_3 = new QVBoxLayout(control);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(control);
        label->setObjectName("label");
        QSizePolicy sizePolicy9(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy9);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        language_comboBox = new QComboBox(control);
        language_comboBox->setObjectName("language_comboBox");
        QSizePolicy sizePolicy10(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(language_comboBox->sizePolicy().hasHeightForWidth());
        language_comboBox->setSizePolicy(sizePolicy10);
        language_comboBox->setMinimumSize(QSize(150, 0));

        verticalLayout_3->addWidget(language_comboBox);

        line_2 = new QFrame(control);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_2);

        label_2 = new QLabel(control);
        label_2->setObjectName("label_2");
        sizePolicy9.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy9);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        save_pushButton = new QPushButton(control);
        save_pushButton->setObjectName("save_pushButton");
        sizePolicy10.setHeightForWidth(save_pushButton->sizePolicy().hasHeightForWidth());
        save_pushButton->setSizePolicy(sizePolicy10);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        save_pushButton->setIcon(icon);

        horizontalLayout_3->addWidget(save_pushButton);

        open_pushButton = new QPushButton(control);
        open_pushButton->setObjectName("open_pushButton");
        sizePolicy10.setHeightForWidth(open_pushButton->sizePolicy().hasHeightForWidth());
        open_pushButton->setSizePolicy(sizePolicy10);
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
        sizePolicy9.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy9);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        label_7 = new QLabel(control);
        label_7->setObjectName("label_7");
        sizePolicy9.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy9);

        verticalLayout_3->addWidget(label_7);

        IPLocal_lineEdit = new QLineEdit(control);
        IPLocal_lineEdit->setObjectName("IPLocal_lineEdit");
        sizePolicy10.setHeightForWidth(IPLocal_lineEdit->sizePolicy().hasHeightForWidth());
        IPLocal_lineEdit->setSizePolicy(sizePolicy10);
#if QT_CONFIG(tooltip)
        IPLocal_lineEdit->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        verticalLayout_3->addWidget(IPLocal_lineEdit);

        label_8 = new QLabel(control);
        label_8->setObjectName("label_8");
        sizePolicy9.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy9);

        verticalLayout_3->addWidget(label_8);

        tcpPort_lineEdit = new QLineEdit(control);
        tcpPort_lineEdit->setObjectName("tcpPort_lineEdit");
        sizePolicy10.setHeightForWidth(tcpPort_lineEdit->sizePolicy().hasHeightForWidth());
        tcpPort_lineEdit->setSizePolicy(sizePolicy10);
#if QT_CONFIG(tooltip)
        tcpPort_lineEdit->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        verticalLayout_3->addWidget(tcpPort_lineEdit);

        tcpOpen_pushButton = new QPushButton(control);
        tcpOpen_pushButton->setObjectName("tcpOpen_pushButton");
        sizePolicy10.setHeightForWidth(tcpOpen_pushButton->sizePolicy().hasHeightForWidth());
        tcpOpen_pushButton->setSizePolicy(sizePolicy10);

        verticalLayout_3->addWidget(tcpOpen_pushButton);

        label_9 = new QLabel(control);
        label_9->setObjectName("label_9");
        QSizePolicy sizePolicy11(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy11);

        verticalLayout_3->addWidget(label_9);

        connectedDevices_comboBox = new QComboBox(control);
        connectedDevices_comboBox->setObjectName("connectedDevices_comboBox");
        sizePolicy.setHeightForWidth(connectedDevices_comboBox->sizePolicy().hasHeightForWidth());
        connectedDevices_comboBox->setSizePolicy(sizePolicy);
#if QT_CONFIG(tooltip)
        connectedDevices_comboBox->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        verticalLayout_3->addWidget(connectedDevices_comboBox);

        line_3 = new QFrame(control);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_3);

        label_10 = new QLabel(control);
        label_10->setObjectName("label_10");
        sizePolicy11.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy11);
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        serialport_comboBox = new QComboBox(control);
        serialport_comboBox->setObjectName("serialport_comboBox");
        serialport_comboBox->setEnabled(true);
        sizePolicy.setHeightForWidth(serialport_comboBox->sizePolicy().hasHeightForWidth());
        serialport_comboBox->setSizePolicy(sizePolicy);
        serialport_comboBox->setMinimumSize(QSize(0, 0));
        serialport_comboBox->setMaximumSize(QSize(16777215, 16777215));
        serialport_comboBox->setSizeIncrement(QSize(210, 0));
#if QT_CONFIG(tooltip)
        serialport_comboBox->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)

        horizontalLayout_7->addWidget(serialport_comboBox);

        serialportFlash_pushButton = new QPushButton(control);
        serialportFlash_pushButton->setObjectName("serialportFlash_pushButton");
        sizePolicy8.setHeightForWidth(serialportFlash_pushButton->sizePolicy().hasHeightForWidth());
        serialportFlash_pushButton->setSizePolicy(sizePolicy8);
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::SyncSynchronizing));
        serialportFlash_pushButton->setIcon(icon2);

        horizontalLayout_7->addWidget(serialportFlash_pushButton);


        verticalLayout_3->addLayout(horizontalLayout_7);

        serialportLink_pushButton = new QPushButton(control);
        serialportLink_pushButton->setObjectName("serialportLink_pushButton");
        sizePolicy10.setHeightForWidth(serialportLink_pushButton->sizePolicy().hasHeightForWidth());
        serialportLink_pushButton->setSizePolicy(sizePolicy10);

        verticalLayout_3->addWidget(serialportLink_pushButton);

        line_5 = new QFrame(control);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        send_btn = new QPushButton(control);
        send_btn->setObjectName("send_btn");
        sizePolicy.setHeightForWidth(send_btn->sizePolicy().hasHeightForWidth());
        send_btn->setSizePolicy(sizePolicy);
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSend));
        send_btn->setIcon(icon3);

        horizontalLayout_6->addWidget(send_btn);

        read_btn = new QPushButton(control);
        read_btn->setObjectName("read_btn");
        sizePolicy.setHeightForWidth(read_btn->sizePolicy().hasHeightForWidth());
        read_btn->setSizePolicy(sizePolicy);
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        read_btn->setIcon(icon4);

        horizontalLayout_6->addWidget(read_btn);


        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout->addWidget(control);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(termial);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(termial);
    } // setupUi

    void retranslateUi(QWidget *termial)
    {
        termial->setWindowTitle(QCoreApplication::translate("termial", "\345\233\275\350\265\253T7", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("termial", "\351\246\226\351\241\265", nullptr));
        checkAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\351\200\211", nullptr));
        checkNotAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\344\270\215\351\200\211", nullptr));
        channelNum_lineEdit->setPlaceholderText(QCoreApplication::translate("termial", "\350\267\263\350\275\254Channel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("termial", "\347\274\226\347\250\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("termial", "\350\256\276\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("termial", "\345\267\245\347\250\213\346\250\241\345\274\217", nullptr));
        label_13->setText(QCoreApplication::translate("termial", "\345\275\223\345\211\215\346\250\241\345\274\217:", nullptr));
        tunerCurrentModel_label->setText(QCoreApplication::translate("termial", "\350\207\252\345\212\250\350\260\203\350\260\220", nullptr));
        auto_radioButton->setText(QCoreApplication::translate("termial", "\350\207\252\345\212\250\350\260\203\350\260\220", nullptr));
        start_radioButton->setText(QCoreApplication::translate("termial", "\346\211\213\345\212\250\350\260\203\350\260\220", nullptr));
        close_radioButton->setText(QCoreApplication::translate("termial", "\345\205\263\351\227\255\350\260\203\350\260\220", nullptr));
        label_5->setText(QCoreApplication::translate("termial", "\347\224\265\345\216\213(\345\215\225\344\275\215:v)", nullptr));
        label_3->setText(QCoreApplication::translate("termial", "\351\251\273\346\263\242\350\260\203\350\260\220\345\200\274", nullptr));
        swtValue_label->setText(QCoreApplication::translate("termial", "0", nullptr));
        label_24->setText(QCoreApplication::translate("termial", "  11", nullptr));
        label_14->setText(QCoreApplication::translate("termial", "1.0", nullptr));
        label_23->setText(QCoreApplication::translate("termial", " 10", nullptr));
        label_21->setText(QCoreApplication::translate("termial", "8", nullptr));
        label_16->setText(QCoreApplication::translate("termial", " 3.0", nullptr));
        label_15->setText(QCoreApplication::translate("termial", "2.0", nullptr));
        label_17->setText(QCoreApplication::translate("termial", "4", nullptr));
        label_18->setText(QCoreApplication::translate("termial", "5", nullptr));
        label_25->setText(QCoreApplication::translate("termial", "  12", nullptr));
        label_26->setText(QCoreApplication::translate("termial", "  13", nullptr));
        label_19->setText(QCoreApplication::translate("termial", "6", nullptr));
        label_22->setText(QCoreApplication::translate("termial", "9", nullptr));
        label_20->setText(QCoreApplication::translate("termial", "7", nullptr));
        label_27->setText(QCoreApplication::translate("termial", "14", nullptr));
        SWT_pushButton->setText(QCoreApplication::translate("termial", "\351\251\273\346\263\242\350\260\203\350\260\220", nullptr));
        label_6->setText(QCoreApplication::translate("termial", "\346\255\243\345\220\221\345\212\237\347\216\207\346\240\241\345\207\206\345\200\274", nullptr));
        PPc_label->setText(QCoreApplication::translate("termial", "0", nullptr));
        label_28->setText(QCoreApplication::translate("termial", "\346\233\264\346\224\271:", nullptr));
        label_11->setText(QCoreApplication::translate("termial", "\351\251\273\346\263\242\346\240\241\345\207\206\345\200\274", nullptr));
        Swc_label->setText(QCoreApplication::translate("termial", "0", nullptr));
        label_29->setText(QCoreApplication::translate("termial", "\346\233\264\346\224\271:", nullptr));
        label_12->setText(QCoreApplication::translate("termial", "\347\224\265\345\216\213\346\240\241\345\207\206\345\200\274", nullptr));
        Vc_label->setText(QCoreApplication::translate("termial", "0", nullptr));
        label_30->setText(QCoreApplication::translate("termial", "\346\233\264\346\224\271:", nullptr));
        ATC_pushButton->setText(QCoreApplication::translate("termial", "\345\244\251\350\260\203\346\240\241\345\207\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("termial", "\345\244\251\350\260\203", nullptr));
        label->setText(QCoreApplication::translate("termial", "\350\257\255\350\250\200", nullptr));
        label_2->setText(QCoreApplication::translate("termial", "\346\226\207\344\273\266", nullptr));
        save_pushButton->setText(QCoreApplication::translate("termial", "\344\277\235\345\255\230", nullptr));
        open_pushButton->setText(QCoreApplication::translate("termial", "\346\211\223\345\274\200", nullptr));
        label_4->setText(QCoreApplication::translate("termial", "\347\275\221\347\273\234\350\277\236\346\216\245", nullptr));
        label_7->setText(QCoreApplication::translate("termial", "\346\234\254\346\234\272\345\234\260\345\235\200", nullptr));
        IPLocal_lineEdit->setText(QCoreApplication::translate("termial", "192.168.1.68", nullptr));
        label_8->setText(QCoreApplication::translate("termial", "TCP\347\253\257\345\217\243", nullptr));
        tcpPort_lineEdit->setText(QCoreApplication::translate("termial", "20108", nullptr));
        tcpOpen_pushButton->setText(QCoreApplication::translate("termial", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
        label_9->setText(QCoreApplication::translate("termial", "\345\267\262\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        label_10->setText(QCoreApplication::translate("termial", "\344\270\262\345\217\243\350\277\236\346\216\245", nullptr));
        serialportFlash_pushButton->setText(QString());
        serialportLink_pushButton->setText(QCoreApplication::translate("termial", "\350\277\236\346\216\245", nullptr));
        send_btn->setText(QCoreApplication::translate("termial", "\345\217\221\351\200\201", nullptr));
        read_btn->setText(QCoreApplication::translate("termial", "\350\257\273\345\217\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class termial: public Ui_termial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERMIAL_H
