#ifndef DATA_H
#define DATA_H
#include <iostream>
using std::string;
class Data{
private:
    string label;
    double data;
public:
    Data(string l="default",double d=0.0);
    ~Data()=default;
    string getLabel() const;
    double getData() const;
    void setLabel(const string& l);
    void setData(const double& d);
    Data& operator=(const Data& d);
    bool operator==(const Data& d2);
};
#endif // DATA_H
