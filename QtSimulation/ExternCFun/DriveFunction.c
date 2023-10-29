


#include "DriveFunction.h"
#include "FontFunction.h"

#include <string.h>
#define     func_abs(x)             ((x) >= 0 ? (x): -(x))
void func_float_to_str (char *str, float number, Drv_Uchar8Type point_bit);
void func_int_to_str (char *str, int number);

void GuideChese_DrvFunction(    Drv_Uint16Type x,
                                Drv_Uint16Type y,
                                Drv_Uint16Type fc,
                                Drv_Uint16Type bc,
                                Drv_Uchar8Type *s   )
{
    Drv_Uint16Type LoopX, LoopY, LoopN;
    Drv_Uint16Type Temp;

    while(*s)
    {
        if((*s) >= 128)
        {
#ifdef GB2312Mode
            for(LoopN = 0; LoopN < CharactersNumber; LoopN++)
            {
                if(Characters[LoopN].Guide[0] == *s && Characters[LoopN].Guide[1] == *(s+1))
                {
                    SetPosition_ImitateFunc(x,y,x+15,y+15);
                    for(LoopX = 0; LoopX < 32; LoopX++)
                    {
                        for(LoopY = 0; LoopY < 8; LoopY++)
                        {
                            if(Characters[LoopN].Code[LoopX] & (0x80 >> LoopY))
                                WritePixel_ImitateFunc(fc);
                            else
                                WritePixel_ImitateFunc(bc);
                        }
                    }
                }

            }
            s+=2; x+=16;
#else
            for(LoopN = 0; LoopN < CharactersNumber; LoopN++)
            {
                if(    Characters[LoopN].Guide[0] == *s
                    && Characters[LoopN].Guide[1] == *(s+1)
                    && Characters[LoopN].Guide[2] == *(s+2))
                {
                    SetPosition_ImitateFunc(x,y,x+15,y+15);
                    for(LoopX = 0; LoopX < 32; LoopX++)
                    {
                        for(LoopY = 0; LoopY < 8; LoopY++)
                        {
                            if(Characters[LoopN].Code[LoopX] & (0x80 >> LoopY))
                                WritePixel_ImitateFunc(fc);
                            else
                                WritePixel_ImitateFunc(bc);
                        }
                    }
                    break;
                }
            }
            s+=3; x+=16;
#endif
        }
        else
        {
            SetPosition_ImitateFunc(x,y,x+7,y+15);
            for(LoopX = 0; LoopX < 16; LoopX++)
            {
                Temp = ascii_font_8x16[(*s)-32][LoopX];
                for(LoopY = 0; LoopY < 8; LoopY++)
                {
                    if(Temp&0x01)
                        WritePixel_ImitateFunc(fc);
                    else
                        WritePixel_ImitateFunc(bc);
                    Temp>>=1;
                }
            }
            s+=1; x+=8;
        }
    }
}





void ShowFlaot_DrvFunction(Drv_Uint16Type x, Drv_Uint16Type y,
                           const float dat,
                           Drv_Uchar8Type num,
                           Drv_Uchar8Type pointnum)
{
    if(x >= WScreen) return;
    if(y >= HScreen) return;
    if(num > 8)           return;
    if(pointnum > 6)      return;

    float dat_temp = dat;
    float offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num + pointnum + 1);

    if(num < 10)
    {
        for(; num > 0; num --)
        {
            offset *= 10;
        }
        dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    }
    func_float_to_str(data_buffer, dat_temp, pointnum);
    GuideChese_DrvFunction(x,y,_ImitScreen.frontcolor,_ImitScreen.backcolor,(Drv_Uchar8Type*)data_buffer);
}

