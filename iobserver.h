#ifndef IObserver_H
#define IObserver_H
#include "mypoint.h"
#include <string>

using std::string;

class IObserver
{
public:
    IObserver() {}
    virtual ~IObserver() {if(grid) delete[] grid;}
    virtual void setGridValue(int row, int col, int val) = 0;
    virtual void clearPathColors() = 0;
public:
    int * grid = nullptr;
    Point src;
    Point dst;
    int numberOfRows = 0;
    int numberOfColumns = 0;
};

#endif // IOBSERVER_H
