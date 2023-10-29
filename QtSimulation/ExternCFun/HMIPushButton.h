

/***
 * @Authour         Miraitowance\Miraitowa
 * @Function        PushButton Event Handle
*/

#ifndef __HMIPushButton_H_
#define __HMIPushButton_H_

//-------------------------------------------------------------------
/**
 * @brief           这里方法建议采用中断方式使用 
 */
//-------------------------------------------------------------------

//-----------------------------INCLUDE-------------------------------

//-----------------------------INCLUDE-------------------------------

//-----------------------------DEFINE--------------------------------

#define         HMIPB_NULL0          0
#define         HMIPB_KEYUP          1
#define         HMIPB_KEYDN          2
#define         HMIPB_KEYLE          3
#define         HMIPB_KEYRD          4
#define         HMIPB_KEYSG          5
/**
 * @brief The definition here is that the pressed state is 1, and the non pressed state is 0
 */
#define         HMIPB_PSDN          0
#define         HMIPB_UNKN          1   
#define         HMIPB_LONG          10
//-----------------------------DEFINE--------------------------------
//-----------------------------TYPEDEF-------------------------------
typedef unsigned char      HMIPB_Uchar8Type;
typedef unsigned short int HMIPB_Uint16Type;
typedef unsigned int       HMIPB_Uint32Type;
typedef  char*             HMIPB_Char08Sprt;
typedef  void*             HMIPB_Void32Sprt;
//-----------------------------TYPEDEF-------------------------------

//-------------------------------------------------------------------
#define         HMIPBTaskNumber         6
extern HMIPB_Uchar8Type    GPIOLimitateIO[HMIPBTaskNumber];
//-------------------------------------------------------------------
typedef enum
{
    _HMIPBFIFO_NULL = 0,
    _HMIPBFIFO_FULL
}__HMIPB_StatusType;
typedef struct
{
    __HMIPB_StatusType Status;
    HMIPB_Uchar8Type TaskSprt;
}__HMIPBToolConfig_Struct;

#define         HMIPB_FIFOSize         20
typedef struct 
{
    HMIPB_Uchar8Type Queue[HMIPB_FIFOSize];
    HMIPB_Uchar8Type *WHead, *RTail;
    __HMIPB_StatusType  Status;
}__HMIPBFunEventConfig_Struct;
extern __HMIPBFunEventConfig_Struct _HMIPBFIFOFun;

typedef enum
{
    _HMIPBStatus_IDLE = 0,
    _HMIPBStatus_TRIP,
    _HMIPBStatus_PSDN,
    _HMIPBStatus_FREE,
    _HMIPBStatus_REST
}__HMIPB_TaskStatusType;

typedef enum 
{
    _TaskResource_OFF = 0,
    _TaskResource_USE
}_TaskResource_ENUM;

typedef struct pxTasks
{
    struct pxTasks *pxNext;
    struct pxTasks *pxPrevious;
    const HMIPB_Uchar8Type _tasksequence;
    __HMIPB_TaskStatusType _taskstatus;
    HMIPB_Uchar8Type       _taskruncnt;
    _TaskResource_ENUM     _taskresource;
}__pxTasksTypeDef_Struct;

typedef struct xMiniLists
{
    struct pxTasks *pxNext;
    struct pxTasks *pxPrevious;
}MiniListItem_t;
typedef struct pxLeads
{
    HMIPB_Uchar8Type uxNumberOfItems;
    __pxTasksTypeDef_Struct *pxIndex;
    MiniListItem_t xListEnd;
}__pxLeadsTypeDef_Struct;
extern __pxLeadsTypeDef_Struct pxReadyLeads;
//------------------------------------------------------------------------------
void                InitialHMIPB_HMIPushButton      (void);
void                ScanImplement_HMIPushButton     (void);
//------------------------------------------------------------------------------

void FunFIFOInit_HMIPushButton(              __HMIPBFunEventConfig_Struct *fifo);
void FunFIFOPush_HMIPushButton(         __HMIPBFunEventConfig_Struct *fifo,
                                                    HMIPB_Uchar8Type InputValue);
HMIPB_Uchar8Type FunFIFOPope_HMIPushButton(  __HMIPBFunEventConfig_Struct *fifo);    
void pxListInitialise_HMIPushButton(void);
void pxListInsertEnd_HMIPushButton(HMIPB_Uchar8Type HMIPB_Sprt);
void pxListDelectEle_HMIPushButton(HMIPB_Uchar8Type HMIPB_Sprt);

void pxTaskDispatch_HMIPushButton(__pxTasksTypeDef_Struct *sprt,
                                   HMIPB_Uchar8Type PollingState);
//------------------------------------------------------------------------------                                   
#endif




