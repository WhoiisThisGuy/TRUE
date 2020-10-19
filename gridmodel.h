#ifndef GRIDMODEL_H
#define GRIDMODEL_H
#include "QAbstractTableModel"
#include "QColor"
#include "QBrush"

class GridModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    GridModel(int n,int m);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual ~GridModel();

    void setRowandCols(int a, int b);

    int getGridValueByIndex(const QModelIndex &index);
    int getGridValueByRowCol(int row, int col);

    void clearGrid();

private:
    char grid[100][100];

    int numberOfRows; // hányszor
    int numberOfColumns;//hányas

    int numOfStartNode = 0;
    int numOfTargetNode = 0;

    QPoint pStart;
    QPoint pTarget;
};

#endif // GRIDMODEL_H
