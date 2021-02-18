#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logger.h"
#include "QMouseEvent"
#include "QFileDialog"
#include "gridmodel.h"
#include "dialogparameters.h"
#include "ipathfinder.h"
#include "workerthreadcontroller.h"
#include "dialogresults.h"
#include "QListWidgetItem"

#define CELLSIZE 16

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
    void AddAlgorithmToFile();
    void ReadAlgorithms(); //
    void StartSearch();
    void LoaddllFile(); //Loads the dll file and gets the IPathfinder object

private slots:

    void handleSearchFinish(int result);

    void on_myGridView_clicked(const QModelIndex &index);

    void on_resizeButton_clicked();

    void on_myGridView_entered(const QModelIndex &index);

    void on_clearButton_clicked();

    void on_paramWindowDestroyed();

    void exit();

    void on_buttonParameters_clicked();

    void on_widgetListAlgorithms_itemSelectionChanged();

    void on_buttonRun_clicked();

    void addAlgorithm();

    void on_button_Results_clicked();

    void on_buttonStop_clicked();

    void on_widgetListAlgorithms_itemClicked(QListWidgetItem *item);

    void on_buttonDeleteAlgo_clicked();

    void on_pushButton_clicked();

    bool eventFilter(QObject *object, QEvent *event) override;



    void on_myGridView_pressed(const QModelIndex &index);

private:

    /*Init list start */
    Ui::MainWindow *ui;
    DialogParameters dialogparam;
    WorkerThreadController threadController;
    Gridcontroller gridcontroller; //the grid controller
    Logger log;
    /*Init list end */

    GridModel myGridModel; //contains the grid data

    int cellsize = CELLSIZE;

    fpointer fp = nullptr; //dll function pointer
    QString algoNameToLoad = "";
    //IPathfinder* algorithmObject = nullptr; //The dll algorithm object

    Mediator mediator; //Used in gridcontroller to emit signals for the gridmodel class

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

    dialogResults dialog_results;

    bool mouseLeftClickOnHold; //Event filter and TableView press event changes this
    bool clickedOnWhite; //to tell if click hold started on a white | grey cell

};
#endif // MAINWINDOW_H
