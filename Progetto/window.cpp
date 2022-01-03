#include "window.h"
#include "controller.h"

void Window::initMenu(QVBoxLayout* mainLayout)
{
    QHBoxLayout* menuLayout = new QHBoxLayout;
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* file = new QMenu("File",menuBar);
    QMenu* chart = new QMenu("Chart",menuBar);
    menuBar->addMenu(file);
    menuBar->addMenu(chart);
    file->addAction(new QAction("Open",file));
    file->addAction(new QAction("Save",file));
    chart->addAction(new QAction("Change",chart));
    menuLayout->addWidget(menuBar);
    mainLayout->addLayout(menuLayout);
}

void Window::initDataChartsLayout(QVBoxLayout* mainLayout)
{
    QHBoxLayout* dataChartLayout = new QHBoxLayout;
    QFrame* charts=new QFrame;
    charts->setMinimumSize(640,480);
    charts->setStyleSheet("background-color: rgb(0,0,0)");
    QFrame* datas=new QFrame;
    datas->setMinimumSize(480,640);
    datas->setStyleSheet("background-color: rgb(0,255,0)");
    dataChartLayout->addWidget(datas);
    dataChartLayout->addWidget(charts);
    mainLayout->addLayout(dataChartLayout);
}

Window::Window(QWidget *parent):QWidget(parent){
    //create the layout
    QVBoxLayout* mainLayout = new QVBoxLayout;

    initMenu(mainLayout);

    initDataChartsLayout(mainLayout);

    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    resize(QSize(640,480));
}
