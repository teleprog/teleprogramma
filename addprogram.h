#ifndef ADDPROGRAM_H
#define ADDPROGRAM_H

#include "mytypes.h"


namespace Ui {
class addprogram;
}

class addprogram : public QDialog
{
   Q_OBJECT

private:
    Ui::addprogram *ui;
    program* param;


    program value;

 void initForm();

signals:
void add(program);


public:
    explicit addprogram(QWidget *parent = 0,struct program *p=NULL,int mode=0);
    ~addprogram();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


};

#endif // ADDPROGRAM_H
