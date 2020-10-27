#ifndef IPATHFINDER_H
#define IPATHFINDER_H
#include "imyobserver.h"

class IPathfinder {

public:
    virtual ~IPathfinder(){}
    virtual bool StartSearch() = 0;
    void Attach(IMyobserver* grindcontroller_) {gridcontroller = grindcontroller_;}
    void Detach();
protected:
    IMyobserver* gridcontroller;
};


#endif // H_IPATHFINDALGORITHM_H
