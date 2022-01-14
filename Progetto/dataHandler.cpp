#include <vector>
#include "dataHandler.h"
const vector<Data> &DataHandler::getDataOnFile() const{
    return dataOnFile;
}

string DataHandler::getTitle() const{
    return title;
}

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
DataHandler& DataHandler::operator=(const DataHandler& dh){
    if(this != &dh){
        title=dh.title;
        dataOnFile=dh.dataOnFile;
    }
    return *this;
}

double DataHandler::getMinData(){
    double min=dataOnFile.at(0).getData();
    bool inserted=false;
    auto it=dataOnFile.begin();
    for(;!inserted && it!=dataOnFile.end();++it){
        if((*it).getData()<min){
            min=(*it).getData();
        }
    }
    return min;
}
double DataHandler::getMaxData(){
    double max=dataOnFile.at(0).getData();
    bool inserted=false;
    auto it=dataOnFile.begin();
    for(;!inserted && it!=dataOnFile.end();++it){
        if((*it).getData()>max){
            max=(*it).getData();
        }
    }
    return max;
}
