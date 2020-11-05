#include "mediator.h"

void Mediator::updateView(int row,int col,int val)
{
    emit(changeView(row,col,val));
}

void Mediator::clearGridColors()
{
    emit(clearColors());
}

Mediator::Mediator()
{

}

