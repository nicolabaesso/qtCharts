#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QFrame>
#include <QLabel>
#include <QDialog>
#include <QFileDialog>

class Controller;

class Window: public QWidget{
  Q_OBJECT
private:
    Controller* controller;

    QMenu* file;
    QMenu* chart;

    void initMenu(QVBoxLayout* mainLayout);

    void initDataChartsLayout(QVBoxLayout* mainLayout);

public:
    Window(QWidget *parent=nullptr);
    void showWarning(const QString& message);
    QString showSaveDialog();
    QString showOpenDialog();
    void setController(Controller* c);
signals:

};
#endif // WINDOW_H
