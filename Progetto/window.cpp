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

void Window::initMenu(QHBoxLayout* mainLayout){
    QMenuBar* menuBar = new QMenuBar(this);
    file = new QMenu("File",menuBar);
    chart = new QMenu("Grafico",menuBar);
    file->addAction(new QAction("Nuovo",file));
    file->addAction(new QAction("Apri",file));
    file->addAction(new QAction("Salva",file));
    file->addAction(new QAction("Salva con nome",file));
    file->addAction(new QAction("Chiudi",file));
    chart->addAction(new QAction("Mostra Istogramma",chart));
    chart->addAction(new QAction("Mostra Diagramma Cartesiano",chart));
    chart->addAction(new QAction("Mostra Areogramma (a torta)",chart));

    menuBar->addMenu(file);
    menuBar->addMenu(chart);
    mainLayout->addWidget(menuBar);
}

void Window::initToolBar(QHBoxLayout* mainLayout){
    newFileButton=new QPushButton(this);
    openFileButton=new QPushButton(this);
    saveFileButton=new QPushButton(this);
    saveNewFileButton=new QPushButton(this);
    loadBarChartButton=new QPushButton(this);
    loadLineChartButton=new QPushButton(this);
    loadPieChartButton=new QPushButton(this);
    newFileButton->setText("Nuovo File");
    openFileButton->setText("Apri File");
    saveFileButton->setText("Salva File");
    saveNewFileButton->setText("Salva File con nome");
    loadBarChartButton->setText("Mostra Istogramma");
    loadLineChartButton->setText("Mostra Diagramma Cartesiano");
    loadPieChartButton->setText("Mostra Areogramma a torta");
    mainLayout->addWidget(newFileButton);
    mainLayout->addWidget(openFileButton);
    mainLayout->addWidget(saveFileButton);
    mainLayout->addWidget(saveNewFileButton);
    mainLayout->addWidget(loadBarChartButton);
    mainLayout->addWidget(loadLineChartButton);
    mainLayout->addWidget(loadPieChartButton);
}

void Window::initDataLayout(QHBoxLayout* mainLayout){
    dataFrame=new QFrame;
    initDataFrame(dataFrame);
    mainLayout->addWidget(dataFrame);
}

void Window::initDataFrame(QFrame* dataFrame){
    rowGridLayoutData=0;
    columnGridLayoutData=0;
    dataL=new QGridLayout;
    idInit=new QLabel("Id",dataFrame);
    labelInit=new QLabel("Etichetta",dataFrame);
    valueInit=new QLabel("Valore",dataFrame);
    addDataButton=new QPushButton(this);
    addDataButton->setText("Aggiungi dati");
    saveDataButton=new QPushButton(this);
    saveDataButton->setText("Salva dati");
    deleteDataButton=new QPushButton(this);
    deleteDataButton->setText("Elimina dati");
    dataFrame->setLayout(dataL);
    idInit->resize(50,50);
    labelInit->resize(50,50);
    valueInit->resize(50,50);
    dataL->addWidget(addDataButton,rowGridLayoutData,0);
    dataL->addWidget(saveDataButton,rowGridLayoutData,1);
    dataL->addWidget(deleteDataButton,rowGridLayoutData,2);
    rowGridLayoutData++;
    dataL->addWidget(idInit,rowGridLayoutData,columnGridLayoutData);
    columnGridLayoutData++;
    dataL->addWidget(labelInit,rowGridLayoutData,columnGridLayoutData);
    columnGridLayoutData++;
    dataL->addWidget(valueInit,rowGridLayoutData,columnGridLayoutData);
    columnGridLayoutData=0;
    rowGridLayoutData++;

}

void Window::initExampleValues(DataHandler readedData){
    initVectors(&readedData);
    int size=readedData.getDataOnFile().size();
    QString pos="";
    QString lab="";
    QString data="";
    for(int i=0;i<size;i++){
        string p=std::to_string(i);
        pos=pos.fromStdString(p);
        idVector.at(i)=new QLabel(pos);
        dataL->addWidget(idVector.at(i),rowGridLayoutData,columnGridLayoutData);
        columnGridLayoutData++;
        lab=lab.fromStdString(readedData.getDataOnFile().at(i).getLabel());
        labelVector.at(i)=new QLineEdit;
        labelVector.at(i)->setText(lab);
        dataL->addWidget(labelVector.at(i),rowGridLayoutData,columnGridLayoutData);
        columnGridLayoutData++;
        data=data.number(readedData.getDataOnFile().at(i).getData());
        dataVector.at(i)=new QLineEdit;
        dataVector.at(i)->setText(data);
        dataL->addWidget(dataVector.at(i),rowGridLayoutData,columnGridLayoutData);
        rowGridLayoutData++;
        columnGridLayoutData=0;
    }
}

