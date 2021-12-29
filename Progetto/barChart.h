#ifndef BARCHART_H
#define BARCHART_H
#include "chart.h"
#include <QBarSeries>
class BarChart: public Chart{
public:
    BarChart();
    void setData();
};

#endif // BARCHART_H
