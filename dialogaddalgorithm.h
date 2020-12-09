#ifndef DIALOGADDALGORITHM_H
#define DIALOGADDALGORITHM_H

#include <QDialog>
#include "QListWidget"
#include "QStatusBar"

#ifndef CFGPATH
#define CFGPATH "SavedAlgorithms.ini"
#endif

namespace Ui {

class DialogAddAlgorithm;

}

class DialogAddAlgorithm : public QDialog
{

    Q_OBJECT

public:

    explicit DialogAddAlgorithm(QWidget *parent = nullptr, QListWidget* algoList_ = nullptr, QStringList* dllPathList_ = nullptr);

    ~DialogAddAlgorithm();

private:

    void saveNewAlgorithm(const QString& algoname, const QString& filename);

private slots:

    void on_addFileButton_clicked();

    void on_addButton_clicked();

    void on_TextNameOfAlgo_textChanged(const QString &arg1);

    void on_cancelButton_clicked();

private:
    Ui::DialogAddAlgorithm *ui;
    QListWidget* algoList;
    QStringList* dllPathList;
    QStatusBar* bar;
};

#endif // DIALOGADDALGORITHM_H
