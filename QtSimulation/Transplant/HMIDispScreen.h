

/***
 * @Authour         Miraitowance\Miraitowa
 * @Function        DispScreen Event Handle
*/

#ifndef _HMIDispScreen_H_
#define _HMIDispScreen_H_

//-----------------------------INCLUDE-------------------------------
#include "Miraitowance.h"
#include "HMIPushButton.h"
//-----------------------------INCLUDE-------------------------------
//-----------------------------TYPEDEF-------------------------------

typedef unsigned char      HMIDS_Uchar8Type;
typedef unsigned short int HMIDS_Uint16Type;
typedef unsigned int       HMIDS_Uint32Type;
typedef     char           HMIDS_Char08Type;
typedef     char*          HMIDS_Char08Sprt;
typedef     void*          HMIDS_Void32Sprt;
//-----------------------------TYPEDEF-------------------------------
//------------------------------DEFINE-------------------------------
#define         HMIScrTaskNumber         6
#define         HMIMainFunctions         0

//------------------------------DEFINE-------------------------------
typedef enum
{
    _HMIPushButtonEvt_NULL = HMIPB_NULL0,
    _HMIPushButtonEvt_PBUP = HMIPB_KEYUP,
    _HMIPushButtonEvt_PBDN = HMIPB_KEYDN,
    _HMIPushButtonEvt_PBLE = HMIPB_KEYLE,
    _HMIPushButtonEvt_PBRD = HMIPB_KEYRD,
    _HMIPushButtonEvt_PBSG = HMIPB_KEYSG,
}_HMIPushButtonEvt_ENUM;

typedef enum
{
    _HMIScreenStatus_CLOS = 0,
    _HMIScreenStatus_SHOW,
}_HMIScreenStatus_ENUM;

typedef enum
{
    _HMIRefreshStatus_CLOS = 0,
    _HMIRefreshStatus_ALLS,
    _HMIRefreshStatus_PART,
    _HMIRefreshStatus_NOUN,
}_HMIRefreshStatus_Enum;

typedef struct 
{
    HMIDS_Uchar8Type          tasksprt;
    _HMIPushButtonEvt_ENUM    extevent;
    _HMIScreenStatus_ENUM     dpstatus;
    _HMIRefreshStatus_Enum    rfstatus;
}_HMIDispScreen_HMIToolDispatch_Struct;

typedef enum 
{
    _HMIDSselect_NONULL = 0,
    _HMIDSselect_SELECT,
    _HMIDSselect_FORCUS,
}_HMIDispScreen_HMIDSselect_Enum;

typedef struct 
{
    HMIDS_Char08Type TaskSerial;
    HMIDS_Uchar8Type LastSerial;

    _HMIDispScreen_HMIDSselect_Enum Select;
    
    void    (*HandlesFunction)      (void);
    void    (*DisplayFunction)      (void);
}_HMIDispScreen_HMITasksSchedule_Struct;

extern _HMIDispScreen_HMIToolDispatch_Struct _HMIDispTool;

void        ConfigInitial_HMIDispScreen         (void);
void        tsRunsDisplay_HMIDispScreen         (void);
void        tsRunDispatch_HMIDispScreen         (HMIDS_Uchar8Type extevents);
//----------------------------------------------------------------------------
void        NULLFunction_SecuresFunction        (void);
void        MainFunction_HandlesFunction        (void);
void        MainFunction_DisplayFunction        (void);
#endif


