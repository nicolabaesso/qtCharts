#include "barChart.h"
BarChart::BarChart(DataHandler& dh):Chart(dh), nSets(0){}
void BarChart::setData(){
    auto it=data.getDataOnFile().begin();
    for(;it!=data.getDataOnFile().end();++it){
        nSets++;
    }
}
QChart* BarChart::showChart(){
    QBarSet* dataSet;
    QBarSeries* series=new QBarSeries();
    QString t="";
    for(int i=0;i<nSets;i++){
        dataSet=new QBarSet(t.fromStdString(data.getDataOnFile().at(i).getLabel()));
        dataSet->append(data.getDataOnFile().at(i).getData());
        series->append(dataSet);
    }
    QChart* barChart=new QChart();
    barChart->addSeries(series);
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(data.getMinData()?data.getMinData():0,data.getMaxData()?data.getMaxData():1);
    barChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    barChart->setTitle(t.fromStdString(data.getTitle()));
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->legend()->setVisible(true);
    barChart->legend()->setAlignment(Qt::AlignBottom);
    return barChart;
}
BarChart& BarChart::operator =(const BarChart &bc){
    if(this != &bc){
        data=bc.data;
        nSets=bc.nSets;
    }
    return *this;
}
