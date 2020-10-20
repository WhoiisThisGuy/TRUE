#ifndef DIALOGADDALGORITHM_H
#define DIALOGADDALGORITHM_H

#include <QDialog>

#ifndef CFGPATH
#define CFGPATH "config.cfg"
#endif

namespace Ui {
class DialogAddAlgorithm;
}

class DialogAddAlgorithm : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddAlgorithm(QWidget *parent = nullptr);
    ~DialogAddAlgorithm();

private:
    bool writeDataConfigFile(const QString& algoname, const QString& filename);
//        inline bool fileExists (const std::string& name) {
//            ifstream f(name.c_str());
//            return f.good();
//        }

private slots:

    void on_addFileButton_clicked();

    void on_addButton_clicked();

    void on_TextNameOfAlgo_textChanged(const QString &arg1);

private:
    Ui::DialogAddAlgorithm *ui;
};

#endif // DIALOGADDALGORITHM_H
