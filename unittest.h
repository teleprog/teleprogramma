#ifndef UNITTEST_H
#define UNITTEST_H

#include <mytypes.h>
#include <QTextStream>

class UnitTest
{
public:
    UnitTest();

QStringList testlist;

int ConnectToDB(); //Первый тест
bool CheckProgramLenght(QTime t); //Второй тест
int clearEfir();  //Третий тест

void autoTest();  //Процедура, запускающая все 3 теста и записывающая результаты в LOG-файл

};

#endif // UNITTEST_H
