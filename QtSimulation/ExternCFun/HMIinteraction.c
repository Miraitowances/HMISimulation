#include "HMIinteraction.h"

/**
 * @brief           Null Function  Protect
 * 
 */
void NullFunction_HMIinteraction(void)
{
    /* Null Function */
}

/**
 * @brief           Variable Initial Function
 * 
 */

void InitalParameter_HMIinteraction(void)
{
    _HMIMonitor._keyStatus = _HMIKeyStatus_Idle;
    _HMIMonitor._keyInform = _HMIKeyInform_Null;
    _HMIMonitor._keyRecord = _HMIKeyInform_Null;
    _HMIMonitor._HMIHandle = _HMIKeyHandle_Reset;    
    _HMIMonitor._HMIDisplay = _HMIDisplay_Reset;
    _HMIMonitor._Renovate  = _HMIRenovate_Whole;

    _HMIMonitor._HMIControl = _HMIDisplay_Enable;

    _HMIMonitor.TaskSprt = 0;
    _HMIMonitor._KeyModeCnt = 0;

    _HMItool._SprtNull = 0;

//    GuideChese_DrvFunction(90,40,Drv_PINK,Drv_BLACK,(Drv_Uchar8Type*)"123鲸落入海321");
//    GuideChese_DrvFunction(73,56,Drv_PINK,Drv_BLACK,(Drv_Uchar8Type*)"Miraitowance");
//    GuideChese_DrvFunction(0,120,Drv_BLUE,Drv_BLACK,(Drv_Uchar8Type*)"WANG SHUANG");
//    GuideChese_DrvFunction(0,20,Drv_BLUE,Drv_BLACK,(Drv_Uchar8Type*)"菜单");
//    ShowFlaot_DrvFunction(100,100, 123.322,3,3);
}

/**
 * @brief   Task Implement Switch Of Status
 *
 */
void TaskImplement_HMIinteraction(void)
{
    if(_HMIMonitor._HMIControl == _HMIDisplay_Enable)
    {
        //Implement Key Scanning and Screen Refresh
        /**
         * @brief Construct a new ScanImplement_HMIinteraction object
         *        On Operating System   the scan function on there thread time 20ms
         *        On Bare Pager         the scan function on Interrupt    time 20ms
         */
        ScanImplement_HMIinteraction();

        if(_HMIMonitor._HMIHandle == _HMIKeyHandle_Enable)
            _HMITaskMenu[_HMIMonitor.TaskSprt].TaskFunction();


        if(_HMIMonitor._HMIDisplay == _HMIDisplay_Enable)
        {
            _HMITaskMenu[_HMIMonitor.TaskSprt].DisplayFunction();
            ImitateUpdataFlag = 1;
        }

    }
    else
    {

    }

}

/**
 * @brief           Key Scaning Implement Function
 *
 */
