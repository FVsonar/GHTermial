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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_termial
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *serialport_comboBox;
    QPushButton *serialportFlash_pushButton;
    QPushButton *serialportLink_pushButton;
    QSpacerItem *horizontalSpacer;
    QComboBox *language_comboBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QWidget *data;
    QVBoxLayout *verticalLayout_2;
    QWidget *tools;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *checkAll_pushButton;
    QPushButton *checkNotAll_pushButton;
    QPushButton *read_btn;
    QPushButton *send_btn;
    QPushButton *save_pushButton;
    QPushButton *open_pushButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_31;
    QSpinBox *channelMaxNum_spinBox;
    QLineEdit *channelNum_lineEdit;
    QProgressBar *load_progressBar;
    QTableView *tableView;

    void setupUi(QWidget *termial)
    {
        if (termial->objectName().isEmpty())
            termial->setObjectName("termial");
        termial->resize(1194, 781);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(termial->sizePolicy().hasHeightForWidth());
        termial->setSizePolicy(sizePolicy);
#if QT_CONFIG(tooltip)
        termial->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        termial->setStyleSheet(QString::fromUtf8("/* \347\273\210\347\253\257\350\203\214\346\231\257 - \346\267\261\347\201\260\351\273\221\350\211\262 */\n"
"#termial {\n"
"    background-color: #1E1F22;\n"
"}\n"
"\n"
"/* ========== QPushButton \346\214\211\351\222\256 ========== */\n"
"QPushButton {\n"
"    border: 1px solid #3E4044;\n"
"    border-radius: 4px;\n"
"    padding: 8px 15px;\n"
"    min-height: 18px;\n"
"    background-color: #2D2F33;\n"
"    color: #D3D6DB;\n"
"    font: 14px \"Segoe UI\", \"Microsoft YaHei\", sans-serif;\n"
"    transition: all 0.2s;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #3A3D42;\n"
"    border-color: #4E5258;\n"
"    color: #EFF1F5;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #25272B;\n"
"    border-color: #5D6066;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    color: #5A5D61;\n"
"    background-color: #2A2C30;\n"
"    border-color: #35373B;\n"
"}\n"
"\n"
"/* ========== QSpinBox \346\225\260\345\255\227\350\276\223\345\205\245\346\241\206 ========== */\n"
"QSpinBox {\n"
"    border: "
                        "1px solid #3E4044;\n"
"    border-radius: 4px;\n"
"    padding: 0 25px 0 8px; /* \345\217\263\344\276\247\344\270\272\347\256\255\345\244\264\347\225\231\345\207\272\347\251\272\351\227\264 */\n"
"	height: 32px;\n"
"	/*min-width:90px;*/\n"
"    background-color: #2D2F33;\n"
"    color: #D3D6DB;\n"
"    selection-background-color: #3A8EE6;\n"
"    selection-color: white;\n"
"    font: 14px \"Segoe UI\", \"Microsoft YaHei\";\n"
"}\n"
"\n"
"/* \347\256\255\345\244\264\346\214\211\351\222\256\351\200\232\347\224\250\346\240\267\345\274\217 */\n"
"QSpinBox::up-button, QSpinBox::down-button {\n"
"    subcontrol-origin: border;\n"
"    width: 20px;\n"
"    height: 15px; /* \347\262\276\347\241\256\346\216\247\345\210\266\351\253\230\345\272\246 */\n"
"    border-left: 1px solid #3E4044;\n"
"    background-color: #35373B;\n"
"}\n"
"\n"
"/* \344\270\212\346\214\211\351\222\256\345\256\232\344\275\215 */\n"
"QSpinBox::up-button {\n"
"    subcontrol-position: top right;\n"
"    top: 1px; /* \345\257\271\351\275\220\350\276"
                        "\271\346\241\206 */\n"
"    right: 1px;\n"
"    border-bottom: 1px solid #3E4044;\n"
"    border-top-right-radius: 3px;\n"
"}\n"
"\n"
"/* \344\270\213\346\214\211\351\222\256\345\256\232\344\275\215 */\n"
"QSpinBox::down-button {\n"
"    subcontrol-position: bottom right;\n"
"    bottom: 1px; /* \345\257\271\351\275\220\350\276\271\346\241\206 */\n"
"    right: 1px;\n"
"    border-bottom-right-radius: 3px;\n"
"}\n"
"\n"
"/* \347\256\255\345\244\264\345\233\276\346\240\207 - \344\275\277\347\224\250SVG\346\210\226PNG */\n"
"QSpinBox::up-arrow {\n"
"    image: url(://img/up.png);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}\n"
"\n"
"QSpinBox::down-arrow {\n"
"    image: url(://img/down.png);\n"
"    width: 10px;\n"
"    height: 10px;\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201 */\n"
"QSpinBox::up-button:hover, QSpinBox::down-button:hover {\n"
"    background-color: #3E4044;\n"
"}\n"
"\n"
"QSpinBox::up-arrow:hover {\n"
"    image: url(://img/up.png);\n"
"}\n"
"\n"
"QSpinBox::down-arrow:"
                        "hover {\n"
"    image: url(://img/down.png);\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201 */\n"
"QSpinBox::up-button:pressed, QSpinBox::down-button:pressed {\n"
"    background-color: #2A2C30;\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QSpinBox:disabled, \n"
"QSpinBox::up-button:disabled, \n"
"QSpinBox::down-button:disabled {\n"
"    background-color: #25272A;\n"
"    color: #5C5F66;\n"
"}\n"
"\n"
"QSpinBox::up-arrow:disabled, \n"
"QSpinBox::down-arrow:disabled {\n"
"    opacity: 0.5;\n"
"}\n"
"/* ========== QLineEdit \350\276\223\345\205\245\346\241\206 ========== */\n"
"QLineEdit {\n"
"    border: 1px solid #3E4044;\n"
"    border-radius: 4px;\n"
"    padding: 0 15px;\n"
"    height: 33px;\n"
"    background-color: #2D2F33;\n"
"    color: #D3D6DB;\n"
"    selection-background-color: #3A8EE6;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border-color: #4E5258;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #3A8EE6;\n"
"}\n"
"\n"
"QLineEdit::placeholder {"
                        "\n"
"    color: #6A6D72;\n"
"    font-style: italic;\n"
"}\n"
"\n"
"/* ========== QComboBox \344\270\213\346\213\211\346\241\206 ========== */\n"
"/* ========== QComboBox \345\237\272\347\241\200\346\240\267\345\274\217 ========== */\n"
"QComboBox {\n"
"    border: 1px solid #45474C;\n"
"    border-radius: 4px;\n"
"    padding: 0 30px 0 12px;  /* \345\217\263\344\276\247\347\225\231\345\207\272\344\270\213\346\213\211\346\214\211\351\222\256\347\251\272\351\227\264 */\n"
"    min-height: 32px;\n"
"    background-color: #2B2D30;\n"
"    color: #E0E3E9;\n"
"    font: 14px \"Segoe UI\", \"Microsoft YaHei\", sans-serif;\n"
"    selection-background-color: #3A8EE6;\n"
"    selection-color: white;\n"
"}\n"
"\n"
"/* \345\217\257\347\274\226\350\276\221\347\212\266\346\200\201\347\211\271\346\256\212\345\244\204\347\220\206 */\n"
"QComboBox:editable {\n"
"    padding-right: 30px;  /* \347\241\256\344\277\235\347\274\226\350\276\221\346\241\206\344\270\215\344\274\232\350\246\206\347\233\226\344\270\213\346\213\211\346"
                        "\214\211\351\222\256 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\346\214\211\351\222\256\345\256\232\344\275\215\344\277\256\346\255\243 */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 30px;\n"
"    border-left: 1px solid #45474C;\n"
"    border-top-right-radius: 3px;\n"
"    border-bottom-right-radius: 3px;\n"
"    background-color: #35373B;\n"
"    right: 1px;  /* \345\257\271\351\275\220\350\276\271\346\241\206 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\347\256\255\345\244\264\345\233\276\346\240\207 */\n"
"QComboBox::down-arrow {\n"
"    image: url(://img/down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* \347\247\273\351\231\244\345\217\257\347\274\226\350\276\221\346\241\206\347\232\204\345\206\205\347\275\256\344\270\213\346\213\211\346\214\207\347\244\272\345\231\250 */\n"
"QComboBox::drop-down:editable {\n"
"    width: 0;\n"
"    border: none;\n"
"}\n"
"/* \344\270\213\346\213\211\350\217\234\345\215\225"
                        "\351\235\242\346\235\277 */\n"
"QComboBox QAbstractItemView {\n"
"    border: 1px solid #45474C;\n"
"    border-top: none;\n"
"    border-radius: 0 0 4px 4px;\n"
"    background-color: #2B2D30;\n"
"    padding: 4px 0;\n"
"    outline: none;\n"
"    margin-top: 2px; /* \346\266\210\351\231\244\344\270\216\344\270\273\346\216\247\344\273\266\347\232\204\351\227\264\351\232\231 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\350\217\234\345\215\225\344\270\255\347\232\204\351\241\271 */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 32px;\n"
"    padding: 0 12px;\n"
"    color: #D8DBE2;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"/* \351\241\271\346\202\254\345\201\234\347\212\266\346\200\201 */\n"
"QComboBox QAbstractItemView::item:hover {\n"
"    background-color: #35373B;\n"
"}\n"
"\n"
"/* \351\241\271\351\200\211\344\270\255\347\212\266\346\200\201 */\n"
"QComboBox QAbstractItemView::item:selected {\n"
"    background-color: #3A8EE6;\n"
"    color: white;\n"
"}\n"
"\n"
"/* \345\217\257\347"
                        "\274\226\350\276\221\347\273\204\345\220\210\346\241\206\347\232\204\347\274\226\350\276\221\345\214\272\345\237\237 */\n"
"QComboBox QLineEdit {\n"
"    padding: 0 8px;\n"
"    background: transparent;\n"
"    color: #E0E3E9;\n"
"    border: none;\n"
"    selection-background-color: #3A8EE6;\n"
"}\n"
"\n"
"/* \345\217\257\347\274\226\350\276\221\347\273\204\345\220\210\346\241\206\347\232\204\347\274\226\350\276\221\345\214\272\345\237\237\347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QComboBox:disabled QLineEdit {\n"
"    color: #5C5F66;\n"
"}\n"
"/* ========== \345\205\250\345\261\200\345\242\236\345\274\272 ========== */\n"
"/* \347\273\237\344\270\200\347\246\201\347\224\250\347\212\266\346\200\201\346\240\267\345\274\217 */\n"
"QSpinBox:disabled, QLineEdit:disabled, QComboBox:disabled {\n"
"    color: #5A5D61;\n"
"    background-color: #25272A;\n"
"    border-color: #303235;\n"
"}\n"
"\n"
"/* \347\273\237\344\270\200\347\204\246\347\202\271\346\225\210\346\236\234 */\n"
"*:focus {\n"
"    outlin"
                        "e: none;\n"
"}\n"
"\n"
"/* \346\273\232\345\212\250\346\235\241\346\240\267\345\274\217 */\n"
"QScrollBar:vertical {\n"
"    background: #25272A;\n"
"    width: 10px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #3E4044;\n"
"    min-height: 20px;\n"
"    border-radius: 5px;\n"
"}"));
        gridLayout = new QGridLayout(termial);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(termial);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(0, 50));
        widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        serialport_comboBox = new QComboBox(widget);
        serialport_comboBox->setObjectName("serialport_comboBox");
        serialport_comboBox->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(serialport_comboBox->sizePolicy().hasHeightForWidth());
        serialport_comboBox->setSizePolicy(sizePolicy2);
        serialport_comboBox->setMinimumSize(QSize(0, 34));
        serialport_comboBox->setMaximumSize(QSize(16777215, 16777215));
        serialport_comboBox->setSizeIncrement(QSize(210, 0));
        serialport_comboBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(serialport_comboBox);

        serialportFlash_pushButton = new QPushButton(widget);
        serialportFlash_pushButton->setObjectName("serialportFlash_pushButton");
        sizePolicy.setHeightForWidth(serialportFlash_pushButton->sizePolicy().hasHeightForWidth());
        serialportFlash_pushButton->setSizePolicy(sizePolicy);
        serialportFlash_pushButton->setMinimumSize(QSize(0, 36));
        serialportFlash_pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border-radius: 17px;  /* \350\256\251\346\214\211\351\222\256\345\217\230\346\210\220\345\234\206\345\275\242 */\n"
