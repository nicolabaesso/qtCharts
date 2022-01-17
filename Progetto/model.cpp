#include "model.h"
Model::Model(){}

DataHandler& Model::readExampleFile(QString path){
    return file.readFromFile(path);
}

DataHandler& Model::readFile(QString path){
    file.clearData();
    return file.readFromFile(path);
}

void Model::saveFile(){
    file.saveFile();
}

void Model::saveNewFile(QString path){
    file.saveNewFile(path);
}

DataHandler& Model::getData(){
    return file.getReadedData();
}

void Model::setData(DataHandler d){
    file.setReadedData(d);
}
