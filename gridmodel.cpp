#include "gridmodel.h"

GridModel::GridModel(int n,int m)
{
    for(int i = 0;i<100;++i)
        for(int j = 0;j<100;++j)
            grid[i][j] = 0; //Minden cella fehér alapból

    //default
    grid[0][0] = 2; //Start
    grid[2][2] = 3; //Target

    pStart.setX(0);
    pStart.setY(0);

    pTarget.setX(2);
    pTarget.setX(2);

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
            if (c == 0) return QColor(Qt::white);
            else if(c == 1) return QColor(Qt::gray);
            else if(c == 2) return QColor(Qt::green);
            else if(c == 3) return QColor(Qt::red);
        }
         break;
        default:
          return QVariant();
          break;
    }
}

bool GridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QPoint pIndex;
    pIndex.setX(index.column());
    pIndex.setY(index.row());

    switch(role){
        case Qt::BackgroundColorRole:

            QVector<int> roles;

            roles.push_back(Qt::BackgroundColorRole);

            QColor c = value.value<QColor>();

            if(c == Qt::white){
                grid[pIndex.x()][pIndex.y()] = 0;

                emit(dataChanged(index, index,roles));
                return true;
            }
            else if(c == Qt::gray){
                grid[pIndex.x()][pIndex.y()] = 1;
                emit(dataChanged(index, index,roles));
                return true;

            }
            else if(c == Qt::green && grid[pIndex.x()][pIndex.y()] == 0){


                if(pStart.x() != index.column() || pStart.y() != index.row()){
                    grid[pStart.x()][pStart.y()] = 0;

                    pStart.setX(index.column());
                    pStart.setY(index.row());
                }

                grid[pStart.x()][pStart.y()] = 2;

                emit(dataChanged(index, index,roles));
                return true;
            }
            else if(c == Qt::red && grid[pIndex.x()][pIndex.y()] == 0){
                if(pTarget.x() != index.column() || pTarget.y() != index.row()){
                    grid[pTarget.x()][pTarget.y()] = 0;

                    pTarget.setX(index.column());
                    pTarget.setY(index.row());

                }

                grid[pTarget.x()][pTarget.y()] = 3;
                emit(dataChanged(index, index,roles));
                return true;
            }
        return false;
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

}

int GridModel::getGridValueByIndex(const QModelIndex &index)
{
    return grid[index.row()][index.column()];
}

int GridModel::getGridValueByRowCol(int row, int col)
{
    return grid[row][col];
}

void GridModel::clearGrid()
{

    for(int i = 0;i<numberOfRows;++i)
        for(int j = 0;j<numberOfColumns;++j)
            if(grid[i][j] == 1){

                QModelIndex index = this->index(i,j);
                grid[i][j] = 0;
                setData(index,QColor(Qt::white),Qt::BackgroundColorRole);

            }



}
