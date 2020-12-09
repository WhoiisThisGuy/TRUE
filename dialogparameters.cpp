#include "dialogparameters.h"
#include "ui_dialogparameters.h"
#include "QComboBox"
#include "QList"
#include "QSpinBox"
#include "QDoubleSpinBox"
#include "QLineEdit"
#include "QFile"


DialogParameters::DialogParameters(QWidget *parent_) :
    QDialog(parent_),
    ui(new Ui::DialogParameters)
  ,newParamRowDialog(this)

{

    ui->setupUi(this);

    setWindowTitle("Paraméterek");

    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);


    ui->gridLayout->addWidget(bar);
    bar->setContentsMargins(0,0,0,0);

    setModal(false);

}

DialogParameters::~DialogParameters()
{
    delete bar;
    delete ui;
}

void DialogParameters::loadParamDialogSettings(QString name)
{
    ui->tableParameters->setSortingEnabled(false);
    nameOfAlgorithm = name; //Save the name of the actual algorithm

    QTableWidgetItem* twi;
    QString type;

    QSettings settings(nameOfAlgorithm+"ParameterSettings.ini",QSettings::IniFormat);

    int arraySize = settings.beginReadArray(nameOfAlgorithm);
    //QStringList qslgroupList = settings.childGroups();
    //QStringList childkeys = settings.allKeys();

    if(arraySize == 0)
        return;
    for(int i = 0;i<arraySize;++i){
        settings.setArrayIndex(i);
        //settings.beginGroup(qslgroupList.at(i));
        auto a = settings.children();
        settings.beginGroup(settings.childGroups().at(0));
        ui->tableParameters->insertRow(i);

        ui->tableParameters->setCellWidget(i,0,new QLabel(settings.value("label").toString()));
        type = settings.value("type").toString();

        if(type == "Lista"){
            QComboBox* cb = new QComboBox();
            cb->addItems(settings.value("listValues").toStringList());
            cb->setCurrentIndex(settings.value("fieldValue").toInt());
            ui->tableParameters->setCellWidget(i,1,cb);
        }
        else if(type == "Egész"){
             QSpinBox* spinbox = new QSpinBox();
             spinbox->setValue(settings.value("fieldValue").toInt());
             ui->tableParameters->setCellWidget(i,1,spinbox);
        }
        else if(type == "Valós"){
            QDoubleSpinBox* dspinbox = new QDoubleSpinBox();
            dspinbox->setValue(settings.value("fieldValue").toDouble());
            ui->tableParameters->setCellWidget(i,1,dspinbox);
        }
        else if(type == "Szöveg"){
            QLineEdit* lineedit = new QLineEdit();
            lineedit->setText(settings.value("fieldValue").toString());
            ui->tableParameters->setCellWidget(i,1,lineedit);
        }

        twi= new QTableWidgetItem();
        twi->setText(type);
        ui->tableParameters->setItem(i,2,twi);
        settings.endGroup();
    }
    settings.endArray();
    bar->showMessage("Paraméter beállítások betöltve.");

}

vector<string> DialogParameters::CompileParameters()
{
    string sclassname;
    Parameters.clear();

    int rowcount = ui->tableParameters->rowCount();

    for(int i = 0;i<rowcount;++i){
        QTableWidgetItem* wti;
        wti = ui->tableParameters->item(i,2);
        sclassname = wti->text().toStdString();
        if(sclassname == "Lista"){//if its a list, save out the list values
            QComboBox* cb;
            cb = (QComboBox*)ui->tableParameters->cellWidget(i,1);
            Parameters.push_back(cb->currentText().toStdString());
        }
        else if(sclassname == "Egész"){
             QSpinBox* spinbox;
             spinbox = (QSpinBox*)ui->tableParameters->cellWidget(i,1);
             Parameters.push_back(std::to_string(spinbox->value()));
        }
        else if(sclassname == "Valós"){
            QDoubleSpinBox* dspinbox;
             dspinbox = (QDoubleSpinBox*)ui->tableParameters->cellWidget(i,1);
             Parameters.push_back(std::to_string(dspinbox->value()));
        }
        else if(sclassname == "Szöveg"){
            QLineEdit* lineedit;
            lineedit = (QLineEdit*)ui->tableParameters->cellWidget(i,1);
            Parameters.push_back(lineedit->text().toStdString());
        }
    }

    return Parameters;
}

