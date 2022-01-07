#ifndef CHART_H
#define CHART_H
#include "dataHandler.h"
#include <QChart>

using QtCharts::QChart;

class Chart{
protected:
    DataHandler data;
public:
   Chart(DataHandler& d);
   virtual void setData(){};
   virtual QChart* showChart();
   Chart &operator =(const Chart &c);
};
#endif // CHART_H
