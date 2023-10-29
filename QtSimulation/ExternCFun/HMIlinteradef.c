


#include "HMIlinteradef.h"

#include "HMIinteraction.h"
/**
 * @brief              Variable definition
 *
 */
__HMIinteraction_Monitor_Struct _HMIMonitor;
__HMIinteraction_HMITool_Struct _HMItool;

__HMIinteraction_TaskMenu_Struct _HMITaskMenu[TaskMenuNumber] =
{
    { 1, 1, _HMIKeySwitch_Close, StatusHandle_MainFunction,   DisplayScreen_MainFunction   },
    { 0, 1, _HMIKeySwitch_Close, NullFunction_HMIinteraction, NullFunction_HMIinteraction  },
    { 0, 0, _HMIKeySwitch_Close, NullFunction_HMIinteraction, NullFunction_HMIinteraction  },
    { 0, 0, _HMIKeySwitch_Close, NullFunction_HMIinteraction, NullFunction_HMIinteraction  },
    { 0, 0, _HMIKeySwitch_Close, NullFunction_HMIinteraction, NullFunction_HMIinteraction  },
    { 0, 0, _HMIKeySwitch_Close, NullFunction_HMIinteraction, NullFunction_HMIinteraction  },
 };

/********       @brief Main menu content set up           *******/
__HMIinteraction_MainMenu_Struct _MainMenu[MainMenuNumber] =
{
        {"Main菜单"},
        {"图像参数"},
        {"电机参数"},
        {"角度参数"},
        {"其它参数"},
        {"存储参数"},
        {"鲸落入海"}
};

/********       @brief Image menu content set up           *******/

#define             ImageReadMenuNumber              2
__HMIinteraction_ImageReadMenu_Struct _ImageReadMenu[ImageReadMenuNumber] = 
{
    //Page 0
    {
        {"图像阈值", "阈值限幅", "拐点数量", "停止点数", "左上点数", "左下点数","右上点数", "右下点数"},
        {
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull
        },
    },

    //Page 1
    {
        {"hello", "name", "hope", "today", "tool", "fuck","you", "other"},
        {
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull
        },
    }
};

#define             ImageWriteMenuNumber             1
__HMIinteraction_ImageWriteMenu_Struct _ImageWriteMenu[ImageWriteMenuNumber] =
{
    //page 0
    {
        {"图像阈值", "阈值限幅", "拐点数量", "停止点数", "左上点数", "左下点数","右上点数", "右下点数"},
        {
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull
        },
        {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}
    }
};


#define             MotorParamNumber                15
__HMIinteraction_HMIAlter_Struct __MotorAlter[MotorParamNumber] = 
{
    {"LMotor-比例",     &_HMItool._SprtNull, 0.1f},
    {"LMotor-微分",     &_HMItool._SprtNull, 0.1f},
    {"LMotor-积分",     &_HMItool._SprtNull, 0.1f},
    {"RMotor-比例",     &_HMItool._SprtNull, 0.1f},
    {"RMotor-微分",     &_HMItool._SprtNull, 0.1f},
    {"RMotor-积分",     &_HMItool._SprtNull, 0.1f},
    {"Nigmtare_WU",    &_HMItool._SprtNull, 0.1f},
    {"Nigmtare_WS",    &_HMItool._SprtNull, 0.1f},
    {"Nigmtare_HH",    &_HMItool._SprtNull, 0.1f},
    {"参数1",    &_HMItool._SprtNull, 0.1f},
    {"参数2",    &_HMItool._SprtNull, 0.1f},
    {"参数3",    &_HMItool._SprtNull, 0.1f},
    {"参数4",    &_HMItool._SprtNull, 0.1f},
    {"参数5",    &_HMItool._SprtNull, 0.1f},
    {"参数6",    &_HMItool._SprtNull, 0.1f},

};

#define             AngleParamNumber                 10
__HMIinteraction_HMIAlter_Struct __AngleAlter[AngleParamNumber] =
{
    {"Angle-1",     &_HMItool._SprtNull, 0.1f},
    {"Angle-2",     &_HMItool._SprtNull, 0.1f},
    {"Angle-3",     &_HMItool._SprtNull, 0.1f},
    {"Angle-4",     &_HMItool._SprtNull, 0.1f},
    {"Angle-5",     &_HMItool._SprtNull, 0.1f},
    {"Angle-6",     &_HMItool._SprtNull, 0.1f},
    {"Angle-7",    &_HMItool._SprtNull, 0.1f},
    {"Angle-8",    &_HMItool._SprtNull, 0.1f},
    {"Angle-9",    &_HMItool._SprtNull, 0.1f},
    {"Angle-0",    &_HMItool._SprtNull, 0.1f},
}; 


#define             ImageFreeMenuNumber             2

#define             OtherPageMenuNumber             1

#define             ElecTypeMenuNumber              2
__HMIinteraction_ElecMenu_Struct _ElecMenu[ElecTypeMenuNumber] = 
{
    {
        //Page 0 Electromagnetic raw data
        {"Elec_LL","Elec_LM","Elec_LR","Elec_MM","Elec_RL","Elec_RM","Elec_RR"},
        {   &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,
            &_HMItool._SprtNull,}
    },
    {
        //Page 1 Electromagnetic processing data
        {"Deal_LL","Deal_LM","Deal_LR","Deal_MM","Deal_RL","Deal_RM","Deal_RR"},
        {   &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,
            &_HMItool._SprtNull,&_HMItool._SprtNull,&_HMItool._SprtNull,
            &_HMItool._SprtNull,}
    }
};


#define             StorePageMenuNumber             1

#define             FuncParamNumber                 8
__HMIinteraction_FuncMenu_Struct _FuncMenu[FuncParamNumber] = 
{
    {"Store",   NullFunction_HMIinteraction},
    {"Read" ,   NullFunction_HMIinteraction},
    {"Imple_3", NullFunction_HMIinteraction},
    {"Imple_4", NullFunction_HMIinteraction},
    {"Imple_5", NullFunction_HMIinteraction},
    {"Imple_6", NullFunction_HMIinteraction},
    {"Imple_7", NullFunction_HMIinteraction},
    {"Imple_8", NullFunction_HMIinteraction}
};


//--------------------------------------------------------------------------------------------

unsigned char ImitateUpdataFlag = 0;
