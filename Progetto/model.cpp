#include "model.h"
Model::Model(){}

DataHandler& Model::getData(){
    return file.getReadedData();
}

void Model::setData(const DataHandler& d){
    file.setReadedData(d);
}

void Model::setTitle(const QString& title){
    if(title == nullptr){
        throw std::runtime_error("Errore: titolo non valido.");
    }
    file.setTitle(title);
}

DataHandler& Model::readExampleFile(const QString& path){
    return file.readFromFile(path);
}

DataHandler& Model::readFile(const QString& path){
    if(path == nullptr){
        throw std::runtime_error("Errore: file non aperto. Posizione non corretta");
    }
    file.clearData();
    return file.readFromFile(path);
}

void Model::saveFile(){
    file.saveFile();
}

void Model::saveNewFile(const QString& path){
    if(path == nullptr){
        throw std::runtime_error("Errore: file non salvato. Posizione non corretta.");
    }
    file.setFileName(path);
    saveFile();
}

void Model::addData(){
    file.addData(Data());
}

void Model::editData(const DataHandler& dh){
    Data fileData, dhData;
    for(unsigned int i=0;i<file.getReadedData().getDataOnFile().size();i++){
        fileData=file.getReadedData().getDataOnFile().at(i);
        dhData=dh.getDataOnFile().at(i);
        if(!(fileData==dhData)){
            file.editData(dhData,i);
        }
    }
}

void Model::deleteData(const int& index){
    file.deleteData(index);
}
