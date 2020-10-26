#include "observerteszt.h"

void ObserverTeszt::setGridValue(int row, int col, int val)
{
    mygridmodel->setGridValue(row,col,val);
    cout << "gridvalues set"<< row << col << val<<endl;
}

void ObserverTeszt::setGridModel(GridModel *mygridmodel_)
{
    mygridmodel = mygridmodel_;
}
