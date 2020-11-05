#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "QObject"

class Mediator : public QObject
{
Q_OBJECT
signals:
     void changeView(int row, int col, int val);
     void clearColors();

public:
    void updateView(int row,int col,int val);
    void clearGridColors();
    Mediator();

};

#endif // MEDIATOR_H
