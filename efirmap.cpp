#include "efirmap.h"

efirmap::efirmap()
{

efirlen=4*60;
load();

}
//if ( (h*60+m+5*value.reklama)>22*60)

bool efirmap::addProgram(program p)
{

int timeprogram = p.time.hour()*60 + p.time.minute() + p.reklama*5;

if (efirlen+timeprogram>26*60)
{
       QMessageBox mb;
        mb.setText("Программа не влезает в сетку эфира.\nВещание может быть только до 2:00 ночи!");
        mb.exec();

return 0;
}

efirlen+=timeprogram;
proglist.push_back(p);
timelist.push_back(timeprogram);


return 1;
}

//----------------------------------------------------------
QTime efirmap::MintoQTime(int tm)
{
    int hour  = tm/60;
    int min = tm - hour*60;

    if (hour>23) hour = hour-24;

    QTime t(hour,min,0);

 return t;
}
//----------------------------------------------------------
QTime efirmap::currTime()
{
  return MintoQTime( efirlen );


}
//-----------------------------------------------------------
void efirmap::reinitTime(int t)
{
    if (t==0)
efirlen=4*60;
else
 efirlen+=t;


}
///-----------------------------------------------------------
void  efirmap::removeProgram(int id)
{
    int count = 0;

    for (QVector<program>::iterator it=proglist.begin();it != proglist.end(); ++it)
      {if ((*it).id==id)
      {
       proglist.erase(it);
       efirlen-= timelist.at(count);
       timelist.removeAt(count);
       return;
      }
     count ++;
    }

}
//---------------------------------------------------------------
void  efirmap::swapProgram(int param,int id)
{
 int t;
 program p;
 int count = 0;

    for (QVector<program>::iterator it=proglist.begin();it != proglist.end(); ++it)
    {if ((*it).id==id) {


          p= proglist.at(count+param);
             proglist.replace(count+param,proglist.at(count));
             proglist.replace(count,p);


          t = timelist.at(count+param);
          timelist.replace(count+param,timelist.at(count));
          timelist.replace(count,t);

             return;
        }


    count++;
    }
}

//--------------------------------------------------------------
void  efirmap::clearefir()
{
  efirlen=4*60;
proglist.clear();
timelist.clear();

}
//---------------------------------------------------------------
void  efirmap::save()
{
     QString  str;
      int count = 0;
    query.exec("delete from efir where efir_id <>0");

  for (QVector<program>::iterator it=proglist.begin();it != proglist.end(); ++it)
  {

      str = "insert into efir values(0,"+QString::number(count)+","+QString::number((*it).id)+")";
      query.exec(str);

       count++;
   }

}
//---------------------------------------------------------------
void  efirmap::load()
{
   program pr;
   int timeprogram;

QString str = "select program_id,lentime,reklama,name,comment,diktor from programs,efir where id_prog=program_id order by count";
 query.exec(str);

 while (query.next()) {
  pr.id=query.value(0).toInt();
  pr.time=query.value(1).toTime();
  pr.reklama= query.value(2).toInt();
  pr.name=query.value(3).toString();
  pr.comment=query.value(4).toString();
  pr.diktor=query.value(5).toString();

  proglist.push_back(pr);
  timeprogram = pr.time.hour()*60 + pr.time.minute() + pr.reklama*5;
  efirlen+= timeprogram;
  timelist.push_back(timeprogram);

 }


}
//---------------------------------
int efirmap::getEfirLen()
{
 return efirlen;

}


