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
    DataHandler& operator=(const DataHandler& d);
    void insertData(Data d);
};
#endif // DATAHANDLER_H
