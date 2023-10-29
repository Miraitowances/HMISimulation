

#include "HMIDispScreen.h"


#include "Base.h"


_HMIDispScreen_HMITasksSchedule_Struct TaskSchedule[HMIScrTaskNumber] = 
{
    //TaskSerial  LastSerial  Select               HandlesFunction               DisplayFunction
    {          1,          1, _HMIDSselect_NONULL, MainFunction_HandlesFunction, MainFunction_DisplayFunction},
    {          0,          0, _HMIDSselect_NONULL, CarsFunction_HandlesFunction, CarsFunction_DisplayFunction},
    {          0,          0, _HMIDSselect_NONULL, CtrlFunction_HandlesFunction, CtrlFunction_DisplayFunction},
    {          0,          0, _HMIDSselect_NONULL, BaseFunction_HandlesFunction, BaseFunction_DisplayFunction},
    {          0,          0, _HMIDSselect_NONULL, NULLFunction_SecuresFunction, NULLFunction_SecuresFunction},
    {          0,          0, _HMIDSselect_NONULL, NULLFunction_SecuresFunction, NULLFunction_SecuresFunction},
};

_HMIDispScreen_HMIToolDispatch_Struct _HMIDispTool;


//---------------------------------------------FUNCTION-------------------------------------------------------
void sDynamicClockInitial(void);
//---------------------------------------------FUNCTION-------------------------------------------------------



void ConfigInitial_HMIDispScreen(void)
{
    _HMIDispTool.tasksprt = HMIMainFunctions;
    _HMIDispTool.extevent = _HMIPushButtonEvt_NULL;
    _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
    _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
    ShowImage_DrvFunction(myloge,0,0,135,135);
    GuideChese_DrvFunction(155, 40,Drv_HotPink,Drv_BLACK,(Drv_Uchar8Type*)"鲸落入海");
    GuideChese_DrvFunction(153, 60,Drv_OperaMauve,Drv_BLACK,(Drv_Uchar8Type*)"~(_0.0_)-");
    GuideChese_DrvFunction(145, 80,Drv_Beige,Drv_BLACK,(Drv_Uchar8Type*)"WANG SHUANG");
    GuideChese_DrvFunction(142,100,Drv_GreenYellow,Drv_BLACK,(Drv_Uchar8Type*)"Miraitowance");
    GuideChese_DrvFunction(136,120,Drv_LightPink,Drv_BLACK,(Drv_Uchar8Type*)"QQ:1791109376");
    sDynamicClockInitial();
    _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;
}

void tsRunDispatch_HMIDispScreen(HMIDS_Uchar8Type extevents)
{
    _HMIDispTool.extevent = (_HMIPushButtonEvt_ENUM)extevents;
    TaskSchedule[_HMIDispTool.tasksprt].HandlesFunction();
}

void tsRunsDisplay_HMIDispScreen(void)
{
    if(_HMIDispTool.dpstatus == _HMIScreenStatus_SHOW)
        TaskSchedule[_HMIDispTool.tasksprt].DisplayFunction();
}


void NULLFunction_SecuresFunction(void)
{
    /**
     * @brief Protect NULL Function
     */
}

//-----------------------------INCLUDE-------------------------------
#include "SuperNumber.h"
#include "ImitateFunction.h"    //模拟接口
//-----------------------------INCLUDE-------------------------------
//一个电子钟包括8个部分
sSuperNum stSuperNum1;
sSuperNum stSuperNum2;
sSuperNum stSuperNum3;
sSuperNum stSuperNum4;
sSuperNum stSuperNum5;
sSuperNum stSuperNum6;
sSuperNum stSuperNum7;
sSuperNum stSuperNum8;
//特效状态转移查询库
uint8_t SegAction[MAX_SEG_STATUE][MAX_SEG_STATUE][SEG_NUM];

void MainFunction_HandlesFunction(void)
{
    switch (_HMIDispTool.extevent)
    {
        case _HMIPushButtonEvt_PBUP:
            if((--TaskSchedule[HMIMainFunctions].TaskSerial) < 1)
                TaskSchedule[HMIMainFunctions].TaskSerial = 1;
            _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;
            break;
        case _HMIPushButtonEvt_PBDN:
            if((++TaskSchedule[HMIMainFunctions].TaskSerial) > 3)
                TaskSchedule[HMIMainFunctions].TaskSerial = 3;
            _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;
            break;
        case _HMIPushButtonEvt_PBLE:
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            break;
        case _HMIPushButtonEvt_PBRD:
            _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
            break;
        case _HMIPushButtonEvt_PBSG:
            _HMIDispTool.tasksprt = (HMIDS_Uchar8Type)TaskSchedule[HMIMainFunctions].TaskSerial;
            _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
            _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            break;                                    
        default:
            break;
    }
}

