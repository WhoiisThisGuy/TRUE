#include "gridcontroller.h"

Gridcontroller::Gridcontroller(Mediator *m)
{
    mediator = m;
}

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
void Gridcontroller::InitGrid(GridModel *mygridmodel_)
{
    numberOfVisitedNodes = 0;
    mygridmodel = mygridmodel_;
    numberOfRows = mygridmodel->numberOfRows;
    numberOfColumns = mygridmodel->numberOfColumns;

    src = mygridmodel->pStart;
    dst = mygridmodel->pTarget;

    if(grid)
        delete [] grid;

    grid = new int[numberOfRows*numberOfColumns];

    for(int i = 0; i<numberOfRows;++i){
        for(int j = 0;j<numberOfColumns;++j){
            grid[i*numberOfColumns+j] = mygridmodel->grid[i*numberOfColumns+j];
        }
    }

    //memcpy(grid,mygridmodel->grid,(sizeof(int))*(numberOfRows*numberOfColumns));
}
