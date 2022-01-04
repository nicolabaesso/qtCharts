#include "controller.h"

Controller::Controller(QObject* parent):QObject(parent){}

void Controller::setModel(Model* newModel){
    model = newModel;
}


void Controller::setView(Window* newView){
    view = newView;
}

void Controller::openFile(){
    try{
        QString path=view->showOpenDialog();
        model->readFile(path);
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::saveFile(){
    try{
        QString path=view->showSaveDialog();
        model->saveFile(path);
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}
