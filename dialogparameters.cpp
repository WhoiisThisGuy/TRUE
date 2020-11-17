#include "dialogparameters.h"
#include "ui_dialogparameters.h"
#include "QComboBox"
#include "QList"
#include "QSpinBox"
#include "QDoubleSpinBox"
#include "QLineEdit"
#include "QFile"

DialogParameters::DialogParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogParameters)
  ,newParamRowDialog(this)

{
    ui->setupUi(this);
    setModal(false);

   // algorithmRunParameters = algorithmParameters;
}

DialogParameters::~DialogParameters()
{
    delete ui;
}

void DialogParameters::loadParamDialogSettings(QString name)
{
    nameOfAlgorithm = name;

    QTableWidgetItem* twi;
    QString sclassname;

    QSettings settings(nameOfAlgorithm+"_dialogsettings.ini",QSettings::IniFormat);

    QStringList keyList = settings.childKeys();

    for(int i = 0;i<keyList.size();++i){
        ui->tableParameters->insertRow(i);

        ui->tableParameters->setCellWidget(i,0,new QLabel(keyList.at(i)));
        sclassname = settings.value(keyList.at(i)).toString();

        if(settings.value(keyList.at(i)).type() == QMetaType::QStringList){

            QComboBox* cb = new QComboBox();
            cb->addItems(settings.value(keyList.at(i)).toStringList());
            ui->tableParameters->setCellWidget(i,1,cb);
        }
        else if(sclassname == "Egész"){
             ui->tableParameters->setCellWidget(i,1,new QSpinBox());
        }
        else if(sclassname == "Valós"){
             ui->tableParameters->setCellWidget(i,1,new QDoubleSpinBox());
        }
        else if(sclassname == "Szöveg"){
            ui->tableParameters->setCellWidget(i,1,new QLineEdit());
        }

        twi= new QTableWidgetItem();
        twi->setText(sclassname);
        ui->tableParameters->setItem(i,2,twi);
    }

    //qDebug("Param dialog settings loaded!");
}

vector<variant<int,double,string>> DialogParameters::CompileParameters()
{

    QTableWidgetItem* wti;
    QSpinBox* spinbox;
    QDoubleSpinBox* dspinbox;
    QLineEdit* lineedit;
    QComboBox* cb;
    string sclassname;

    Parameters.clear();

    int rowcount = ui->tableParameters->rowCount();

    for(int i = 0;i<rowcount;++i){
        wti = ui->tableParameters->item(i,2);
        sclassname = wti->text().toStdString();

        if(sclassname == "Lista"){//if its a list, save out the list values
            cb = (QComboBox*)ui->tableParameters->cellWidget(i,1);
            Parameters.push_back(cb->currentText().toStdString());
        }
        else if(sclassname == "Egész"){
             spinbox = (QSpinBox*)ui->tableParameters->cellWidget(i,1);
             Parameters.push_back(spinbox->value());
        }
        else if(sclassname == "Valós"){
             dspinbox = (QDoubleSpinBox*)ui->tableParameters->cellWidget(i,1);
             Parameters.push_back(dspinbox->value());
        }
        else if(sclassname == "Szöveg"){
            lineedit = (QLineEdit*)ui->tableParameters->cellWidget(i,1);
            Parameters.push_back(lineedit->text().toStdString());
        }
    }

    return Parameters;
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
    QModelIndex selected = ui->tableParameters->selectionModel()->selectedRows().at(0);

    QSettings settings(nameOfAlgorithm+"_dialogsettings.ini",QSettings::IniFormat);
    QString whattoremove = selected.data().toString();
    ui->tableParameters->removeRow(selected.row());
    settings.remove(whattoremove);
}

void DialogParameters::on_buttonSaveParams_clicked()
{
    //Save into .ini
    saveParamDialogSettings();
}

void DialogParameters::saveParamDialogSettings()
{
    QSettings settings(nameOfAlgorithm+"_dialogsettings.ini",QSettings::IniFormat);
    QTableWidgetItem* wit;
    QString sclassname;
    QLabel* label;

    for(int i = 0;i<ui->tableParameters->rowCount();++i){ //Save the label name and the widget type first.

        label = dynamic_cast<QLabel*>(ui->tableParameters->cellWidget(i,0));
        wit = ui->tableParameters->item(i,2);
        sclassname = wit->text();

        if(sclassname == "Lista"){//if its a list, save out the list values

            QComboBox* cb = (QComboBox*)ui->tableParameters->cellWidget(i,1);
            QStringList valuelist;
            for(int j = 0;j<cb->count();++j){
                valuelist.push_back(cb->itemText(j));
            }
            settings.setValue(label->text(), valuelist);
        }
        else{
            settings.setValue(label->text(), sclassname);
        }
    }

    qDebug("Param dialog settings saved!");

}

void DialogParameters::on_DialogParameters_finished(int result)
{
    CompileParameters();
    for(int i = ui->tableParameters->rowCount();i>=0;--i){
        ui->tableParameters->removeRow(i);
    }
    //qDebug("rows removed!");
}
