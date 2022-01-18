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
    view->createChart(exampleChart);
}

void Controller::deleteData(){
    qDebug()<<"Deleting data";
    int id=view->getDeleteDataComboBoxValue().toInt();
    view->closeDeleteDialog();
    model->deleteData(id);
    //view->removeDeletedElement(id);
    model->saveFile();
    view->removeDataValues();
    view->initDataValues(model->getData());
    view->showWarning("Dato eliminato con successo!");
}

void Controller::addData(){
    qDebug()<<"Adding data";
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
        view->createChart(newLineChart);
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
        view->createChart(newLineChart);
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
    view->createChart(newLineChart);
}

void Controller::loadPieChart(){
    view->deletePreviousChart();
    PieChart* newPieChart=new PieChart(model->getData());
    view->createChart(newPieChart);
}

void Controller::loadBarChart(){
    view->deletePreviousChart();
    BarChart* newBarChart=new BarChart(model->getData());
    view->createChart(newBarChart);
}