void ScanImplement_HMIinteraction(void)
{
    switch(_HMIMonitor._keyStatus)
    {
    case _HMIKeyStatus_Idle:
        if(_KEY_U_ == GPIO_LOW || _KEY_D_ == GPIO_LOW || _KEY_L_ == GPIO_LOW || _KEY_R_ == GPIO_LOW || _KEY_S_ == GPIO_LOW)
        {
            _HMIMonitor._keyStatus = _HMIKeyStatus_Chick;
        }
        break;
    case _HMIKeyStatus_Chick:
        if(_KEY_U_ == GPIO_LOW || _KEY_D_ == GPIO_LOW || _KEY_L_ == GPIO_LOW || _KEY_R_ == GPIO_LOW || _KEY_S_ == GPIO_LOW)
        {
            _HMIMonitor._keyStatus = _HMIKeyStatus_Enable;
        }
        else
        {
            _HMIMonitor._keyStatus = _HMIKeyStatus_Idle;
        }
        break;
    case _HMIKeyStatus_Enable:
        _HMIMonitor._keyStatus = _HMIKeyStatus_Release;
        _HMIMonitor._KeyModeCnt = _KeyModeCnt_Reset;
        if     (_KEY_U_ == GPIO_LOW)
        {
            _HMIMonitor._keyInform = _HMIKeyInform_Ukey;
        }
        else if(_KEY_D_ == GPIO_LOW)
        {
            _HMIMonitor._keyInform = _HMIKeyInform_Dkey;
        }
        else if(_KEY_L_ == GPIO_LOW)
        {
            _HMIMonitor._keyInform = _HMIKeyInform_Lkey;
        }
        else if(_KEY_R_ == GPIO_LOW)
        {
            _HMIMonitor._keyInform = _HMIKeyInform_Rkey;
        }
        else if(_KEY_S_ == GPIO_LOW)
        {
            _HMIMonitor._keyInform = _HMIKeyInform_SKey;
        }
        else
        {
            _HMIMonitor._keyStatus = _HMIKeyStatus_Idle;
        }
        //record key status information
        _HMIMonitor._keyRecord = _HMIMonitor._keyInform;
        break;
    case _HMIKeyStatus_Release:
        if(_KEY_U_ == GPIO_HIGH && _KEY_D_ == GPIO_HIGH && _KEY_L_ == GPIO_HIGH && _KEY_R_ == GPIO_HIGH && _KEY_S_ == GPIO_HIGH)
        {
            //enable screen refresh
            _HMIMonitor._HMIHandle = _HMIKeyHandle_Enable;
            _HMIMonitor._keyStatus = _HMIKeyStatus_Idle;
        }
        else
        {
            // chick long press mode
            if(++_HMIMonitor._KeyModeCnt > _KeyModeCnt_Enable)
            {
                //prevent data overflow
                _HMIMonitor._KeyModeCnt = _KeyModeCnt_Enable;

                //continue screen refresh
                _HMIMonitor._keyInform = _HMIMonitor._keyRecord;
                _HMIMonitor._HMIHandle = _HMIKeyHandle_Enable;
            }
        }
        break;
    }
}

/**
 * @brief Main Function Select and Modify
 *
 */

void StatusHandle_MainFunction(void)
{
    _HMIMonitor._HMIHandle = _HMIKeyHandle_Reset;
    _HMIMonitor._HMIDisplay = _HMIDisplay_Enable;

    switch(_HMIMonitor._keyInform)
    {
        case _HMIKeyInform_Ukey:
            if((--_HMITaskMenu[MainFunction].TaskSerial) < 1)
                _HMITaskMenu[MainFunction].TaskSerial = 1;
            break;
        case _HMIKeyInform_Dkey:
            if((++_HMITaskMenu[MainFunction].TaskSerial) > MainMenuNumber - 1)
                _HMITaskMenu[MainFunction].TaskSerial = MainMenuNumber - 1;
            break;
        case _HMIKeyInform_Lkey:
            _HMIMonitor._Renovate = _HMIRenovate_Whole;
            _HMITaskMenu[MainFunction].TaskSerial = 1;
            _HMITaskMenu[MainFunction].SelectData = _HMIKeySwitch_Close;
            break;
        case _HMIKeyInform_Rkey:
            if(_HMITaskMenu[MainFunction].TaskSerial == 6)
            {
                _HMITaskMenu[MainFunction].SelectData = _HMIKeySwitch_Open;
            }
            else
            {
                _HMIMonitor.TaskSprt = _HMITaskMenu[MainFunction].TaskSerial;
//                _HMIMonitor._HMIDisplay = _HMIDisplay_Enable;
                _HMIMonitor._Renovate = _HMIRenovate_Whole;

            }
            break;
        case _HMIKeyInform_SKey:
            if( _HMITaskMenu[MainFunction].TaskSerial == 6 &&
                _HMITaskMenu[MainFunction].SelectData == _HMIKeySwitch_Open )
            {
                /**
                     * @brief on this call the smart car start-up
                     *
                     */


                _HMIMonitor._HMIControl = _HMIDisplay_Reset;
                _HMITaskMenu[MainFunction].SelectData = _HMIKeySwitch_Close;
            }

            break;
        default:
            _HMIMonitor._HMIDisplay = _HMIDisplay_Reset;
            break;
    }
}



