//#include "mainwindow.h"
#include "window.h"
#include "model.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    Model m;
    Window w;
    w.show();
    m.readFile();
    return a.exec();
}
