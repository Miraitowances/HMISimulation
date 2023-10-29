
/**
 * @brief           human-computer interaction
 * @author          Nightmare-WU
 * @version         1.0
 * @note            HMIControl Updata
 */




#ifndef __HMIinteraction_H_
#define __HMIinteraction_H_


/**
 * @brief           Include underlying driver files
 *
 */
#include "DriveFunction.h"
#include "ImitateFunction.h"
/********           @brief User Function         ********/
void        InitalParameter_HMIinteraction      (void);
void        TaskImplement_HMIinteraction        (void);


/******** @brief Underlying function declaration ********/

void        NullFunction_HMIinteraction         (void);
void        ScanImplement_HMIinteraction        (void);

void        StatusHandle_MainFunction           (void);
void        DisplayScreen_MainFunction          (void);

// void        ReadHandle_ImageFunction            (void);
// void        ReadDisplay_ImageFunction           (void);

// void        WriteHandle_ImageFunction           (void);
// void        WriteDisplay_ImageFunction          (void);

// void        FreedomHandle_ImageFunction         (void);
// void        FreedomDisplay_ImageFunction        (void);

// void        StatusHandle_MotorFunction          (void);
// void        ScreenDisplay_MotorFunction         (void);

// void        StatusHandle_AngleFunction          (void);
// void        ScreenDisplay_AngleFunction         (void);

// void        StatusHandle_OtherFunction          (void);
// void        ScreenDisplay_OtherFunction         (void);

// void        StatusHandle_StoreFunction          (void);
// void        ScreenDisplay_StoreFunction         (void);

// void        RefreshParam_StoreFunction          (void);
// void        OldReadParam_StoreFunction          (void);


#include "HMIlinteradef.h"

void DisplayPage_HMIinteraction(unsigned char TaskFunction, unsigned char TaskParamNumber,
                                __HMIinteraction_HMIAlter_Struct _TaskAlter[]);

#endif
