

#include "HMIPushButton.h"

//-----------------------------INCLUDE-------------------------------
#include "Miraitowance.h"


__pxTasksTypeDef_Struct pxHMIPBTasks[HMIPBTaskNumber] =
    {
        {0, 0, HMIPB_NULL0, _HMIPBStatus_IDLE, 0, _TaskResource_OFF},
        {0, 0, HMIPB_KEYUP, _HMIPBStatus_IDLE, 0, _TaskResource_OFF},
        {0, 0, HMIPB_KEYDN, _HMIPBStatus_IDLE, 0, _TaskResource_OFF},
        {0, 0, HMIPB_KEYLE, _HMIPBStatus_IDLE, 0, _TaskResource_OFF},
        {0, 0, HMIPB_KEYRD, _HMIPBStatus_IDLE, 0, _TaskResource_OFF},
        {0, 0, HMIPB_KEYSG, _HMIPBStatus_IDLE, 0, _TaskResource_OFF},
};
__pxLeadsTypeDef_Struct pxReadyLeads;
__HMIPBToolConfig_Struct _HMIPBTool;
__HMIPBFunEventConfig_Struct _HMIPBFIFOFun;

//@#Interface------------------------------------------------
HMIPB_Uchar8Type HMIPB_GPIO_ReadPin(HMIPB_Uchar8Type func)
{
    switch (func)
    {
        case HMIPB_KEYUP:
            return;
            break;
        case HMIPB_KEYDN:
            return;
            break;
        case HMIPB_KEYLE:
            return;
            break;
        case HMIPB_KEYRD:
            break;
        case HMIPB_KEYSG:
            break;
        default:
            break;
    }
    // Normal not running there
    return HMIPB_UNKN;
}
//@#Interface------------------------------------------------

/**
 * @brief   Initiation HMIPushButton
 **/
void InitialHMIPB_HMIPushButton(void)
{
    _HMIPBTool.Status = _HMIPBFIFO_NULL;
    _HMIPBTool.TaskSprt = HMIPB_NULL0;

    FunFIFOInit_HMIPushButton(&_HMIPBFIFOFun);
    pxListInitialise_HMIPushButton();
    ConfigInitial_HMIDispScreen();
}

void ScanImplement_HMIPushButton(void)
{
    if (pxReadyLeads.uxNumberOfItems != 0)
    {
        __pxTasksTypeDef_Struct *pxCurrentTCB = pxReadyLeads.xListEnd.pxNext;
        for (int sprt = 0; sprt < pxReadyLeads.uxNumberOfItems; sprt++)
        {
            pxTaskDispatch_HMIPushButton(pxCurrentTCB, HMIPB_GPIO_ReadPin(pxCurrentTCB->_tasksequence));
            pxCurrentTCB = pxCurrentTCB->pxNext;
        }

        while (_HMIPBFIFOFun.Status)
        {
            tsRunDispatch_HMIDispScreen(FunFIFOPope_HMIPushButton(&_HMIPBFIFOFun));
        }
    }
}

/**
 * @brief Initialize event list
 *
 * @param fifo Initialize event list fifo
 */

void FunFIFOInit_HMIPushButton(__HMIPBFunEventConfig_Struct *fifo)
{
    HMIPB_Uchar8Type _HMIPBLoop;
    for (_HMIPBLoop = 0; _HMIPBLoop < HMIPB_FIFOSize; _HMIPBLoop++)
    {
        fifo->Queue[_HMIPBLoop] = 0;
    }
    fifo->WHead = &(fifo->Queue[0]);
    fifo->RTail = fifo->WHead;
    fifo->Status = _HMIPBFIFO_NULL;
}

/**
 * @brief Queue stacking using pointer mode
 *
 * @param fifo          Stacking structure
 * @param InputValue    input data
 */
void FunFIFOPush_HMIPushButton(__HMIPBFunEventConfig_Struct *fifo, HMIPB_Uchar8Type InputValue)
{
    fifo->Status = _HMIPBFIFO_FULL;
    *(fifo->WHead) = InputValue;
    fifo->WHead += 1;
    if (fifo->WHead - fifo->Queue >= HMIPB_FIFOSize)
        fifo->WHead = &fifo->Queue[0];

    if (fifo->WHead == fifo->RTail)
    {
        fifo->RTail += 1;
        if (fifo->RTail - fifo->Queue >= HMIPB_FIFOSize)
            fifo->RTail = &fifo->Queue[0];
    }
}
/**
 * @brief Stacking output data
 *
 * @param fifo                  Stacking structure
 * @return HMIPB_Uchar8Type     output data
 */
