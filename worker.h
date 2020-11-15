#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include "QThread"
#include "ipathfinder.h"
#include "QElapsedTimer"

class Worker : public QObject
{
    Q_OBJECT
public slots:
    void doSearch() {
        timer.start();
        int result = pathfinderobject->StartSearch();
        //qDebug("Workerthread threadid: %d",QThread::currentThreadId());
        /* ... here is the expensive or blocking operation ... */
        //qDebug("Worker: result ready emitting result signal!");

        qDebug("Timer stopped!");
        qDebug("---------------------");
        qDebug()<<"Timer: Elapsed time: "<<timer.elapsed()<<" milliseconds"<<endl;
        qDebug("---------------------");
        emit resultReady(result);

    }
public:

    Worker(IPathfinder* p);
    virtual ~ Worker() { qDebug("Worker deleted.");}
public:
    IPathfinder* pathfinderobject;
    QElapsedTimer timer;
signals:
    void resultReady(bool solutionfound);

};

#endif // WORKERTHREAD_H
