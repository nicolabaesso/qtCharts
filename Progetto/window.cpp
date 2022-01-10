#include "window.h"
#include "controller.h"


Window::Window(QWidget *parent):QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* menuLayout=new QHBoxLayout;
    initMenu(menuLayout);
    QHBoxLayout* toolbarLayout=new QHBoxLayout;
    initToolBar(toolbarLayout);
    QHBoxLayout* visualisationLayout=new QHBoxLayout;
    initDataLayout(visualisationLayout);
    initChartLayout(visualisationLayout);
    mainLayout->addLayout(menuLayout);
    mainLayout->addLayout(toolbarLayout);
    mainLayout->addLayout(visualisationLayout);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    resize(QSize(1280,720));
}


void Window::initMenu(QHBoxLayout* mainLayout){
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

void Window::initToolBar(QHBoxLayout* mainLayout){
    newFileButton=new QPushButton(this);
    openFileButton=new QPushButton(this);
    saveFileButton=new QPushButton(this);
    loadBarChartButton=new QPushButton(this);
    loadLineChartButton=new QPushButton(this);
    loadPieChartButton=new QPushButton(this);
    newFileButton->setText("New File");
    openFileButton->setText("Open File");
    saveFileButton->setText("Save File");
    loadBarChartButton->setText("Load Bar Chart");
    loadLineChartButton->setText("Load Line Chart");
    loadPieChartButton->setText("Load Pie Chart");
    mainLayout->addWidget(newFileButton);
    mainLayout->addWidget(openFileButton);
    mainLayout->addWidget(saveFileButton);
    mainLayout->addWidget(loadBarChartButton);
    mainLayout->addWidget(loadLineChartButton);
    mainLayout->addWidget(loadPieChartButton);
}

void Window::initDataLayout(QHBoxLayout* mainLayout){
    dataL=new QGridLayout;
    QFrame* datas=new QFrame;
    QLabel* id=new QLabel("Id",datas);
    QLabel* label=new QLabel("Label",datas);
    QLabel* value=new QLabel("Value",datas);
    addDataButton=new QPushButton(this);
    addDataButton->setText("Add data");
    datas->setMinimumSize(480,640);
    datas->setLayout(dataL);
    dataL->addWidget(addDataButton,0,1);
    dataL->addWidget(id,1,0);
    dataL->addWidget(label,1,1);
    dataL->addWidget(value,1,2);
    mainLayout->addWidget(datas);
}

void Window::initChartLayout(QHBoxLayout* mainLayout){
    chartL=new QGridLayout;
    QFrame* charts=new QFrame;
    charts->setLayout(chartL);
    charts->setMinimumSize(640,480);
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
    connect(newFileButton, SIGNAL(clicked()), controller, SLOT(newFile()));
    connect(openFileButton, SIGNAL(clicked()), controller, SLOT(openFile()));
    connect(saveFileButton, SIGNAL(clicked()), controller, SLOT(saveFile()));
    connect(loadBarChartButton, SIGNAL(clicked()), controller, SLOT(loadBarChart()));
    connect(loadLineChartButton, SIGNAL(clicked()), controller, SLOT(loadLineChart()));
    connect(loadPieChartButton, SIGNAL(clicked()), controller, SLOT(loadPieChart()));
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
    QPushButton* ok=new QPushButton(this);
    QGridLayout* dialogLayout=new QGridLayout(this);
    fileName->setPlainText("My chart");
    ok->setText("Ok");
    dialog->setLayout(dialogLayout);
    dialogLayout->addWidget(new QLabel("Set the title for your graph (WARNING, YOU CANNOT CHANGE IT!)",dialog),0,1);
    dialogLayout->addWidget(fileName,1,1);
    dialogLayout->addWidget(ok,2,1);
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
