#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QTextStream"
#include "QComboBox"
#include "QLibrary"
#include "qdebug.h"

#include "dialogaddalgorithm.h"
#include "dialogparameters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,dialogparam(this)
    ,threadController(this,&dialog_results)
    ,gridcontroller(&mediator)
    ,log(this,"log.txt")
{
    mouseLeftClickOnHold = false;
    clickedOnWhite = false;

    ui->setupUi(this);

    myGridModel.InitGrid(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value()); //Create grid array
    InitModelView(); //Table gemoetry setup

    connect(&dialogparam,&DialogParameters::finished,this,&MainWindow::on_paramWindowDestroyed);
    connect(&threadController,&WorkerThreadController::SearchFinished,this,&MainWindow::handleSearchFinish);

    CreateActions();
    CreateMenus();

    ReadAlgorithms(); //load in the list of algorithms
    threadController.log = &log;

    ui->myGridView->viewport()->installEventFilter(this);

}


MainWindow::~MainWindow()
{
    delete ui;

    //clean up
    if(newAlgoAct) //Do I have to delete this ?
        delete newAlgoAct;
    if(exitAct)
        delete exitAct;
    log.closeFile();
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
    else if( cellData == 2 || cellData == 3 ){

        isStartOrTargetSelected = true;
        startOrTargetSelectedIndex.row = index.row();
        startOrTargetSelectedIndex.col = index.column();
        startOrTargetSelectedColor = cellData;

        return;
    }
}

void MainWindow::on_myGridView_entered(const QModelIndex &index)
{

  if(isStartOrTargetSelected) { //Handle endpoints drag
    int oppositeColor = startOrTargetSelectedColor == 2 ? 3 : 2; //opposite: red <-> green
      if(myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()] != oppositeColor
      && myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()] != 1
      && (index.column() != startOrTargetSelectedIndex.col || startOrTargetSelectedIndex.row != index.row())) //if cursor moved in a different cell
      {
          myGridModel.setGridValue(startOrTargetSelectedIndex.row,startOrTargetSelectedIndex.col,0);
          startOrTargetSelectedIndex.row = index.row();
          startOrTargetSelectedIndex.col = index.column();
      }
      myGridModel.setGridValue(index.row(),index.column(),startOrTargetSelectedColor);
   }
  if(mouseLeftClickOnHold){
      if(myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()] == 0 && clickedOnWhite){
          myGridModel.setGridValue(index.row(),index.column(),1);
      }
      else if(myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()] == 1 && !clickedOnWhite){
          myGridModel.setGridValue(index.row(),index.column(),0);
      }
  }
}

void MainWindow::on_resizeButton_clicked()
{

    myGridModel.ResizeGrid(ui->numberOfRowsBox->value(),ui->numberOfColumnsBox->value());
    statusBar()->showMessage("Map resized.");
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

void MainWindow::AddAlgorithmToFile()
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
   QSettings settings(CFGPATH,QSettings::IniFormat);

   if (!QFile(CFGPATH).exists()){
       log.write("SavedAlgorithms.ini file is missing.");
   }

   QStringList algoNameList = settings.childKeys();

   int size = algoNameList.size();

   for (int i = 0; i < size; ++i) {

    slistAlgoDllPaths.push_back(settings.value(algoNameList.at(i)).toString()); //Store all dll path

   }

    ui->widgetListAlgorithms->addItems(algoNameList); //Set the algo name list

}

void MainWindow::on_clearButton_clicked()
{

    myGridModel.clearGrid();
    statusBar()->showMessage("Map cleaned.");

}

void MainWindow::on_paramWindowDestroyed()
{

    ui->buttonParameters->setEnabled(true);
    ui->buttonRun->setEnabled(false);

}

void MainWindow::addAlgorithm()
{
    ui->buttonParameters->setEnabled(false);
    ui->buttonRun->setEnabled(false);
    ui->buttonDeleteAlgo->setEnabled(false);
    DialogAddAlgorithm dialog(this,ui->widgetListAlgorithms,&slistAlgoDllPaths);

    dialog.exec();

    setStatusTip(tr("Window closed."));
}

void MainWindow::exit()
{
    close();
}

void MainWindow::CreateMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAlgoAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::CreateActions()
{
    newAlgoAct = new QAction(tr("&New algorithm"), this);
    newAlgoAct->setStatusTip(tr("Add new algorithm to the list."));
    connect(newAlgoAct, &QAction::triggered, this, &MainWindow::addAlgorithm);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Exit the program."));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exit);
}

void MainWindow::on_buttonParameters_clicked()
{
    dialogparam.loadParamDialogSettings(ui->widgetListAlgorithms->selectedItems().at(0)->text());
    dialogparam.show();
    ui->buttonParameters->setEnabled(false);
    statusBar()->showMessage("Paraméter beállítások mutatása.");
}

void MainWindow::on_widgetListAlgorithms_itemSelectionChanged()
{
    QList<QListWidgetItem*> selected = ui->widgetListAlgorithms->selectedItems();
    if(!dialogparam.isVisible() && !selected.empty()){
        ui->buttonParameters->setEnabled(true);
        ui->buttonRun->setEnabled(true);
        ui->buttonDeleteAlgo->setEnabled(true);
    }
    else{
        ui->buttonParameters->setEnabled(false);
        ui->buttonRun->setEnabled(false);
        ui->buttonDeleteAlgo->setEnabled(false);
    }
}

