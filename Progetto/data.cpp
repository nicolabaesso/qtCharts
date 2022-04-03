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

void Data::setLabel(const string& l){
    label=l;
}

void Data::setData(const double& d){
    data=d;
}

Data& Data::operator=(const Data& d){
    label=d.label;
    data=d.data;
    return *this;
}

bool Data::operator==(const Data &d2){
    return label==d2.label && data==d2.data;
}
