#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QFrame>

class Window: public QWidget{
  Q_OBJECT
private:
    void initMenu(QVBoxLayout* mainLayout);

    void initDataChartsLayout(QVBoxLayout* mainLayout);

public:
    Window(QWidget *parent=nullptr);
signals:

};
#endif // WINDOW_H
