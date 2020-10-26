#ifndef IMYOBSERVER_H
#define IMYOBSERVER_H

class IMyobserver
{
public:
    IMyobserver() {}
    virtual ~IMyobserver() {}
    virtual void setGridValue(int row, int col, int val) = 0;
};

#endif // IOBSERVER_H