void Window::initDataValues(DataHandler readedData){
    initVectors(&readedData);
    initDataFrame(dataFrame);
    setDataConnect();
    int size=readedData.getDataOnFile().size();
    QString pos="";
    QString lab="";
    QString data="";
    for(int i=0;i<size;i++){
        string p=std::to_string(i);
        pos=pos.fromStdString(p);
        idVector.at(i)=new QLabel(pos);
        dataL->addWidget(idVector.at(i),rowGridLayoutData,columnGridLayoutData);
        columnGridLayoutData++;
        lab=lab.fromStdString(readedData.getDataOnFile().at(i).getLabel());
        labelVector.at(i)=new QLineEdit;
        labelVector.at(i)->setText(lab);
        dataL->addWidget(labelVector.at(i),rowGridLayoutData,columnGridLayoutData);
        columnGridLayoutData++;
        data=data.number(readedData.getDataOnFile().at(i).getData());
        dataVector.at(i)=new QLineEdit;
        dataVector.at(i)->setText(data);
        dataL->addWidget(dataVector.at(i),rowGridLayoutData,columnGridLayoutData);
        rowGridLayoutData++;
        columnGridLayoutData=0;
    }
}

void Window::initVectors(DataHandler* readedData){
    for(unsigned int i=0;i<readedData->getDataOnFile().size();i++){
        idVector.push_back(new QLabel);
        labelVector.push_back(new QLineEdit);
        dataVector.push_back(new QLineEdit);
    }
}

void Window::initChartLayout(QHBoxLayout* mainLayout){
    chartL=new QGridLayout;
    QFrame* charts=new QFrame;
    charts->setLayout(chartL);
    mainLayout->addWidget(charts);
}

void Window::removeDataValues(){
    QLayoutItem* child;
    columnGridLayoutData=2;
    while(rowGridLayoutData != -1){
        child=dataFrame->layout()->takeAt(rowGridLayoutData+columnGridLayoutData);
        delete child;
        if(columnGridLayoutData==0){
            columnGridLayoutData=2;
            rowGridLayoutData--;
        }
        else{
            columnGridLayoutData--;
        }
    }
    columnGridLayoutData=0;
    delete dataFrame->layout();
    idVector.clear();
    labelVector.clear();
    dataVector.clear();
}



void Window::deletePreviousChart(){
    chartL->removeWidget(chartViewer);
    delete chartViewer;
}

QString Window::getNewFileName(){
    if(fileName==nullptr){
        return "Il mio grafico";
    }
    return fileName->toPlainText();
}

void Window::setController(Controller* c){
    controller=c;
    connect(file->actions().at(0), SIGNAL(triggered()), controller, SLOT(newFile()));
    connect(file->actions().at(1), SIGNAL(triggered()), controller, SLOT(openFile()));
    connect(file->actions().at(2),  SIGNAL(triggered()), controller, SLOT(saveFile()));
    connect(file->actions().at(3), SIGNAL(triggered()), controller, SLOT(saveNewFile()));
    connect(file->actions().at(4), SIGNAL(triggered()), this, SLOT(close()));
    connect(chart->actions().at(0),  SIGNAL(triggered()), controller, SLOT(loadBarChart()));
    connect(chart->actions().at(1),  SIGNAL(triggered()), controller, SLOT(loadLineChart()));
    connect(chart->actions().at(2),  SIGNAL(triggered()), controller, SLOT(loadPieChart()));
    connect(newFileButton, SIGNAL(clicked()), controller, SLOT(newFile()));
    connect(openFileButton, SIGNAL(clicked()), controller, SLOT(openFile()));
    connect(saveFileButton, SIGNAL(clicked()), controller, SLOT(saveFile()));
    connect(saveNewFileButton, SIGNAL(clicked()), controller, SLOT(saveFile()));
    connect(loadBarChartButton, SIGNAL(clicked()), controller, SLOT(loadBarChart()));
    connect(loadLineChartButton, SIGNAL(clicked()), controller, SLOT(loadLineChart()));
    connect(loadPieChartButton, SIGNAL(clicked()), controller, SLOT(loadPieChart()));
    setDataConnect();
}

void Window::setDataConnect(){
    //connect(addDataButton, SIGNAL(clicked()), controller, SLOT(newFile()));
    connect(saveDataButton, SIGNAL(clicked()), controller, SLOT(saveFile()));
    //connect(deleteDataButton, SIGNAL(clicked()), controller, SLOT(newFile()));
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

void Window::closeWarning(){
    warningDialog->close();
    delete warningDialog;
}

void Window::showWarning(const QString& message){
    warningDialog=new QDialog(this);
    exitWarningButton=new QPushButton(this);
    warningDialog->setLayout(new QVBoxLayout);
    exitWarningButton->setText("Ok");
    warningDialog->layout()->addWidget(new QLabel(message,warningDialog));
    warningDialog->layout()->addWidget(new QLabel("",warningDialog));
    warningDialog->layout()->addWidget(exitWarningButton);
    warningDialog->layout()->setAlignment(Qt::AlignCenter);
    warningDialog->setMinimumWidth(120);
    warningDialog->setMaximumWidth(480);
    warningDialog->setMinimumHeight(120);
    warningDialog->setMaximumHeight(480);
    warningDialog->show();
    connect(exitWarningButton, SIGNAL(clicked()), this, SLOT(closeWarning()));
}

QString Window::showSaveDialog(){
    QString filename=QFileDialog::getSaveFileName(this, tr("Save file"),"./home",tr("XML files (*.xml)"));
    return filename;
}

QString Window::showOpenDialog(){
    QString filename=QFileDialog::getOpenFileName(this, tr("Open file"),"./home",tr("XML files (*.xml)"));
    return filename;
}
