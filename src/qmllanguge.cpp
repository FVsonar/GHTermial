#include "qmllanguge.h"

QmlLanguage::QmlLanguage(QGuiApplication &app, QQmlApplicationEngine& engine)
{
    m_app = &app;
    m_engine = &engine;
}


void QmlLanguage::setLocalLanguage(){
    QTranslator translator;
    QLocale locale;
    if( locale.language() == QLocale::English ) {
        translator.load(":/en_US.qm");
    }
    else if( locale.language() == QLocale::Chinese ) {
        translator.load(":/zh_CN.qm");
    }
    m_app->installTranslator(&translator);
    //重新载入语言包
    m_engine->retranslate();
}


void QmlLanguage::setLanguage(int indexOfLanguage)
{
    QTranslator translator;
    if (indexOfLanguage == 0)
    {
        translator.load(":/en_US.qm");  //注意路径
    }else if (indexOfLanguage == 1) {
        translator.load(":/zh_CN.qm");
    }else{
        translator.load(":/en_US.qm");
    }
    m_app->installTranslator(&translator);
    m_engine->retranslate();
}

int QmlLanguage::getLocalLanguage(){
    QLocale locale;
    if(locale.language() == QLocale::English){
        return 0;
    }else if(locale.language() == QLocale::Chinese){
        return 1;
    }
    return 0;
}
