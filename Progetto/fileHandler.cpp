#include "fileHandler.h"
#include "exception.h"
FileHandler::FileHandler(DataHandler rd): readedData(rd){
    initExampleFile();
}
DataHandler& FileHandler::readFromFile(QString path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Error: File not open.";
    }
    else{
        QDomDocument readedFile;
        if(!readedFile.setContent(&file)){
            qDebug()<<"Error: Cannot load document.";
        }
        else{
            QDomElement root=readedFile.firstChildElement();
            readedData.setTitle(root.attribute("Name").toStdString());
            QDomNodeList data=readedFile.elementsByTagName("Data");
            Data d;
            string l="";
            double value=0.0;
            for(int i=0; i<data.count();i++){
                QDomNode item=data.at(i);
                if(item.isElement()){
                    QDomElement elem=item.toElement();
                    l=elem.attribute("Label").toStdString();
                    value=elem.attribute("Data").toDouble();
                    d.setData(value);
                    d.setLabel(l);
                    readedData.insertData(d);
                }
            }
            qDebug()<<"File succesfully readed!";
        }
    }
    file.close();
    return readedData;
}
DataHandler& FileHandler::getReadedData(){
    return readedData;
}

void FileHandler::initExampleFile(){
    QDomDocument example;
    QDomElement root=example.createElement("Title");
    root.setAttribute("Name","Example data");
    example.appendChild(root);
    for(int i=0;i<5;i++){
        QDomElement data=example.createElement("Data");
        data.setAttribute("ID",QString::number(i));
        data.setAttribute("Label","Default");
        data.setAttribute("Data",i);
        root.appendChild(data);
    }
    QFile ex("./example.xml");
    ex.open(QIODevice::WriteOnly);
    QTextStream stream(&ex);
    stream<<example.toString();
    ex.close();
}
void FileHandler::saveFile(QString path){
    if(path == nullptr){
        qDebug()<<"Cannot save file: no valid path";
        return;
    }
    QDomDocument save;
    QDomElement root=save.createElement("Title");
    root.setAttribute("Name",QString::fromStdString(readedData.title));
    save.appendChild(root);
    for(unsigned int i=0;i<readedData.dataOnFile.size();i++){
        Data sd=readedData.dataOnFile.at(i);
        QDomElement data=save.createElement("Data");
        data.setAttribute("ID",QString::number(i));
        data.setAttribute("Label",QString::fromStdString(sd.getLabel()));
        data.setAttribute("Data",sd.getData());
        root.appendChild(data);
    }
    QFile s(path);
    s.open(QIODevice::WriteOnly);
    QTextStream stream(&s);
    stream<<save.toString();
    s.close();
}
FileHandler::~FileHandler(){
    //delete this;
}

void FileHandler::clearData(){
    DataHandler noData=DataHandler();
    readedData=noData;
}
