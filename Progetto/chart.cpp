#include "chart.h"
Chart::Chart(DataHandler& d): data(d){}
QChart* Chart::showChart(){return new QChart();}
