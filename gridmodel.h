#ifndef GRIDMODEL_H
#define GRIDMODEL_H
#include "QAbstractTableModel"
#include "QColor"
#include "QBrush"
#include "mypoint.h"

//[event_receiver(native)]
class GridModel : public QAbstractTableModel
{

    Q_OBJECT
public:
    char grid[100][100];
public:
    GridModel(int n,int m);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual ~GridModel();

    void setRowandCols(int a, int b);
    void setGridValue(int row, int col, int value);

    int getGridValueByIndex(const QModelIndex &index);
    int getGridValueByRowCol(int row, int col);

    void clearGrid();

    int numberOfRows; // hányszor
    int numberOfColumns;//hányas

    Point pStart;
    Point pTarget;

};

#endif // GRIDMODEL_H
