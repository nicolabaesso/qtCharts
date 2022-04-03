#include "chart.h"
Chart::Chart(DataHandler& d): data(d){}
QChart* Chart::showChart(){return new QChart();}

Chart &Chart::operator =(const Chart &c){
    if(this != &c){
        data=c.data;
    }
    return *this;
}
