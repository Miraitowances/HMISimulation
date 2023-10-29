

#ifndef __HMIlinteradef_H_
#define __HMIlinteradef_H_

/**
 * @brief           Macro Definition
 *
 */
#define         GPIO_LOW                 0
#define         GPIO_HIGH                1

#include "InterfaceDefine.h"
#define         _KEY_U_                  1//ReturnKeyValue_catch(1)//IfxPort_getPinState(&MODULE_P13, 1)
#define         _KEY_D_                  2//ReturnKeyValue_catch(2)//IfxPort_getPinState(&MODULE_P13, 2)
#define         _KEY_L_                  3//ReturnKeyValue_catch(3)//IfxPort_getPinState(&MODULE_P13, 0)
#define         _KEY_R_                  4//ReturnKeyValue_catch(4)//IfxPort_getPinState(&MODULE_P11, 2)
#define         _KEY_S_                  5//ReturnKeyValue_catch(5)//IfxPort_getPinState(&MODULE_P13, 3)


#define         _KeyModeCnt_Reset       0
#define         _KeyModeCnt_Enable      8

/**
 * @brief       HMIinteraction data type definion
 *
 */

typedef         char*                   HMINameTypdef;
typedef         void*                   HMIDataTypdef;

/**
 * @brief           Enumeration constant
 *
 */

typedef enum
{
    /**
     * @brief Key Running Status
     *
     */
    _HMIKeyStatus_Idle = 0,

    _HMIKeyStatus_Chick,
    _HMIKeyStatus_Enable,
    _HMIKeyStatus_Release

}__HMIinteraction_KeyStatus_enum;

typedef enum
{
    /**
     * @brief Key Information
     *
     */

    _HMIKeyInform_Null = 0,

    _HMIKeyInform_Ukey,
    _HMIKeyInform_Dkey,
    _HMIKeyInform_Lkey,
    _HMIKeyInform_Rkey,
    _HMIKeyInform_SKey,

}__HMIinteraction_KeyInform_enum;


typedef enum
{
    /**
     * @brief  Screen Refresh Enable
     *
     */
    _HMIDisplay_Reset = 0,
    _HMIDisplay_Enable,
}__HMIinteraction_HMIDisplay_enum;


typedef enum
{
    /**
     * @brief Data modification enable
     *
     */
    _HMIKeyHandle_Reset = 0,
    _HMIKeyHandle_Enable,

}__HMIinteraction_HMIHandle_enum;

typedef enum
{
    /**
     * @brief data select enale
     *
     */
    _HMIKeySwitch_Close = 0,
    _HMIKeySwitch_Open,
    _HMIKeySwitch_Enable,
}__HMIinteraction_HMISwitch_enum;


typedef enum
{

    /**
     * @brief screen renovate method
     *
     */
    _HMIRenovate_Whole = 0,
    _HMIRenovate_Special,

}__HMIinteraction_Renovate_enum;



/**
 * @brief           Structure state machine definition
 *
 */

typedef struct _HMI_STRUCT_
{
    __HMIinteraction_KeyStatus_enum     _keyStatus;         //Key status
    __HMIinteraction_KeyInform_enum     _keyInform;         //Pressent key data
    __HMIinteraction_KeyInform_enum     _keyRecord;         //Long Press data

    __HMIinteraction_HMIHandle_enum     _HMIHandle;         //Data Process Handle

    __HMIinteraction_Renovate_enum      _Renovate;

    __HMIinteraction_HMIDisplay_enum    _HMIDisplay;        //Screen Refresh enable
    __HMIinteraction_HMIDisplay_enum    _HMIControl;        //Control Use HIM Intreaction


    unsigned char TaskSprt;
    unsigned int _KeyModeCnt;                           //record Press time

}__HMIinteraction_Monitor_Struct;


/**
 * @brief           Top Menu Sturct Control
 *
 */

typedef struct _HMITask_STRUCT_
{
    char TaskSerial;

    unsigned char LastSerial;

    __HMIinteraction_HMISwitch_enum SelectData;

    void (*TaskFunction) (void);

    void (*DisplayFunction)(void);

}__HMIinteraction_TaskMenu_Struct;

/**
 * @brief           Top Menu Name
 *
 */

typedef struct _MHIMAIN_MENU_STRUCT_
{
    HMINameTypdef Name;
}__HMIinteraction_MainMenu_Struct;

/**
 * @brief           Image Menu Paramter
 *
 */
typedef struct _HMIIMGE_WriteMENU_STRUCT_
{
    HMINameTypdef fpName[8];
    HMIDataTypdef ParamterSprt[8];
    float         Stepping[8];
}__HMIinteraction_ImageWriteMenu_Struct;

typedef struct _HMIIMGE_ReadMENU_STRUCT_
{
    HMINameTypdef fpName[8];
    HMIDataTypdef ParamterSprt[8];
}__HMIinteraction_ImageReadMenu_Struct;

typedef struct _HMIIMGE_Attribute_STRUCT_
{
    unsigned char *AttributeFunction;
}__HMIinteraction_Attribute_Struct;

typedef struct _HMIOTHER_ElecMenu_STRUCT_
{
    HMINameTypdef TipsName[7];
    HMIDataTypdef DisplaySprt[7];
}__HMIinteraction_ElecMenu_Struct;

typedef struct _HMIimple_FuncMenu_STRUCT_
{
    HMINameTypdef TipsName;
    void (*ImpleFunction)(void);
}__HMIinteraction_FuncMenu_Struct;

/**
 * @brief           tool struct
 *
 */
typedef struct _HMITOOL_STRUCT_
{
    unsigned short int LoopCount;
    unsigned char PageStare;

    float   _SprtNull;
}__HMIinteraction_HMITool_Struct;

/**
 * @brief ParamAlter Struct
 *
 */
typedef struct _HMIAlter_STRUCT_
{
    HMINameTypdef TipsName;
    HMIDataTypdef Paramter;
    float         Stepping;

}__HMIinteraction_HMIAlter_Struct;


//------------------------------------------------------------------------------
extern unsigned char ImitateUpdataFlag;
//------------------------------------------------------------------------------
#define             TaskMenuNumber              6
extern __HMIinteraction_Monitor_Struct _HMIMonitor;
extern __HMIinteraction_HMITool_Struct _HMItool;
extern __HMIinteraction_TaskMenu_Struct _HMITaskMenu[TaskMenuNumber];

#define             MainFunction                0
#define             ImageFunction               1
#define             MotorFunction               2
#define             AngleFunction               3
#define             OtherFunction               4
#define             StoreFunction               5

#define             MainMenuNumber              7
extern __HMIinteraction_MainMenu_Struct _MainMenu[MainMenuNumber];


#endif

