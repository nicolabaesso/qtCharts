#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <vector>
#include "data.h"
#include <QString>

class FileHandler;

using std::vector;
class DataHandler{
private:
    string title;
    vector<Data> dataOnFile;
    friend class FileHandler;
public:
    DataHandler(string t="");
    ~DataHandler();
    DataHandler& operator=(const DataHandler& dh);
    void insertData(Data d);
    void setTitle(string t);
    const vector<Data> &getDataOnFile() const;
    string getTitle() const;
};
#endif // DATAHANDLER_H
