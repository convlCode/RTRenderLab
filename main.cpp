#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"fuck"<<endl;
    MainWindow w;
    w.show();

    return a.exec();
}
