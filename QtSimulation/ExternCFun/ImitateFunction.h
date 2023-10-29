

#ifndef __ImitateFunction_H_
#define __ImitateFunction_H_

#include "InterfaceDefine.h"

void InitConfig_ImitateFunction(__ImitateScreen_TyDef *sprt);

void SetPosition_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                 Drv_Uint32Type x1, Drv_Uint32Type y1,
                                 Drv_Uint32Type x2, Drv_Uint32Type y2);

void WritePixel_ImitateFunction(__ImitateScreen_TyDef *sprt, Drv_Uint16Type color);

void SetFrontBack_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                  Drv_Uint16Type fontcolor,
                                  Drv_Uint16Type backcolor);

void SetFillClear_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                  Drv_Uint16Type color);


void DrawPoint_ImitateFunction(__ImitateScreen_TyDef *sprt,
                               Drv_Uint16Type x, Drv_Uint16Type y,
                               Drv_Uint16Type color);

void ClearSpecial_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                  Drv_Uint16Type Y, Drv_Uint16Type color);

#define InitConfig_ImitateFunc()                InitConfig_ImitateFunction(&_ImitScreen)
#define SetPosition_ImitateFunc(x1,x2,y1,y2)    SetPosition_ImitateFunction(&_ImitScreen,x1,x2,y1,y2)
#define WritePixel_ImitateFunc(color)           WritePixel_ImitateFunction(&_ImitScreen,color)
#define SetFrontBack_ImitateFunc(fc,bc)         SetFrontBack_ImitateFunction(&_ImitScreen,fc,bc)
#define SetFillClear_ImitateFunc(color)         SetFillClear_ImitateFunction(&_ImitScreen,color)
#define DrawPoint_ImitateFunc(x,y,color)        DrawPoint_ImitateFunction(&_ImitScreen,x,y,color);
#define ClearSpecial_ImitateFunc(Y,color)       ClearSpecial_ImitateFunction(&_ImitScreen,Y,color)

void SNDrawPoint_ImitateFunction(int iPosX, int iPosY, int iColor);
#endif



