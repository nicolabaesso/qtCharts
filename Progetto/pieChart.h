#ifndef PIECHART_H
#define PIECHART_H
#include "chart.h"
#include <QPieSeries>
#include <QPieSlice>

using QtCharts::QPieSeries;
using QtCharts::QPieSlice;

class PieChart: public Chart{
private:
    int nSlices;
public:
    PieChart(DataHandler& dh);
    void setData();
    QChart* showChart();
    PieChart &operator =(const PieChart& pc);
};

#endif // PIECHART_H
