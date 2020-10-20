#include "dialogaddalgorithm.h"
#include "ui_dialogaddalgorithm.h"
#include "QFileDialog"
#include "QTextStream"
#include "QDebug"

DialogAddAlgorithm::DialogAddAlgorithm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddAlgorithm)
{
    ui->setupUi(this);
    ui->addButton->setEnabled(false);
}

DialogAddAlgorithm::~DialogAddAlgorithm()
{
    delete ui;
}

bool DialogAddAlgorithm::writeDataConfigFile(const QString &algoname, const QString &filename)
{
    QFile file(CFGPATH);
    bool fileopened = false;
    if(file.exists()){
    //if file exists check if the algoname is already in the text

        if (file.open(QIODevice::ReadOnly))
        {

            fileopened = true;
            QTextStream in(&file);
            QStringList strings;
            while (!in.atEnd()) {
                strings+=in.readLine().split('=');
                if(strings[0] == algoname){
                    qDebug("Algo name already exists.");
                    file.close();
                    fileopened =false;
                    return false;  //you cant have the same name
                }
                strings.clear();
            }

        }
        else{
            qDebug("Could not open file for reading.");
        }
    }

    QString data;
    data.push_back(algoname);
    data.append("=");
    data.append(filename);
    data.append('\n');

    if(fileopened){
       file.close();
       fileopened = false;
    }


    if(file.open(QIODevice::WriteOnly | QIODevice::Append)) {
         //write stuff
        fileopened = true;
        file.write(data.toUtf8());
      }
     else{
        fileopened = false;//error happened
        file.close();
        return false;
     }
     file.close();
     fileopened = false;
     return true;
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
    writeDataConfigFile(ui->TextNameOfAlgo->text(),ui->TextFileName->text());
}

void DialogAddAlgorithm::on_TextNameOfAlgo_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->TextFileName->text() == "")
        ui->addButton->setEnabled(false);
    else
        ui->addButton->setEnabled(true);
}
