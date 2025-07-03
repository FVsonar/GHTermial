#include "termial.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QApplication::setStyle("WindowsVista");
    // 设置应用程序的字体
    // 隐藏默认标题栏和边框
    QFont font = a.font();
    font.setFamily("Microsoft YaHei");
    font.setPointSize(12); // 设置字体大小为12点
    a.setFont(font);
    termial w;
    // 无边框
    // w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
