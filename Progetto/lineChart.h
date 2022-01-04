#ifndef LINECHART_H
#define LINECHART_H
#include "chart.h"
#include <QValueAxis>
class LineChart: public Chart{
public:
    LineChart();
    void setData();
};
#endif // LINECHART_H
