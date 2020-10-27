#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include "QThread"
#include "ipathfinder.h"

class Worker : public QObject
{
    Q_OBJECT
public slots:
    void doSearch() {
        bool result = pathfinderobject->StartSearch();
        //qDebug("Workerthread threadid: %d",QThread::currentThreadId());
        /* ... here is the expensive or blocking operation ... */
        //qDebug("Worker: result ready emitting result signal!");
        emit resultReady(result);
    }
public:
    Worker(IPathfinder* p);
    virtual ~ Worker(){};
public:
    IPathfinder* pathfinderobject;

signals:
    void resultReady(bool solutionfound);

};

#endif // WORKERTHREAD_H
