#include "lineChart.h"
LineChart::LineChart(DataHandler& dh):Chart(dh),nPoints(0){}
void LineChart::setData(){
    auto it=data.getDataOnFile().begin();
    for(;it!=data.getDataOnFile().end();++it){
        nPoints++;
    }
}
LineChart& LineChart::operator=(const LineChart& lc){
    if(this != &lc){
        nPoints=lc.nPoints;
        data=lc.data;
    }
    return *this;
}

QChart* LineChart::showChart(){
    const vector<Data> d=data.getDataOnFile();
    QLineSeries* s=new QLineSeries();
    for(int i=0;i<nPoints;i++){
        s->append(i+1,d.at(i).getData());
    }
    QChart* lineChart=new QChart();
    QString t="";
    lineChart->legend()->hide();
    lineChart->addSeries(s);
    lineChart->createDefaultAxes();
    lineChart->setAnimationOptions(QChart::SeriesAnimations);
    lineChart->setTitle(t.fromStdString(data.getTitle()));
    return lineChart;
}
