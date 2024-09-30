#ifndef QMLLANGUGE_H
#define QMLLANGUGE_H

#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class QmlLanguage : public QObject
{
    Q_OBJECT
  public:
      QmlLanguage(QGuiApplication& app, QQmlApplicationEngine &engine);
      //设置为当前系统语言
      void setLocalLanguage();
      //获取当前系统语言，必须添加 Q_INVOKABLE 后才能在前端调用该函数
      Q_INVOKABLE int getLocalLanguage();
      //设置为indexOfLanguage指定的语言
      Q_INVOKABLE void setLanguage(int indexOfLanguage);

  private:
      QGuiApplication *m_app;   // 创建一个Qt图形用户界面应用实例
      QQmlApplicationEngine *m_engine;
};

#endif // QMLLANGUGE_H