unsigned char CurrCnt = 0,CurrHour = 0, CurrMin = 0,CurrSec = 0;

void MainFunction_DisplayFunction(void)
{
    switch(_HMIDispTool.rfstatus)
    {
        case _HMIRefreshStatus_CLOS:
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            return;
            break;
        case _HMIRefreshStatus_NOUN:
            if(++CurrCnt > 50)
            {
                CurrCnt = 0;
                CurrSec++;
            }
            if(CurrSec >= 60)
            {
                CurrSec = 0;
                CurrMin++;
                if(CurrMin >= 60)
                {
                    CurrMin = 0;
                    CurrHour++;
                    if(CurrHour >= 24)
                    {
                        CurrHour = 0;
                    }
                }
            }
            SuperNumActionPlay(&stSuperNum1,(uint8_t*)SegAction,CurrHour/10);
            SuperNumActionPlay(&stSuperNum2,(uint8_t*)SegAction,CurrHour%10);
            SuperNumActionPlay(&stSuperNum3,(uint8_t*)SegAction,11);
            SuperNumActionPlay(&stSuperNum4,(uint8_t*)SegAction,CurrMin/10);
            SuperNumActionPlay(&stSuperNum5,(uint8_t*)SegAction,CurrMin%10);
            SuperNumActionPlay(&stSuperNum6,(uint8_t*)SegAction,11);
            SuperNumActionPlay(&stSuperNum7,(uint8_t*)SegAction,CurrSec/10);
            SuperNumActionPlay(&stSuperNum8,(uint8_t*)SegAction,CurrSec%10);
            break;
        case _HMIRefreshStatus_PART:

            if(TaskSchedule[HMIMainFunctions].TaskSerial == 1)
            {
                ShowSquare_DrvFunction(_SmartCar,20,93,Drv_Blue,Drv_BLACK,50,31);
            }
            else 
            {
                ShowSquare_DrvFunction(_SmartCar,20,93,Drv_CoralPink,Drv_BLACK,50,31);
            }

            if(TaskSchedule[HMIMainFunctions].TaskSerial == 2)
            {
                ShowSquare_DrvFunction(_Elementdata,110,90,Drv_Blue,Drv_BLACK,39,36);
            }
            else 
            {
                ShowSquare_DrvFunction(_Elementdata,110,90,Drv_CoralPink,Drv_BLACK,39,36);
            }

            if(TaskSchedule[HMIMainFunctions].TaskSerial == 3)
            {
                ShowSquare_DrvFunction(_SetUp,190,90,Drv_Blue,Drv_BLACK,38,37);
            }
            else
            {
                ShowSquare_DrvFunction(_SetUp,190,90,Drv_CoralPink,Drv_BLACK,38,37);
            }

            _HMIDispTool.rfstatus = _HMIRefreshStatus_NOUN;
            break;
        case _HMIRefreshStatus_ALLS:
            SetFillClear_ImitateFunc(Drv_BLACK);
            GuideChese_DrvFunction(90,14,Drv_Rose,Drv_BLACK,(Drv_Uchar8Type*)"鲸落入海");
            sDynamicClockInitial();
            _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;
            break;
    }
}

void sDynamicClockInitial(void)
{
#define NUM_OFFSET (19)

    uint16_t x_Location = 55;
    uint16_t y_Location = 40;

    stSuperNum1.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum1,x_Location,y_Location,10,10,3);
    InitialSegShowAction(&stSuperNum1,(uint8_t*)SegAction);

    x_Location += NUM_OFFSET;

    stSuperNum2.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum2,x_Location,y_Location,10,10,3);
    InitialSegShowAction(&stSuperNum2,(uint8_t*)SegAction);

    x_Location += NUM_OFFSET;
    stSuperNum3.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum3,x_Location,y_Location,2,10,2);
    InitialSegShowAction(&stSuperNum3,(uint8_t*)SegAction);

    x_Location += NUM_OFFSET/2 + 2;
    stSuperNum4.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum4,x_Location,y_Location,10,10,3);
    InitialSegShowAction(&stSuperNum4,(uint8_t*)SegAction);

    x_Location += NUM_OFFSET;
    stSuperNum5.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum5,x_Location,y_Location,10,10,3);
    InitialSegShowAction(&stSuperNum6,(uint8_t*)SegAction);

    x_Location += NUM_OFFSET;
    stSuperNum6.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum6,x_Location,y_Location,2,10,2);
    InitialSegShowAction(&stSuperNum6,(uint8_t*)SegAction);

    x_Location += NUM_OFFSET/2 + 2;
    stSuperNum7.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum7,x_Location,y_Location,10,10,3);
    InitialSegShowAction(&stSuperNum7,(uint8_t*)SegAction);

    x_Location += NUM_OFFSET;
    stSuperNum8.pDrawPoint = SNDrawPoint_ImitateFunction;
    InitialSuperNum(&stSuperNum8,x_Location,y_Location,10,10,3);
    InitialSegShowAction(&stSuperNum8,(uint8_t*)SegAction);
}




