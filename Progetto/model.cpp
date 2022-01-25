#include "model.h"
Model::Model(){}

DataHandler& Model::readExampleFile(QString path){
    return file.readFromFile(path);
}

DataHandler& Model::readFile(QString path){
    if(path == nullptr){
        throw std::runtime_error("Errore: file non aperto. Posizione non corretta");
    }
    file.clearData();
    return file.readFromFile(path);
}

void Model::saveFile(){
    file.saveFile();
}

void Model::saveNewFile(QString path){
    if(path == nullptr){
        throw std::runtime_error("Errore: file non salvato. Posizione non corretta.");
    }
    file.saveNewFile(path);
}

DataHandler& Model::getData(){
    return file.getReadedData();
}

void Model::setData(DataHandler d){
    file.setReadedData(d);
}

void Model::setTitle(QString title){
    if(title == nullptr){
        throw std::runtime_error("Errore: titolo non valido.");
    }
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
