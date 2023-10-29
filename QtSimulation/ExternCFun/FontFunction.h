

#ifndef __FontFunction_H_
#define __FontFunction_H_


#define             CharactersNumber            114

typedef struct CheseHZ
{
    #ifdef GB2312Mode
        const unsigned char Guide[2];
    #else
        const unsigned char Guide[3];
    #endif
    const unsigned char Code[32];
}__CharactersTypeDef;

extern const __CharactersTypeDef Characters[CharactersNumber];
extern const unsigned char ascii_font_8x16[][16];
extern const unsigned short loge[17280];
extern const unsigned short ws[100][100];
extern const unsigned char LOGO1[35370];
extern const unsigned short myloge[18225];
extern const unsigned char RSquare[93];
#endif


