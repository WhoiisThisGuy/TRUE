#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gridmodel.h"
#include "QVariant"
#include "QMouseEvent"
#include "QPainter"
#include "QFileDialog"
#include "dialogparameters.h"
#include "ipathfinder.h"
#include "observerteszt.h"
#include "workerthreadcontroller.h"

#define CELLSIZE 20

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/* Definitions for dll files. */

typedef IPathfinder* (*FUNCPOINTER)();
//#define procname "InitPathfinderObject"

/* Definitions for dll files end. */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private:
    void createMenus();
    void createActions();
    void InitModelView();
    void AddAlgorithmToFile(const QString& string);
    bool ReadAlgorithms(); //Read the algortihm names and paths at the start.
    bool InitAlgorithmListWidget();

    void runsearch();

    void loaddll();//load dll file
private slots:


    void on_myGridView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_myGridView_entered(const QModelIndex &index);

    void on_clearButton_clicked();

    void on_paramWindowDestroyed();
    void addAlgorithm();
    void exit();

    void on_buttonParameters_clicked();

    void on_widgetListAlgorithms_itemSelectionChanged();



    void on_buttonRun_clicked();

private:
    typedef IPathfinder* (*fpointer)(); //define the file pointer
    fpointer fp = nullptr;
    IPathfinder* algorithmObject = nullptr; //The object that will do the search
    ObserverTeszt* gridcontroller = nullptr; //the grid controller
    Mediator mediator;
    DialogParameters dialogparam;
    WorkerThreadController threadController;

    FUNCPOINTER myFunction; //the dll function pointer

    Ui::MainWindow *ui;

    int cellsize;
    bool grabbed = false;
    bool isStartOrTargetSelected = false;


    QStringList slistAlgoNames;
    QStringList slistAlgoDllPaths;

    Point startOrTargetSelectedIndex;
    int startOrTargetSelectedColor;

    QColor previousClickedColor;

    GridModel* myGridModel = nullptr; //Pointer because resizing the grid is solved by creating a new object. Faster than smarter solution.
    QMenu *fileMenu= nullptr;
    QAction *newAlgoAct= nullptr;
    QAction *exitAct= nullptr;
    vector<string> algorithmRunParameters;

};
#endif // MAINWINDOW_H
