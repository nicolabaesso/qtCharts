#include "fileHandler.h"
FileHandler::FileHandler(DataHandler rd): readedData(rd){
    initExampleFile();
}

DataHandler& FileHandler::getReadedData(){
    return readedData;
}

void FileHandler::setReadedData(const DataHandler& newReadedData){
    readedData = newReadedData;
}

void FileHandler::setFileName(const QString& newFileName){
    fileName = newFileName;
}

void FileHandler::setTitle(const QString& title){
    readedData.setTitle(title.toStdString());
}

void FileHandler::initExampleFile(){
    QDomDocument example;
    QDomElement root=example.createElement("Title");
    root.setAttribute("Name","Dati d'esempio");
    example.appendChild(root);
    int j;
    for(int i=0;i<5;i++){
        j=i+1;
        QDomElement data=example.createElement("Data");
        data.setAttribute("ID",QString::number(i));
        data.setAttribute("Label","Default");
        data.setAttribute("Data",j);
        root.appendChild(data);
    }
    QFile ex("./example.xml");
    ex.open(QIODevice::WriteOnly);
    QTextStream stream(&ex);
    stream<<example.toString();
    ex.close();
}

DataHandler& FileHandler::readFromFile(const QString& path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        throw std::runtime_error("Errore: file non aperto.");
    }
    else{
        QDomDocument readedFile;
        if(!readedFile.setContent(&file)){
            throw std::runtime_error("Errore: impossibile caricare il documento.");
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
            setFileName(path);
        }
    }
    file.close();
    return readedData;
}

void FileHandler::saveFile(){
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
    QFile s(fileName);
    s.open(QIODevice::WriteOnly);
    QTextStream stream(&s);
    stream<<save.toString();
    s.close();
}

void FileHandler::addData(const Data& d){
    readedData.insertData(d);
}

void FileHandler::editData(const Data& d, const int& index){
    readedData.editData(d,index);
}

void FileHandler::deleteData(const int& index){
    readedData.deleteData(index);
}

void FileHandler::clearData(){
    DataHandler noData=DataHandler();
    readedData=noData;
}
