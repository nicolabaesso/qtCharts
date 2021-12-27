#include <iostream>
#include "data.h"
using std::string;
Data::Data(string l, double d):label(l), data(d){}
string Data::getLabel() const{
    return label;
}
double Data::getData() const{
    return data;
}
void Data::setLabel(string l){
    label=l;
}
void Data::setData(double d){
    data=d;
}
Data::~Data(){
    delete this;
}
