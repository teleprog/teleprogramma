#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,int id_user) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userid=id_user;
    roleid=4;
    currow=0;
    if (userid!=0) {
    QString str ="SELECT id_role FROM roles_map where id_user ="+QString::number(userid);
         QSqlQuery query(str);
         query.first();

        roleid=query.value(0).toInt();

    initmenu();}


    browseProgram(0);

    initsbar();


}
//-------------------------------------------------

MainWindow::~MainWindow()
{
    db->close();
    delete ui;
}
//-----------------------------------------------
void MainWindow::initsbar()
{
    QString str ="SELECT users.fio,roles.role from users,roles,roles_map where roles_map.id_user=roles_map.id_role and users.id_user="+QString::number(userid);
       query.exec(str);
         query.first();

l = new QLabel();

if (roleid!=4)
l->setText("Вы вошли как: <b>"+query.value(0).toString()+"</b> Роль: <b>"+query.value(1).toString()+"</b>");
else
l->setText("Вы вошли как: <b>Неавторизованный пользователь</b>");
ui->statusBar->addWidget(l);
}

//-----------------------------------------------
QWidget* MainWindow::createWidget()
 {
  QWidget *s = new QWidget(this);
  s->resize(570,460);
  s->move(120,10);

 return s;
 }

 //-----------------------------------------------
  void MainWindow::browseProgram(int param)
  {

      if (param==1)
      {w->hide();
      delete w;}


 w = createWidget();
e = new efirmap();

QTableWidget *t = new QTableWidget(w);
tw=t;

t->setColumnCount(4);
t->setColumnHidden(0,true);
 t->horizontalHeader()->resizeSection(1,70);
   t->verticalHeader()->setDefaultSectionSize(20);

if (roleid==4 || roleid==3) //если простой пользователь (авт или неавт)
{

w->move(0,0);
w->resize(700,500);
t->resize(680,450);
t->move(10,10);
 t->horizontalHeader()->resizeSection(2,400);
 t->horizontalHeader()->resizeSection(3,190);

}
else
{
t->resize(570,450);
t->move(0,10);
   t->horizontalHeader()->resizeSection(2,300);
      t->horizontalHeader()->resizeSection(3,170);
}

if (roleid!=4)
{
    currow=0;
   conmenu=new QMenu();

   t->setContextMenuPolicy(Qt::CustomContextMenu);
   connect(t, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showusermenu(const QPoint &)));



}




    t->setHorizontalHeaderItem(1,new QTableWidgetItem("Время"));
  t->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("Программа")));
  t->setHorizontalHeaderItem(3,new QTableWidgetItem(tr("Ведущий")));


  w->show();
 reinit();

  }


  //------------------------------------------------
 void MainWindow::initmenu()
{
if (roleid==3)
    return;

QPushButton *b = new QPushButton(this);
b->resize(100,50);
b->move(10,50);
b->setText("Просмотр");
connect(b, SIGNAL(clicked()),this, SLOT(browseClicked()));

QPushButton *b1 = new QPushButton(this);
b1->resize(100,50);
b1->move(10,130);
b1->setText("Редактор");
connect(b1, SIGNAL(clicked()),this, SLOT(editClicked()));

if (roleid==1) {
QPushButton *b2 = new QPushButton(this);
b2->resize(100,50);
b2->move(10,210);
b2->setText("Управление\nпользователями");
connect(b2, SIGNAL(clicked()),this, SLOT(adminClicked()));

QPushButton *b3 = new QPushButton(this);
b3->resize(100,50);
b3->move(10,290);
b3->setText("Настройки\nсоденинения");
connect(b3, SIGNAL(clicked()),this, SLOT(settingsClicked()));


}

}
//---------------------------------------------------------
  void MainWindow::settingsClicked()
 {
      BaseParamDialog *b = new BaseParamDialog(this);
      b->setModal(true);
connect(b,SIGNAL(changed()),this,SLOT(close()));

      b->show();

  }

 //----------------------------------------------------
 void MainWindow::browseClicked()
 {
  browseProgram(1);
 }
//------------------------------------------------------
  void MainWindow::editClicked()
  {
editEfir();

  }
 //------------------------------------------------------
   void MainWindow::adminClicked()
   {


alterUsers();


   }
   //-----------------------------------------------------------

void MainWindow::alterUsers()
{
    w->hide();
    delete w;


w = createWidget();

QTableWidget *t = new QTableWidget(w);
tw=t;
t->resize(570,460);
t->setColumnCount(3);

t->setColumnHidden(0,true);

 t->horizontalHeader()->resizeSection(1,300);
  t->horizontalHeader()->resizeSection(2,250);
 t->verticalHeader()->setDefaultSectionSize(20);
   t->setHorizontalHeaderItem(1,new QTableWidgetItem("Пользователь"));
 t->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("Роль")));


