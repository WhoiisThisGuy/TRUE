#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,myGridModel(3,3) //default 3x3
{

    ui->setupUi(this);

    ui->myGridView->setModel(&myGridModel);
    ui->myGridView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //nem méretezhető
    ui->myGridView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); //nem méretezhető
    ui->myGridView->show();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_myGridView_clicked(const QModelIndex &index)
{
    QVariant qv = myGridModel.data(index,Qt::BackgroundColorRole);
    if(qv.value<QColor>() == Qt::white){
        QColor c = Qt::gray;
        myGridModel.setData(index,c,Qt::BackgroundColorRole);
    }
    else if(qv.value<QColor>() == Qt::gray){
        QColor c = Qt::white;
        myGridModel.setData(index,c,Qt::BackgroundColorRole);
    }
}

void MainWindow::on_myGridView_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_clicked()
{
    myGridModel.setRowandCols(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value());
}
