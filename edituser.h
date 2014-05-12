#ifndef EDITUSER_H
#define EDITUSER_H

#include "mytypes.h"

namespace Ui {
class edituser;
}

class edituser : public QDialog
{
    Q_OBJECT

public:
    explicit edituser(QWidget *parent = 0,int param=0,int iduser=0);
    ~edituser();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
void closed();

private:
    Ui::edituser *ui;
 int parametr;
 int id;
 QString passwordBuffer;
void initDialog(int);


};

#endif // EDITUSER_H
