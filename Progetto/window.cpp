#include "window.h"
#include "controller.h"


Window::Window(QWidget *parent):QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* menuLayout=new QHBoxLayout;
    initMenu(menuLayout);
    QHBoxLayout* toolbarLayout=new QHBoxLayout;
    initToolBar(toolbarLayout);
    QHBoxLayout* containerLayout=new QHBoxLayout;
    containerLayout->addLayout(toolbarLayout);
    containerLayout->addWidget(new QLabel);
    QHBoxLayout* visualisationLayout=new QHBoxLayout;
    initDataLayout(visualisationLayout);
    initChartLayout(visualisationLayout);
    mainLayout->addLayout(menuLayout);
    mainLayout->addLayout(containerLayout);
    mainLayout->addLayout(visualisationLayout);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    resize(QSize(1280,720));
}

QString Window::getNewFileName(){
    if(fileName==nullptr){
        return "Il mio grafico";
    }
    return fileName->toPlainText();
}

void Window::initMenu(QHBoxLayout* mainLayout){
    QMenuBar* menuBar = new QMenuBar(this);
    file = new QMenu("File",menuBar);
    chart = new QMenu("Grafico",menuBar);
    file->addAction(new QAction("Nuovo",file));
    file->addAction(new QAction("Apri",file));
    file->addAction(new QAction("Salva",file));
    file->addAction(new QAction("Chiudi",file));
    chart->addAction(new QAction("Mostra Istogramma",chart));
    chart->addAction(new QAction("Mostra Diagramma Cartesiano",chart));
    chart->addAction(new QAction("Mostra Areogramma (a torta)",chart));
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
    newFileButton->setText("Nuovo File");
    openFileButton->setText("Apri File");
    saveFileButton->setText("Salva File");
    loadBarChartButton->setText("Mostra Istogramma");
    loadLineChartButton->setText("Mostra Diagramma Cartesiano");
    loadPieChartButton->setText("Mostra Areogramma a torta");
    mainLayout->addWidget(newFileButton);
    mainLayout->addWidget(openFileButton);
    mainLayout->addWidget(saveFileButton);
    mainLayout->addWidget(loadBarChartButton);
    mainLayout->addWidget(loadLineChartButton);
    mainLayout->addWidget(loadPieChartButton);
}

void Window::initDataLayout(QHBoxLayout* mainLayout){
    rowGridLayoutData=0;
    columnGridLayoutData=0;
    dataL=new QGridLayout;
    QFrame* datas=new QFrame;
    QLabel* id=new QLabel("Id",datas);
    QLabel* label=new QLabel("Label",datas);
    QLabel* value=new QLabel("Value",datas);
    addDataButton=new QPushButton(this);
    addDataButton->setText("Add data");
    datas->setMinimumSize(480,640);
    datas->setLayout(dataL);
    dataL->addWidget(addDataButton,rowGridLayoutData,1);
    rowGridLayoutData++;
    dataL->addWidget(id,rowGridLayoutData,columnGridLayoutData);
    columnGridLayoutData++;
    dataL->addWidget(label,rowGridLayoutData,columnGridLayoutData);
    columnGridLayoutData++;
    dataL->addWidget(value,rowGridLayoutData,columnGridLayoutData);
    columnGridLayoutData=0;
    mainLayout->addWidget(datas);
}

void Window::initDataValues(DataHandler readedData){
    //initVectors(readedData);
    QLabel* id;
    //QPlainTextEdit* labelEdit=new QPlainTextEdit;
    //QPlainTextEdit* dataEdit=new QPlainTextEdit;
    int size=readedData.getDataOnFile().size();
    QString pos="";
    QString lab="";
    QString data="";
    for(int i=0;i<size;i++){
        string p=std::to_string(i);
        id=new QLabel(pos.fromStdString(p));
        dataL->addWidget(id,rowGridLayoutData,columnGridLayoutData);
        //columnGridLayoutData++;
        lab=lab.fromStdString(readedData.getDataOnFile().at(i).getLabel());
        //labelEdit->setPlainText(lab);
        //labelVector.push_back(*labelEdit);
        //dataL->addWidget(&labelVector.at(i),rowGridLayoutData,columnGridLayoutData);
        //columnGridLayoutData++;
        data=data.number(readedData.getDataOnFile().at(i).getData());
        //dataEdit->setPlainText(data);
        //dataVector.push_back(*dataEdit);
        //dataL->addWidget(&dataVector.at(i),rowGridLayoutData,columnGridLayoutData);
        rowGridLayoutData++;
        //columnGridLayoutData=0;
    }
}
/*
void Window::initVectors(DataHandler readedData){
    QPlainTextEdit* label=new QPlainTextEdit;
    QPlainTextEdit* data=new QPlainTextEdit;
    for(unsigned int i=0;i<readedData.getDataOnFile().size();i++){
        labelVector.push_back(*label);
        dataVector.push_back(*data);
    }
}*/

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

void Window::showNewFileDialog(){
    newFileDialog=new QDialog(this);
    fileName=new QPlainTextEdit(this);
    confirmNewFileButton=new QPushButton(this);
    dialogLayout=new QGridLayout(this);
    fileName->setPlainText("Il mio grafico");
    confirmNewFileButton->setText("Ok");
    newFileDialog->setLayout(dialogLayout);
    dialogLayout->addWidget(new QLabel("Scrivi un titolo per il tuo grafico (Attenzione, non lo potrai cambiare!)",newFileDialog),0,1);
    dialogLayout->addWidget(fileName,1,1);
    dialogLayout->addWidget(confirmNewFileButton,2,1);
    dialogLayout->addWidget(new QLabel("",newFileDialog),2,0);
    dialogLayout->addWidget(new QLabel("",newFileDialog),2,2);
    newFileDialog->setMinimumWidth(120);
    newFileDialog->setMaximumWidth(480);
    newFileDialog->setMinimumHeight(120);
    newFileDialog->setMaximumHeight(480);
    newFileDialog->show();
    connect(confirmNewFileButton, SIGNAL(clicked()), controller, SLOT(manageNewFile()));
}

void Window::closeNewFileDialog(){
    newFileDialog->close();
    delete newFileDialog;
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
