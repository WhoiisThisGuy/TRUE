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
public slots:
    void updateView(int row, int col, int value);
    void clearGridPathColors();
public:
    int* grid;
public:
    GridModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    /* Reimplemented */
    virtual bool insertRows(int position, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int position, int count, const QModelIndex &parent = QModelIndex())override;
    virtual bool insertColumns(int position, int count, const QModelIndex &parent = QModelIndex())override;
    virtual bool removeColumns(int position, int count, const QModelIndex &parent = QModelIndex())override;
    bool ReadMap();

    virtual ~GridModel();

    void InitGrid(int row, int col);
    void ResizeGrid(int row, int col);


    void setGridValue(int row, int col, int value);

    int getGridValueByIndex(const QModelIndex &index);
    int getGridValueByRowCol(int row, int col);

    void clearGrid();
    void clearGridPaths();

    int numberOfRows; // hányszor
    int numberOfColumns;//hányas

    Point pStart;
    Point pTarget;

};

#endif // GRIDMODEL_H
