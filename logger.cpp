#include "Logger.h"

Logger::Logger(QObject *parent, QString fileName) : QObject(parent) {


if (!fileName.isEmpty() && !file.isOpen()) {
 file.setFileName(fileName);
 file.open(QIODevice::Append | QIODevice::Text);

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
