#include "programblock.h"

programblock::programblock()
{


 init();

}
//--------------------------------------------------
void programblock::init()
{
vprog.clear();

    QString str ="select program_id,lentime,reklama,name,comment,diktor from programs";

         query.exec(str);

         program p;

           while (query.next()) {

           p.id=query.value(0).toInt();
           p.time=query.value(1).toTime();
           p.reklama=query.value(2).toInt();
           p.name=query.value(3).toString();
           p.comment=query.value(4).toString();
           p.diktor=query.value(5).toString();

           vprog.push_back(p);



           }

if (vprog.count()!=0)
 currentit=vprog.begin();
else currentit=NULL;




}
//---------------------------------------------------
int programblock::getCurrentRecordId(int index)
{
int i=0;

for (QVector<program>::iterator it=vprog.begin();it != vprog.end(); ++it)
   {
if (i==index)
return (*it).id;

    i++;
}

return -1;
}

bool programblock::setCurrentRecordId()
{



}

//--------------------------------------------------------

QStringList programblock::getProgramNames()
{

init();


QStringList l ;

for (QVector<program>::iterator it=vprog.begin();it != vprog.end(); ++it)
   l.push_back((*it).name);



return l;
}

//---------------------------------------------------------
void programblock::addnewprogram(int param)
{


}

//----------------------------------------------------------
struct program *programblock::getRecord(int index)
{
    int i=0;

    for (QVector<program>::iterator it=vprog.begin();it != vprog.end(); ++it)
       {
    if (i==index)
    return &(*it);

        i++;
    }

    return NULL;

}
//--------------------------------------------
