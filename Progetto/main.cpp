//#include "mainwindow.h"
#include "window.h"
#include "model.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //MainWindow w;

    Window w;
    Controller c;
    Model m;
    c.setModel(&m);
    c.setView(&w);
    w.setController(&c);
    w.show();
    return a.exec();
}
