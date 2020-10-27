#include "workerthreadcontroller.h"
int counter = 0;
WorkerThreadController::WorkerThreadController(QObject *parent) : QObject(parent)
{

}

bool WorkerThreadController::Init(IPathfinder *p)
{
    Worker* worker;
    worker = new Worker(p);
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &WorkerThreadController::operate, worker, &Worker::doSearch);
    connect(worker, &Worker::resultReady, this, &WorkerThreadController::handleResults);
    workerThread.start();
    return true;
}

void WorkerThreadController::handleResults(const bool &result)
{
    ++counter;
    qDebug("Countdfgdfdfghdfhdfher: %d",counter);
    if(result)
        qDebug("WorkerThreadController: Sikeres keresés. Signal az eredménykiírásra vagy valami...");
    else
        qDebug("WorkerThreadController: Sikertelen keresés.");
    //worker->quit();
}
