#include "worker.h"
#include "QLibrary"
#include "QDebug"

void Worker::doSearch()
{

timer.start();
int result = 0;

result = pathfinderobject->StartSearch(abortFlag);
double time = timer.elapsed();

qRegisterMetaType<vector<int>>("vector<int>");

emit (resultReady(pathfinderobject->getPath(),time,result));

}

int Worker::LoadPathfinderObject(const QString& algoNameToLoad,Gridcontroller* gridcontroller)
{
    QLibrary myLib(algoNameToLoad);
    fpointer fp = (fpointer) myLib.resolve("InitPathfinderObject");
    if (!fp){
      return -1;
    }
   pathfinderobject = fp();

   if(!pathfinderobject){

     return -2;
   }

   pathfinderobject->Attach(gridcontroller);

   try{

     pathfinderobject->Init(Parameters);
     return 0;

   }catch(std::error_code e){

     return e.value();
   }
}

Worker::Worker(const vector<string> &Parameters_, bool *abortFlag_)
{
    abortFlag = abortFlag_;
    Parameters = Parameters_;
}

Worker::~Worker()
{
    if(pathfinderobject){
        delete pathfinderobject;       
    }
}

