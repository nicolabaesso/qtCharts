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
    visualisationLayout=new QHBoxLayout;
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
    edit=new QMenu("Modifica",menuBar);
    chart = new QMenu("Grafico",menuBar);
    about=new QMenu("Aiuto",menuBar);
    file->addAction(new QAction("Nuovo",file));
    file->addAction(new QAction("Apri",file));
    file->addAction(new QAction("Salva",file));
    file->addAction(new QAction("Salva con nome",file));
    file->addAction(new QAction("Chiudi",file));
    edit->addAction(new QAction("Aggiungi un dato",edit));
    edit->addAction(new QAction("Salva i dati",edit));
    edit->addAction(new QAction("Elimina un dato",edit));
    chart->addAction(new QAction("Cambia il titolo",chart));
    chart->addAction(new QAction("Mostra Istogramma",chart));
    chart->addAction(new QAction("Mostra Diagramma Cartesiano",chart));
    chart->addAction(new QAction("Mostra Areogramma (a torta)",chart));
    about->addAction(new QAction("Informazioni su QtCharts...",about));

    menuBar->addMenu(file);
    menuBar->addMenu(edit);
    menuBar->addMenu(chart);
    menuBar->addMenu(about);
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
    changeTitleButton=new QPushButton(this);
    newFileButton->setText("Nuovo File");
    openFileButton->setText("Apri File");
    saveFileButton->setText("Salva File");
    saveNewFileButton->setText("Salva File con nome");
    loadBarChartButton->setText("Mostra Istogramma");
    loadLineChartButton->setText("Mostra Diagramma Cartesiano");
    loadPieChartButton->setText("Mostra Areogramma a torta");
    changeTitleButton->setText("Cambia il titolo del grafico");
    mainLayout->addWidget(newFileButton);
    mainLayout->addWidget(openFileButton);
    mainLayout->addWidget(saveFileButton);
    mainLayout->addWidget(saveNewFileButton);
    mainLayout->addWidget(changeTitleButton);
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
    addDataButton->setText("Aggiungi un dato");
    saveDataButton=new QPushButton(this);
    saveDataButton->setText("Salva dati");
    deleteDataButton=new QPushButton(this);
    deleteDataButton->setText("Elimina un dato");
    dataFrame->setLayout(dataL);
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
    dataFrame=new QFrame(this);
    initDataFrame(dataFrame);
    visualisationLayout->replaceWidget(oldDataFrame,dataFrame);
    delete oldDataFrame;
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

void Window::initDataId(){
    unsigned int i=labelVector.size();
    for(unsigned int j=0;j<i;j++){
        deleteDataComboBox->addItem(QString::number(j));
    }
}

void Window::removeDataValues(){
    QLayoutItem* child;
    columnGridLayoutData=2;
    while(rowGridLayoutData >= 2){
        dataFrame->layout()->itemAt(rowGridLayoutData+columnGridLayoutData)->widget()->hide();
        child=dataFrame->layout()->takeAt(rowGridLayoutData+columnGridLayoutData);
        dataFrame->layout()->removeItem(child);
        delete child;
        if(columnGridLayoutData==0){
            columnGridLayoutData=2;
            rowGridLayoutData--;
        }
        else{
            columnGridLayoutData--;
        }
    }
    oldDataFrame=dataFrame;
    idVector.clear();
    labelVector.clear();
    dataVector.clear();
}



void Window::deletePreviousChart(){
    chartL->removeWidget(chartViewer);
    delete chartViewer;
}

QString Window::getNewFileName() const{
    if(fileName==nullptr){
        return "Il mio grafico";
    }
    return fileName->text();
}

QString Window::getNewTitle() const{
    if(newTitle==nullptr){
        return "Il mio grafico";
    }
    return newTitle->text();
}

QString Window::getDeleteDataComboBoxValue() const{
    return deleteDataComboBox->currentText();
}

const vector<QLabel *>& Window::getIdVector() const{
    return idVector;
}

const vector<QLineEdit *>& Window::getLabelVector() const{
    return labelVector;
}

const vector<QLineEdit *>& Window::getDataVector() const{
    return dataVector;
}

Chart* Window::getActiveChart() const{
    return activeChart;
}

void Window::setActiveChart(Chart *newActiveChart){
    activeChart = newActiveChart;
}

