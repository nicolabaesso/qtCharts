#include <vector>
#include "dataHandler.h"
DataHandler::DataHandler(){
    //tomama
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
