#include "window.h"
#include "controller.h"
#include "lineChart.h"
#include "pieChart.h"
#include "barChart.h"

Window::Window(QWidget *parent):QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    initMenu(mainLayout);
    QHBoxLayout* visualisationLayout=new QHBoxLayout;
    initDataLayout(visualisationLayout);
    initChartLayout(visualisationLayout);
    mainLayout->addLayout(visualisationLayout);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    resize(QSize(1280,720));
}


void Window::initMenu(QVBoxLayout* mainLayout){
    QMenuBar* menuBar = new QMenuBar(this);
    file = new QMenu("File",menuBar);
    chart = new QMenu("Chart",menuBar);
    file->addAction(new QAction("New",file));
    file->addAction(new QAction("Open",file));
    file->addAction(new QAction("Save",file));
    file->addAction(new QAction("Close",file));
    chart->addAction(new QAction("Show Bar Chart",chart));
    chart->addAction(new QAction("Show Line Chart",chart));
    chart->addAction(new QAction("Show Pie Chart",chart));
    connect(file->actions().at(3),SIGNAL(triggered()),this,SLOT(close()));
    menuBar->addMenu(file);
    menuBar->addMenu(chart);
    mainLayout->addWidget(menuBar);
}

void Window::initDataLayout(QHBoxLayout* mainLayout){
    QGridLayout* dataL=new QGridLayout;
    QFrame* datas=new QFrame;
    QLabel* id=new QLabel("Id",datas);
    QLabel* label=new QLabel("Label",datas);
    QLabel* value=new QLabel("Value",datas);
    datas->setMinimumSize(480,640);
    datas->setStyleSheet("background-color: rgb(0,255,0)");
    datas->setLayout(dataL);
    dataL->addWidget(id);
    dataL->addWidget(label,0,1);
    dataL->addWidget(value,0,2);
    mainLayout->addWidget(datas);
}

void Window::initChartLayout(QHBoxLayout* mainLayout){
    chartL=new QGridLayout;
    QFrame* charts=new QFrame;
    charts->setLayout(chartL);
    charts->setMinimumSize(640,480);
    charts->setStyleSheet("background-color: rgb(0,0,0)");
    mainLayout->addWidget(charts);
}

void Window::setController(Controller* c){
    controller=c;
    connect(file->actions().at(0), SIGNAL(triggered()), controller, SLOT(newFile()));
    connect(file->actions().at(1), SIGNAL(triggered()), controller, SLOT(openFile()));
    connect(file->actions().at(2),  SIGNAL(triggered()), controller, SLOT(saveFile()));
    connect(chart->actions().at(0),  SIGNAL(triggered()), controller, SLOT(loadBarChart()));
    connect(chart->actions().at(1),  SIGNAL(triggered()), controller, SLOT(loadLineChart()));
    connect(chart->actions().at(2),  SIGNAL(triggered()), controller, SLOT(loadPieChart()));
}

void Window::createLineChart(DataHandler d){
   LineChart* charted=new LineChart(d);
   charted->setData();
   showChart(charted->showChart());
}

void Window::showChart(QChart* c){
    QChartView* cw = new QChartView(c);
    cw->setRenderHint(QPainter::Antialiasing);
    chartL->addWidget(cw);
}

QString Window::showNewFileDialog(DataHandler& d){
    QDialog* dialog=new QDialog(this);
    QPlainTextEdit* fileName=new QPlainTextEdit(this);
    fileName->setPlainText("My chart");
    dialog->setLayout(new QHBoxLayout);
    dialog->layout()->addWidget(new QLabel("Set the title for your graph (WARNING, YOU CANNOT CHANGE IT!)",dialog));
    dialog->layout()->addWidget(fileName);
    dialog->layout()->setAlignment(Qt::AlignCenter);
    dialog->setMinimumWidth(120);
    dialog->setMaximumWidth(480);
    dialog->setMinimumHeight(120);
    dialog->setMaximumHeight(480);
    dialog->show();
    return nullptr;
}

void Window::showWarning(const QString& message){
    QDialog* dialog=new QDialog(this);
    dialog->setLayout(new QHBoxLayout);
    dialog->layout()->addWidget(new QLabel(message,dialog));
    dialog->layout()->setAlignment(Qt::AlignCenter);
    dialog->setMinimumWidth(120);
    dialog->setMaximumWidth(480);
    dialog->setMinimumHeight(120);
    dialog->setMaximumHeight(480);
    dialog->show();
}

QString Window::showSaveDialog(){
    QString filename=QFileDialog::getSaveFileName(this, tr("Save file"),"./home",tr("XML files (*.xml)"));
    return filename;
}

QString Window::showOpenDialog(){
    QString filename=QFileDialog::getOpenFileName(this, tr("Open file"),"./home",tr("XML files (*.xml)"));
    return filename;
}
