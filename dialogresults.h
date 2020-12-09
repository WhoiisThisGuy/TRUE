#ifndef DIALOGRESULTS_H
#define DIALOGRESULTS_H

#include <QDialog>


namespace Ui {
class dialogResults;
}

class dialogResults : public QDialog
{
    Q_OBJECT

public:
    explicit dialogResults(QWidget *parent = nullptr);
    ~dialogResults();
    void setResults(QString name,double time, int length, int expanded);

private:
    Ui::dialogResults *ui;
};

#endif // DIALOGRESULTS_H
