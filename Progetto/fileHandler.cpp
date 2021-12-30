#include "fileHandler.h"
#include "exception.h"
FileHandler::FileHandler(DataHandler rd): readedData(rd){
    initExampleFile();
    QFile file("./data/example.xml");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug()<<"File not open nor created.";
    }
    file.close();
}
void FileHandler::readFromFile(string name){

}
void FileHandler::initExampleFile(){
    QDomDocument example;
    QDomElement root=example.createElement("Example");
    example.appendChild(root);
    QDomElement title=example.createElement("Title");
    example.appendChild(title);
    for(int i=0;i<5;i++){
        QDomElement data=example.createElement("Data");
        data.setAttribute("ID",QString::number(i));
        data.setAttribute("Label","Default");
        data.setAttribute("Data",0.0);
        example.appendChild(data);
    }
    QFile ex("./data/example.xml");
    ex.open(QIODevice::ReadWrite);
    QTextStream stream(&ex);
    stream<<example.toString();
    ex.close();
}
void FileHandler::saveFile(){

}
FileHandler::~FileHandler(){
    //delete this;
}
