#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "dialogaddalgorithm.h"
#include "QTextStream"
#include "dialogparameters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cellsize(20)
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

    if(myGridModel) //Safety + clean up
        delete myGridModel;
    delete ui;
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


void MainWindow::on_myGridView_entered(const QModelIndex &index)
{
 QVariant qvarIndex = myGridModel->data(index,Qt::BackgroundColorRole);

  //QColor qcolorIndex = qvarIndex.value<QColor>();

  if(isStartOrTargetSelected && myGridModel->getGridValueByIndex(index) == 0) {
        myGridModel->setData(index, startOrTargetSelectedColor,Qt::BackgroundColorRole);
   }
  else{
      return;
  }

}

void MainWindow::on_clearButton_clicked()
{

    myGridModel->clearGrid();

}

void MainWindow::on_paramWindowDestroyed()
{
    ui->buttonParameters->setEnabled(true);
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
    dialogparam.show();
    ui->buttonParameters->setEnabled(false);

}

void MainWindow::on_widgetListAlgorithms_itemSelectionChanged()
{
    QList<QListWidgetItem*> selected = ui->widgetListAlgorithms->selectedItems();
    if(selected.empty() || dialogparam.isVisible())
        ui->buttonParameters->setEnabled(false);
    else
        ui->buttonParameters->setEnabled(true);
}
