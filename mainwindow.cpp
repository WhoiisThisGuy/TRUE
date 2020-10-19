#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cellsize(20)
{

    ui->setupUi(this);



    InitModelView();
}


MainWindow::~MainWindow()
{
    if(myGridModel) //Safety + clean up
        delete myGridModel;
    delete ui;
}

void MainWindow::on_myGridView_clicked(const QModelIndex &index)
{
    QVariant qvIndex = myGridModel->data(index,Qt::BackgroundColorRole);

    QColor qcolorIndex = qvIndex.value<QColor>();

    if(isStartOrTargetSelected){

        if(myGridModel->getGridValueByIndex(index) == 0){

            isStartOrTargetSelected = false;

            myGridModel->setData(index,startOrTargetSelectedColor,Qt::BackgroundColorRole);
            return;
        }
        return;
    }
    if(qcolorIndex == Qt::white){
        QColor c = Qt::gray;
        myGridModel->setData(index,c,Qt::BackgroundColorRole);

    }
    else if(qcolorIndex == Qt::gray){
        QColor c = Qt::white;
        myGridModel->setData(index,c,Qt::BackgroundColorRole);
    }
    else if(qcolorIndex == Qt::red || qcolorIndex == Qt::green){
        if(!isStartOrTargetSelected){

            isStartOrTargetSelected = true;

            startOrTargetSelectedIndex = index;
            startOrTargetSelectedColor = qcolorIndex;
            QColor c = Qt::white;
            myGridModel->setData(index, c,Qt::BackgroundColorRole);

            return;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    InitModelView();
}

void MainWindow::InitModelView()
{
    if(myGridModel)
        delete myGridModel;

    myGridModel = new GridModel(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value());

    ui->myGridView->setModel(myGridModel);
    ui->myGridView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //Fixed cell size
    ui->myGridView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); //Fixed cell size

    int viewWidth;
    int viewHeight;

    viewWidth = cellsize * (ui->numberOfColumnsBox->value()+2);
    viewHeight = cellsize * (ui->numberOfRowsBox->value()+2);

    QRect rect = ui->myGridView->geometry();

    rect.setWidth(viewWidth);
    rect.setHeight(viewHeight);

    ui->myGridView->setGeometry(rect);
    ui->myGridView->show();
}


void MainWindow::on_myGridView_entered(const QModelIndex &index)
{
 QVariant qvarIndex = myGridModel->data(index,Qt::BackgroundColorRole);

  QColor qcolorIndex = qvarIndex.value<QColor>();

  if(isStartOrTargetSelected && myGridModel->getGridValueByIndex(index) == 0) {
        myGridModel->setData(index, startOrTargetSelectedColor,Qt::BackgroundColorRole);
   }
  else{
      return;
  }

}

void MainWindow::on_clearButton_clicked()
{

//    for(int i = 0;i<100;++i)
//        for(int j = 0;j<100;++j)
//            if(myGridModel->getGridValueByRowCol(i,j) == 1){

//                QModelIndex index = myGridModel->index(i,j);
//                myGridModel->setData(index,QColor(Qt::red),Qt::BackgroundColorRole);
//                //grid[i][j] = 0; //Minden cella fehér alapból

//            }

    myGridModel->clearGrid();

}
