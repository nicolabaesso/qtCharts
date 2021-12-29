#include "fileHandler.h"
FileHandler::FileHandler(){
    QFile file("./example.xml");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QDomElement root=doc.createElement("Data");
        doc.appendChild(root);
        QTextStream stream(&file);
        stream<<doc.toString();
        file.close();
    }
}
