#include "controller.h"

Controller::Controller(QObject* parent):QObject(parent){}

void Controller::setModel(Model* newModel){
    model = newModel;
}

void Controller::setView(Window* newView){
    view = newView;
}

void Controller::loadExampleFile(){
    DataHandler exampleData=model->readExampleFile("./example.xml");
    view->initExampleValues(exampleData);
    LineChart* exampleChart=new LineChart(exampleData);
    view->setActiveChart(exampleChart);
    view->createChart();
}

void Controller::changeTitle(){
    view->showChangeTitleDialog();
}

void Controller::manageChangeTitle(){
    QString newTitle=view->getNewTitle();
    view->closeNewTitleDialog();
    try{
        model->setTitle(newTitle);
        Chart* chart=view->getActiveChart();
        updateChart(chart);
        view->showWarning("Nome del grafico aggiornato con successo!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::updateData(DataHandler dh){
    view->removeDataValues();
    view->initDataValues(dh);
}

void Controller::deleteData(){
    int id=view->getDeleteDataComboBoxValue().toInt();
    view->closeDeleteDialog();
    model->deleteData(id);
    model->saveFile();
    updateData(model->getData());
    Chart* chart=view->getActiveChart();
    updateChart(chart);
    view->showWarning("Dato eliminato con successo!");
}

void Controller::addData(){
    model->addData();
    model->saveFile();
    updateData(model->getData());
    Chart* chart=view->getActiveChart();
    updateChart(chart);
    view->showWarning("Dato aggiunto con successo!");
}

void Controller::updateChart(Chart* chart){
    bool identifiedChart=false;
    if(dynamic_cast<LineChart*>(chart)){
        loadLineChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<BarChart*>(chart)){
        loadBarChart();
        identifiedChart=true;
    }
    if(!identifiedChart && dynamic_cast<PieChart*>(chart)){
        loadPieChart();
    }
}

void Controller::saveData(){
    try{
        view->checkDataLabel();
        vector<QLineEdit*> labels=view->getLabelVector();
        vector<QLineEdit*> datas=view->getDataVector();
        DataHandler dataToSave;
        Data singleDataToSave;
        QString label, data;
        for(unsigned int i=0;i<labels.size();i++){
            label=labels.at(i)->text();
            data=datas.at(i)->text();
            singleDataToSave.setLabel(label.toStdString());
            singleDataToSave.setData(data.toDouble());
            dataToSave.insertData(singleDataToSave);
        }
        model->editData(dataToSave);
        model->saveFile();
        Chart* chart=view->getActiveChart();
        updateChart(chart);
        view->showWarning("Dati aggiornati con successo!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::newFile(){
    view->showNewFileDialog();
}

void Controller::manageNewFile(){
    view->closeNewFileDialog(); 
    QString name=view->getNewFileName();
    DataHandler newFileData=DataHandler(name.toStdString());
    try{
        QString path=view->showSaveDialog();
        if(path == nullptr){
            throw std::runtime_error("Errore durante il salvataggio: file non creato.");
        }
        model->setData(newFileData);
        model->saveNewFile(path);
        DataHandler readedData=model->readFile(path);
        updateData(readedData);
        Chart* chart=view->getActiveChart();
        updateChart(chart);
        view->showWarning("File creato con successo!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::openFile(){
    try{
        QString path=view->showOpenDialog();
        DataHandler readedData=model->readFile(path);
        updateData(readedData);
        Chart* chart=view->getActiveChart();
        updateChart(chart);
        view->showWarning("File aperto con successo!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::saveNewFile(){
    QString path=view->showSaveDialog();
    try{
        model->saveNewFile(path);
        view->showWarning("File salvato con successo!");
    }
    catch(std::runtime_error exc){
        view->showWarning(exc.what());
    }
}

void Controller::saveFile(){
    model->saveFile();
    view->showWarning("File salvato con successo!");
}

void Controller::loadLineChart(){
    view->deletePreviousChart();
    LineChart* newLineChart=new LineChart(model->getData());
    view->setActiveChart(newLineChart);
    view->createChart();
}

void Controller::loadPieChart(){
    view->deletePreviousChart();
    PieChart* newPieChart=new PieChart(model->getData());
    view->setActiveChart(newPieChart);
    view->createChart();
}

void Controller::loadBarChart(){
    view->deletePreviousChart();
    BarChart* newBarChart=new BarChart(model->getData());
    view->setActiveChart(newBarChart);
    view->createChart();
}
