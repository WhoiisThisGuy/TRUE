#include "dialogaddparamrow.h"
#include "ui_dialogaddparamrow.h"
#include "QLabel"
#include "QSpinBox"

DialogAddParamRow::DialogAddParamRow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddParamRow)
{

    ui->setupUi(this);

}

DialogAddParamRow::~DialogAddParamRow()
{
    delete ui;
}

void DialogAddParamRow::setUpParamDialog(QTableWidget * table)
{
    paramTable = table;

}

void DialogAddParamRow::on_buttonSave_clicked()
{
    insertNewParameter();
    close();
}

void DialogAddParamRow::insertNewParameter()
{
    int rowindexToInsert = paramTable->rowCount();
    paramTable->insertRow(rowindexToInsert);
    paramTable->setCellWidget(rowindexToInsert,0,new QLabel(ui->lineParamName->text()));//Insert name

    QString selectedType = ui->comboBoxParamType->currentText();

    if(selectedType == "Egész"){
        paramTable->setCellWidget(rowindexToInsert,1,new QSpinBox());
    }
    else if(selectedType == "Valós"){
        paramTable->setCellWidget(rowindexToInsert,1,new QDoubleSpinBox());
    }
    else if(selectedType == "Lista"){
        QComboBox* cbox = new QComboBox();
        QStringList items;

        for(int i = 0;i<ui->comboBoxListValues->count();++i){ //Get list values
                items.push_back(ui->comboBoxListValues->itemText(i));
        }
        cbox->addItems(items);
        paramTable->setCellWidget(rowindexToInsert,1,cbox);
    }

}

void DialogAddParamRow::on_buttonAddNewValue_clicked()
{
    ui->comboBoxListValues->addItem(ui->lineSingleListValue->text());
    ui->lineSingleListValue->clear();
}

void DialogAddParamRow::on_comboBoxParamType_currentIndexChanged(int index)
{
    if(index == 2){
        ui->buttonAddNewValue->setEnabled(true);
        ui->comboBoxListValues->setEnabled(true);
        ui->lineSingleListValue->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->label_4->setEnabled(true);
        ui->groupBox->setEnabled(true);
    }
    else{
        ui->buttonAddNewValue->setEnabled(false);
        ui->comboBoxListValues->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->groupBox->setEnabled(false);
        ui->lineSingleListValue->setEnabled(false);
    }
}

void DialogAddParamRow::on_lineParamName_textChanged(const QString &arg1)
{
    if(arg1 == ""){
        ui->buttonSave->setEnabled(false);
    }
    else{
        ui->buttonSave->setEnabled(true);
    }
}

void DialogAddParamRow::on_buttonCancel_clicked()
{
    close();
}