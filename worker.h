#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include "QThread"
#include "ipathfinder.h"
#include "QElapsedTimer"
#include "gridcontroller.h"
#include <memory.h>
#include <vector>
#include <QMetaType>

using namespace std;

/* Definitions for dll files. */

typedef IPathfinder* (*fpointer)();

/* Definitions for dll files end. */

class Worker : public QObject
{

    Q_OBJECT
public slots:
    void doSearch();
public:
    int LoadPathfinderObject(const QString& algoNameToLoad,Gridcontroller* gridcontroller);
    Worker(const vector<string>& Parameters_,bool* abortFlag_);
    virtual ~ Worker();
public:

    bool* abortFlag;
    QElapsedTimer timer;
    vector<string> Parameters;
    IPathfinder* pathfinderobject = nullptr;


private:
    //bool abortFlag;
signals:
    void resultReady(vector<int> ThePath,double time,int result);

};

#endif // WORKERTHREAD_H
