#ifndef DIALOGPARAMETERS_H
#define DIALOGPARAMETERS_H

#include <QDialog>
#include "QGridLayout"
#include "QLabel"
#include "dialogaddparamrow.h"

namespace Ui {
class DialogParameters;
}

class DialogParameters : public QDialog
{
    Q_OBJECT

public:
    explicit DialogParameters(QWidget *parent = nullptr);
    ~DialogParameters();

private slots:
    void on_buttonAdd_clicked();

    void on_tableParameters_itemSelectionChanged();

    void on_buttonDelete_clicked();

    void on_buttonSaveParams_clicked();

private:
    Ui::DialogParameters *ui;

    DialogAddParamRow newParamRowDialog;

};

#endif // DIALOGPARAMETERS_H
