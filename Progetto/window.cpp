#include "window.h"
#include "controller.h"

Window::Window(QWidget *parent):QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* file = new QMenu("File",menuBar);
    QMenu* chart = new QMenu("Chart",menuBar);
    file->addAction(new QAction("New",file));
    file->addAction(new QAction("Open",file));
    file->addAction(new QAction("Save",file));
    file->addAction(new QAction("Close",file));
    chart->addAction(new QAction("Change",chart));
    connect(file->actions().at(3),SIGNAL(triggered()),this,SLOT(close()));
    menuBar->addMenu(file);
    menuBar->addMenu(chart);
    mainLayout->addWidget(menuBar);
    //initMenu(mainLayout);
qDebug()<<file->actions().size();
    //initDataChartsLayout(mainLayout);
qDebug()<<file->actions().size();
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
qDebug()<<file->actions().size();
    //resize(QSize(1280,720));
}


void Window::initMenu(QVBoxLayout* mainLayout){

}

void Window::initDataChartsLayout(QVBoxLayout* mainLayout){
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

void Window::setController(Controller* c){
    qDebug()<<file->actions().size();
    controller=c;
    if(file->actions().size()<1){
        qDebug()<<"No connect!";
    }
    else{
        connect(file->actions().at(1), SIGNAL(triggered()), controller, SLOT(openFile()));
        //connect(file->actions().at(2),  SIGNAL(triggered()), controller, SLOT(saveFile()));
        //connect(chart->actions().at(0),  SIGNAL(triggered()), controller, SLOT(/**/));
    }
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
