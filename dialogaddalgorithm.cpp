#include "dialogaddalgorithm.h"
#include "ui_dialogaddalgorithm.h"
#include "QFileDialog"
#include "QTextStream"
#include "QDebug"
#include "QSettings"

DialogAddAlgorithm::DialogAddAlgorithm(QWidget *parent,QListWidget* algoList_,QStringList* dllPathList_) :
    QDialog(parent),
    ui(new Ui::DialogAddAlgorithm)
{
    ui->setupUi(this);
    ui->addButton->setEnabled(false);
    algoList = algoList_;
    dllPathList = dllPathList_;

    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    ui->gridLayout->addWidget(bar);
    ui->gridLayout->setContentsMargins(0,0,0,0);
    bar->showMessage(tr("Új algoritmus felvétele."));

}

DialogAddAlgorithm::~DialogAddAlgorithm()
{
    delete bar;
    delete ui;
}

void DialogAddAlgorithm::saveNewAlgorithm(const QString &algoName, const QString &filePath)
{
   QSettings settings("SavedAlgorithms.ini",QSettings::IniFormat);

   //save settings only if table has any items
   if(settings.contains(algoName)){
    bar->showMessage(tr("A név már használatban van."));
    return;
   }

   settings.setValue(algoName, filePath);

   algoList->addItem(algoName);
   dllPathList->push_back(filePath);

   bar->showMessage(tr("Új algoritmus felvéve."));

}


void DialogAddAlgorithm::on_addFileButton_clicked()
{
        QString fileName = QFileDialog::getOpenFileName(this,
        tr("Algoritmus hozzáadása"), "",
        tr("Address Book (*.dll)"));
        if (fileName.isEmpty())
                return;
        ui->TextFileName->setText(fileName);

        if(ui->TextNameOfAlgo->text() != ""){
            ui->addButton->setEnabled(true);
        }else{
            ui->addButton->setEnabled(false);
        }
}

void DialogAddAlgorithm::on_addButton_clicked()
{
    saveNewAlgorithm(ui->TextNameOfAlgo->text(),ui->TextFileName->text());

}

void DialogAddAlgorithm::on_TextNameOfAlgo_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->TextFileName->text() == "")
        ui->addButton->setEnabled(false);
    else
        ui->addButton->setEnabled(true);
}

void DialogAddAlgorithm::on_cancelButton_clicked()
{
    close();
}
