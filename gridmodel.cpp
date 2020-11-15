#include "gridmodel.h"
#include "Qthread"
#include "QFile"
#include "QTextStream"


GridModel::GridModel()
{

}

void GridModel::updateView(int row, int col, int val){

    //qDebug("Got the signal. Thread gridmodel update thread id: %d",QThread::currentThreadId());
    setGridValue(row,col,val);

}

void GridModel::clearGridPathColors()
{
    clearGridPaths();
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
            char c = grid[index.row()*numberOfColumns+index.column()];
            if (c == 0) return QColor(Qt::white);
            else if(c == 1) return QColor(Qt::gray);
            else if(c == 2) return QColor(Qt::green);
            else if(c == 3) return QColor(Qt::red);
            else if(c == 4) return QColor(Qt::black);
            else if(c == 5) return QColor(Qt::cyan);
            else if(c == 6) return QColor(Qt::yellow);
            else if(c == 7) return QColor(Qt::blue);
            else if(c == 8) return QColor(Qt::magenta);
            else if(c == 9) return QColor(Qt::darkRed);
        }
         break;
        default:
          return QVariant();
          break;
    }
}

bool GridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int cellData = grid[index.row()*numberOfColumns+index.column()];

    QVector<int> roles;

    roles.push_back(Qt::BackgroundColorRole);

    switch(role){
        case Qt::BackgroundColorRole:
            QColor c = value.value<QColor>();

            if(c == Qt::cyan && cellData != 2 && cellData != 3){
                grid[index.row()*numberOfColumns+index.column()] = 5;

                return true;
            }
            else if(c == Qt::black && cellData != 2 && cellData != 3){
                grid[index.row()*numberOfColumns+index.column()] = 4;

                return true;
            }

            else if(c == Qt::white){
                grid[index.row()*numberOfColumns+index.column()] = 0;

                return true;
            }
            else if(c == Qt::gray && cellData != 2 && cellData != 3){
                grid[index.row()*numberOfColumns+index.column()] = 1;

                return true;

            }
            else if(c == Qt::green && cellData != 1 && cellData != 3){

                grid[index.row()*numberOfColumns+index.column()] = 2;
                pStart.x = index.column();
                pStart.y = index.row();

                return true;
            }
            else if(c == Qt::red && cellData != 1 && cellData != 2){

                grid[index.row()*numberOfColumns+index.column()] = 3;
                pTarget.x = index.column();
                pTarget.y = index.row();
                return true;
            }
            else if(c == Qt::yellow) {
                grid[index.row()*numberOfColumns+index.column()] = 6;
                return true;
            }
            else if(c == Qt::blue) {
                grid[index.row()*numberOfColumns+index.column()] = 7;
                return true;
            }
            else if(c == Qt::magenta) {
                grid[index.row()*numberOfColumns+index.column()] = 8;
                return true;
            }
            else if(c == Qt::darkRed) {
                grid[index.row()*numberOfColumns+index.column()] = 9;
                return true;
            }
        break;
    }

    return false;
}

void GridModel::ResizeGrid(int newRow, int newcol)
{

    if(newRow<numberOfRows){

        removeRows(newRow,numberOfRows-newRow);
    }
    if(newRow>numberOfRows){
        insertRows(numberOfRows,newRow-numberOfRows);
    }
    if(newcol<numberOfColumns){
        removeColumns(newcol,numberOfColumns-newcol);
    }
    if(newcol>numberOfColumns){
        insertColumns(numberOfColumns,newcol-numberOfColumns);
    }
    clearGrid();
    grid[pStart.y*numberOfColumns+pStart.x] = 2;
    grid[pTarget.y*numberOfColumns+pTarget.x] = 3;
}

bool GridModel::insertRows(int position, int count, const QModelIndex &parent)
{
   beginInsertRows(QModelIndex(), position, position+count-1);
   int oldsize = numberOfRows*numberOfColumns;
   numberOfRows +=count;
   int newsize = numberOfRows*numberOfColumns;

   grid = (int*)realloc(grid,newsize*sizeof(grid));

   void* p = grid+oldsize;

   if(grid){
       void* p = grid+oldsize;
       memset(p,0,sizeof(grid)*count*numberOfColumns);
   }

   endInsertRows();

   return true;
}

bool GridModel::removeRows(int position, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+count-1);
    numberOfRows -=count;
    int newsize = numberOfRows*numberOfColumns;

    grid = (int*)realloc(grid,newsize*sizeof(grid));

    endRemoveRows();

    return true;
}

