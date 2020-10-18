#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "QTableView"
#include "gridmodel.h"
#include "QVariant"

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

    void on_myGridView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //QTableView myGridView;
    GridModel myGridModel;
};
#endif // MAINWINDOW_H
