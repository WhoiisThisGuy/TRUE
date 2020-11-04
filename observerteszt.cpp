#include "observerteszt.h"

void ObserverTeszt::setGridValue(int row, int col, int val)
{
    //mygridmodel->setGridValue(row,col,val);
     //grid[row*numberOfColumns+col] = val;
    mediator->updateView(row,col,val); //emits the signal for the main thread to update the view
    return;
}
void ObserverTeszt::InitGridModel(GridModel *mygridmodel_)
{

    numberOfRows = mygridmodel_->numberOfRows;
    numberOfColumns = mygridmodel_->numberOfColumns;
    mygridmodel = mygridmodel_;

    src = mygridmodel->pStart;
    dst = mygridmodel->pTarget;

    grid = new int[numberOfRows*numberOfColumns];
    memcpy(grid,mygridmodel->grid,sizeof(grid)*(numberOfRows*numberOfColumns));
}
