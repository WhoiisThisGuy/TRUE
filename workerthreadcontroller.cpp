#include "workerthreadcontroller.h"

WorkerThreadController::WorkerThreadController(QObject *parent) : QObject(parent)
{

}

bool WorkerThreadController::Init(IPathfinder *p_,const vector<variant<int,double,string>>& Parameters)
{
    p = p_;
    Worker* worker;
    worker = new Worker(p);
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &WorkerThreadController::operate, worker, &Worker::doSearch);
    connect(worker, &Worker::resultReady, this, &WorkerThreadController::handleResults);
    p->Init(Parameters);
    workerThread.start();
    return true;
}

void WorkerThreadController::handleResults(const int &result)
{

    if(result == -1){
        qDebug("WorkerThreadController: result = -1");
    }
    //else if(result == 1)
        //qDebug("WorkerThreadController: Sikeres keresés. Signal az eredménykiírásra vagy valami...");
    else if(result != 0)
       qDebug("WorkerThreadController: Sikertelen keresés.");

}
