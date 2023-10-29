#ifndef EXTCFUNCTION_H
#define EXTCFUNCTION_H


#include <QDebug>
#include <QString>
extern "C"
{
    #include "InterfaceDefine.h"
    #include "DriveFunction.h"
    #include "ImitateFunction.h"
    #include "HMIinteraction.h"
    #include "HMIPushButton.h"
    #include "HMIDispScreen.h"
}

void InitConfig_extcfunction(void);
void Implement_extcfunction(void);





#endif // EXTCFUNCTION_H
