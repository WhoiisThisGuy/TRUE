#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "QObject"

class Mediator : public QObject
{
Q_OBJECT
signals:
     void changeView(int row, int col, int val);

public:
    void updateView(int row,int col,int val);
    Mediator();

};

#endif // MEDIATOR_H
