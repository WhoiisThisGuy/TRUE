#ifndef OBSTESZT_H
#define OBSTESZT_H

#include "gridmodel.h"
#include "imyobserver.h"
#include <iostream>

using namespace std;

class ObserverTeszt : public IMyobserver
{
public:
    virtual ~ObserverTeszt() { cout << "deleted obsteszt" << endl; }
    virtual void setGridValue(int row, int col, int val);
    void setGridModel(GridModel* mygridmodel_);
    GridModel* mygridmodel;

};
#endif
