
#include "ImitateFunction.h"
__ImitateScreen_TyDef _ImitScreen;


void InitConfig_ImitateFunction(__ImitateScreen_TyDef *sprt)
{
    Drv_Uint32Type loptr;
    Drv_Uint16Type *cont = &(sprt->Screen[0][0]);
    sprt->ScreenSprt = Drvnullprt;
    sprt->WSelected = 0;
    sprt->HSelected = 0;

    sprt->frontcolor = FColor;
    sprt->backcolor  = BColor;
    sprt->ScreenSize = WScreen * HScreen;
    for(loptr = 0; loptr < sprt->ScreenSize; loptr++,cont++)
    {
        *cont = BColor;
    }
}


void SetPosition_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                 Drv_Uint32Type x1, Drv_Uint32Type y1,
                                 Drv_Uint32Type x2, Drv_Uint32Type y2)
{
    //设置位置先检查位置的安全性
    if(((int)x2 - (int)x1) >= 0 && (x2 - x1) < WScreen &&((int)y2 - (int)y1) >= 0 && (y2 - y1 < HScreen))
    {
        sprt->ScreenSprt = &(sprt->Screen[y1][x1]);
        sprt->WSelected = x2 - x1;
        sprt->HSelected = y2 - y1;
        sprt->movestepx = 0;
        sprt->movestepy = 0;
    }
    else
    {
        sprt->ScreenSprt = Drvnullprt;
        sprt->WSelected = 0;
        sprt->HSelected = 0;
        sprt->movestepx = 0;
        sprt->movestepy = 0;
    }
}

void WritePixel_ImitateFunction(__ImitateScreen_TyDef *sprt, Drv_Uint16Type color)
{
    if(sprt->WSelected != 0 || sprt->HSelected != 0)
    {
        if(sprt->movestepy <= sprt->HSelected)
        {
            *(sprt->ScreenSprt) = color;
//            if(sprt->WSelected != 0)
                sprt->ScreenSprt++;
            sprt->movestepx++;
            if(sprt->movestepx > sprt->WSelected)
            {
                sprt->ScreenSprt += (WScreen - sprt->WSelected - 1);
                sprt->movestepx = 0;
                sprt->movestepy++;
            }
        }
        else
        {
            sprt->ScreenSprt = Drvnullprt;
            sprt->WSelected = 0;
            sprt->HSelected = 0;
            sprt->movestepx = 0;
            sprt->movestepy = 0;
        }
    }
}


void SetFrontBack_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                  Drv_Uint16Type fontcolor,
                                  Drv_Uint16Type backcolor)
{
    sprt->frontcolor = fontcolor;
    sprt->backcolor  = backcolor;
}

void SetFillClear_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                  Drv_Uint16Type color)
{
    Drv_Uint32Type LoopX = WScreen * HScreen;

    SetPosition_ImitateFunction(sprt,0,0,239,134);
    while((LoopX--) > 0)
    {
        WritePixel_ImitateFunction(sprt, color);
    }

}


void ClearSpecial_ImitateFunction(__ImitateScreen_TyDef *sprt,
                                  Drv_Uint16Type Y, Drv_Uint16Type color)
{
    Drv_Uint16Type LoopX = 4800;
    SetPosition_ImitateFunction(sprt,0,Y,239,Y+19);
    while((LoopX--) > 0)
    {
        WritePixel_ImitateFunction(sprt, color);
    }
}

void DrawPoint_ImitateFunction(__ImitateScreen_TyDef *sprt,
                               Drv_Uint16Type x, Drv_Uint16Type y,
                               Drv_Uint16Type color)
{
    sprt->Screen[y][x] = color;
}


void SNDrawPoint_ImitateFunction(int iPosX, int iPosY, int iColor)
{
    DrawPoint_ImitateFunction(&_ImitScreen,iPosX,iPosY,iColor);
}
