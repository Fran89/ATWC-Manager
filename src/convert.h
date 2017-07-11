#ifndef CONVERT_H
#define CONVERT_H
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "includes/earlybirdlib.h"

class Convert{
public:
    Convert();
    ~Convert();
    int readATWC(QString filename);
    int writeMSEED(QString dirname);
private:
    int iNumStnDisk;
    STATION *StaArrayDisk;
};



#endif // CONVERT_H
