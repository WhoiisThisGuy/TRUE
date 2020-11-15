#ifndef IPATHFINDER_H
#define IPATHFINDER_H
#include "iobserver.h"
#include <vector>
#include <string>
#include "qdebug.h"

using std::vector;
using std::string;

class IPathfinder {

public:
    virtual ~IPathfinder(){qDebug("deleted IPathfinder.");}
    virtual int StartSearch() = 0;
    virtual bool Init(vector<string> Parameters) = 0;
    void Attach(IObserver* grindcontroller_) {gridcontroller = grindcontroller_;}
protected:
    IObserver* gridcontroller;
};


#endif // H_IPATHFINDALGORITHM_H
