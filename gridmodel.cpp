#include "gridmodel.h"

GridModel::GridModel(int n,int m) :
    pStart(0,0)
  ,pTarget(3,3)
{
    for(int i = 0;i<n;++i)
        for(int j = 0;j<m;++j)
            grid[i][j] = 0; //Minden cella fehér alapból

    //default
    grid[0][0] = 2; //Start
    grid[3][3] = 3; //Target

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
    //cellák: 0 - üres, 1 - foglalt, 2 - start, 3 - target, 4 - útvonal része, 5 - megvizsgált
    switch(role){
        case Qt::BackgroundColorRole:{
            char c = grid[index.column()][index.row()];
            if (c == 0) return QColor(Qt::white);
            else if(c == 1) return QColor(Qt::gray);
            else if(c == 2) return QColor(Qt::green);
            else if(c == 3) return QColor(Qt::red);
            else if(c == 4) return QColor(Qt::blue);
            else if(c == 5) return QColor(Qt::cyan);
        }
         break;
        default:
          return QVariant();
          break;
    }
}

bool GridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int cellData = grid[index.column()][index.row()];

    QVector<int> roles;

    roles.push_back(Qt::BackgroundColorRole);

    switch(role){
        case Qt::BackgroundColorRole:
            QColor c = value.value<QColor>();

            if(c == Qt::cyan && cellData != 2 && cellData != 3){
                grid[index.column()][index.row()] = 5;

                return true;
            }
            else if(c == Qt::blue && cellData != 2 && cellData != 3){
                grid[index.column()][index.row()] = 4;

                return true;
            }

            else if(c == Qt::white){
                grid[index.column()][index.row()] = 0;

                return true;
            }
            else if(c == Qt::gray && cellData != 2 && cellData != 3){
                grid[index.column()][index.row()] = 1;

                return true;

            }
            else if(c == Qt::green && grid[index.column()][index.row()] == 0){

                grid[index.column()][index.row()] = 2;
                pStart.x = index.column();
                pStart.y = index.row();

                return true;
            }
            else if(c == Qt::red && grid[index.column()][index.row()] == 0){

                grid[index.column()][index.row()] = 3;
                pTarget.x = index.column();
                pTarget.y = index.row();
                return true;
            }
        break;
    }

    return false;
}

GridModel::~GridModel()
{

}

void GridModel::setRowandCols(int a, int b)
{
    numberOfRows = a;
    numberOfColumns = b;

}

void GridModel::setGridValue(int row, int col, int value)
{
    QVector<int> roles;

    roles.push_back(Qt::BackgroundColorRole);
    QVariant v;
    switch (value){
        case 0:
            v.setValue(QColor(Qt::white));
        break;
    case 1:
        v.setValue(QColor(Qt::gray));
        break;
    case 2:
        v.setValue(QColor(Qt::green));
        break;
    case 3:
        v.setValue(QColor(Qt::red));
        break;
    case 4:
        v.setValue(QColor(Qt::blue));
        break;
    case 5:
        v.setValue(QColor(Qt::cyan));
        break;
    }

    if(setData(index(row,col),v,Qt::BackgroundColorRole)){
        emit(dataChanged(index(row,col), index(row,col),roles));
    }
}

int GridModel::getGridValueByIndex(const QModelIndex &index)
{
    return grid[index.column()][index.row()];
}

int GridModel::getGridValueByRowCol(int row, int col)
{
    return grid[row][col];
}

void GridModel::clearGrid()
{
    for(int i = 0;i<numberOfRows;++i)
        for(int j = 0;j<numberOfColumns;++j)
            if(grid[i][j] != 1 && grid[i][j] != 2 && grid[i][j] != 3){
                grid[i][j] = 0;
            }

    QVector<int> roles;
    roles.push_back(Qt::BackgroundColorRole);

    emit(dataChanged(index(0,0), index(numberOfRows,numberOfColumns),roles));

}
