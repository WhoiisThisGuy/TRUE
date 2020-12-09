#ifndef IObserver_H
#define IObserver_H
#include "mypoint.h"

class IObserver
{
public:
    IObserver() {}
    virtual ~IObserver() {}
    virtual void setGridValue(int row, int col, int val) = 0;
    virtual void clearPathColors() = 0;
public:
    int * grid = nullptr;
    Point src;
    Point dst;
    int numberOfRows = 0;
    int numberOfColumns = 0;
    unsigned int numberOfVisitedNodes = 0;
};

#endif // IOBSERVER_H
