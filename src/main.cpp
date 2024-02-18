#include "mainwindow.h"
#include <QApplication>
#include <string>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    myDataBase::Instance();
    return a.exec();
}
