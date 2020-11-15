#include "gridcontroller.h"

void Gridcontroller::setGridValue(int row, int col, int val)
{
    //mygridmodel->setGridValue(row,col,val);
     //grid[row*numberOfColumns+col] = val;
    mediator->updateView(row,col,val); //emits the signal for the main thread to update the view
    return;
}

void Gridcontroller::clearPathColors()
{
    mediator->clearGridColors();
}
void Gridcontroller::InitGridModel(GridModel *mygridmodel_)
{

    numberOfRows = mygridmodel_->numberOfRows;
    numberOfColumns = mygridmodel_->numberOfColumns;
    mygridmodel = mygridmodel_;

    src = mygridmodel->pStart;
    dst = mygridmodel->pTarget;
    if(grid)
        delete [] grid;
    grid = new int[numberOfRows*numberOfColumns];
    memcpy(grid,mygridmodel->grid,sizeof(grid)*(numberOfRows*numberOfColumns));
}
