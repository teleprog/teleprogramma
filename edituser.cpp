#include "edituser.h"
#include "ui_edituser.h"

edituser::edituser(QWidget *parent,int param,int iduser) :
    QDialog(parent),
    ui(new Ui::edituser)
{
    ui->setupUi(this);

    parametr=param;
       id = iduser;


    QString str ="select role from roles where id_role!=4";

               query.exec(str);

     while (query.next()) {
      ui->comboBox->addItem(query.value(0).toString());
     }



    if (parametr==0)
        this->setWindowTitle("Новый пользователь");
else
initDialog(id);
    }

edituser::~edituser()
{
    delete ui;
}

//-------------------------------------------------------------
void edituser::initDialog(int id)
{

QString str ="select users.FIO,users.login,users.password,roles_map.id_role from \
        users,roles_map where users.id_user="+QString::number(id)+" and roles_map.id_user="+QString::number(id);
     query.exec(str);
  //   query.exec();

query.first();

ui->lineEdit->setText(query.value(0).toString());
ui->lineEdit_2->setText(query.value(1).toString());
ui->lineEdit_3->setText(query.value(2).toString());

int roleid = query.value(3).toInt();
passwordBuffer = query.value(2).toString();


  ui->comboBox->setCurrentIndex(roleid-1);

}

//----------------------------------------------------------------

void edituser::on_pushButton_2_clicked()
{
    close();
}

//-----------------------------------------------------------------

void edituser::on_pushButton_clicked()
{
  if (ui->lineEdit->text().trimmed().length()==0 || ui->lineEdit_2->text().trimmed().length()==0 || ui->lineEdit_3->text().trimmed().length()==0)
  { QMessageBox mb;
      mb.setText("Все поля должны быть заполнены!");
     mb.exec();
  return;}

  QString str;


  if (parametr==0)
  {

   str = "insert into users values(0,\""+ui->lineEdit_2->text()+"\",md5(\""+ \
   ui->lineEdit_3->text()+"\"),\""+ui->lineEdit->text()+"\")";
   if (query.exec(str)==false)
   {
       QMessageBox mb;
             mb.setText("Ошибка создания записи!");
            mb.exec();
   return;
   }
   str="select LAST_INSERT_ID()";
      query.exec(str);
      query.first();
   int aid=query.value(0).toInt();
   str = "insert into roles_map values(+"+QString::number(aid)+","+QString::number(ui->comboBox->currentIndex()+1)+")";
    query.exec(str);

  }

 else

{
 str = "update users set login=\""+ ui->lineEdit_2->text()+"\",fio=\""+ui->lineEdit->text()+"\" ";

if (ui->lineEdit_3->text().compare(passwordBuffer)!=0)
str+=",password=md5(\""+ ui->lineEdit_3->text()+"\") ";

str+="where id_user="+QString::number(id);


if (query.exec(str)==false)
{
    QMessageBox mb;
          mb.setText("Ошибка записи!");
         mb.exec();
return;
}

str = "update roles_map set id_role="+QString::number(ui->comboBox->currentIndex()+1)+" where id_user="+QString::number(id);
if (query.exec(str)==false)
{
    QMessageBox mb;
          mb.setText("Ошибка записи роли пользователя!");
         mb.exec();
return;
}
}

QMessageBox mb;
      mb.setText("Информация сохранена успешно!");
     mb.exec();

     emit closed();
close();
}
