#ifndef OBSTESZT_H
#define OBSTESZT_H

#include "gridmodel.h"
#include "iobserver.h"
#include "mediator.h"
#include <iostream>

using namespace std;

class Gridcontroller : public IObserver
{

public:

    Gridcontroller(Mediator* m);
    void setGridValue(int row, int col, int val) override;
    void clearPathColors() override;
    virtual ~Gridcontroller() { if(grid){delete[] grid;qDebug("GridController: deleted grid");} }
    void InitGrid(GridModel* mygridmodel_);
    GridModel* mygridmodel;
    Mediator* mediator;



};
#endif
