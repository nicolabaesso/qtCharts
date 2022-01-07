#include "window.h"
#include "controller.h"


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

void Window::deletePreviousChart(){
    chartL->removeWidget(chartViewer);
    delete chartViewer;
}

void Window::createChart(Chart* c){
    if(dynamic_cast<LineChart*>(c)){
        static_cast<LineChart*>(c)->setData();
        showChart(static_cast<LineChart*>(c)->showChart());
        return;
    }
    if(dynamic_cast<BarChart*>(c)){
        static_cast<BarChart*>(c)->setData();
        showChart(static_cast<BarChart*>(c)->showChart());
        return;
    }
    if(dynamic_cast<PieChart*>(c)){
        static_cast<PieChart*>(c)->setData();
        showChart(static_cast<PieChart*>(c)->showChart());
        return;
    }
}

void Window::showChart(QChart* c){
    chartViewer = new QChartView(c);
    chartViewer->setRenderHint(QPainter::Antialiasing);
    chartL->addWidget(chartViewer);
}

QString Window::showNewFileDialog(DataHandler& d){
    QDialog* dialog=new QDialog(this);
    fileName=new QPlainTextEdit(this);
    //QDialogButtonBox* confirm=new QDialogButtonBox(this);
    QPushButton* ok=new QPushButton(this);
    fileName->setPlainText("My chart");
    dialog->setLayout(new QGridLayout);
    dialog->layout()->addWidget(new QLabel("Set the title for your graph (WARNING, YOU CANNOT CHANGE IT!)",dialog));
    dialog->layout()->addWidget(fileName);
    dialog->layout()->addWidget(ok);
    dialog->setMinimumWidth(120);
    dialog->setMaximumWidth(480);
    dialog->setMinimumHeight(120);
    dialog->setMaximumHeight(480);
    dialog->show();
    /*QKeyEvent* click=new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
    QString tString="";
    while(true){
        if(click->key()==Qt::Key_Enter){
            tString=fileName->toPlainText();
            d.setTitle(tString.toStdString());
        }
    }*/
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