vector<std::string> DialogParameters::getParametersFromFile(QString name)
{
    Parameters.clear();
    QString type;
    string value;

    QSettings settings(name+"ParameterSettings.ini",QSettings::IniFormat);


    int size = settings.beginReadArray(name);

    //QStringList qslgroupList = settings.childGroups();

    for(int i = 0;i<size;++i){
        settings.setArrayIndex(i);
        settings.beginGroup(settings.childGroups().at(0));
        type = settings.value("type").toString();

        if(type == "Lista"){

            QStringList list = settings.value("listValues").toStringList();
            int i = settings.value("fieldValue").toInt();
            value = list.at(i).toStdString();
        }
        else {
            value = settings.value("fieldValue").toString().toStdString();
        }
        Parameters.push_back(value);
        settings.endGroup();
    }
    settings.endArray();

    return Parameters;
}


void DialogParameters::on_buttonAdd_clicked()
{
    newParamRowDialog.setUpParamDialog(ui->tableParameters);
    newParamRowDialog.exec();
    int re = newParamRowDialog.result();
    if(re == 1)
        bar->showMessage("Új paraméter hozzá adva.");
    else
        bar->showMessage("Ablak bezárva.");
}


void DialogParameters::on_tableParameters_itemSelectionChanged()
{
    ui->buttonDelete->setEnabled(true);
}

void DialogParameters::on_buttonDelete_clicked()
{

    QModelIndexList selectedList =  ui->tableParameters->selectionModel()->selectedRows();
    if(selectedList.empty())
        return;
    QModelIndex selected = selectedList.at(0);

    QSettings settings(nameOfAlgorithm+"ParameterSettings.ini",QSettings::IniFormat);
    QString temp;
    ui->tableParameters->removeRow(selected.row());
    settings.clear();
    saveParamDialogSettings();
    bar->showMessage("Paraméter törölve.");

}

void DialogParameters::on_buttonSaveParams_clicked()
{
    //Save into .ini
    saveParamDialogSettings();
    //parent->status
}

void DialogParameters::saveParamDialogSettings()
{
    QSettings settings(nameOfAlgorithm+"ParameterSettings.ini",QSettings::IniFormat);

    /* temp values */
    QTableWidgetItem* wit;
    QString type;
    QVariant value;

    //settings.beginWriteArray(nameOfAlgorithm);
    settings.beginWriteArray(nameOfAlgorithm);

    for(int i = 0;i<ui->tableParameters->rowCount();++i){ //Save the label name and the widget type first.
        settings.setArrayIndex(i);
        QLabel* label;
        label = dynamic_cast<QLabel*>(ui->tableParameters->cellWidget(i,0));
        wit = ui->tableParameters->item(i,2);
        type = wit->text();

        settings.beginGroup(label->text());

        settings.setValue("label", label->text()); //Save the label key

        if(type == "Lista"){//if its a list, save out the list values

            QComboBox* cb = (QComboBox*)ui->tableParameters->cellWidget(i,1);
            QStringList valuelist;
            for(int j = 0;j<cb->count();++j){
                valuelist.push_back(cb->itemText(j));
            }
            settings.setValue("listValues", valuelist); //Save the list values if the widget is a combobox
            value = cb->currentIndex();

        }
        else if(type == "Egész"){
            QSpinBox* spinbox;
             spinbox = (QSpinBox*)ui->tableParameters->cellWidget(i,1);
             value = spinbox->value();
        }
        else if(type == "Valós"){
            QDoubleSpinBox* dspinbox;
             dspinbox = (QDoubleSpinBox*)ui->tableParameters->cellWidget(i,1);
             value = dspinbox->value();
        }
        else if(type == "Szöveg"){
            QLineEdit* lineedit;
            lineedit = (QLineEdit*)ui->tableParameters->cellWidget(i,1);
            value = lineedit->text();
        }
        settings.setValue("fieldValue", value); //Save the list values if the widget is a combobox
        settings.setValue("type", type); //Save the label key
        settings.endGroup();
    }
    settings.endArray();

    bar->showMessage("Paraméter beállítások elmentve.");

}

void DialogParameters::on_DialogParameters_finished(int result)
{
    Parameters = CompileParameters();
    for(int i = ui->tableParameters->rowCount();i>=0;--i){
        ui->tableParameters->removeRow(i);
    }
    bar->showMessage("");
}
