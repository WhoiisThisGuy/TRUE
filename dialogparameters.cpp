#include "dialogparameters.h"
#include "ui_dialogparameters.h"
#include "QComboBox"
#include "QList"
#include "QSpinBox"
#include "QDoubleSpinBox"
#include "QLineEdit"

vector<string> DialogParameters::algorithmRunParameters;

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
//load settings only if algoname_dialogsettings.ini file exists

    QFile file(nameOfAlgorithm+"_dialogsettings.ini");

    if(!file.exists()) return;

    QTableWidgetItem* twi;
    QString sclassname;

    QSettings settings(nameOfAlgorithm+"_dialogsettings.ini",QSettings::IniFormat);

    int size= settings.beginReadArray("rowdata");
    for(int i = 0;i<size;++i){ //Save the label name and the widget class first.
        ui->tableParameters->insertRow(i);
        settings.setArrayIndex(i);
        ui->tableParameters->setCellWidget(i,0,new QLabel(settings.value("label").toString()));

        sclassname = settings.value("datatype").toString(); //type;

        if(sclassname == "Lista"){//if its a list, save out the list values

            QComboBox* cb = new QComboBox();
            cb->addItems(settings.value("listvalues").toStringList());
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
        twi->setText(settings.value("datatype").toString());
        ui->tableParameters->setItem(i,2,twi);
    }
    settings.endArray();
    //qDebug("Param dialog settings loaded!");
}

vector<string> DialogParameters::getParameters()
{
    return algorithmRunParameters;
}

void DialogParameters::setParameters()
{
    algorithmRunParameters.clear();
    //Parameter* param;
    QLabel* label;
    QSpinBox* spinbox;
    QDoubleSpinBox* dspinbox;
    QLineEdit* lineedit;
    QComboBox* cb;
    string sclassname;
    string value;

    QTableWidgetItem* wti;

    int rowcount = ui->tableParameters->rowCount();

    if(rowcount == 0) //find out something for 0 params.
    {
        return;
    }

    for(int i = 0;i<rowcount;++i){


        label = (QLabel*)ui->tableParameters->cellWidget(i,0);

        wti = ui->tableParameters->item(i,2);
        sclassname = wti->text().toStdString();

        if(sclassname == "Lista"){//if its a list, save out the list values

            cb = (QComboBox*)ui->tableParameters->cellWidget(i,1);
            value = cb->currentText().toStdString();
        }
        else if(sclassname == "Egész"){
             spinbox = (QSpinBox*)ui->tableParameters->cellWidget(i,1);
             value = std::to_string(spinbox->value());
        }
        else if(sclassname == "Valós"){
             dspinbox = (QDoubleSpinBox*)ui->tableParameters->cellWidget(i,1);
             value = std::to_string(dspinbox->value());
        }
        else if(sclassname == "Szöveg"){
            lineedit = (QLineEdit*)ui->tableParameters->cellWidget(i,1);
            value = lineedit->text().toStdString();
        }
        algorithmRunParameters.push_back(value);
        //qDebug("Param added value = %s",value.data());

    }

    return;
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
    QSettings settings(nameOfAlgorithm+"_dialogsettings.ini",QSettings::IniFormat);

    settings.beginReadArray("rowdata");
    for(int i = 0;i<selected.count();++i){ //This does not remove correctly, there will be garbage in the ini file.
        settings.setArrayIndex(selected.at(i).row());
        settings.remove("label");
        settings.remove("class");
        settings.remove("listvalues");
        settings.remove("datatype");
        ui->tableParameters->removeRow(selected.at(i).row());
    }
    settings.endArray();
}

void DialogParameters::on_buttonSaveParams_clicked()
{
    //Save into .ini
    saveParamDialogSettings();
}

void DialogParameters::saveParamDialogSettings()
{
    QSettings settings(nameOfAlgorithm+"_dialogsettings.ini",QSettings::IniFormat);
    //save settings only if table has any items
    if(ui->tableParameters->rowCount()==0){
        settings.beginWriteArray("rowdata",0);
        settings.endArray();
        return;
    }
    QTableWidgetItem* wit;
    QString sclassname;
    QLabel* label;
    settings.beginWriteArray("rowdata");
    for(int i = 0;i<ui->tableParameters->rowCount();++i){ //Save the label name and the widget type first.
        settings.setArrayIndex(i);
        label = (QLabel*)ui->tableParameters->cellWidget(i,0);
        settings.setValue("label", label->text()); //save name

        wit = ui->tableParameters->item(i,2);
        sclassname = wit->text();

        settings.setValue("datatype", sclassname); //save class

        if(sclassname == "Lista"){//if its a list, save out the list values

            QComboBox* cb = (QComboBox*)ui->tableParameters->cellWidget(i,1);
            QStringList valuelist;
            for(int j = 0;j<cb->count();++j){
                valuelist.push_back(cb->itemText(j));
            }
            settings.setValue("listvalues",valuelist);
        }
    }
    settings.endArray();
    qDebug("Param dialog settings saved!");

}

void DialogParameters::on_DialogParameters_finished(int result)
{

    for(int i = ui->tableParameters->rowCount();i>=0;--i){ //This does not remove correctly, there will be garbage in the ini file.
        ui->tableParameters->removeRow(i);
    }
    qDebug("rows removed!");
}

void DialogParameters::on_pushButton_clicked()
{
//
}
