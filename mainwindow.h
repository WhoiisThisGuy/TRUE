#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gridmodel.h"
#include "QVariant"
#include "QMouseEvent"
#include "QPainter"
#include "QFileDialog"
#include "dialogparameters.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;
    int cellsize;
    bool grabbed = false;
    bool isStartOrTargetSelected = false;

    DialogParameters dialogparam;

    QStringList slistAlgoNames;
    QStringList slistAlgoDllPaths;

    QModelIndex startOrTargetSelectedIndex;
    QColor startOrTargetSelectedColor;

    QColor previousClickedColor;

    GridModel* myGridModel = nullptr; //Pointer because resizing the grid is solved by creating a new object. Faster than smarter solution.
    QMenu *fileMenu;
    QAction *newAlgoAct;
    QAction *exitAct;
};
#endif // MAINWINDOW_H
