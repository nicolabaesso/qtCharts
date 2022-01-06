#include "lineChart.h"
LineChart::LineChart(DataHandler dh):Chart(dh),nPoints(0){}
void LineChart::setData(){
    auto it=data.getDataOnFile().begin();
    for(;it!=data.getDataOnFile().end();++it){
        nPoints++;
    }
}
LineChart& LineChart::operator=(const LineChart& l){
    if(this != &l){
        nPoints=l.nPoints;
        data=l.data;
    }
    return *this;
}

QChart* LineChart::showChart(){
    const vector<Data> d=data.getDataOnFile();
    QLineSeries* s=new QLineSeries();
    for(int i=0;i<nPoints;i++){
        s->append(i+1,d.at(i).getData());
    }
    QChart* c=new QChart();
    QString t="";
    c->legend()->hide();
    c->addSeries(s);
    c->createDefaultAxes();
    c->setTitle(t.fromStdString(data.getTitle()));
    return c;
}
