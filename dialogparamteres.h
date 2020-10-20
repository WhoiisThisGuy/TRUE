#ifndef DIALOGPARAMTERES_H
#define DIALOGPARAMTERES_H

#include <QDialog>

namespace Ui {
class DialogParamteres;
}

class DialogParamteres : public QDialog
{
    Q_OBJECT

public:
    explicit DialogParamteres(QWidget *parent = nullptr);
    ~DialogParamteres();

private:
    Ui::DialogParamteres *ui;
};

#endif // DIALOGPARAMTERES_H
