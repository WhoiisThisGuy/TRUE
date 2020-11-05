#ifndef OBSTESZT_H
#define OBSTESZT_H

#include "gridmodel.h"
#include "iobserver.h"
#include "mediator.h"
#include <iostream>

using namespace std;

class ObserverTeszt : public IObserver
{

public:
    ObserverTeszt(Mediator* m){mediator = m;}
    void setGridValue(int row, int col, int val) override;
    void clearPathColors() override;
    virtual ~ObserverTeszt() { if(grid) delete[] grid; }
    void InitGridModel(GridModel* mygridmodel_);
    GridModel* mygridmodel;
    Mediator* mediator;

};
#endif
