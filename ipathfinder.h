#ifndef IPATHFINDER_H
#define IPATHFINDER_H
#include "imyobserver.h"
#include "mypoint.h"


class IPathfinder {

public:
    virtual ~IPathfinder(){}
    virtual bool StartSearch(Point src, Point dst,int row, int col) = 0;
    void Attach(IMyobserver* grindcontroller_) {gridcontroller = grindcontroller_;}
    void Detach();
protected:
    IMyobserver* gridcontroller;
};


#endif // H_IPATHFINDALGORITHM_H
