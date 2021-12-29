#ifndef PIECHART_H
#define PIECHART_H
#include "chart.h"
#include <QPieSeries>
#include <QPieSlice>
class PieChart: public Chart{
public:
    PieChart();
    void setData();
};

#endif // PIECHART_H
