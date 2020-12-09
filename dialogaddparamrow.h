#ifndef DIALOGADDPARAMROW_H
#define DIALOGADDPARAMROW_H

#include <QDialog>
#include "QTableWidget"

namespace Ui {

class DialogAddParamRow;

}

class DialogAddParamRow : public QDialog
{
    Q_OBJECT

public:

    explicit DialogAddParamRow(QWidget *parent = nullptr);

    ~DialogAddParamRow();

    void setUpParamDialog(QTableWidget*);

private slots:

    void on_buttonSave_clicked();

    void on_buttonAddNewValue_clicked();

    void on_comboBoxParamType_currentIndexChanged(int index);

    void on_lineParamName_textChanged(const QString &arg1);

    void on_buttonCancel_clicked();

    void on_DialogAddParamRow_finished(int result);

private:

    void insertNewParameter();

private:

    Ui::DialogAddParamRow *ui;

    QTableWidget* paramTable; //holds dialogparam table
};

#endif // DIALOGADDPARAMROW_H