currow=0;
 conmenu=new QMenu();

 t->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(t, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showconmenu(const QPoint &)));


 QString str ="select users.id_user,users.FIO,roles.role from users,roles,roles_map where roles_map.id_role=roles.id_role and roles_map.id_user=users.id_user";

      query.exec(str);

   QTableWidgetItem *tw_item;

      int i=0;
      t->insertRow(i);

      while (query.next()) {

          tw_item = new QTableWidgetItem();
          tw_item->setText(query.value(0).toString());
          tw_item->setFlags(Qt::ItemIsEnabled);
          t->setItem(i,0,tw_item);

          tw_item = new QTableWidgetItem();
          tw_item->setText(query.value(1).toString());
          tw_item->setFlags(Qt::ItemIsEnabled);
          t->setItem(i,1,tw_item);

          tw_item = new QTableWidgetItem();
          tw_item->setText(query.value(2).toString());
          tw_item->setFlags(Qt::ItemIsEnabled);
          t->setItem(i,2,tw_item);


          i++;
          t->insertRow(i);
   }
t->removeRow(i);



w->show();

}

//------------------------------------------------------------

void MainWindow::showconmenu(const QPoint &pos)

    {

 if (tw->itemAt(pos)==0)
  { conmenu->clear();
     conmenu->addAction("Добавить новую запись",this,SLOT(newuserrecord()));
}
 else
   {
     tw->item(currow,1)->setBackgroundColor(QColor(255,255,255));
    tw->item(currow,2)->setBackgroundColor(QColor(255,255,255));

currow = tw->itemAt(pos)->row();

tw->item(currow,1)->setBackgroundColor(QColor(201,225,251));
tw->item(currow,2)->setBackgroundColor(QColor(201,225,251));
conmenu->clear();
conmenu->addAction("Редактировать запись",this,SLOT(edituserrecord()));
conmenu->addAction("Удалить запись",this,SLOT(deleteuserrecord()));
conmenu->addSeparator();
conmenu->addAction("Добавить новую запись",this,SLOT(newuserrecord()));

 }


    conmenu->exec(tw->mapToGlobal(pos));
    }
//-------------------------------------------------------------
void MainWindow::edituserrecord()
{
edituser *eu = new edituser(0,1,tw->item(tw->currentRow(),0)->text().toInt());
eu->setModal(true);
eu->show();
connect(eu,SIGNAL(closed()),this,SLOT(adminClicked()));


}
//--------------------------------------------------------------
void MainWindow::deleteuserrecord()
{
    QString str ="delete from users where id_user="+tw->item(tw->currentRow(),0)->text();
         QSqlQuery query(str);
        if (query.exec()==false)
          {  QMessageBox mb;
                  mb.setText("Ошибка удаления записи!");
                 mb.exec();
        }
       else
           { QMessageBox mb;
                  mb.setText("Запись удалена успешно!");
                 mb.exec();
           adminClicked();
        }


}
//--------------------------------------------------------------
void MainWindow::newuserrecord()
{
    edituser *eu = new edituser(0,0);
    eu->setModal(true);
    eu->show();
connect(eu,SIGNAL(closed()),this,SLOT(adminClicked()));

}
//---------------------------------------------------------------
void MainWindow::editEfir()
{
    w->hide();
    delete w;

w = createWidget();
connect(w,SIGNAL(destroyed()),this,SLOT(saveefir()));

pblock = new programblock();

QLabel *i1 = new QLabel(w);
i1->setText("Список телепрограмм:");

listprog = new QComboBox(w);
listprog->move(0,20);
listprog->resize(400,25);

QPushButton *badd = new QPushButton(w);
badd->move(410,20);
badd->resize(60,25);
badd->setText("Добавить");
connect (badd,SIGNAL(clicked()),this,SLOT(addProgram()));

QPushButton *bdel = new QPushButton(w);
bdel->move(480,20);
bdel->resize(60,25);
bdel->setText("Удалить");
connect (bdel,SIGNAL(clicked()),this,SLOT(removeProgram()));

QPushButton *bedit = new QPushButton(w);
bedit->move(0,50);
bedit->resize(100,25);
bedit->setText("Редактировать");
connect (bedit,SIGNAL(clicked()),this,SLOT(editProgram()));

QPushButton *befir = new QPushButton(w);
befir->move(120,50);
befir->resize(130,25);
befir->setText("Отправить в эфир");
connect (befir,SIGNAL(clicked()),this,SLOT(toefir()));
e = new efirmap();


listprog->addItems(pblock->getProgramNames());

QLabel *i2 = new QLabel(w);
i2->move(0,85);
i2->setText("Программы в эфире:");

QTableWidget *t = new QTableWidget(w);
tw=t;
t->resize(570,360);
t->move(0,100);
t->setColumnCount(4);

t->setColumnHidden(0,true);

 t->horizontalHeader()->resizeSection(1,70);
  t->horizontalHeader()->resizeSection(2,300);
 t->verticalHeader()->setDefaultSectionSize(20);
   t->setHorizontalHeaderItem(1,new QTableWidgetItem("Время"));
 t->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("Программа")));
 t->setHorizontalHeaderItem(3,new QTableWidgetItem(tr("Ведущий")));

  currow=0;
 conmenu=new QMenu();

 t->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(t, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showefirmenu(const QPoint &)));

 w->show();
