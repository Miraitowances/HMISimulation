/************************************************************************* 
 ** Copyright.											 
 ** FileName: SuperNumber.h								 
 ** Author: 公众号:最后一个bug
 ** Data:2020-09-26 
 ** Description: dynamic Segment Show	 
 *************************************************************************/
#ifndef __SUPER_NUMBER_H__
#define __SUPER_NUMBER_H__

typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
//=======================================================================
// User Macro definition.								
//=======================================================================
//定义每个段运动的状态
#define HOLD_NOW      (0)
#define RIGHT_SHOW    (1)
#define RIGHT_LOSS    (2)
#define LEFT_SHOW     (3)
#define LEFT_LOSS     (4)
#define DOWN_SHOW     (5)
#define DOWN_LOSS     (6)
#define UP_SHOW       (7)
#define UP_LOSS       (8)
#define RIGHT_MOV     (9)
#define RIGHT_MOV_R   (10)
#define LEFT_MOV      (11)
#define LEFT_MOV_R    (12)
#define DOWN_MOV      (13)
#define DOWN_MOV_R    (14)
#define UP_MOV        (15)
#define UP_MOV_R      (16)
#define RIGHT_ALL_SHOW    (17)
#define RIGHT_ALL_LOSS    (18)
#define NO_SHOW       (19)


//目前的数字所有状态
#define NUM_0 (0)
#define NUM_1 (1)
#define NUM_2 (2)
#define NUM_3 (3)
#define NUM_4 (4)
#define NUM_5 (5)
#define NUM_6 (6)
#define NUM_7 (7)
#define NUM_8 (8)
#define NUM_9 (9)
#define NUM_NO (10)
#define NUM_POINT (11)
#define NUM_MAX (12)


//参数设置
#define SEG_NUM        (7)    //一个数码显示为7段
#define MAX_SEG_STATUE (NUM_MAX)   //目前定义10中状态0,1,2,3.....9,10(无显示)


//每个段的信息
typedef struct _tag_SegPara
{
	uint16_t X_pos;
	uint16_t Y_pos;  
	uint16_t with;
	uint16_t heigh;
	uint16_t timercount; //时基统计
}sSegPara;

//一个超级数据的信息
typedef struct _tag_SuperNum
{
	uint16_t X_pos;     //数字显示整体X坐标
	uint16_t Y_pos;     //数字显示整体Y坐标
    uint16_t width;     //段宽度
	uint16_t Height;    //段高度
	uint8_t  oft;       //段之间的相对偏移
	uint8_t  staNow;    //表示当前的状态
    sSegPara SegPara[SEG_NUM];//每个段的位置信息
    void (*pDrawPoint)(int iPosX, int iPosY, int iColor); //画点函数--再外面更新
}sSuperNum; //超级动态数字


//=======================================================================
//Public function declaration.							
//=======================================================================
uint8_t InitialSuperNum(sSuperNum *pSuperNum,uint16_t xp,uint16_t yp,uint16_t w,uint16_t h,uint16_t oft);
uint8_t InitialSegShowAction(sSuperNum *pSuperNum,uint8_t *pSegAction);

uint8_t SuperNumActionPlay(sSuperNum *pSuperNum,uint8_t *pSegAction,uint8_t staNext);

void sDrawPoint(uint16_t PointX,uint16_t PointY,uint8_t color);
uint8_t SegmentShow(sSuperNum *pSuperNum,uint8_t *pSegAction,uint8_t segIndex,uint8_t staNow,uint8_t staNext);

void RsetSegmentCnt(sSuperNum *pSuperNum,uint8_t segIndex);
void RsetAllSegmentCnt(sSuperNum *pSuperNum);


#endif
