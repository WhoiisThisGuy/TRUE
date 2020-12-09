#ifndef DIALOGPARAMETERS_H
#define DIALOGPARAMETERS_H

#include <QDialog>
#include "QGridLayout"
#include "QLabel"
#include "dialogaddparamrow.h"
#include "QSettings"
#include <vector>
#include <string>
#include "QStatusBar"

using std::vector;
using std::string;
using std::variant;

namespace Ui {
class DialogParameters;
}

class DialogParameters : public QDialog
{
    Q_OBJECT

public:
    explicit DialogParameters(QWidget *parent_ = nullptr);
    ~DialogParameters();
    void loadParamDialogSettings(QString name);
    vector<string> CompileParameters();
    vector<string> getParametersFromFile(QString name);


public:
    vector<string> Parameters;
private slots:
    void on_buttonAdd_clicked();

    void on_tableParameters_itemSelectionChanged();

    void on_buttonDelete_clicked();

    void on_buttonSaveParams_clicked();

    void on_DialogParameters_finished(int result);



private:
    void saveParamDialogSettings();

private:

    QStatusBar* bar;
    QString nameOfAlgorithm;

    Ui::DialogParameters *ui;

    DialogAddParamRow newParamRowDialog;


};

#endif // DIALOGPARAMETERS_H