void Window::setController(Controller* c){
    controller=c;
    connect(file->actions().at(0), SIGNAL(triggered()), controller, SLOT(newFile()));
    connect(file->actions().at(1), SIGNAL(triggered()), controller, SLOT(openFile()));
    connect(file->actions().at(2),  SIGNAL(triggered()), controller, SLOT(saveFile()));
    connect(file->actions().at(3), SIGNAL(triggered()), controller, SLOT(saveNewFile()));
    connect(file->actions().at(4), SIGNAL(triggered()), this, SLOT(close()));
    connect(chart->actions().at(0), SIGNAL(triggered()), controller, SLOT(changeTitle()));
    connect(chart->actions().at(1),  SIGNAL(triggered()), controller, SLOT(loadBarChart()));
    connect(chart->actions().at(2),  SIGNAL(triggered()), controller, SLOT(loadLineChart()));
    connect(chart->actions().at(3),  SIGNAL(triggered()), controller, SLOT(loadPieChart()));
    connect(edit->actions().at(0), SIGNAL(triggered()), controller, SLOT(addData()));
    connect(edit->actions().at(1), SIGNAL(triggered()), controller, SLOT(saveData()));
    connect(edit->actions().at(2), SIGNAL(triggered()), this, SLOT(deleteData()));
    connect(about->actions().at(0), SIGNAL(triggered()), this, SLOT(showInfo()));
    connect(newFileButton, SIGNAL(clicked()), controller, SLOT(newFile()));
    connect(openFileButton, SIGNAL(clicked()), controller, SLOT(openFile()));
    connect(saveFileButton, SIGNAL(clicked()), controller, SLOT(saveFile()));
    connect(saveNewFileButton, SIGNAL(clicked()), controller, SLOT(saveNewFile()));
    connect(loadBarChartButton, SIGNAL(clicked()), controller, SLOT(loadBarChart()));
    connect(loadLineChartButton, SIGNAL(clicked()), controller, SLOT(loadLineChart()));
    connect(loadPieChartButton, SIGNAL(clicked()), controller, SLOT(loadPieChart()));
    connect(changeTitleButton, SIGNAL(clicked()), controller, SLOT(changeTitle()));
    setDataConnect();
}

void Window::setDataConnect(){
    connect(addDataButton, SIGNAL(clicked()), controller, SLOT(addData()));
    connect(saveDataButton, SIGNAL(clicked()), controller, SLOT(saveData()));
    connect(deleteDataButton, SIGNAL(clicked()), this, SLOT(deleteData()));
}

void Window::checkDataLabel(){
    bool isOk;
    for(unsigned int i=0;i<dataVector.size();i++){
        dataVector.at(i)->text().toDouble(&isOk);
        if(!isOk){
            throw std::runtime_error("Uno o più valori non sono validi. Modificarli e riprovare.");
        }
    }
}

void Window::createChart(){
    LineChart* activeLineChart=dynamic_cast<LineChart*>(activeChart);
    if(activeLineChart){
        activeLineChart->setData();
        showChart(activeLineChart->showChart());
    }
    else{
        BarChart* activeBarChart=dynamic_cast<BarChart*>(activeChart);
        if(activeBarChart){
            activeBarChart->setData();
            showChart(activeBarChart->showChart());
        }
        else{
            PieChart* activePieChart=static_cast<PieChart*>(activeChart);
            activePieChart->setData();
            showChart(activePieChart->showChart());
        }
    }
}

void Window::showChart(QChart* c){
    chartViewer = new QChartView(c);
    chartViewer->setRenderHint(QPainter::Antialiasing);
    chartL->addWidget(chartViewer);
}

void Window::showNewFileDialog(){
    newFileDialog=new QDialog(this);
    fileName=new QLineEdit(this);
    confirmNewFileButton=new QPushButton(this);
    abortOperationButton=new QPushButton(this);
    QGridLayout* dialogLayout=new QGridLayout;
    fileName->setText("Il mio grafico");
    confirmNewFileButton->setText("Ok");
    abortOperationButton->setText("Annulla");
    newFileDialog->setLayout(dialogLayout);
    dialogLayout->addWidget(new QLabel("Scrivi un titolo per il tuo grafico.",newFileDialog),0,1);
    dialogLayout->addWidget(new QLabel("(Potrai cambiarlo successivamente.)",newFileDialog),1,1);
    dialogLayout->addWidget(fileName,2,1);
    dialogLayout->addWidget(confirmNewFileButton,3,0);
    dialogLayout->addWidget(abortOperationButton,3,2);
    newFileDialog->setMinimumWidth(360);
    newFileDialog->setMaximumWidth(360);
    newFileDialog->setMinimumHeight(240);
    newFileDialog->setMaximumHeight(240);
    newFileDialog->setModal(true);
    newFileDialog->show();
    connect(confirmNewFileButton, SIGNAL(clicked()), controller, SLOT(manageNewFile()));
    connect(abortOperationButton, SIGNAL(clicked()), this, SLOT(abortNewFile()));
}

