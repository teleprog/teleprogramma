#include "addprogram.h"
#include "ui_addprogram.h"

addprogram::addprogram(QWidget *parent,struct program *p,int mode) :
    QDialog(parent),
    ui(new Ui::addprogram)
{
    ui->setupUi(this);
    param=p;

    if (p!=NULL)
        initForm();

    if (mode==1)
    {
       ui->lineEdit->setReadOnly(true);
       ui->lineEdit_2->setReadOnly(true);
       ui->lineEdit_3->setReadOnly(true);
       ui->timeEdit->setReadOnly(true);
       ui->plainTextEdit->setReadOnly(true);
       ui->pushButton->setVisible(false);
    }

}
//------------------------------------------------------
addprogram::~addprogram()
{
    delete ui;
}

void addprogram::on_pushButton_2_clicked()
{
    close();
}
//------------------------------------------------------
void addprogram::on_pushButton_clicked()
{
if (param==NULL)
    value.id=-1;


value.name=ui->lineEdit->text();
value.time = ui->timeEdit->time();
value.reklama=ui->lineEdit_2->text().toInt();
value.diktor=ui->lineEdit_3->text();
value.comment=ui->plainTextEdit->document()->toPlainText();

int h = value.time.hour();
int m = value.time.minute();



if ( (h*60+m+5*value.reklama)>22*60)
{
    QMessageBox mb;
     mb.setText("Время программы с учётом рекламных\nблоков не может быть больше > 22 часов!");
     mb.exec();

return;
}


if ( (h*60+m+5*value.reklama)<30)
{
    QMessageBox mb;
     mb.setText("Время программы с учётом рекламных\nблоков должно быть >30минут!");
     mb.exec();

return;
}



emit add(value);

close();
}

//---------------------------------------------------
 void addprogram::initForm()
 {
ui->lineEdit->setText(param->name);
ui->timeEdit->setTime(param->time);
ui->lineEdit_2->setText(QString::number(param->reklama));
ui->lineEdit_3->setText(param->diktor);
ui->plainTextEdit->setPlainText(param->comment);
value.id=param->id;

 }
