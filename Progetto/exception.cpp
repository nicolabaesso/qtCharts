#include "exception.h"
void Exception::raise() const{
    throw *this;
}
Exception* Exception::clone() const{
    return new Exception(*this);
}