HMIPB_Uchar8Type FunFIFOPope_HMIPushButton(__HMIPBFunEventConfig_Struct *fifo)
{
    HMIPB_Uchar8Type returval = 0;

    returval = *(fifo->RTail);
    fifo->RTail += 1;
    if (fifo->RTail - fifo->Queue >= HMIPB_FIFOSize)
        fifo->RTail = &fifo->Queue[0];

    if (fifo->RTail == fifo->WHead)
        fifo->Status = _HMIPBFIFO_NULL;

    return returval;
}
//----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------
void pxListInitialise_HMIPushButton(void)
{
    pxReadyLeads.pxIndex = (__pxTasksTypeDef_Struct *)&pxReadyLeads.xListEnd;
    pxReadyLeads.xListEnd.pxNext = (__pxTasksTypeDef_Struct *)&pxReadyLeads.xListEnd;
    pxReadyLeads.xListEnd.pxPrevious = (__pxTasksTypeDef_Struct *)&pxReadyLeads.xListEnd;
    pxReadyLeads.uxNumberOfItems = (HMIPB_Uchar8Type)0U;
}

void pxListInsertEnd_HMIPushButton(HMIPB_Uchar8Type HMIPB_Sprt)
{

    __pxTasksTypeDef_Struct *const pxIndex = pxReadyLeads.pxIndex;
    __pxTasksTypeDef_Struct *const pxNewListItem = (__pxTasksTypeDef_Struct *)&(pxHMIPBTasks[HMIPB_Sprt]);

    if (pxNewListItem->_taskresource == _TaskResource_OFF)
    {
        pxNewListItem->_taskresource = _TaskResource_USE;
        pxNewListItem->pxNext = pxIndex;
        pxNewListItem->pxPrevious = pxIndex->pxPrevious;
        pxIndex->pxPrevious->pxNext = pxNewListItem;
        pxIndex->pxPrevious = pxNewListItem;

        pxReadyLeads.uxNumberOfItems += (HMIPB_Uchar8Type)1;
    }
}

void pxListDelectEle_HMIPushButton(HMIPB_Uchar8Type HMIPB_Sprt)
{
    __pxTasksTypeDef_Struct *const pxItemToRemove = (__pxTasksTypeDef_Struct *)&(pxHMIPBTasks[HMIPB_Sprt]);

    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

    if (pxReadyLeads.pxIndex == pxItemToRemove)
        pxReadyLeads.pxIndex = pxItemToRemove->pxPrevious;

    pxReadyLeads.uxNumberOfItems -= (HMIPB_Uchar8Type)1;
    pxItemToRemove->_taskstatus = _HMIPBStatus_IDLE;
    pxItemToRemove->_taskresource = _TaskResource_OFF;
}

void pxTaskDispatch_HMIPushButton(__pxTasksTypeDef_Struct *sprt,
                                  HMIPB_Uchar8Type PollingState)
{
    switch (sprt->_taskstatus)
    {
        case _HMIPBStatus_IDLE:
            if (HMIPB_PSDN == PollingState)
                sprt->_taskstatus = _HMIPBStatus_TRIP;
            else
                sprt->_taskstatus = _HMIPBStatus_REST;
            break;
        case _HMIPBStatus_TRIP:
            if (HMIPB_PSDN == PollingState)
                sprt->_taskstatus = _HMIPBStatus_PSDN;
            else
                sprt->_taskstatus = _HMIPBStatus_REST;
            break;
        case _HMIPBStatus_PSDN:
            if (HMIPB_PSDN == PollingState)
            {
                sprt->_taskruncnt = (HMIPB_Uint16Type)0;
                sprt->_taskstatus = _HMIPBStatus_FREE;
            }
            else
                sprt->_taskstatus = _HMIPBStatus_REST;
            break;
        case _HMIPBStatus_FREE:
            if (HMIPB_UNKN == PollingState)
            {
                FunFIFOPush_HMIPushButton(&_HMIPBFIFOFun, sprt->_tasksequence);
                pxListDelectEle_HMIPushButton(sprt->_tasksequence);
            }
            else
            {
                if (++sprt->_taskruncnt > HMIPB_LONG)
                {
                    sprt->_taskruncnt = HMIPB_LONG;
                    FunFIFOPush_HMIPushButton(&_HMIPBFIFOFun, sprt->_tasksequence);
                }
            }
            break;
        default:
            pxListDelectEle_HMIPushButton(sprt->_tasksequence);
            break;
    }
}
