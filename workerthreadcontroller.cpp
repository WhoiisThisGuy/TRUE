#include "workerthreadcontroller.h"
#include "QDebug"

void WorkerThreadController::stop()
{
    *abortFlag = true;
}

WorkerThreadController::WorkerThreadController(QObject *parent,dialogResults* dialog_Results_) : QObject(parent)
{
    dialog_Results = dialog_Results_;
}

bool WorkerThreadController::Init(QString AlgoName,const QString& algoNameToLoad,Gridcontroller* gridcontroller_,const vector<string>& Parameters_)
{
    algoName = AlgoName;
    gridcontroller = gridcontroller_;
    Worker* worker;
      abortFlag = new bool();
      *abortFlag = false;
      worker = new Worker(Parameters_,abortFlag);
      int result = worker->LoadPathfinderObject(algoNameToLoad,gridcontroller);

      if(result == 0){

          log->write("Worker LoadPathfinderObject(): Resolving function from .dll successful.");
          worker->moveToThread(&workerThread);
          connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
          connect(this, &WorkerThreadController::StartSearchSignal, worker, &Worker::doSearch);
          connect(worker, &Worker::resultReady, this, &WorkerThreadController::handleResults);
          workerThread.start();
          return true;
      }
      else if(result == -1){
        log->write("*ERROR* Worker: LoadPathfinderObject(): Resolving InitPathfinderObject() function from .dll failed.");
      }
      else if(result == -2){
        log->write("*ERROR* Worker LoadPathfinderObject(): InitPathfinderObject() failed. Pathfinderobject is NULL.");
      }
      else{
        log->write("*ERROR* WorkerThreadController: Init() Error: LoadPathFinderObject() failed. Error code: "+QString::number(result));
      }

    delete worker;
    delete abortFlag;
    abortFlag = nullptr;
    worker = nullptr;
    return false;
}

void WorkerThreadController::handleResults(vector<int> ThePath, double time_,int result)
{

    gridcontroller->mygridmodel->DrawPath(ThePath);

    foundPath = ThePath;

    time = time_;

    dialog_Results->setResults(algoName,time,ThePath.size(),gridcontroller->numberOfVisitedNodes);

    workerThread.quit();
    emit(SearchFinished(result));

}
