#include "mediator.h"

void Mediator::updateView(int row,int col,int val)
{
    emit(changeView(row,col,val));
}

Mediator::Mediator()
{

}

