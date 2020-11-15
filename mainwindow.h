#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QVariant"
#include "QMouseEvent"
#include "QFileDialog"

#include "gridmodel.h"
#include "dialogparameters.h"
#include "ipathfinder.h"
#include "gridcontroller.h"
#include "workerthreadcontroller.h"

#define CELLSIZE 13

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/* Definitions for dll files. */

typedef IPathfinder* (*fpointer)();
#define procname "InitPathfinderObject"

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

    void CreateMenus();
    void CreateActions();
    void InitModelView();
    void AddAlgorithmToFile(const QString& string);
    void ReadAlgorithms(); //
    void StartSearch();
    void LoaddllFile(); //Loads the dll file and gets the IPathfinder object

private slots:


    void on_myGridView_clicked(const QModelIndex &index);

    void on_resizeButton_clicked();

    void on_myGridView_entered(const QModelIndex &index);

    void on_clearButton_clicked();

    void on_paramWindowDestroyed();

    void exit();

    void on_buttonParameters_clicked();

    void on_widgetListAlgorithms_itemSelectionChanged();

    void on_buttonRun_clicked();

    void on_pushButton_2_clicked();

    void addAlgorithm();

private:

    /*Init list start */
    Ui::MainWindow *ui;
    DialogParameters dialogparam;
    WorkerThreadController threadController;
    /*Init list end */

    GridModel myGridModel; //contains the grid data

    int cellsize = CELLSIZE;

    fpointer fp = nullptr; //dll function pointer
    IPathfinder* algorithmObject = nullptr; //The dll algorithm object
    Gridcontroller* gridcontroller = nullptr; //the grid controller
    Mediator mediator;

    QStringList slistAlgoNames;
    QStringList slistAlgoDllPaths;

    /* For moving start and end points with cursor */
    Point startOrTargetSelectedIndex;
    int startOrTargetSelectedColor;
    QColor previousClickedColor;
    bool isStartOrTargetSelected = false;

    QMenu *fileMenu= nullptr;
    QAction *newAlgoAct= nullptr;
    QAction *exitAct= nullptr;
    vector<string> algorithmRunParameters;

};
#endif // MAINWINDOW_H
