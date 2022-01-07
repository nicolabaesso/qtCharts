#ifndef BARCHART_H
#define BARCHART_H
#include "chart.h"
#include <QBarSet>
#include <QBarSeries>

using QtCharts::QBarSet;
using QtCharts::QBarSeries;

class BarChart: public Chart{
private:
    int nSets;
public:
    BarChart(DataHandler& dh);
    void setData();
    QChart* showChart();
    BarChart &operator =(const BarChart &pc);
};

#endif // BARCHART_H
