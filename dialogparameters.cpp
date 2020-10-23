#include "dialogparameters.h"
#include "ui_dialogparameters.h"
#include "QComboBox"

DialogParameters::DialogParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogParameters)
  ,newParamRowDialog(this)
{
    ui->setupUi(this);
    setModal(false);

}

DialogParameters::~DialogParameters()
{
    delete ui;
}

void DialogParameters::on_buttonAdd_clicked()
{
    newParamRowDialog.setUpParamDialog(ui->tableParameters);
    newParamRowDialog.open();

}


void DialogParameters::on_tableParameters_itemSelectionChanged()
{
    ui->buttonDelete->setEnabled(true);
}

void DialogParameters::on_buttonDelete_clicked()
{
    QModelIndexList selected = ui->tableParameters->selectionModel()->selectedRows();

    //QList<QTableWidgetItem*> selected = ui->tableParameters->selectedItems();
    for(int i = 0;i<selected.count();++i){
        ui->tableParameters->removeRow(selected.at(i).row());
    }

}

void DialogParameters::on_buttonSaveParams_clicked()
{
    //Save into .ini
}
