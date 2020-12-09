#ifndef WORKERTHREADCONTROLLER_H
#define WORKERTHREADCONTROLLER_H

#include <QObject>
#include "dialogresults.h"
#include "worker.h"
#include "logger.h"

/* Definitions for dll files. */

typedef IPathfinder* (*fpointer)();

/* Definitions for dll files end. */


class WorkerThreadController : public QObject
{
    Q_OBJECT
        QThread workerThread;

public:
    void stop();
    explicit WorkerThreadController(QObject *parent = nullptr,dialogResults* dialog_Results_ = nullptr);

    bool Init(QString AlgoName,const QString& algoNameToLoad,Gridcontroller* gridcontroller_, const vector<string>& Parameters_);

virtual ~WorkerThreadController() {
        workerThread.quit();
        workerThread.wait();
        if(abortFlag)
            delete abortFlag;
    }
public:
    Logger* log;
    Gridcontroller* gridcontroller;
    bool *abortFlag = nullptr;
    /* Results */
    vector<int> foundPath;
    double time;
    QString algoName;

private:
    dialogResults *dialog_Results;
public slots:
    void handleResults(vector<int> ThePath,double time,int result);
signals:
    void StartSearchSignal();
    void SearchFinished(int result);
    void StopSearch();

};

#endif // WORKERTHREADCONTROLLER_H
