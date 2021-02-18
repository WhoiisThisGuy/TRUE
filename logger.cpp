#include "Logger.h"
#include "iostream"
#include "QDir"

Logger::Logger(QObject *parent, QString fileName) : QObject(parent) {


    if (!fileName.isEmpty() && !file.isOpen()) {

     file.setFileName("log.txt");

     if(file.open(QIODevice::WriteOnly)){
         ;//good
     }

     else{ //not good
         cout<<file.errorString().toStdString()<<endl;
        cout<<file.error()<<endl;
        cout<<file.PermissionsError<<endl;
        cout<<file.permissions()<<endl;
        cout<<file.OpenError<<endl;
        cout<<file.fileName().toStdString()<<endl;

     }

    }
}

void Logger::write(const QString &value) {

QString text = value;// + "";

text = "\n"+QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ") + text;
QTextStream out(&file);
out.setCodec("UTF-8");

out << text;

}

void Logger::closeFile()
{
    if(file.isOpen())
     file.close();
}


Logger::~Logger() {


}
