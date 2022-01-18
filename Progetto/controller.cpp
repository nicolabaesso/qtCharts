#include "controller.h"

Controller::Controller(QObject* parent):QObject(parent){}

void Controller::setModel(Model* newModel){
    model = newModel;
}

void Controller::setView(Window* newView){
    view = newView;
}

void Controller::loadExampleFile(){
    DataHandler exampleData=model->readExampleFile("./example.xml");
    view->initExampleValues(exampleData);
    LineChart* exampleChart=new LineChart(exampleData);
    view->setActiveChart(exampleChart);
    view->createChart();
}

void Controller::deleteData(){
    int id=view->getDeleteDataComboBoxValue().toInt();
    view->closeDeleteDialog();
    model->deleteData(id);
    model->saveFile();
    view->removeDataValues();
    view->initDataValues(model->getData());
    Chart* chart=view->getActiveChart();
    bool identifiedChart=false;
    if(dynamic_cast<LineChart*>(chart)){
        loadLineChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<BarChart*>(chart)){
        loadBarChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<PieChart*>(chart)){
        loadPieChart();
    }
    view->showWarning("Dato eliminato con successo!");
}

void Controller::addData(){
    DataHandler dataWithNew=model->getData();
    dataWithNew.insertData(Data());
    model->setData(dataWithNew);
    model->saveFile();
    view->removeDataValues();
    view->initDataValues(model->getData());
    Chart* chart=view->getActiveChart();
    bool identifiedChart=false;
    if(dynamic_cast<LineChart*>(chart)){
        loadLineChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<BarChart*>(chart)){
        loadBarChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<PieChart*>(chart)){
        loadPieChart();
    }
    view->showWarning("Dato aggiunto con successo!");
}

void Controller::saveData(){
    vector<QLineEdit*> labels=view->getLabelVector();
    vector<QLineEdit*> datas=view->getDataVector();
    DataHandler dataToSave;
    Data singleDataToSave;
    QString label, data;
    for(unsigned int i=0;i<labels.size();i++){
        label=labels.at(i)->text();
        data=datas.at(i)->text();
        singleDataToSave.setLabel(label.toStdString());
        singleDataToSave.setData(data.toDouble());
        dataToSave.insertData(singleDataToSave);
    }
    model->editData(dataToSave);
    model->saveFile();
    Chart* chart=view->getActiveChart();
    bool identifiedChart=false;
    if(dynamic_cast<LineChart*>(chart)){
        loadLineChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<BarChart*>(chart)){
        loadBarChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<PieChart*>(chart)){
        loadPieChart();
    }
    view->showWarning("Dati aggiornati con successo!");
}

void Controller::newFile(){
    view->showNewFileDialog();
}

void Controller::manageNewFile(){
    view->closeNewFileDialog();
    DataHandler newFileData=DataHandler();
    QString name=view->getNewFileName();
    newFileData.setTitle(name.toStdString());
    try{
        QString path=view->showSaveDialog();
        if(path == nullptr){
            throw std::runtime_error("Error while saving: file not created.");
        }
        model->setData(newFileData);
        model->saveNewFile(path);
        DataHandler readedData=model->readFile(path);
        view->deletePreviousChart();
        LineChart* newLineChart=new LineChart(readedData);
        view->setActiveChart(newLineChart);
        view->createChart();
        view->showWarning("File successfully created!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::openFile(){
    try{
        QString path=view->showOpenDialog();
        if(path == nullptr){
            throw std::runtime_error("Error: file not open. Not a correct path");
        }
        DataHandler readedData=model->readFile(path);
        view->removeDataValues();
        view->initDataValues(readedData);
        view->deletePreviousChart();
        LineChart* newLineChart=new LineChart(readedData);
        view->setActiveChart(newLineChart);
        view->createChart();
        view->showWarning("File successfully opened!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::saveNewFile(){
    try{
        QString path=view->showSaveDialog();
        if(path == nullptr){
            throw std::runtime_error("Error: file not saved. Not a correct path.");
        }
        model->saveNewFile(path);
        view->showWarning("File successfully saved!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::saveFile(){
    try{
        model->saveFile();
        view->showWarning("File successfully saved!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::loadLineChart(){
    view->deletePreviousChart();
    LineChart* newLineChart=new LineChart(model->getData());
    view->setActiveChart(newLineChart);
    view->createChart();
}

void Controller::loadPieChart(){
    view->deletePreviousChart();
    PieChart* newPieChart=new PieChart(model->getData());
    view->setActiveChart(newPieChart);
    view->createChart();
}

void Controller::loadBarChart(){
    view->deletePreviousChart();
    BarChart* newBarChart=new BarChart(model->getData());
    view->setActiveChart(newBarChart);
    view->createChart();
}