"    border: none;\n"
"    font-weight: bold;\n"
"	width: 8px;\n"
"    height: 20px;\n"
"	background-image: url(\"://img/flash.png\");\n"
"    background-repeat: no-repeat;  /* \347\246\201\346\255\242\345\233\276\347\211\207\351\207\215\345\244\215 */\n"
"    background-position: center;  /* \345\233\276\347\211\207\345\261\205\344\270\255 */\n"
"    background-clip: padding-box;  /* \347\241\256\344\277\235\350\203\214\346\231\257\345\217\252\345\234\250padding\345\214\272\345\237\237\345\206\205 */\n"
"}"));

        horizontalLayout_3->addWidget(serialportFlash_pushButton);

        serialportLink_pushButton = new QPushButton(widget);
        serialportLink_pushButton->setObjectName("serialportLink_pushButton");
        sizePolicy.setHeightForWidth(serialportLink_pushButton->sizePolicy().hasHeightForWidth());
        serialportLink_pushButton->setSizePolicy(sizePolicy);
        serialportLink_pushButton->setStyleSheet(QString::fromUtf8("QPushButton.success {\n"
"    background-color: #67C23A;\n"
"    border-color: #67C23A;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton.success:hover {\n"
"    background-color: #85ce61;\n"
"    border-color: #85ce61;\n"
"}\n"
"\n"
"QPushButton.success:pressed {\n"
"    background-color: #5daf34;\n"
"    border-color: #5daf34;\n"
"}\n"
"\n"
"QPushButton.success:disabled {\n"
"    background-color: #C8E6C9;\n"
"    border-color: #C8E6C9;\n"
"    color: white;\n"
"}"));

        horizontalLayout_3->addWidget(serialportLink_pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        language_comboBox = new QComboBox(widget);
        language_comboBox->setObjectName("language_comboBox");
        sizePolicy2.setHeightForWidth(language_comboBox->sizePolicy().hasHeightForWidth());
        language_comboBox->setSizePolicy(sizePolicy2);
        language_comboBox->setMinimumSize(QSize(0, 34));
        language_comboBox->setAcceptDrops(false);
        language_comboBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(language_comboBox);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(termial);
        tabWidget->setObjectName("tabWidget");
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setStyleSheet(QString::fromUtf8("/* ========== QTabWidget \344\270\273\345\256\271\345\231\250 ========== */\n"
"QTabWidget {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"/* ========== \346\240\207\347\255\276\346\240\217\346\240\267\345\274\217 ========== */\n"
"QTabWidget::pane {\n"
"    border: 1px solid #3A3C40;\n"
"    border-radius: 4px;\n"
"    background: #25272B;\n"
"    margin: 0;\n"
"    padding: 0;\n"
"    top: -1px; /* \346\266\210\351\231\244\344\270\216\346\240\207\347\255\276\347\232\204\351\227\264\351\232\231 */\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    alignment: left;\n"
"    left: 8px; /* \346\240\207\347\255\276\346\240\217\345\267\246\344\276\247\345\201\217\347\247\273 */\n"
"}\n"
"\n"
"/* ========== \345\215\225\344\270\252\346\240\207\347\255\276\346\240\267\345\274\217 ========== */\n"
"QTabBar::tab {\n"
"    background: #2D2F33;\n"
"    color: #B0B3B8;\n"
"    border: 1px solid #3A3C40;\n"
"    border-bottom: none;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px"
                        ";\n"
"    padding: 8px 16px;\n"
"    margin-right: 4px;\n"
"    min-width: 80px;\n"
"    font: 14px \"Segoe UI\", \"Microsoft YaHei\";\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201 */\n"
"QTabBar::tab:hover {\n"
"    background: #35373B;\n"
"    color: #D3D6DB;\n"
"}\n"
"\n"
"/* \351\200\211\344\270\255\347\212\266\346\200\201 */\n"
"QTabBar::tab:selected {\n"
"    background: #25272B;\n"
"    color: #E0E3E9;\n"
"    border-color: #3A3C40;\n"
"    border-bottom: 1px solid #25272B; /* \344\270\216\345\206\205\345\256\271\345\214\272\345\237\237\350\236\215\345\220\210 */\n"
"    margin-bottom: -1px; /* \344\270\213\347\247\2731px\350\246\206\347\233\226\345\206\205\345\256\271\345\214\272\350\276\271\346\241\206 */\n"
"}\n"
"\n"
"/* \351\235\236\351\200\211\344\270\255\347\212\266\346\200\201 */\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px; /* \350\247\206\350\247\211\344\270\212\351\231\215\344\275\216\346\234\252\351\200\211\346\240\207\347\255\276 */\n"
"}\n"
"\n"
"/* \347\246\201"
                        "\347\224\250\347\212\266\346\200\201 */\n"
"QTabBar::tab:disabled {\n"
"    color: #5C5F66;\n"
"    background: #2A2C30;\n"
"}\n"
"\n"
"/* ========== \346\240\207\347\255\276\346\240\217\350\247\222\350\220\275\346\216\247\344\273\266 ========== */\n"
"QTabBar::scroller {\n"
"    width: 20px;\n"
"    background: #2D2F33;\n"
"}\n"
"\n"
"QTabBar QToolButton {\n"
"    background: #2D2F33;\n"
"    border: 1px solid #3A3C40;\n"
"}\n"
"\n"
"/* ========== \345\206\205\345\256\271\345\214\272\345\237\237\346\240\267\345\274\217 ========== */\n"
"QTabWidget::tab-contents {\n"
"    background: #25272B;\n"
"    border-top: none;\n"
"    border-radius: 0 0 4px 4px;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName("tab");
        tab->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName("verticalLayout");
        data = new QWidget(tab);
        data->setObjectName("data");
        data->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(data);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tools = new QWidget(data);
        tools->setObjectName("tools");
        tools->setStyleSheet(QString::fromUtf8("#tools{\n"
"	background-color: #3C3D3F;\n"
"	border-radius: 15px\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(tools);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        checkAll_pushButton = new QPushButton(tools);
        checkAll_pushButton->setObjectName("checkAll_pushButton");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkAll_pushButton->sizePolicy().hasHeightForWidth());
        checkAll_pushButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(checkAll_pushButton);

        checkNotAll_pushButton = new QPushButton(tools);
        checkNotAll_pushButton->setObjectName("checkNotAll_pushButton");
        sizePolicy3.setHeightForWidth(checkNotAll_pushButton->sizePolicy().hasHeightForWidth());
        checkNotAll_pushButton->setSizePolicy(sizePolicy3);
        checkNotAll_pushButton->setMinimumSize(QSize(0, 36));
        checkNotAll_pushButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(checkNotAll_pushButton);

        read_btn = new QPushButton(tools);
        read_btn->setObjectName("read_btn");
        sizePolicy.setHeightForWidth(read_btn->sizePolicy().hasHeightForWidth());
        read_btn->setSizePolicy(sizePolicy);
        read_btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(read_btn);

        send_btn = new QPushButton(tools);
        send_btn->setObjectName("send_btn");
        sizePolicy.setHeightForWidth(send_btn->sizePolicy().hasHeightForWidth());
        send_btn->setSizePolicy(sizePolicy);
        send_btn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(send_btn);

        save_pushButton = new QPushButton(tools);
        save_pushButton->setObjectName("save_pushButton");
        sizePolicy.setHeightForWidth(save_pushButton->sizePolicy().hasHeightForWidth());
        save_pushButton->setSizePolicy(sizePolicy);
        save_pushButton->setStyleSheet(QString::fromUtf8("/*QPushButton{\n"
"	background-image: url(\"://img/saveJson.png\");\n"
"    background-repeat: no-repeat;  \n"
"    background-position: center;  \n"
"    background-clip: padding-box;\n"
"}\n"
"*/"));

        horizontalLayout_2->addWidget(save_pushButton);

        open_pushButton = new QPushButton(tools);
        open_pushButton->setObjectName("open_pushButton");
        sizePolicy.setHeightForWidth(open_pushButton->sizePolicy().hasHeightForWidth());
        open_pushButton->setSizePolicy(sizePolicy);
        open_pushButton->setStyleSheet(QString::fromUtf8(" /*QPushButton{\n"
"	background-image: url(\"://img/openJson.png\");\n"
"    background-repeat: no-repeat;  \n"
"    background-position: center;  \n"
"    background-clip: padding-box;\n"
"}*/"));

        horizontalLayout_2->addWidget(open_pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_31 = new QLabel(tools);
        label_31->setObjectName("label_31");
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_31->setMinimumSize(QSize(0, 0));
        label_31->setAcceptDrops(false);
        label_31->setStyleSheet(QString::fromUtf8("#label_31{\n"
"color:rgb(255, 255, 255)\n"
"}"));
        label_31->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_2->addWidget(label_31);

        channelMaxNum_spinBox = new QSpinBox(tools);
        channelMaxNum_spinBox->setObjectName("channelMaxNum_spinBox");
        sizePolicy3.setHeightForWidth(channelMaxNum_spinBox->sizePolicy().hasHeightForWidth());
        channelMaxNum_spinBox->setSizePolicy(sizePolicy3);
        channelMaxNum_spinBox->setStyleSheet(QString::fromUtf8("#channelMaxNum_spinBox{\n"
"	min-width:90px;\n"
"}"));
        channelMaxNum_spinBox->setMaximum(1000);
        channelMaxNum_spinBox->setValue(10);

        horizontalLayout_2->addWidget(channelMaxNum_spinBox);

        channelNum_lineEdit = new QLineEdit(tools);
        channelNum_lineEdit->setObjectName("channelNum_lineEdit");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(channelNum_lineEdit->sizePolicy().hasHeightForWidth());
        channelNum_lineEdit->setSizePolicy(sizePolicy4);

        horizontalLayout_2->addWidget(channelNum_lineEdit);

        load_progressBar = new QProgressBar(tools);
        load_progressBar->setObjectName("load_progressBar");
        load_progressBar->setValue(24);

        horizontalLayout_2->addWidget(load_progressBar);


        verticalLayout_2->addWidget(tools);

        tableView = new QTableView(data);
        tableView->setObjectName("tableView");
        tableView->setStyleSheet(QString::fromUtf8("/* ========== \345\237\272\347\241\200\350\241\250\346\240\274\346\240\267\345\274\217 ========== */\n"
"QTableView {\n"
"    border: 1px solid #3A3C40;\n"
"    background-color: #25272B;  /* \346\257\224\344\270\273\350\203\214\346\231\257\347\250\215\346\265\205\347\232\204\346\267\261\350\211\262 */\n"
"    gridline-color: #3A3C40;\n"
"    border-radius: 4px;\n"
"    font-family: \"Segoe UI\", \"Microsoft YaHei\", sans-serif;\n"
"    font-size: 14px;  /* \347\250\215\345\260\217\347\232\204\345\255\227\345\217\267\346\217\220\351\253\230\345\217\257\350\257\273\346\200\247 */\n"
"    selection-background-color: #3A5F8A;\n"
"    selection-color: #E0E2E5;\n"
"    outline: 0;\n"
"    alternate-background-color: #2D2F33;  /* \344\272\244\346\233\277\350\241\214\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"/* ========== \350\241\250\345\244\264\346\240\267\345\274\217 ========== */\n"
"QHeaderView {\n"
"    background-color: #2D2F33;  /* \346\257\224\350\241\250\346\240\274\350\203\214\346\231\257\347\225\245\344\272"
                        "\256 */\n"
"    border: none;\n"
"    border-bottom: 1px solid #3A3C40;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: transparent;\n"
"    color: #C5C8CF;\n"
"    padding: 8px 0;  /* \345\207\217\345\260\221\345\206\205\350\276\271\350\267\235 */\n"
"    border: none;\n"
"    border-right: 1px solid #3A3C40;\n"
"    font-weight: 600;  /* \345\212\240\347\262\227\350\241\250\345\244\264\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"QHeaderView::section:hover {\n"
"    background-color: #35373B;  /* \346\202\254\345\201\234\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"QHeaderView::section:checked {\n"
"    background-color: #3A5F8A;  /* \351\200\211\344\270\255\347\212\266\346\200\201\344\275\277\347\224\250\344\270\273\351\242\230\350\223\235\350\211\262 */\n"
"    color: white;\n"
"}\n"
"\n"
"/* ========== \345\215\225\345\205\203\346\240\274\346\240\267\345\274\217 ========== */\n"
"QTableView::item {\n"
"    color: #D3D6DB;\n"
"    border-bottom: 1px solid #3A3C40;\n"
"    /*padding: 6px 8px;   \351"
                        "\200\202\344\270\255\347\232\204\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"/* \344\272\244\346\233\277\350\241\214\351\242\234\350\211\262 - \346\257\224\345\237\272\347\241\200\350\203\214\346\231\257\347\250\215\344\272\256 */\n"
"QTableView::item:alternate {\n"
"    background-color: #2A2C30;\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\346\225\210\346\236\234 - \344\275\277\347\224\250\345\215\212\351\200\217\346\230\216\350\223\235\350\211\262 */\n"
"QTableView::item:hover {\n"
"    background-color: rgba(58, 143, 230, 0.15);\n"
"}\n"
"\n"
"/* \351\200\211\344\270\255\350\241\214\346\240\267\345\274\217 - \346\267\261\350\223\235\350\211\262 */\n"
"QTableView::item:selected {\n"
"    background-color: #3A5F8A;\n"
"    color: white;\n"
"}\n"
"\n"
"/* \351\200\211\344\270\255\350\241\214\344\275\206\346\227\240\347\204\246\347\202\271\346\227\266\347\232\204\346\240\267\345\274\217 */\n"
"QTableView::item:selected:!active {\n"
"    background-color: #2D4A6B;\n"
"}\n"
"\n"
"/* ========== \350\241\250"
                        "\346\240\274\350\247\222\351\203\250\346\240\267\345\274\217 ========== */\n"
"QTableCornerButton::section {\n"
"    background-color: #2D2F33;\n"
"    border: none;\n"
"    border-bottom: 1px solid #3A3C40;\n"
"    border-right: 1px solid #3A3C40;\n"
"}\n"
"\n"
"/* ========== \346\273\232\345\212\250\346\235\241\346\240\267\345\274\217 ========== */\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: #25272B;\n"
"    width: 10px;  /* \347\250\215\345\256\275\347\232\204\346\273\232\345\212\250\346\235\241 */\n"
"    margin: 0;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #3E4044;\n"
"    border-radius: 5px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #4A4D51;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    border: none;\n"
"    background: #25272B;\n"
"    height: 10px;\n"
"    margin: 0;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background: #3E4044;\n"
"    border-radius: 5px;\n"
"    min-width: 30px;\n"
"}\n"
""
                        "\n"
"/* \347\247\273\351\231\244\346\273\232\345\212\250\346\235\241\347\256\255\345\244\264 */\n"
"QScrollBar::add-line, QScrollBar::sub-line,\n"
"QScrollBar::add-page, QScrollBar::sub-page {\n"
"    background: none;\n"
"    border: none;\n"
"}\n"
"\n"
"/* ========== \347\211\271\346\256\212\347\212\266\346\200\201 ========== */\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QTableView:disabled {\n"
"    color: #6A6D72;\n"
"    background-color: #25272B;\n"
"}\n"
"\n"
"/* \345\217\252\350\257\273\347\212\266\346\200\201 */\n"
"QTableView:read-only {\n"
"    background-color: #25272B;\n"
"}\n"
"QCheckBox {\n"
"    color: #D3D6DB;\n"
"    spacing: 8px;\n"
"    padding: 2px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"    border: 1px solid #3A3C40;\n"
"    border-radius: 3px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #2D2F33, stop:1 #25272B);\n"
"    transition: all 0.3s ease;  /* \345\271\263\346\273\221\350\277"
                        "\207\346\270\241\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                stop:0 #3A5F8A, stop:1 #2D4A6B);\n"
"    image: url(:/icons/checkmark_white.svg);\n"
"    transform: scale(1.05);  /* \350\275\273\345\276\256\346\224\276\345\244\247\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* ========== \344\270\215\345\217\257\347\274\226\350\276\221\345\215\225\345\205\203\346\240\274\346\240\267\345\274\217 ========== */\n"
"/* \344\275\277\347\224\250\345\261\236\346\200\247\351\200\211\346\213\251\345\231\250\346\235\245\347\262\276\347\241\256\345\214\271\351\205\215\344\270\215\345\217\257\347\274\226\350\276\221\345\215\225\345\205\203\346\240\274 */\n"
"QTableView::item[readOnly=\"true\"] {\n"
"    background-color: #2A2C30;\n"
"    color: #8A8D93;\n"
"    border-right: 1px dashed #3A3C40;\n"
"}\n"
"\n"
"/* \344\272\244\346\233\277\350\241\214\344\270\255\347\232\204\344\270\215\345\217\257\347\274\226\350\276\221\345"
                        "\215\225\345\205\203\346\240\274 */\n"
"QTableView::item[readOnly=\"true\"]:alternate {\n"
"    background-color: #25272B;\n"
"}\n"
"\n"
"/* \351\200\211\344\270\255\347\212\266\346\200\201\344\270\213\347\232\204\344\270\215\345\217\257\347\274\226\350\276\221\345\215\225\345\205\203\346\240\274 */\n"
"QTableView::item[readOnly=\"true\"]:selected {\n"
"    background-color: #2D4A6B;\n"
"    color: #B0B3B8;\n"
"}\n"
""));

        verticalLayout_2->addWidget(tableView);


        verticalLayout->addWidget(data);

        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);


        retranslateUi(termial);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(termial);
    } // setupUi

    void retranslateUi(QWidget *termial)
    {
        termial->setWindowTitle(QCoreApplication::translate("termial", "\346\216\247\345\210\266\347\273\210\347\253\257", nullptr));
#if QT_CONFIG(tooltip)
        serialport_comboBox->setToolTip(QCoreApplication::translate("termial", "\350\257\267\351\200\211\346\213\251\345\257\271\345\272\224\344\270\262\345\217\243", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        serialportFlash_pushButton->setToolTip(QCoreApplication::translate("termial", "\345\210\267\346\226\260\344\270\262\345\217\243\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        serialportFlash_pushButton->setText(QString());
#if QT_CONFIG(tooltip)
        serialportLink_pushButton->setToolTip(QCoreApplication::translate("termial", "\350\277\236\346\216\245\344\270\262\345\217\243", nullptr));
#endif // QT_CONFIG(tooltip)
        serialportLink_pushButton->setText(QCoreApplication::translate("termial", "\350\277\236\346\216\245", nullptr));
#if QT_CONFIG(tooltip)
        language_comboBox->setToolTip(QCoreApplication::translate("termial", "\351\200\211\346\213\251\350\257\255\350\250\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkAll_pushButton->setToolTip(QCoreApplication::translate("termial", "\345\205\250\351\200\211", nullptr));
#endif // QT_CONFIG(tooltip)
        checkAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\351\200\211", nullptr));
#if QT_CONFIG(tooltip)
        checkNotAll_pushButton->setToolTip(QCoreApplication::translate("termial", "\345\217\226\346\266\210\345\205\250\351\200\211", nullptr));
#endif // QT_CONFIG(tooltip)
        checkNotAll_pushButton->setText(QCoreApplication::translate("termial", "\345\205\250\344\270\215\351\200\211", nullptr));
#if QT_CONFIG(tooltip)
        read_btn->setToolTip(QCoreApplication::translate("termial", "\350\257\273\345\217\226\344\270\262\345\217\243\346\225\260\346\215\256", nullptr));
#endif // QT_CONFIG(tooltip)
        read_btn->setText(QCoreApplication::translate("termial", "\350\257\273\345\217\226", nullptr));
#if QT_CONFIG(tooltip)
        send_btn->setToolTip(QCoreApplication::translate("termial", "\345\217\221\351\200\201\344\270\262\345\217\243\346\225\260\346\215\256", nullptr));
#endif // QT_CONFIG(tooltip)
        send_btn->setText(QCoreApplication::translate("termial", "\345\217\221\351\200\201", nullptr));
#if QT_CONFIG(tooltip)
        save_pushButton->setToolTip(QCoreApplication::translate("termial", "\344\277\235\345\255\230\344\277\241\351\201\223\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        save_pushButton->setText(QCoreApplication::translate("termial", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(tooltip)
        open_pushButton->setToolTip(QCoreApplication::translate("termial", "\345\206\231\345\205\245\344\277\241\351\201\223\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        open_pushButton->setText(QCoreApplication::translate("termial", "\346\211\223\345\274\200", nullptr));
        label_31->setText(QCoreApplication::translate("termial", "0~", nullptr));
#if QT_CONFIG(tooltip)
        channelMaxNum_spinBox->setToolTip(QCoreApplication::translate("termial", "\345\277\253\351\200\237\345\213\276\351\200\211\344\277\241\351\201\223", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        channelNum_lineEdit->setToolTip(QCoreApplication::translate("termial", "\350\267\263\350\275\254\350\207\263\345\257\271\345\272\224\344\277\241\351\201\223\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
        channelNum_lineEdit->setPlaceholderText(QCoreApplication::translate("termial", "\350\267\263\350\275\254Channel", nullptr));
#if QT_CONFIG(tooltip)
        tableView->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("termial", "\347\274\226\347\250\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class termial: public Ui_termial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERMIAL_H
