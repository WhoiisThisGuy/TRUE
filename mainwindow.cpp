#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QTextStream"
#include "QComboBox"
#include "QLibrary"

#include "dialogaddalgorithm.h"
#include "dialogparameters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,dialogparam(this)
    ,threadController(this)
{

    ui->setupUi(this);

    myGridModel.InitGrid(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value()); //Create grid array
    InitModelView(); //Table gemoetry setup

    connect(&dialogparam,&DialogParameters::finished,this,&MainWindow::on_paramWindowDestroyed);

    CreateActions();
    CreateMenus();

    ReadAlgorithms(); //load in the list of algorithms

}


MainWindow::~MainWindow()
{
    delete ui;

    //clean up
    if(algorithmObject)
        delete algorithmObject;
    if(gridcontroller)
        delete gridcontroller;
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
    int cellData = myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()]; //what is in the cell

    //Place the start or target node if it is selected
    if(isStartOrTargetSelected){

     int oppositeColor = startOrTargetSelectedColor == 2 ? 3 : 2;
        if(cellData != 1 && cellData != oppositeColor){

            isStartOrTargetSelected = false;
            //on_myGridView_entered function sets the position

            return;
        }
        return;
    }

    if(cellData == 0){ //clicked on white cell

        myGridModel.setGridValue(index.row(),index.column(),1); //set gray cell

    }
    else if(cellData == 1){//clicked on gray cell

       myGridModel.setGridValue(index.row(),index.column(),0); //set white cell
    }
    else if( cellData == 2 || cellData == 3 ){

        isStartOrTargetSelected = true;
        startOrTargetSelectedIndex.x = index.row();
        startOrTargetSelectedIndex.y = index.column();
        startOrTargetSelectedColor = cellData;

        return;
    }
}

void MainWindow::on_myGridView_entered(const QModelIndex &index)
{

  if(isStartOrTargetSelected) {
    int oppositeColor = startOrTargetSelectedColor == 2 ? 3 : 2;
      if(myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()] != oppositeColor
      && myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()] != 1
      && (index.column() != startOrTargetSelectedIndex.y || startOrTargetSelectedIndex.x != index.row())) //if cursor moved in a different cell
      {
          myGridModel.setGridValue(startOrTargetSelectedIndex.x,startOrTargetSelectedIndex.y,0);
          startOrTargetSelectedIndex.x = index.row();
          startOrTargetSelectedIndex.y = index.column();
      }
      myGridModel.setGridValue(index.row(),index.column(),startOrTargetSelectedColor);
   }
}

void MainWindow::on_resizeButton_clicked()
{
    myGridModel.ResizeGrid(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value());
}

void MainWindow::InitModelView()
{

    connect(&mediator,&Mediator::changeView,&myGridModel,&GridModel::updateView);
    connect(&mediator,&Mediator::clearColors,&myGridModel,&GridModel::clearGridPathColors);

    ui->myGridView->setModel(&myGridModel);
    ui->myGridView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //Fixed cell size
    ui->myGridView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); //Fixed cell size

    int viewWidth;
    int viewHeight;

    viewWidth = cellsize * (ui->numberOfColumnsBox->value());
    viewHeight = cellsize * (ui->numberOfRowsBox->value());

    QRect rect = ui->myGridView->geometry();

    rect.setWidth(viewWidth);
    rect.setHeight(viewHeight);

    ui->myGridView->setGeometry(rect);
    ui->myGridView->show();

    ui->numberOfRowsBox->setValue(myGridModel.numberOfRows);
    ui->numberOfColumnsBox->setValue(myGridModel.numberOfColumns);
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

void MainWindow::ReadAlgorithms()
{
    QFile file(CFGPATH);

    if(file.exists()){
        if (file.open(QIODevice::ReadOnly))
        {

            QTextStream in(&file);
            QStringList stringTokens;
            while (!in.atEnd()) {
                stringTokens+=in.readLine().split("=");
                slistAlgoNames.push_back(stringTokens[0]);
                slistAlgoDllPaths.push_back(stringTokens[1]);
                stringTokens.clear();
            }
            //Success
            ui->widgetListAlgorithms->addItems(slistAlgoNames);
            return;

        }
        else{
            qDebug("Could not open file for reading.");
        }
    }
    else{
        qDebug("Config file not found.");

        file.close();
        return;
    }
    file.close();
    return;
}

void MainWindow::on_clearButton_clicked()
{

    myGridModel.clearGrid();

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

void MainWindow::CreateMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Fájl"));
    fileMenu->addAction(newAlgoAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::CreateActions()
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
    if(!dialogparam.isVisible() && !selected.empty()){
        ui->buttonParameters->setEnabled(true);
        ui->buttonRun->setEnabled(true);
    }
    else{
        ui->buttonParameters->setEnabled(false);
        ui->buttonRun->setEnabled(false);
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
        LoaddllFile();
    StartSearch();

}
void MainWindow::StartSearch()
{

    if(!gridcontroller){
        gridcontroller = new Gridcontroller(&mediator); //this will be used only in the new thread

    }
    gridcontroller->InitGridModel(&myGridModel);//not using in the main thread anymore from this point

    if(algorithmObject){
        algorithmObject->Attach(gridcontroller);//not using in the main thread anymore from this point

        //From this part a new thread is started
        qDebug("Mainwindow threadid: %d",QThread::currentThreadId());
        if(threadController.Init(algorithmObject)){
            threadController.operate(true);//this is on a new thread now
        }
    }

}



void MainWindow::LoaddllFile()
{

    QLibrary myLib("dllteszt"); //AntColonyOptimization,qtdllteszt,Astar

    fp = (fpointer) myLib.resolve("InitPathfinderObject");

    if (fp){

      qDebug("resolve successful");
      algorithmObject = fp();
      if(!algorithmObject)
           qDebug("algorithmObject NOT ok.");

    }
    else
       qDebug("%s",myLib.errorString().toUtf8().constData());


}

void MainWindow::on_pushButton_2_clicked()
{
    QFile file("out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug("File open for write not ok!");
    }

    QTextStream out(&file);

    out << myGridModel.numberOfRows<<"\n"<<myGridModel.numberOfColumns<<"\n";
    for(int i = 0;i<myGridModel.numberOfRows;++i)
    {
        for(int j= 0;j<myGridModel.numberOfColumns;++j){
            out<<myGridModel.getGridValueByRowCol(i,j);
        }
        out<<"\n";
    }

}