/**
 * @brief Main Menu Select Related Functions
 *
 */

void DisplayScreen_MainFunction(void)
{
    _HMIMonitor._HMIDisplay = _HMIDisplay_Reset;
    // adjust renovate method

//    switch(_HMIMonitor._Renovate)
//    {
//        case _HMIRenovate_Special:
//            if(_HMITaskMenu[MainFunction].LastSerial == _HMITaskMenu[MainFunction].TaskSerial)
//            {
//                //on this indicate data max or min
//            }
//            else
//            {
//                //clear last sprt
//                ClearSpecial_ImitateFunc(_HMITaskMenu[MainFunction].LastSerial * 20,Drv_BLACK);
//                GuideChese_DrvFunction(40, _HMITaskMenu[MainFunction].LastSerial * 20, Drv_PINK, Drv_BLACK,
//                                      (Drv_Uchar8Type*)_MainMenu[_HMITaskMenu[MainFunction].LastSerial].Name);
//                //display current task screen
//                GuideChese_DrvFunction(40, _HMITaskMenu[MainFunction].TaskSerial * 20, Drv_RED,  Drv_BLACK,
//                                      (Drv_Uchar8Type*)_MainMenu[_HMITaskMenu[MainFunction].TaskSerial].Name);
//                GuideChese_DrvFunction(160,_HMITaskMenu[MainFunction].TaskSerial * 20, Drv_BLUE, Drv_YELLOW, (Drv_Uchar8Type*)"吾");
//            }
//            break;
//        case _HMIRenovate_Whole:
            SetFillClear_ImitateFunc(Drv_BLACK);
            for(_HMItool.LoopCount = 0; _HMItool.LoopCount < MainMenuNumber; _HMItool.LoopCount++)
            {
                if(_HMItool.LoopCount == _HMITaskMenu[MainFunction].TaskSerial)
                {
                    GuideChese_DrvFunction(160,_HMItool.LoopCount * 20, Drv_BLUE, Drv_YELLOW, (Drv_Uchar8Type*)"吾");
                    GuideChese_DrvFunction(40, _HMItool.LoopCount * 20, Drv_RED,  Drv_BLACK, (Drv_Uchar8Type*)_MainMenu[_HMItool.LoopCount].Name);
                }
                else
                {
                    GuideChese_DrvFunction(40, _HMItool.LoopCount * 20, Drv_PINK, Drv_BLACK,(Drv_Uchar8Type*)_MainMenu[_HMItool.LoopCount].Name);
                }
            }
            _HMIMonitor._Renovate = _HMIRenovate_Special;
//            break;
//    }

//     record last renovate type
    _HMITaskMenu[MainFunction].LastSerial = _HMITaskMenu[MainFunction].TaskSerial;
}



void DisplayPage_HMIinteraction(unsigned char TaskFunction, unsigned char TaskParamNumber, __HMIinteraction_HMIAlter_Struct _TaskAlter[])
{
    _HMItool.PageStare = _HMITaskMenu[TaskFunction].TaskSerial - _HMITaskMenu[TaskFunction].TaskSerial % 7;
    _HMItool.LoopCount = _HMItool.PageStare - 1;

    SetFillClear_ImitateFunc(Drv_BLACK);

    while((++_HMItool.LoopCount) < _HMItool.PageStare + 7 && _HMItool.LoopCount < TaskParamNumber)
    {
        if(_HMItool.LoopCount == _HMITaskMenu[TaskFunction].TaskSerial)
        {
            GuideChese_DrvFunction(20,(_HMItool.LoopCount % 7) * 19, Drv_RED, Drv_BLACK,
                                      (Drv_Uchar8Type*)_TaskAlter[_HMItool.LoopCount].TipsName);
        }
        else
        {
            GuideChese_DrvFunction(20,(_HMItool.LoopCount % 7) * 19, Drv_PINK, Drv_BLACK,
                                      (Drv_Uchar8Type*)_TaskAlter[_HMItool.LoopCount].TipsName);
        }
    }
}





