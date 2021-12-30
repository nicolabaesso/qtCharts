#ifndef CHART_H
#define CHART_H
#include "dataHandler.h"
class Chart{
private:
    DataHandler data;
public:
   virtual ~Chart()=default;
   Chart(DataHandler& d);
   virtual void setData(){};
};
#endif // CHART_H
