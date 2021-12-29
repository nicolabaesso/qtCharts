#include <vector>
#include "dataHandler.h"
DataHandler::DataHandler(){
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
DataHandler::~DataHandler(){
    delete this;
}
DataHandler& DataHandler::operator=(const DataHandler& d){
    if(this != &d){
        dataOnFile=d.dataOnFile;
    }
    return *this;
}
