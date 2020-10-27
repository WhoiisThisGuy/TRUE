#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "dialogaddalgorithm.h"
#include "QTextStream"
#include "dialogparameters.h"
#include "QComboBox"
#include <iterator>
#include "windows.h"
#include "QLibrary"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cellsize(20)
    ,dialogparam(this)
    ,threadController(this)
{

    ui->setupUi(this);
    connect(&dialogparam,&DialogParameters::finished,this,&MainWindow::on_paramWindowDestroyed);

    createActions();
    createMenus();
    InitModelView(); //Grid gemoetry setup

    InitAlgorithmListWidget(); //load in the list of algorithms

}


MainWindow::~MainWindow()
{
    delete ui;


    //Thread stops

    //Safety + clean up
    if(algorithmObject)
        delete algorithmObject;
    if(gridcontroller)
        delete gridcontroller;
    if(myGridModel)
        delete myGridModel;
    if(newAlgoAct)
        delete newAlgoAct;
    if(exitAct)
        delete exitAct;


}
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
void MainWindow::on_myGridView_clicked(const QModelIndex &index)
{
    int cellData = myGridModel->grid[index.row()*myGridModel->numberOfColumns+index.column()]; //what is in the cell

    if(isStartOrTargetSelected){
    int oppositeColor = startOrTargetSelectedColor == 2 ? 3 : 2;
        if(cellData != 1 && cellData != oppositeColor){

            isStartOrTargetSelected = false;

            return;
        }
        return;
    }
    if(cellData == 0){ //clicked on white cell

        myGridModel->setGridValue(index.row(),index.column(),1); //set gray cell

    }
    else if(cellData == 1){//clicked on gray cell

       myGridModel->setGridValue(index.row(),index.column(),0); //set white cell
    }
    else if( cellData == 2 || cellData == 3 ){
        if(!isStartOrTargetSelected){

            isStartOrTargetSelected = true;

            startOrTargetSelectedIndex.x = index.row();
            startOrTargetSelectedIndex.y = index.column();

            startOrTargetSelectedColor = cellData;


            return;
        }
    }
}

void MainWindow::on_myGridView_entered(const QModelIndex &index)
{

  if(isStartOrTargetSelected) {
    int oppositeColor = startOrTargetSelectedColor == 2 ? 3 : 2;
      if(myGridModel->grid[index.row()*myGridModel->numberOfColumns+index.column()] != oppositeColor
      && myGridModel->grid[index.row()*myGridModel->numberOfColumns+index.column()] != 1
      && (index.column() != startOrTargetSelectedIndex.y || startOrTargetSelectedIndex.x != index.row()))
      {
          myGridModel->setGridValue(startOrTargetSelectedIndex.x,startOrTargetSelectedIndex.y,0);
          startOrTargetSelectedIndex.x = index.row();
          startOrTargetSelectedIndex.y = index.column();
      }
      myGridModel->setGridValue(index.row(),index.column(),startOrTargetSelectedColor);
   }
  else{
      return;
  }

}

void MainWindow::on_pushButton_clicked()
{
    myGridModel->ResizeGrid(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value());
    //InitModelView();
    //myGridModel->InitGrid(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value());
}

