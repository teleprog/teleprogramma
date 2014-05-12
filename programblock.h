#ifndef PROGRAMBLOCK_H
#define PROGRAMBLOCK_H

#include "mytypes.h"

class programblock
{

private:

int currentrecord;
void init();




QVector<program> vprog;
QVector<program>::iterator currentit;


public:
    programblock();
    int getCurrentRecordId(int index);
    struct program *getRecord(int index);
    bool setCurrentRecordId();
    QStringList getProgramNames();
    void addnewprogram(int);


};

#endif // PROGRAMBLOCK_H
