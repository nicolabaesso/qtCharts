#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <vector>
#include "data.h"
using std::vector;
class DataHandler{
private:
    vector<Data> dataOnFile;
public:
    DataHandler();
    ~DataHandler();
    void insertData(Data d);
};
#endif // DATAHANDLER_H
