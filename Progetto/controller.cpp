#include "controller.h"

Controller::Controller(QObject* parent):QObject(parent){}

void Controller::setModel(Model* newModel){
    model = newModel;
}

void Controller::loadExampleFile(){
    model->readFile("./example.xml");
}

void Controller::setView(Window* newView){
    view = newView;
}

void Controller::newFile(){
    try{
        QString path=view->showSaveDialog();
        if(path == nullptr){
            throw std::runtime_error("Error: new file not saved.");
        }
        model->saveFile(path);
        model->readFile(path);
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
