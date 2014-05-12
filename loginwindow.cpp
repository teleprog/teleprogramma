#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);


    //connection();


    ui->username->setStyleSheet("color: rgb(255, 255, 255)");
    ui->password->setStyleSheet("color: rgb(255, 255, 255)");
    ui->checkBox->setStyleSheet("color: rgb(255, 255, 255)");


}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1==(int)Qt::Checked)
    {
    ui->loginEdit->clear();
    ui->loginEdit->setEnabled(false);

    ui->passwdEdit->clear();
    ui->passwdEdit->setEnabled(false);
      }

    if (arg1==(int)Qt::Unchecked)
    {

    ui->loginEdit->setEnabled(true);
    ui->passwdEdit->setEnabled(true);
    ui->loginEdit->setFocus();
      }



}

void LoginWindow::on_enterButton_clicked()
{
    int id_user=0;

    if (ui->checkBox->checkState()==(int)Qt::Checked)
    {
        id_user=0;
    }
    else
    {
    QString login =  ui->loginEdit->text().trimmed();
     QString password =  ui->passwdEdit->text().trimmed();

     if (login.length()==0 || password.length()==0)
     {
        QMessageBox mb;
        mb.setText("Поля имени пользователя и пароля\nдолжны быть заполнены!");
        mb.exec();

      return;
     }
QString str ="SELECT id_user FROM users where login like \""+login+"\" and password like md5(\""+password+"\")";
      query.exec(str);

       if  (query.first()==false)
         {  QMessageBox mb;
           mb.setText("Учётные данные введены неверно!");
           mb.exec();
           ui->passwdEdit->clear();
           ui->passwdEdit->setFocus();
          return; }

    id_user=query.value(0).toInt();
     }

   MainWindow *w = new MainWindow(0,id_user);
   w->show();
   close();

    }



//-------------------------------------------------------------


bool LoginWindow::connection()
{
  // db = new QSqlDatabase;
    *db = QSqlDatabase::addDatabase("QMYSQL");
 /*   db->setHostName("localhost");
    db->setDatabaseName("teleprog");
    db->setUserName("telep");
    db->setPassword("tele308");  //доделать ф-ию шифровки пароля
*/
    db->setHostName(authparam.host);
        db->setDatabaseName(authparam.dbname);
        db->setUserName(authparam.login);
        db->setPassword(authparam.passwd);

    if (!db->open())
    {
        BaseParamDialog *b = new BaseParamDialog();
        b->setModal(true);
        b->show();

        QMessageBox *mes = new QMessageBox;
        mes->setText("Сервер БД сообщает:\n"+db->lastError().text()+"\n\nПроверьте настройки соединения");
        mes->setModal(true);
        mes->show();



        return 0;
    }


    query =  QSqlQuery(*db);

    return 1;

}

//---------------------------------------------------------------

void LoginWindow::checkSettings()
{
    QSettings settings("Teleprogramma", "v01");


             settings.beginGroup("settings");
             authparam.host = settings.value("host", QVariant::String).toString();
             authparam.dbname = settings.value("dbname", QVariant::String).toString();
             authparam.login = settings.value("login", QVariant::String).toString();
             authparam.passwd = settings.value("passwd", QVariant::String).toString();
             settings.endGroup();

              authparam.passwd=code((char*)authparam.passwd.toLatin1().data(), authparam.passwd.length(),(char*)"/_+-=+!-",8);


}

//----------------------------------------------------------------
QString LoginWindow::code(char *in,int szin,char *key,int szkey)
     {
         for(int i = 0,t = 0; i < szin; i++,t++)
         {   in[i] ^= key[t];
             if(t >= szkey) t = 0;
         }
         return in;
     }
//----------------------------------------------------------------

