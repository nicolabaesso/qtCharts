#include "pieChart.h"
PieChart::PieChart(DataHandler& dh):Chart(dh), nSlices(0){}
void PieChart::setData(){
    auto it=data.getDataOnFile().begin();
    for(;it!=data.getDataOnFile().end();++it){
        nSlices++;
    }
}
QChart* PieChart::showChart(){
    QPieSeries* pieSeries=new QPieSeries();
    QString labelS="";
    for(int i=0;i<nSlices;i++){
        labelS=labelS.fromStdString(data.getDataOnFile().at(i).getLabel());
        pieSeries->append(labelS,data.getDataOnFile().at(i).getData());
    }
    pieSeries->setVisible();
    QChart* pieChart=new QChart();
    pieChart->addSeries(pieSeries);
    labelS=labelS.fromStdString(data.getTitle());
    pieChart->setAnimationOptions(QChart::SeriesAnimations);
    pieChart->setTitle(labelS);
    return pieChart;
}
PieChart& PieChart::operator =(const PieChart &pc){
    if(this != &pc){
        data=pc.data;
        nSlices=pc.nSlices;
    }
    return *this;
}