reinit();

}

//----------------------------------------------------------
void MainWindow::addProgram()
{
    addprogram *p = new addprogram(0,NULL);
    p->setModal(true);
   connect(p,SIGNAL(add(program)),this,SLOT(add(program)));
    p->show();

//pblock->addnewprogram(0);

}

//------------------------------------------------------------
void MainWindow::add(program p)
{

 if (p.id==-1)
   {
    QString str ="insert into programs values(0,\""+p.time.toString("hh:mm")+"\","+QString::number(p.reklama) + \
            ",\""+p.name+"\",\""+p.comment+"\",\""+p.diktor+"\")";

              if (query.exec(str)==false)
           {
                  QMessageBox mb;
                   mb.setText("Ошибка добавления программы!");
                   mb.exec();
         }
              else {
                  QMessageBox mb;
                   mb.setText("Программа добавлена!");
                   mb.exec(); }
}
 else
 {
  QString str ="update programs set lentime=\""+p.time.toString("hh:mm")+"\",reklama="+QString::number(p.reklama) + \
          ",name=\""+p.name+"\",comment=\""+p.comment+"\",diktor=\""+p.diktor+"\" where program_id="+QString::number(p.id);

            if (query.exec(str)==false)
         {
                QMessageBox mb;
                 mb.setText("Ошибка обновления программы!");
                 mb.exec();
       }
            else {
                QMessageBox mb;
                 mb.setText("Программа обновлена успешно!\nОбновите эфирную сетку");
                 mb.exec();
                 tw->clearContents();
                 tw->setRowCount(0);
            }

 }


 listprog->clear();
    listprog->addItems(pblock->getProgramNames());
}

//------------------------------------------------------------------------------------
void MainWindow::removeProgram()
{
int id =  pblock->getCurrentRecordId(listprog->currentIndex());
if (id==-1)
{
    QMessageBox mb;
     mb.setText("Ошибка удаления программы. Индекс не найден!");
      mb.exec();
 return;
}
QString str ="delete from programs where program_id="+QString::number(id);


          if (query.exec(str)==false)
       {
              QMessageBox mb;
               mb.setText("Ошибка удаления!");
               mb.exec();
     }
          else {
              QMessageBox mb;
               mb.setText("Программа удалена успешно!");
               mb.exec(); }

          listprog->clear();
             listprog->addItems(pblock->getProgramNames());

             e->clearefir();
             reinit();
}

//----------------------------------------------------------------------------------
void MainWindow::editProgram()
{
    addprogram *p = new addprogram(0,pblock->getRecord(listprog->currentIndex()));
    p->setModal(true);
   connect(p,SIGNAL(add(program)),this,SLOT(add(program)));
    p->show();

}

//--------------------------------------------------------------------------------
void MainWindow::toefir()
{

    program pb = *(pblock->getRecord(listprog->currentIndex()));

    QTime timebuff = e->currTime();

    if (e->addProgram(pb))
    {
       int rowcount = tw->rowCount();
        tw->insertRow(rowcount);

        QTableWidgetItem *tw_item;

            tw_item = new QTableWidgetItem();
            tw_item->setText(QString::number(pb.id));
            tw_item->setFlags(Qt::ItemIsEnabled);
            tw->setItem(rowcount,0,tw_item);


            tw_item = new QTableWidgetItem();
            tw_item->setText(timebuff.toString("hh:mm"));
            tw_item->setFlags(Qt::ItemIsEnabled);
            tw->setItem(rowcount,1,tw_item);

            tw_item = new QTableWidgetItem();
            tw_item->setText(pb.name);
            tw_item->setFlags(Qt::ItemIsEnabled);
            tw->setItem(rowcount,2,tw_item);

            tw_item = new QTableWidgetItem();
            tw_item->setText(pb.diktor);
            tw_item->setFlags(Qt::ItemIsEnabled);
            tw->setItem(rowcount,3,tw_item);
    }

    tw->scrollToBottom();


    return;



}

