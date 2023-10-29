

#ifndef __DriverFunction_H_
#define __DriverFunction_H_

#include "InterfaceDefine.h"



void GuideChese_DrvFunction(Drv_Uint16Type x,
                            Drv_Uint16Type y,
                            Drv_Uint16Type fc,
                            Drv_Uint16Type bc,
                            Drv_Uchar8Type *s);


void ShowFlaot_DrvFunction(Drv_Uint16Type x, Drv_Uint16Type y,
                           const float dat,
                           Drv_Uchar8Type num,
                           Drv_Uchar8Type pointnum);
void ShowBase_DrvFunction(Drv_Uint16Type x, Drv_Uint16Type y,
                           const int dat,
                           Drv_Uchar8Type num);

void DisplayInt32Type_DrvFunction(Drv_Uint16Type x,
                                  Drv_Uint16Type y,
                                  Drv_Uint16Type fc,
                                  Drv_Uint16Type bc,
                                  const int   value,
                                  Drv_Uchar8Type num);

void DisplayFloatType_DrvFunction( Drv_Uint16Type x,  Drv_Uint16Type y,
                                  Drv_Uint16Type fc, Drv_Uint16Type bc,
                                  const float dat,
                                  Drv_Uchar8Type num,
                                  Drv_Uchar8Type pointnum);

void ShowLoge_DSPFunction(  const unsigned char *Sprt,
                          Drv_Uint16Type X,
                          Drv_Uint16Type Y,
                          Drv_Uint16Type Width,
                          Drv_Uint16Type Hight);

void ShowImage_DrvFunction(const unsigned short *Sprt,
                           Drv_Uint16Type X,
                           Drv_Uint16Type Y,
                           Drv_Uint16Type Width,
                           Drv_Uint16Type Hight);
void ShowSquare_DrvFunction(const unsigned char *Sprt,
                            Drv_Uint16Type X,
                            Drv_Uint16Type Y,
                            Drv_Uint16Type fc,
                            Drv_Uint16Type bc,
                            Drv_Uint16Type Width,
                            Drv_Uint16Type Hight);
#endif
