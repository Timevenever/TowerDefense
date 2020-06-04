#include "mainwindow.h"
#include "start.h"
#include <QApplication>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start s;
    s.show();
    /*MainWindow w;
    w.show();*/

    return a.exec();
}
