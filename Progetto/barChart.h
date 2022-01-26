#ifndef BARCHART_H
#define BARCHART_H
#include "chart.h"
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>

using QtCharts::QBarSet;
using QtCharts::QBarSeries;
using QtCharts::QValueAxis;

class BarChart: public Chart{
private:
    int nSets;
public:
    BarChart(DataHandler& dh);
    void setData();
    QChart* showChart();
    BarChart &operator =(const BarChart& bc);
};

#endif // BARCHART_H
