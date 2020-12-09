#ifndef IPATHFINDER_H
#define IPATHFINDER_H
#include "iobserver.h"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class IPathfinder {

public:
    virtual ~IPathfinder(){}
    virtual int StartSearch(bool *abortFlag) = 0;
    virtual bool Init(const vector<string>& Parameters) = 0;
    void Attach(IObserver* grindcontroller_) {gridcontroller = grindcontroller_;}
    virtual vector<int> getPath() = 0;
protected:
    IObserver* gridcontroller;
};


#endif // H_IPATHFINDALGORITHM_H
