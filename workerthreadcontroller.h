#ifndef WORKERTHREADCONTROLLER_H
#define WORKERTHREADCONTROLLER_H

#include <QObject>
#include "worker.h"

class WorkerThreadController : public QObject
{
    Q_OBJECT
        QThread workerThread;

public:
    explicit WorkerThreadController(QObject *parent = nullptr);

    bool Init(IPathfinder* p);

virtual ~WorkerThreadController() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(const int &);
signals:
    void operate(const bool&);
};

#endif // WORKERTHREADCONTROLLER_H