//--------------------------------------------------------------------------------------
void MainWindow::showefirmenu(const QPoint &pos)

    {

 if (tw->itemAt(pos)==0)
  { conmenu->clear();
     return;
    // conmenu->addAction("Добавить новую запись",this,SLOT(newuserrecord()));
}
 else
   {
     tw->item(currow,1)->setBackgroundColor(QColor(255,255,255));
    tw->item(currow,2)->setBackgroundColor(QColor(255,255,255));
tw->item(currow,3)->setBackgroundColor(QColor(255,255,255));

currow = tw->itemAt(pos)->row();

tw->item(currow,1)->setBackgroundColor(QColor(201,225,251));
tw->item(currow,2)->setBackgroundColor(QColor(201,225,251));
tw->item(currow,3)->setBackgroundColor(QColor(201,225,251));

conmenu->clear();
QMenu *s = new QMenu("Переместить запись",conmenu);
s->addAction("На позицию вверх по времени",this,SLOT(moveProgramUpFromEfir()));
s->addAction("На позицию вниз по времени",this,SLOT(moveProgramDownFromEfir()));
conmenu->addMenu(s);
conmenu->addSeparator();
conmenu->addAction("Удалить запись",this,SLOT(removeProgramFromEfir()));

 }


    conmenu->exec(tw->mapToGlobal(pos));
    }

//-------------------------------------------------------------------------------------------
void MainWindow::reinit()
{

 tw->clearContents();
 tw->setRowCount(0);
 int rowcount=0;
 e->reinitTime(0);


for (QVector<program>::iterator it=e->proglist.begin();it != e->proglist.end(); ++it)
  {
         tw->insertRow(rowcount);

     QTableWidgetItem *tw_item;

         tw_item = new QTableWidgetItem();
         tw_item->setText(QString::number(it->id));
         tw_item->setFlags(Qt::ItemIsEnabled);
         tw->setItem(rowcount,0,tw_item);

         tw_item = new QTableWidgetItem();
         tw_item->setText(e->currTime().toString("hh:mm"));
         tw_item->setFlags(Qt::ItemIsEnabled);
         tw->setItem(rowcount,1,tw_item);

         e->reinitTime(e->timelist.at(rowcount));

         tw_item = new QTableWidgetItem();
         tw_item->setText(it->name);
         tw_item->setFlags(Qt::ItemIsEnabled);
         tw->setItem(rowcount,2,tw_item);

         tw_item = new QTableWidgetItem();
         tw_item->setText(it->diktor);
         tw_item->setFlags(Qt::ItemIsEnabled);
         tw->setItem(rowcount,3,tw_item);

         rowcount++;
}

}

//--------------------------------------------------------------------------------------------
void MainWindow::removeProgramFromEfir()
{
   e->removeProgram(tw->item(tw->currentRow(),0)->text().toInt());
    reinit();
}

//---------------------------------------------------------------------------------------------
void MainWindow::moveProgramUpFromEfir()
{
    if (tw->item(tw->currentRow(),0)->row()==tw->rowCount()-1)
     { reinit();
        return;  }

    moveProgramFromEfir(1);
}
//----------------------------------------------------------------------------------------------
void MainWindow::moveProgramDownFromEfir()
{
    if (tw->item(tw->currentRow(),0)->row()==0)
      { reinit();
        return;  }

    moveProgramFromEfir(-1);
}
//-----------------------------------------------------------------------------------------------

void MainWindow::moveProgramFromEfir(int param)
{
// param =-1 - up
// param =+1 - down

e->swapProgram(param,tw->item(tw->currentRow(),0)->text().toInt());
reinit();
}
//---------------------------------------------------------------------
void MainWindow::saveefir()
{

     e->save();

}

//--------------------------------------------------------------------------------------------------
void MainWindow::showusermenu(const QPoint &pos)
{
if (tw->itemAt(pos)==0)
 { return;
}
else
  {
    tw->item(currow,1)->setBackgroundColor(QColor(255,255,255));
   tw->item(currow,2)->setBackgroundColor(QColor(255,255,255));

currow = tw->itemAt(pos)->row();

tw->item(currow,1)->setBackgroundColor(QColor(201,225,251));
tw->item(currow,2)->setBackgroundColor(QColor(201,225,251));
conmenu->clear();
conmenu->addAction("Обзор программы",this,SLOT(showuserprogram()));

}

  conmenu->exec(tw->mapToGlobal(pos));
}

//----------------------------------------------
void MainWindow::showuserprogram()
{
program r = e->proglist.value(currow);

addprogram *p = new addprogram(0,&r,1);
p->setModal(true);
p->show();

}
