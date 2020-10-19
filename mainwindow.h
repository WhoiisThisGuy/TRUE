#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "QTableView"
#include "gridmodel.h"
#include "QVariant"
#include "QMouseEvent"
#include "QPainter"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_myGridView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void InitModelView();

    void on_myGridView_entered(const QModelIndex &index);

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    int cellsize;
    bool grabbed = false;
    bool isStartOrTargetSelected = false;

    QModelIndex startOrTargetSelectedIndex;
    QColor startOrTargetSelectedColor;

    QColor previousClickedColor;

    GridModel* myGridModel = nullptr; //Pointer because resizing the grid is solved by creating a new object. Faster than smarter solution.

};
#endif // MAINWINDOW_H