void MainWindow::on_buttonRun_clicked()
{

    //LoaddllFile();
    statusBar()->showMessage("Starting search...");
    log.write("Starting new search process...");
    StartSearch();

}
void MainWindow::StartSearch()
{
    log.write("Reading selected algorithm name.");
    QListWidgetItem* item = ui->widgetListAlgorithms->selectedItems().at(0);
    log.write("Selected algorithm name: "+item->text());
    int rowOfItem = ui->widgetListAlgorithms->row(item);

    algoNameToLoad = slistAlgoDllPaths.at(rowOfItem);
    log.write("The path for the dll file: "+algoNameToLoad);
    myGridModel.clearGridPaths();

    gridcontroller.InitGrid(&myGridModel);//not using gridcontroller in the main thread anymore from this point
    vector<string> parameters;
    log.write("Compiling search parameters...");
    if(dialogparam.isVisible())
      parameters = dialogparam.CompileParameters();
    else{
      parameters = dialogparam.getParametersFromFile(item->text());
    }
    log.write("Search parameters compiled.");
    try{
        statusBar()->showMessage("Initialize");
        log.write("Initializing threadController...");
        if(threadController.Init(item->text(),algoNameToLoad,&gridcontroller,parameters)){
            log.write("threadController Init successful, sending out StartSearchSignal...");
           threadController.StartSearchSignal();//this is on a new thread now
           ui->buttonStop->setEnabled(true);
           ui->buttonRun->setEnabled(false);
           ui->buttonRun->setEnabled(false);
           ui->resizeButton->setEnabled(false);
           ui->clearButton->setEnabled(true);
           statusBar()->showMessage("Search is in progress...");
           log.write("Search started.");
        }
        else{
           statusBar()->showMessage("Initializing search failed.");
           log.write("INITIALIZATION OF THREADCONTROLLER WAS UNSUCCESSFUL.");
        }
    }catch(std::error_code e){
        statusBar()->showMessage("Initializing failed.");

        log.write("*ERROR* error_code:" +QString::number(e.value())+QString::fromStdString(e.message()));
    }

}

void MainWindow::handleSearchFinish(int result)
{
    ui->buttonRun->setEnabled(true);
    ui->buttonStop->setEnabled(false);
    ui->resizeButton->setEnabled(true);
    ui->clearButton->setEnabled(true);
    ui->button_Results->setEnabled(true);

    if(result == 0){
        statusBar()->showMessage(tr("Successful search."));
        log.write("Search finished successfully.");
    }
    else if(result == -1){
        statusBar()->showMessage(tr("Search stopped."));
        log.write("Search was stopped by the User.");
    }
    else{
        statusBar()->showMessage("Search returned with: "+QString::number(result));
        log.write("Search has returned with the value: "+QString::number(result));
    }

}

void MainWindow::on_buttonDeleteAlgo_clicked()
{
 QString deletableAlgo = ui->widgetListAlgorithms->selectedItems().at(0)->text();

 if(deletableAlgo == "")
     return;

 QListWidgetItem* item = ui->widgetListAlgorithms->selectedItems().at(0);

 if(!item)
     return;

 int rowOfItem = ui->widgetListAlgorithms->row(item);

 delete item; //remove it from the list widget

 slistAlgoDllPaths.removeAt(rowOfItem);

 QSettings settings(CFGPATH,QSettings::IniFormat);
 settings.remove(deletableAlgo);

 QFile file(deletableAlgo+"ParameterSettings.ini");

 file.remove();

 statusBar()->showMessage(tr("Algorithm deleted."));
}

void MainWindow::on_button_Results_clicked()
{
    statusBar()->showMessage("Show results.");
    dialog_results.show();
}

void MainWindow::on_buttonStop_clicked()
{
    threadController.stop();
}


void MainWindow::on_widgetListAlgorithms_itemClicked(QListWidgetItem *item)
{
    if(item){
        ui->buttonParameters->setEnabled(true);
        ui->buttonRun->setEnabled(true);
        ui->buttonDeleteAlgo->setEnabled(true);

    }
    else{
        ui->buttonParameters->setEnabled(false);
        ui->buttonRun->setEnabled(false);
        ui->buttonDeleteAlgo->setEnabled(false);
    }
}


void MainWindow::on_pushButton_clicked()
{
    statusBar()->showMessage("Remove previous search colors.");
    myGridModel.clearGridPaths();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->myGridView->viewport() && event->type() == QEvent::MouseButtonRelease) {
            mouseLeftClickOnHold = false;
            return true;//view does not have to process this event
     }
     return false;
}

void MainWindow::on_myGridView_pressed(const QModelIndex &index)
{
    mouseLeftClickOnHold = true;
    if(myGridModel.grid[index.row()*myGridModel.numberOfColumns+index.column()] == 0){
        clickedOnWhite = true;
        myGridModel.setGridValue(index.row(),index.column(),1);
    }
    else{
        clickedOnWhite = false;
        myGridModel.setGridValue(index.row(),index.column(),0);
    }

}