void MainWindow::InitModelView()
{

    if(myGridModel){
        delete myGridModel;
        //disconnect(&mediator,&Mediator::changeView,myGridModel,&GridModel::updateView);
    }

    myGridModel = new GridModel(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value());
    connect(&mediator,&Mediator::changeView,myGridModel,&GridModel::updateView);

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

void MainWindow::AddAlgorithmToFile(const QString& string)
{


    QFile file(CFGPATH);

    if (!file.open(QIODevice::ReadOnly)) {
         QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
         return;
     }

}

bool MainWindow::ReadAlgorithms()
{
    QFile file(CFGPATH);
    bool fileopened = false;
    if(file.exists()){
    //if file exists check if the algoname is already in the text

        if (file.open(QIODevice::ReadOnly))
        {
            fileopened = true;
            QTextStream in(&file);
            QStringList stringTokens;
            while (!in.atEnd()) {
                stringTokens+=in.readLine().split("=");
                slistAlgoNames.push_back(stringTokens[0]);
                slistAlgoDllPaths.push_back(stringTokens[1]);
                stringTokens.clear();
            }

        }
        else{
            qDebug("Could not open file for reading.");
        }
    }
    else{
        qDebug("Config file not found.");
        fileopened = false;
        file.close();
        return false;
    }

    fileopened = false;
    file.close();
    return true;
}

bool MainWindow::InitAlgorithmListWidget()
{
    if(!ReadAlgorithms()){
        qDebug("Reading config file failed.");
        return false;
    }
    ui->widgetListAlgorithms->addItems(slistAlgoNames);

    return true;
}



void MainWindow::on_clearButton_clicked()
{

    myGridModel->clearGrid();

}

void MainWindow::on_paramWindowDestroyed()
{

    ui->buttonParameters->setEnabled(true);
    ui->buttonRun->setEnabled(false);

}

void MainWindow::addAlgorithm()
{
    DialogAddAlgorithm dialog(this);
    dialog.exec();
}

void MainWindow::exit()
{
    close();
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Fájl"));
    fileMenu->addAction(newAlgoAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::createActions()
{
    newAlgoAct = new QAction(tr("&Új algoritmus"), this);
    newAlgoAct->setStatusTip(tr("Új algoritmus felvétele a listába."));
    connect(newAlgoAct, &QAction::triggered, this, &MainWindow::addAlgorithm);

    exitAct = new QAction(tr("&Kilépés"), this);
    exitAct->setStatusTip(tr("Program bezárása."));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exit);
}

void MainWindow::on_buttonParameters_clicked()
{
    dialogparam.loadParamDialogSettings(ui->widgetListAlgorithms->selectedItems().at(0)->text());
    dialogparam.show();
    ui->buttonParameters->setEnabled(false);
    ui->buttonRun->setEnabled(true);
}

void MainWindow::on_widgetListAlgorithms_itemSelectionChanged()
{
    QList<QListWidgetItem*> selected = ui->widgetListAlgorithms->selectedItems();
    if(selected.empty() || dialogparam.isVisible()){
        ui->buttonParameters->setEnabled(false);
        ui->buttonRun->setEnabled(false);
    }
    else{
        ui->buttonParameters->setEnabled(true);
    }
}

void MainWindow::on_buttonRun_clicked()
{
//    dialogparam.setParameters();
//    algorithmRunParameters = DialogParameters::getParameters();
//    for(auto x: algorithmRunParameters){
//        qDebug("param: %s",x.data());
//    }
//    qDebug("Got the parameters!");

    if(!fp) //implement check for different algorithm fp
        loaddll();
    runsearch();

}
void MainWindow::runsearch()
{
    qDebug("Search start.");
    if(!gridcontroller){
        gridcontroller = new ObserverTeszt(&mediator); //this will be used only in the new thread

    }
    gridcontroller->InitGridModel(myGridModel);//not using in the main thread anymore from this point

    if(algorithmObject){
        algorithmObject->Attach(gridcontroller);//not using in the main thread anymore from this point

        //From this part a new thread is started
        //if()
        qDebug("Mainwindow threadid: %d",QThread::currentThreadId());
        if(threadController.Init(algorithmObject))
            threadController.operate(true);//this is on a new thread now


    }

    else{
        qDebug("algorithmObject NOT ok.");
    }

}



void MainWindow::loaddll()
{

    QLibrary myLib("qtdllteszt");

    fp = (fpointer) myLib.resolve("InitPathfinderObject");

    if (fp){

      qDebug("resolve successful");
      algorithmObject = fp();

    }
    else
       qDebug("%s",myLib.errorString().toUtf8().constData());


}
