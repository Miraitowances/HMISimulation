

#include "HMIDispScreen.h"

_HMIDispScreen_HMITasksSchedule_Struct TaskSchedule[HMIScrTaskNumber] = 
{
    //TaskSerial  LastSerial  Select               HandlesFunction               DisplayFunction
    {          1,          1, _HMIDSselect_NONULL, MainFunction_HandlesFunction, MainFunction_DisplayFunction},
    {          0,          0, _HMIDSselect_NONULL, NULLFunction_SecuresFunction, NULLFunction_SecuresFunction},
    {          0,          0, _HMIDSselect_NONULL, NULLFunction_SecuresFunction, NULLFunction_SecuresFunction},
    {          0,          0, _HMIDSselect_NONULL, NULLFunction_SecuresFunction, NULLFunction_SecuresFunction},
    {          0,          0, _HMIDSselect_NONULL, NULLFunction_SecuresFunction, NULLFunction_SecuresFunction},
    {          0,          0, _HMIDSselect_NONULL, NULLFunction_SecuresFunction, NULLFunction_SecuresFunction},
};

_HMIDispScreen_HMIToolDispatch_Struct _HMIDispTool;


//---------------------------------------------FUNCTION-------------------------------------------------------
//---------------------------------------------FUNCTION-------------------------------------------------------

void ConfigInitial_HMIDispScreen(void)
{
    _HMIDispTool.tasksprt = HMIMainFunctions;
    _HMIDispTool.extevent = _HMIPushButtonEvt_NULL;
    _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
    _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
	SetFillClear_ImitateFunc(BColor);
    ShowImage_DrvFunction(myloge,0,0,135,135);
    GuideChese_DrvFunction(155, 40,Drv_HotPink,Drv_BLACK,(Drv_Uchar8Type*)"鲸落入海");
    GuideChese_DrvFunction(153, 60,Drv_OperaMauve,Drv_BLACK,(Drv_Uchar8Type*)"~(_0.0_)-");
    GuideChese_DrvFunction(145, 80,Drv_Beige,Drv_BLACK,(Drv_Uchar8Type*)"WANG SHUANG");
    GuideChese_DrvFunction(142,100,Drv_GreenYellow,Drv_BLACK,(Drv_Uchar8Type*)"Miraitowance");
    GuideChese_DrvFunction(136,120,Drv_LightPink,Drv_BLACK,(Drv_Uchar8Type*)"QQ:1791109376");

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
//-------------------------DEFINE--------------------------
#ifdef         HMITaskFunctions
#undef         HMITaskFunctions
#endif
#define        HMITaskFunctions        (HMIMainFunctions)

#ifdef         _HMITaskMinIndex
#undef         _HMITaskMinIndex
#endif
#ifdef         _HMITaskMaxIndex
#undef         _HMITaskMaxIndex
#endif

#define        _HMITaskMinIndex        0
#define        _HMITaskMaxIndex        0
//-------------------------DEFINE--------------------------
//-----------------------------INCLUDE-------------------------------

//-----------------------------INCLUDE-------------------------------


void MainFunction_HandlesFunction(void)
{
   _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;
   /*  @Note:  If you don't want to refresh the screen.
               you can close it under this function _HMIScreenStatus_CLOS*/
   switch (_HMIDispTool.extevent)
   {
       case _HMIPushButtonEvt_PBUP:
           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)
           {
                   /*Add user functions here*/

           }
           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_FORCUS)
           {
                   /*Add user functions here*/

           }
           else
           {
               if((--TaskSchedule[HMITaskFunctions].TaskSerial < _HMITaskMinIndex))
                   TaskSchedule[HMITaskFunctions].TaskSerial = _HMITaskMinIndex;
           }
					 
					 _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
           break;
       case _HMIPushButtonEvt_PBDN:
           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)
           {
                   /*Add user functions here*/

           }
           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_FORCUS)
           {
                   /*Add user functions here*/

           }
           else
           {
               if((++TaskSchedule[HMITaskFunctions].TaskSerial >= _HMITaskMaxIndex))
                   TaskSchedule[HMITaskFunctions].TaskSerial = _HMITaskMaxIndex;
           }
					 
					 _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
					 
           break;
       case _HMIPushButtonEvt_PBLE:
           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_FORCUS)
               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_SELECT;
           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)
               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_NONULL;
           else
           {
               _HMIDispTool.tasksprt = HMIMainFunctions;
               _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
           }
					 _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;
           break;
       case _HMIPushButtonEvt_PBRD:
           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_NONULL)
               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_SELECT;
           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)
               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_FORCUS;
           break;
       case _HMIPushButtonEvt_PBSG:
                   /*Add user functions here*/

           break;
       default:
           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
           break;
   }
	
}


void MainFunction_DisplayFunction(void)
{
   switch (_HMIDispTool.rfstatus)
   {
       case _HMIRefreshStatus_CLOS:
           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
           break;
       case _HMIRefreshStatus_NOUN:
           /*Add user functions here*/

           break;
       case _HMIRefreshStatus_PART:
           /*Add user functions here*/
		   GuideChese_DrvFunction(155, 40,Drv_HotPink,Drv_BLACK,(Drv_Uchar8Type*)"HELLO");
           _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;
           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
           break;
       case _HMIRefreshStatus_ALLS:
           /*Add user functions here*/

           /* @Note: Can add logic to select refresh method. */
			 
		   SetFillClear_ImitateFunc(Drv_BLACK);
           _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;
           //_HMIDispTool.rfstatus = _HMIRefreshStatus_NOUN;
           break;
       default:
           _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;
           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
           break;
   }
}