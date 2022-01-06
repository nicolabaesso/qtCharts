#include "model.h"
Model::Model(){}

DataHandler& Model::readFile(QString path){
    return file.readFromFile(path);
}

void Model::saveFile(QString path){
    file.saveFile(path);
}

DataHandler& Model::getData(){
    return file.getReadedData();
}
