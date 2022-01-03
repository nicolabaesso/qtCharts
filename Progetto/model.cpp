#include "model.h"
Model::Model(){}

void Model::readFile(QString path){
    file.readFromFile(path);
}
