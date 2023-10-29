#include "extcfunction.h"
#include <string.h>
#include <QTextEdit>
#include "HMIPushButton.h"
#include "information.h"

extern QTextEdit *extctrlsprt;

void InitConfig_extcfunction(void)
{

    InitConfig_ImitateFunction(&_ImitScreen);
    SetFillClear_ImitateFunction(&_ImitScreen, Drv_BLACK);

//    InitalParameter_HMIinteraction();
    ImitateUpdataFlag = 1;
    InitialHMIPB_HMIPushButton();
}

// __pxTasksTypeDef_Struct *tasksprt;
void Implement_extcfunction(void)
{
    ScanImplement_HMIPushButton();
    if(_HMIDispTool.dpstatus == _HMIScreenStatus_SHOW)
    {
        ImitateUpdataFlag = 1;
        extctrlsprt->clear();
        extctrlsprt->append(QString("Status:%1").arg(_HMIDispTool.rfstatus));
    }
    tsRunsDisplay_HMIDispScreen();
}
