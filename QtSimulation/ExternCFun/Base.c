


/*********************************
 * @Authour:Miraitowance/Miraitowa*
 * @Function:鲸落の入海 ~(_0.0_)- *
 ********************************/
#include "Base.h"
//-------------------------INCLUDE-------------------------
#include "DriveFunction.h"
#include "ImitateFunction.h"
#include "HMIPushButton.h"
#include "FontFunction.h"
#include "FImageFunction.h"
//-------------------------INCLUDE-------------------------
//-------------------------DEFINE--------------------------
#ifdef         HMITaskFunctions
#undef         HMITaskFunctions
#endif
#define        HMITaskFunctions        (HMIBaseFunctions)
#ifdef         _HMITaskMinIndex
#undef         _HMITaskMinIndex
#endif
#ifdef         _HMITaskMaxIndex
#undef         _HMITaskMaxIndex
#endif

#define        _HMITaskMinIndex        0
#define        _HMITaskMaxIndex        0
//-------------------------DEFINE--------------------------
//-------------------------EXTERN--------------------------
extern _HMIDispScreen_HMITasksSchedule_Struct TaskSchedule[HMIScrTaskNumber];
//-------------------------EXTERN--------------------------
//-------------------------VARIABLE------------------------

//-------------------------VARIABLE------------------------
//-------------------------NOTICE--------------------------
/***************************************************************************************
 * @_HMIDispTool.tasksprt                       Function: 页面指针
 * @_HMIDispTool.dpstatus                       Function：控制是否刷新屏幕开关
 * @_HMIDispTool.extevent                       Function：触发的按键处理事件
 * @_HMIDispTool.rfstatus                       Function: 刷新方式 关闭 循环 触发 全刷
 * @TaskSchedule[HMITaskFunctions].Select       Function: 选择状态 选择 选中 NULL
 * @TaskSchedule[HMITaskFunctions].TaskSerial   Function: 当前任务下的引导变量
 * @TaskSchedule[HMITaskFunctions].LastSerial   Function: 记录任务下的引导变量
 ***************************************************************************************/
//-------------------------NOTICE--------------------------
//-------------------------FUNCTION------------------------
void BaseFunction_HandlesFunction(void)
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
           break;
   }
}
unsigned char count = 0;
void BaseFunction_DisplayFunction(void)
{
   switch (_HMIDispTool.rfstatus)
   {
       case _HMIRefreshStatus_CLOS:
           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
           break;
       case _HMIRefreshStatus_NOUN:
           /*Add user functions here*/
           count++;
           DisplayInt32Type_DrvFunction(0,0,Drv_BLACK,Drv_WHITE,(int)count,3);
           GuideChese_DrvFunction(50,30,Drv_Rose,Drv_WHITE,(Drv_Uchar8Type*)"I Base OK!");
           break;
       case _HMIRefreshStatus_PART:
           /*Add user functions here*/
           GuideChese_DrvFunction(50,30,Drv_Rose,Drv_WHITE,(Drv_Uchar8Type*)"I Base OK!");
           count++;
           DisplayInt32Type_DrvFunction(0,0,Drv_BLACK,Drv_WHITE,(int)count,3);
           _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;
           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
           break;
       case _HMIRefreshStatus_ALLS:
           /*Add user functions here*/
           SetFillClear_ImitateFunc(Drv_BLACK);
           ShowImage_DrvFunction(maliao_png_txt,0,20,37,50);
           ShowSquare_DrvFunction(closefile_png_txt,100,60,Drv_BLACK,Drv_Amber,50,40);
           GuideChese_DrvFunction(150,20,Drv_Rose,Drv_WHITE,(Drv_Uchar8Type*)"我是你无");
           ShowImage_DrvFunction(wegame_png_txt,0,100,115,29);
           /* @Note: Can add logic to select refresh method. */
           _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;
//           _HMIDispTool.rfstatus = _HMIRefreshStatus_NOUN;
           break;
       default:
           _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;
           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;
           break;
   }
}
//-------------------------FUNCTION------------------------