bool GridModel::insertColumns(int position, int count, const QModelIndex &parent)
{
    beginInsertColumns(QModelIndex(), position, position+count-1);
    int oldsize = numberOfRows*numberOfColumns;
    numberOfColumns +=count;
    int newsize = numberOfRows*numberOfColumns;

    grid = (int*)realloc(grid,newsize*sizeof(grid));
    if(grid){
        void* p = grid+oldsize;
        memset(p,0,sizeof(grid)*count*numberOfRows);
    }

    endInsertColumns();

    return true;
}

bool GridModel::removeColumns(int position, int count, const QModelIndex &parent)
{
    beginRemoveColumns(QModelIndex(), position, position+count-1);
    numberOfColumns -=count;
    int newsize = numberOfRows*numberOfColumns;

    grid = (int*)realloc(grid,newsize*sizeof(grid));
    endRemoveColumns();

    return true;
}

bool GridModel::ReadMap()
{

    QFile file("manhattan.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                qDebug("REading file NOT OK!");
                return false;
        }
        QTextStream in(&file);

        numberOfRows = in.readLine().toInt(); //row,
        numberOfColumns = in.readLine().toInt();// col read first

        grid = new int[numberOfRows*numberOfColumns];
        QString line = in.readLine();

            for(int i = 0;i<numberOfRows;++i)
            {
                for(int j= 0;j<numberOfColumns;++j){

                    grid[i*numberOfColumns+j] = line.at(j).digitValue();
                }
                line = in.readLine();
            }
     return true;
}

GridModel::~GridModel()
{
    delete[] grid;
}

void GridModel::InitGrid(int row, int col)
{
    if(row < 2 && col < 2)
    {
        qDebug("Wrong grid dimensions, must be atleast 2x2!");
        return;
    }
    pStart.x = 0;
    pStart.y = 0;

    pTarget.x = 0;
    pTarget.y = 1;


    numberOfRows = row;
    numberOfColumns = col;

    if(!ReadMap()){
        grid = new int[numberOfRows*numberOfColumns];
        for(int i = 0; i < numberOfRows; ++i)
            for(int j = 0; j < numberOfColumns; ++j)
                grid[i*numberOfColumns+j] = 0;
        //default
        grid[0] = 2; //Start
        grid[1] = 3; //Target
    }
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
        v.setValue(QColor(Qt::black));
        break;
    case 5:
        v.setValue(QColor(Qt::cyan));
        break;
    case 6:
        v.setValue(QColor(Qt::yellow));
        break;
    case 7:
        v.setValue(QColor(Qt::blue));
        break;
    case 8:
        v.setValue(QColor(Qt::magenta));
        break;
    case 9:
        v.setValue(QColor(Qt::darkRed));
        break;
    }


    if(setData(index(row,col),v,Qt::BackgroundColorRole)){
        emit(dataChanged(index(row,col), index(row,col),roles));
    }
}

int GridModel::getGridValueByIndex(const QModelIndex &index)
{
    return grid[index.row()*numberOfColumns+index.column()];
}

int GridModel::getGridValueByRowCol(int row, int col)
{
    return grid[row*numberOfColumns+col];
}

void GridModel::clearGrid()
{
    for(int i = 0;i<numberOfRows;++i)
        for(int j = 0;j<numberOfColumns;++j)
            if(grid[i*numberOfColumns+j] != 0 && grid[i*numberOfColumns+j] != 2 && grid[i*numberOfColumns+j] != 3){
                grid[i*numberOfColumns+j] = 0;
            }

    QVector<int> roles;
    roles.push_back(Qt::BackgroundColorRole);

    emit(dataChanged(index(0,0), index(numberOfRows,numberOfColumns),roles));

}

void GridModel::clearGridPaths()
{
    for(int i = 0;i<numberOfRows;++i)
        for(int j = 0;j<numberOfColumns;++j)
            if(grid[i*numberOfColumns+j] != 0 && grid[i*numberOfColumns+j] != 1 && grid[i*numberOfColumns+j] != 2 && grid[i*numberOfColumns+j] != 3){
                grid[i*numberOfColumns+j] = 0;
            }

    QVector<int> roles;
    roles.push_back(Qt::BackgroundColorRole);

    emit(dataChanged(index(0,0), index(numberOfRows,numberOfColumns),roles));
}
