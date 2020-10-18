#include "gridmodel.h"

GridModel::GridModel(int n,int m)
{
    for(int i = 0;i<100;++i)
        for(int j = 0;j<100;++j)
            grid[i][j] = 0; //Minden cella fehér alapból

    //default
    grid[0][0] = 2; //Start
    grid[2][2] = 3; //Target

    numberOfRows = n;
    numberOfColumns = m;



}

int GridModel::rowCount(const QModelIndex &parent) const
{
    return numberOfRows;
}

int GridModel::columnCount(const QModelIndex &parent) const
{
    return numberOfColumns;
}

QVariant GridModel::data(const QModelIndex &index, int role) const
{
    //csak a background role-t állítom, minden más üres (QVariant)
    //cellák: 0 - üres, 1 - foglalt, 2 - start, 3 - target
    switch(role){
        case Qt::BackgroundColorRole:{
            char c = grid[index.column()][index.row()];
            if (c == 0) return QBrush(Qt::white);
            else if(c == 1) return QBrush(Qt::gray);
            else if(c == 2) return QBrush(Qt::green);
            else if(c == 3) return QBrush(Qt::red);
        }
         break;
        default:
          return QVariant();
          break;
    }
}

bool GridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role){
        case Qt::BackgroundColorRole:

            QColor c = value.value<QColor>();

            if(c == Qt::white){
                grid[index.column()][index.row()] = 0;
                emit(dataChanged(index, index));
            }
            else if(c == Qt::gray){
                grid[index.column()][index.row()] = 1;
                emit(dataChanged(index, index));

            }
            else if(c == Qt::green){
                grid[index.column()][index.row()] = 2;
                emit(dataChanged(index, index));
            }
            else if(c == Qt::red){
                grid[index.column()][index.row()] = 3;
                emit(dataChanged(index, index));
            }

         break;
    }
}

GridModel::~GridModel()
{

}

void GridModel::setRowandCols(int a, int b)
{
    numberOfRows = a;
    numberOfColumns = b;
    //emit(dataChanged(this->index(0, 0), this->index(rowCount(), columnCount())));

}
