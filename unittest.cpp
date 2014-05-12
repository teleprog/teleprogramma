#include "unittest.h"
#include "loginwindow.h"

UnitTest::UnitTest()
{

}

//----------------------------------------------------
int UnitTest::ConnectToDB()
{

    LoginWindow login;
    login.checkSettings();
    login.connection();

    testlist.append("Test1:"+QString::number((int)db));

return (int)db;
}
//----------------------------------------------------

bool UnitTest::CheckProgramLenght(QTime t)
{
bool status;

program p;
p.time = t;
efirmap *e = new efirmap();

status = e->addProgram(p);

testlist.append("Test2:"+QString::number((int)status));

return status;

}
//----------------------------------------------------

int UnitTest::clearEfir()
{
efirmap *e = new efirmap();

e->clearefir();

testlist.append("Test3:"+QString::number(e->getEfirLen()));

return e->getEfirLen();

}

//----------------------------------------------------
void UnitTest::autoTest()
{
 ConnectToDB();
 CheckProgramLenght(QTime(25,0));
 clearEfir();

 QFile file("autotest.log");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    for (int i=0;i<testlist.size();i++)
    out << testlist.at(i) << "\n\n";

    file.close();
}





