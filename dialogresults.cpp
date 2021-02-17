#include "dialogresults.h"
#include "ui_dialogresults.h"

dialogResults::dialogResults(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogResults)
{
    ui->setupUi(this);
    setModal(false);
}

dialogResults::~dialogResults()
{
    delete ui;
}

void dialogResults::setResults(QString name, double time, int length, int expanded)
{
    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(QString::number(time));
    ui->lineEdit_3->setText(QString::number(expanded));
    ui->lineEdit_4->setText(QString::number(length));
}
