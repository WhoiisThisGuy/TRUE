#ifndef DIALOGPARAMETERS_H
#define DIALOGPARAMETERS_H

#include <QDialog>
#include "QGridLayout"
#include "QLabel"
#include "dialogaddparamrow.h"
#include "QSettings"
#include <vector>
#include <string>

using std::vector;
using std::string;

struct Parameter{

public:
    string name;
    string value;
public:
    Parameter(){ }
    ~Parameter(){qDebug("Parameter destructed.");}


};

namespace Ui {
class DialogParameters;
}

class DialogParameters : public QDialog
{
    Q_OBJECT

public:
    explicit DialogParameters(QWidget *parent = nullptr);
    ~DialogParameters();
    void loadParamDialogSettings(QString name);
    void setParameters();
    static vector<string> getParameters(); //not needed if the variable is public anyway
public:
    static vector<string> algorithmRunParameters;
private slots:
    void on_buttonAdd_clicked();

    void on_tableParameters_itemSelectionChanged();

    void on_buttonDelete_clicked();

    void on_buttonSaveParams_clicked();

    void on_DialogParameters_finished(int result);

    void on_pushButton_clicked();

private:
    void saveParamDialogSettings();

private:


    QString nameOfAlgorithm;

    Ui::DialogParameters *ui;

    DialogAddParamRow newParamRowDialog;


};

#endif // DIALOGPARAMETERS_H
