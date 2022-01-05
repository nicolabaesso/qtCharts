#ifndef LINECHART_H
#define LINECHART_H
#include "chart.h"
#include <QLineSeries>

using QtCharts::QLineSeries;

class LineChart: public Chart{
private:
    int nPoints;
public:
    LineChart(DataHandler dh);
    void setData();
    QChart* showChart();
    LineChart &operator =(const LineChart &dh);
};
#endif // LINECHART_H
