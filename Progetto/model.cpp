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

void Model::setTitle(QString title){
    file.setTitle(title);
}

void Model::editData(DataHandler dh){
    Data fileData, dhData;
    for(unsigned int i=0;i<file.getReadedData().getDataOnFile().size();i++){
        fileData=file.getReadedData().getDataOnFile().at(i);
        dhData=dh.getDataOnFile().at(i);
        if(!(fileData==dhData)){
            file.editData(dhData,i);
        }
    }
}

void Model::deleteData(int index){
    file.deleteData(index);
}
