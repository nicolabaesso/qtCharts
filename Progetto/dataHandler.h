#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <vector>
#include "data.h"
using std::vector;
class DataHandler{
private:
    string title;
    vector<Data> dataOnFile;
public:
    DataHandler(string t="");
    ~DataHandler();
    DataHandler& operator=(const DataHandler& d);
    void insertData(Data d);
    void setTitle(string t);
};
#endif // DATAHANDLER_H
