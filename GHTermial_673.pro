QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entity/channel.cpp \
    Entity/channeldmr.cpp \
    Entity/dmr.cpp \
    Tools/serialporttools.cpp \
    Tools/tcptools.cpp \
    Tools/tools.cpp \
    clientinfo.cpp \
    main.cpp \
    termial.cpp

HEADERS += \
    Entity/channel.h \
    Entity/channeldmr.h \
    Entity/dmr.h \
    Tools/serialporttools.h \
    Tools/tcptools.h \
    Tools/tools.h \
    clientinfo.h \
    termial.h

FORMS += \
    termial.ui

TRANSLATIONS =  \
    lang_Chinese.ts \
    lang_English.ts \
    lang_German.ts \
    lang_French.ts \
    lang_Russian.ts \
    lang_Japanese.ts \
    lang_Arabic.ts \
    lang_Spanish.ts \
    lang_Portuguese.ts \
    lang_Hindi.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc \
    language.qrc

RC_ICONS = GHTermial.ico
