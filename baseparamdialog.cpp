#include "baseparamdialog.h"
#include "ui_baseparamdialog.h"

BaseParamDialog::BaseParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseParamDialog)
{
    ui->setupUi(this);

    QSettings settings("Teleprogramma", "v01");

             settings.beginGroup("settings");
             ui->lineEdit->setText(settings.value("host", QVariant::String).toString());
             ui->lineEdit_4->setText(settings.value("dbname", QVariant::String).toString());
             ui->lineEdit_2->setText(settings.value("login", QVariant::String).toString());
             QString str = settings.value("passwd", QVariant::String).toString();
             settings.endGroup();

             str=code((char*)str.toLatin1().data(),str.length(),(char*)"/_+-=+!-",8);
             ui->lineEdit_3->setText(str);

}

BaseParamDialog::~BaseParamDialog()
{
    delete ui;
}

void BaseParamDialog::on_pushButton_2_clicked()
{
    close();
}

void BaseParamDialog::on_pushButton_clicked()
{
    QString str= code((char*)ui->lineEdit_3->text().toLatin1().data(),ui->lineEdit_3->text().length(),(char*)"/_+-=+!-",8);

       QSettings settings("Teleprogramma", "v01");

            settings.beginGroup("settings");
            settings.setValue("host", ui->lineEdit->text());
            settings.setValue("dbname", ui->lineEdit_4->text());
            settings.setValue("login",ui->lineEdit_2->text());
            settings.setValue("passwd", str);
            settings.endGroup();

            QMessageBox *mb = new QMessageBox(QMessageBox::Information,tr("Сообщение"),"");
            mb->setText(tr("Параметры подключения сохранены успешно!\nПерезапустите программу!"));
            mb->exec();


           emit changed();

            close();





}

//-----------------------------------------------------------------------------
QString BaseParamDialog::code(char *in,int szin,char *key,int szkey)
{//Код шифрующей функции


    for(int i = 0,t = 0; i < szin; i++,t++)
    {
                in[i] ^= key[t];

        if(t >= szkey) t = 0;
    }
    return in;
}
//------------------------------------------------------------------------------