void CarsFunction_HandlesFunction(void)
{
    switch (_HMIDispTool.extevent)
    {
        case _HMIPushButtonEvt_PBUP:
            if((--TaskSchedule[HMICarsFunctions].TaskSerial) < 1)
                TaskSchedule[HMICarsFunctions].TaskSerial = 1;
            _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            break;
        case _HMIPushButtonEvt_PBDN:
            if((++TaskSchedule[HMICarsFunctions].TaskSerial) > 99)
                TaskSchedule[HMICarsFunctions].TaskSerial = 99;
            _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            break;
        case _HMIPushButtonEvt_PBLE:
            if(TaskSchedule[HMICarsFunctions].Select == _HMIDSselect_NONULL) 
            {
                _HMIDispTool.tasksprt = HMIMainFunctions;
                _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
                _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            }
            break;
        case _HMIPushButtonEvt_PBRD:

            break;
        case _HMIPushButtonEvt_PBSG:
            break;                                    
        default:
            break;
    }
}

void CarsFunction_DisplayFunction(void)
{
    switch(_HMIDispTool.rfstatus)
    {
        case _HMIRefreshStatus_CLOS:
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            break;
        case _HMIRefreshStatus_PART:
            DisplayInt32Type_DrvFunction(200,10,Drv_FireBrick,Drv_WHITE,(int)TaskSchedule[HMICarsFunctions].TaskSerial,3);
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            break;
        case _HMIRefreshStatus_ALLS:
            SetFillClear_ImitateFunc(Drv_WHITE);
            GuideChese_DrvFunction(20,5,Drv_ChromeYellow,Drv_WHITE,(Drv_Uchar8Type*)"图像处理");
            GuideChese_DrvFunction(0, 70,    Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"普通超宽");
            GuideChese_DrvFunction(0, 86,    Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"严重超宽");
            GuideChese_DrvFunction(0, 102,   Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"绝对超宽");
            GuideChese_DrvFunction(0, 118,   Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"存储状态");

            GuideChese_DrvFunction(120, 70,  Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"控制状态");
            GuideChese_DrvFunction(120, 86,  Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"元素状态");
            GuideChese_DrvFunction(120, 102, Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"左边点数");
            GuideChese_DrvFunction(120, 118, Drv_RoyalBlue, Drv_WHITE,(Drv_Uchar8Type*)"右边点数");
            _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;
            break;
        default:
            _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            break;
    }
}

void CtrlFunction_HandlesFunction(void)
{
    switch (_HMIDispTool.extevent)
    {
        case _HMIPushButtonEvt_PBUP:
            if((--TaskSchedule[HMICtrlFunctions].TaskSerial) < 1)
                TaskSchedule[HMICtrlFunctions].TaskSerial = 1;
            _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            break;
        case _HMIPushButtonEvt_PBDN:
            if((++TaskSchedule[HMICtrlFunctions].TaskSerial) > 99)
                TaskSchedule[HMICtrlFunctions].TaskSerial = 99;
            _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            break;
        case _HMIPushButtonEvt_PBLE:
            if(TaskSchedule[HMICtrlFunctions].Select == _HMIDSselect_NONULL) 
            {
                _HMIDispTool.tasksprt = HMIMainFunctions;
                _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
                _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
            }
            break;
        case _HMIPushButtonEvt_PBRD:

            break;
        case _HMIPushButtonEvt_PBSG:
            break;                                    
        default:
            break;
    }
}

void CtrlFunction_DisplayFunction(void)
{
    switch(_HMIDispTool.rfstatus)
    {
        case _HMIRefreshStatus_CLOS:
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            break;
        case _HMIRefreshStatus_PART:
            DisplayInt32Type_DrvFunction(10,30,Drv_FireBrick,Drv_BLACK,(int)TaskSchedule[HMICtrlFunctions].TaskSerial,3);
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            break;
        case _HMIRefreshStatus_ALLS:
            SetFillClear_ImitateFunc(Drv_BLACK);
            GuideChese_DrvFunction(20,5,Drv_ChromeYellow,Drv_BLACK,(Drv_Uchar8Type*)"Set参数");
            ShowImage_DrvFunction(myloge,110,0,135,135);
            _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;
            break;
        default:
            _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;
            _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
            break;
    }
}


