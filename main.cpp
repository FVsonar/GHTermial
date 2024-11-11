#include "termial.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    termial w;
    w.show();
    return a.exec();
}