void ShowBase_DrvFunction(Drv_Uint16Type x, Drv_Uint16Type y,
                           const int dat,
                           Drv_Uchar8Type num)
{
    if(x >= WScreen) return;
    if(y >= HScreen) return;
    if(num > 10)     return;

    int dat_temp = dat;
    int offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num + 1);


    if(num < 10)
    {
        for(; num > 0; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    GuideChese_DrvFunction(x,y,_ImitScreen.frontcolor,_ImitScreen.backcolor,(Drv_Uchar8Type*)data_buffer);
}

void func_float_to_str (char *str, float number, Drv_Uchar8Type point_bit)
{
    if(str == NULL) return;
    int data_int = 0;
    int data_float = 0.0;
    int data_temp[8];
    int data_temp_point[6];
    Drv_Uchar8Type bit = point_bit;
    data_int = (int)number;
    if(0 > number)
    {
        *str ++ = '-';
    }
    else if(0.0 == number)
    {
        *str ++ = '0';
        *str ++ = '.';
        *str = '0';
        return ;
    }
    number = number - data_int;
    while(bit --)
    {
        number = number * 10;
    }
    data_float = (int)number;
    bit = 0;
    do
    {
        data_temp[bit ++] = data_int % 10;
        data_int /= 10;
    }while(0 != data_int);
    while(0 != bit)
    {
        *str ++ = (func_abs(data_temp[bit - 1]) + 0x30);
        bit --;
    }

    if(point_bit != 0)
    {
        bit = 0;
        *str ++ = '.';
        if(0 == data_float)
        {
            *str = '0';
        }
        else
        {
            while(0 != point_bit)
            {
                data_temp_point[bit ++] = data_float % 10;
                data_float /= 10;
                point_bit --;
            }
            while(0 != bit)
            {
                *str ++ = (func_abs(data_temp_point[bit - 1]) + 0x30);
                bit --;
            }
        }
    }

}



void func_int_to_str (char *str, int number)
{
    if(str == NULL) return;
    unsigned char data_temp[16];                                                        
    unsigned char bit = 0;                                                             
    int number_temp = 0;

    if(0 > number)                                                        
    {
        *str ++ = '-';
        number = -number;
    }
    else if(0 == number)                                                   
    {
        *str = '0';
        return;
    }

    while(0 != number)                                                     
    {
        number_temp = number % 10;
        data_temp[bit ++] = func_abs(number_temp);                        
        number /= 10;                                                     
    }
    while(0 != bit)                                                        
    {
        *str ++ = (data_temp[bit - 1] + 0x30);                             
        bit --;
    }

}


void DisplayInt32Type_DrvFunction(    Drv_Uint16Type x,
                                      Drv_Uint16Type y,
                                      Drv_Uint16Type fc,
                                      Drv_Uint16Type bc,
                                      const int      dat,
                                      Drv_Uchar8Type num)
{
    if(x >= WScreen) return;
    if(y >= HScreen) return;
    if(num > 10)     return;

    int dat_temp = dat;
    int offset = 1;
    char data_buffer[12];
    unsigned char sprt;

    for(sprt = 0; sprt < num + 1; sprt++)
    {
        data_buffer[sprt] = ' ';
    }
    data_buffer[sprt] = 0;

    if(num < 10)
    {
        for(; num > 0; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    GuideChese_DrvFunction(x,y,fc,bc,(Drv_Uchar8Type*)data_buffer);
}

void DisplayFloatType_DrvFunction( Drv_Uint16Type x,  Drv_Uint16Type y,
                                   Drv_Uint16Type fc, Drv_Uint16Type bc,
                                   const float dat,
                                   Drv_Uchar8Type num,
                                   Drv_Uchar8Type pointnum)
{
    if(x >= WScreen)      return;
    if(y >= HScreen)      return;
    if(num > 8)           return;
    if(pointnum > 6)      return;

    float dat_temp = dat;
    float offset = 1.0;
    char data_buffer[17];
    unsigned char sprt;

    for(sprt = 0; sprt < num + pointnum + 1; sprt++)
    {
        data_buffer[sprt] = ' ';
    }
    data_buffer[sprt] = 0;
    if(num < 10)
    {
        for(; num > 0; num --)
        {
            offset *= 10;
        }
        dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    }
    func_float_to_str(data_buffer, dat_temp, pointnum);
    GuideChese_DrvFunction(x,y,fc,bc,(Drv_Uchar8Type*)data_buffer);
}



void ShowLoge_DSPFunction(  const unsigned char *Sprt,
                          Drv_Uint16Type X,
                          Drv_Uint16Type Y,
                          Drv_Uint16Type Width,
                          Drv_Uint16Type Hight)
{
    Drv_Uchar8Type Loge_L, Loge_H;
    Drv_Uint16Type Colour;
    Drv_Uint32Type LoopX;

    SetPosition_ImitateFunc(X, Y, X+Width-1, Y+Hight-1);
    for (LoopX = 0; LoopX < Width * Hight; LoopX++)
    {
        Loge_L=*(Sprt+LoopX*2);
        Loge_H=*(Sprt+LoopX*2+1);
        Colour = Loge_H << 8 | Loge_L;
        WritePixel_ImitateFunc(Colour);
    }
}

void ShowImage_DrvFunction(const unsigned short *Sprt,
                            Drv_Uint16Type X,
                            Drv_Uint16Type Y,
                            Drv_Uint16Type Width,
                            Drv_Uint16Type Hight)
{

    Drv_Uint32Type LoopX;
    SetPosition_ImitateFunc(X, Y, X+Width-1, Y+Hight-1);
    for (LoopX = 0; LoopX < Width * Hight; LoopX++)
    {
        WritePixel_ImitateFunc(*Sprt);
        Sprt++;
    }
}

void ShowSquare_DrvFunction(const unsigned char *Sprt,
                            Drv_Uint16Type X,
                            Drv_Uint16Type Y,
                            Drv_Uint16Type fc,
                            Drv_Uint16Type bc,
                            Drv_Uint16Type Width,
                            Drv_Uint16Type Hight)
{
    Drv_Uint32Type LoopX,looptr;
    SetPosition_ImitateFunc(X, Y, X+Width-1, Y+Hight-1);
    for (LoopX = 0; LoopX <= (Width*Hight/8); LoopX++)
    {
        for(looptr = 0; looptr < 8; looptr++)
        {
            if((*Sprt << looptr)&0x80)
            {
                WritePixel_ImitateFunc(bc);
            }
            else
            {
                WritePixel_ImitateFunc(fc);
            }
        }
        Sprt++;
    }
}


