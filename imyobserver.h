#ifndef IMYOBSERVER_H
#define IMYOBSERVER_H
#include "mypoint.h"

class IMyobserver
{
public:
    IMyobserver() {}
    virtual ~IMyobserver() {if(grid) delete[] grid;}
    virtual void setGridValue(int row, int col, int val) = 0;
public:
    int * grid = nullptr;
    Point src;
    Point dst;
    int numberOfRows = 0;
    int numberOfColumns = 0;
};

#endif // IOBSERVER_H
