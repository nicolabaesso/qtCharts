#include "controller.h"

Controller::Controller(QObject* parent):QObject(parent){}

void Controller::setModel(Model* newModel){
    model = newModel;
}

void Controller::loadExampleFile(){
    DataHandler exampleData=model->readFile("./example.xml");
    LineChart* exampleChart=new LineChart(exampleData);
    view->createChart(exampleChart);
}

void Controller::setView(Window* newView){
    view = newView;
}

void Controller::newFile(){
    try{
        QString path=view->showNewFileDialog(model->getData());
        /*
        if(path == nullptr){
            throw std::runtime_error("Error: new file not saved.");
        }
        */
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
        model->readFile(path);
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::saveFile(){
    try{
        QString path=view->showSaveDialog();
        if(path == nullptr){
            throw std::runtime_error("Error: file not saved. Not a correct path.");
        }
        model->saveFile(path);
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::loadLineChart(){
    qDebug()<<"Loading line chart";
    view->deletePreviousChart();
    LineChart* newLineChart=new LineChart(model->getData());
    view->createChart(newLineChart);
}

void Controller::loadPieChart(){
    qDebug()<<"Loading pie chart";
    view->deletePreviousChart();
    PieChart* newPieChart=new PieChart(model->getData());
    view->createChart(newPieChart);
}

void Controller::loadBarChart(){
    qDebug()<<"Loading bar chart";
    view->deletePreviousChart();
    BarChart* newBarChart=new BarChart(model->getData());
    view->createChart(newBarChart);
}
