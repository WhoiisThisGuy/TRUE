#ifndef LOGGER_H
#define LOGGER_H
#include <QObject>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <string>

using namespace std;

class Logger : public QObject {

Q_OBJECT
public:

explicit Logger(QObject *parent, QString fileName);
void write(const QString &value);
void closeFile();

~Logger();


private:
    QFile file;
};

#endif // LOGGER_H