void Window::showDeleteDataDialog(){
    deleteDataDialog=new QDialog(this);
    QGridLayout* deleteDataLayout=new QGridLayout;
    deleteDataDialog->setLayout(deleteDataLayout);
    deleteDataComboBox=new QComboBox(this);
    initDataId();
    deleteDataButton=new QPushButton(this);
    abortOperationButton=new QPushButton(this);
    deleteDataButton->setText("Ok");
    abortOperationButton->setText("Annulla");
    deleteDataLayout->addWidget(new QLabel("Scegliere l'ID del dato da eliminare.",deleteDataDialog));
    deleteDataLayout->addWidget(deleteDataComboBox,1,1);
    deleteDataLayout->addWidget(deleteDataButton,2,0);
    deleteDataLayout->addWidget(abortOperationButton,2,2);
    deleteDataDialog->setMinimumWidth(240);
    deleteDataDialog->setMaximumWidth(240);
    deleteDataDialog->setMinimumHeight(120);
    deleteDataDialog->setMaximumHeight(120);
    deleteDataDialog->setModal(true);
    deleteDataDialog->show();
    connect(deleteDataButton, SIGNAL(clicked()), controller, SLOT(deleteData()));
    connect(abortOperationButton, SIGNAL(clicked()), this, SLOT(abortDeleteData()));
}

void Window::showChangeTitleDialog(){
    changeTitleDialog=new QDialog(this);
    newTitle=new QLineEdit(this);
    confirmNewTitleButton=new QPushButton(this);
    abortOperationButton=new QPushButton(this);
    QGridLayout* dialogLayout=new QGridLayout;
    newTitle->setText("Il mio grafico");
    confirmNewTitleButton->setText("Ok");
    abortOperationButton->setText("Annulla");
    changeTitleDialog->setLayout(dialogLayout);
    dialogLayout->addWidget(new QLabel("Inserisci il nuovo titolo per il tuo grafico.",changeTitleDialog),0,1);
    dialogLayout->addWidget(newTitle,2,1);
    dialogLayout->addWidget(confirmNewTitleButton,3,0);
    dialogLayout->addWidget(abortOperationButton,3,2);
    changeTitleDialog->setMinimumWidth(400);
    changeTitleDialog->setMaximumWidth(400);
    changeTitleDialog->setMinimumHeight(120);
    changeTitleDialog->setMaximumHeight(120);
    changeTitleDialog->setModal(true);
    changeTitleDialog->show();
    connect(confirmNewTitleButton, SIGNAL(clicked()), controller, SLOT(manageChangeTitle()));
    connect(abortOperationButton, SIGNAL(clicked()), this, SLOT(abortChangeTitle()));
}

void Window::showInfo(){
    QMessageBox::about(this,"QtCharts","Versione 1.0.\nCreato con Qt 5.9.5");
}

void Window::closeNewFileDialog(){
    newFileDialog->close();
    delete newFileDialog;
}

void Window::closeWarning(){
    warningDialog->close();
    delete warningDialog;
}

void Window::closeDeleteDialog(){
    deleteDataDialog->close();
    delete deleteDataDialog;
}

void Window::closeNewTitleDialog(){
    changeTitleDialog->close();
    delete changeTitleDialog;
}

void Window::abortNewFile(){
    newFileDialog->close();
    delete newFileDialog;
    abortOperation();
}

void Window::abortChangeTitle(){
    changeTitleDialog->close();
    delete changeTitleDialog;
    abortOperation();
}

void Window::abortDeleteData(){
    deleteDataDialog->close();
    delete deleteDataDialog;
    abortOperation();
}

void Window::abortOperation(){
    showWarning("Operazione annullata.");
}

void Window::deleteData(){
    showDeleteDataDialog();
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
    warningDialog->setModal(true);
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
