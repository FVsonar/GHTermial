QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DAO/channel_dao.cpp \
    DAO/channeldmr_dao.cpp \
    DAO/dmr_dao.cpp \
    Delegates/checkboxdelegate.cpp \
    Delegates/comboboxdelegate.cpp \
    Delegates/doublespinboxdelegate.cpp \
    Delegates/spinboxdelegate.cpp \
    Entity/a_b.cpp \
    Entity/channel.cpp \
    Entity/channeldmr.cpp \
    Entity/dmr.cpp \
    Entity/stlip.cpp \
    Service/channel_service.cpp \
    Service/dmr_service.cpp \
    Service/SerialPortManager.cpp \
    Service/SerialCommandManager.cpp \
    Tools/serialporttools.cpp \
    Tools/tools.cpp \
    main.cpp \
    termial.cpp

HEADERS += \
    DAO/channel_dao.h \
    DAO/channeldmr_dao.h \
    DAO/dmr_dao.h \
    Delegates/checkboxdelegate.h \
    Delegates/comboboxdelegate.h \
    Delegates/doublespinboxdelegate.h \
    Delegates/spinboxdelegate.h \
    Entity/a_b.h \
    Entity/channel.h \
    Entity/channeldmr.h \
    Entity/dmr.h \
    Entity/stlip.h \
    Service/channel_service.h \
    Service/dmr_service.h \
    Service/SerialPortManager.h \
    Service/SerialCommandManager.h \
    Tools/serialporttools.h \
    Tools/tools.h \
    termial.h

FORMS += \
    termial.ui

TRANSLATIONS = \
    language/lang_Arabic.ts \
    language/lang_Chinese.ts \
    language/lang_English.ts \
    language/lang_French.ts \
    language/lang_German.ts \
    language/lang_Hindi.ts \
    language/lang_Japanese.ts \
    language/lang_Portuguese.ts \
    language/lang_Russian.ts \
    language/lang_Spanish.ts


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc \
    language.qrc

RC_ICONS = GHTermial.ico

DISTFILES += \
    view/新建 文本文档.txt
TARGET = GHTerminal-Beta
