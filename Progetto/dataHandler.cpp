#include <vector>
#include "dataHandler.h"
DataHandler::DataHandler(string t):title(t){
    dataOnFile.push_back(Data());
}
void DataHandler::insertData(Data d){
    bool inserted=false;
    auto it=dataOnFile.begin();
    for(;!inserted && it!=dataOnFile.end();++it){
        if((*it).getLabel()=="default"){
            (*it)=d;
            inserted=true;
        }
    }
    if(!inserted){
        dataOnFile.push_back(d);
    }
}

void DataHandler::setTitle(std::string t){
    title=t;
}
DataHandler::~DataHandler(){
    //delete this;
}
DataHandler& DataHandler::operator=(const DataHandler& dh){
    if(this != &dh){
        title=dh.title;
        dataOnFile=dh.dataOnFile;
    }
    return *this;
}
