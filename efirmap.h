#ifndef EFIRMAP_H
#define EFIRMAP_H

#include "mytypes.h"

class efirmap
{
public:

    efirmap();
bool addProgram(program p);
QTime currTime();
void reinitTime(int);
void swapProgram(int,int);
void removeProgram(int);
QVector<program> proglist;
QVector<int>timelist;
QTime MintoQTime(int tm);
void clearefir();
void save();
void  load();
int getEfirLen();

private:

int efirlen;



};

#endif // EFIRMAP_H
