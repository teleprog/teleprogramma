#ifndef BASEPARAMDIALOG_H
#define BASEPARAMDIALOG_H

#include <QDialog>
#include "mytypes.h"

namespace Ui {
class BaseParamDialog;
}

class BaseParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseParamDialog(QWidget *parent = 0);
    ~BaseParamDialog();

signals:
void changed();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::BaseParamDialog *ui;
  QString  code(char *in,int szin,char *key,int szkey);
};

#endif // BASEPARAMDIALOG_H
