#include "dialogparamteres.h"
#include "ui_dialogparamteres.h"

DialogParamteres::DialogParamteres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogParamteres)
{
    ui->setupUi(this);
}

DialogParamteres::~DialogParamteres()
{
    delete ui;
}
