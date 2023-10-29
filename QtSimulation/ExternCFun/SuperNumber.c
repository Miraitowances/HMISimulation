

#include "SuperNumber.h"

#define VETSION "V1.01.001.20200926"

#define 		BC			0x0000
#define 		FC			0X67FC

uint8_t InitialSuperNum(sSuperNum *pSuperNum,uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t oft)
{

#define SET_SEG_PARAM(n,X,Y,w,h,cnt) \
	pSuperNum->SegPara[n].timercount = cnt;\
	pSuperNum->SegPara[n].X_pos = X;\
	pSuperNum->SegPara[n].Y_pos = Y;\
	pSuperNum->SegPara[n].with  = w;\
	pSuperNum->SegPara[n].heigh = h


	if(pSuperNum == 0) return 0;


	pSuperNum->X_pos   = x;      //数字显示整体X坐标
	pSuperNum->Y_pos   = y;      //数字显示整体Y坐标
	pSuperNum->width   = w;      //段宽度
	pSuperNum->Height  = h;      //段高度
	pSuperNum->oft     = oft;    //段之间的相对偏移
	pSuperNum->staNow  = 10;     //初始化为无图片


		/**					1
	 *             --------------------
	 * 			   |				  |
	 * 			   |				  |
	 * 			   |2				  |	3
	 * 			   |				  |
	 * 			   |		4		  | 
	 *             --------------------
	 * 			   |				  |
	 * 			   |				  |
	 * 			   |5				  |	6
	 * 			   |				  |
	 * 			   |		7		  | 
	 *             --------------------
	 */


	SET_SEG_PARAM(0,x + oft      ,y            ,w        ,h + 2*oft,0);
	SET_SEG_PARAM(1,x            ,y + oft      ,w + 2*oft,h        ,0);
	SET_SEG_PARAM(2,x + w + 2*oft,y + oft      ,w + 2*oft,h        ,0);
	SET_SEG_PARAM(3,x + oft      ,y + h + 2*oft,w        ,h + 2*oft,0);
	SET_SEG_PARAM(4,x            ,y + h + 3*oft,w + 2*oft,h        ,0);
	SET_SEG_PARAM(5,x + w + 2*oft,y + h + 3*oft,w + 2*oft,h        ,0);
	SET_SEG_PARAM(6,x + oft      ,y +2*h +4*oft,w        ,h + 2*oft,0);


#undef SET_SEG_PARAM
	return 1;
}

/*************************************************************************
 ** Function Name:	InitialSegShowAction		                               
 ** Purpose:		initial SuperNumber segment Show Action Map			   		        
 ** Params:															                              
 **	@ pSuperNum:	pSuperNum object pointer.					                   
 **	@ pSegAction:	segment Show Action Map			                                        			 
 ** Return:		False or True							  	 
 ** Notice:	  None.												 
 ** Author:		公众号:最后一个bug											 
 *************************************************************************/
uint8_t InitialSegShowAction(sSuperNum *pSuperNum,uint8_t *pSegAction)
{

#define SET_ACTION(now,next,seg0,seg1,seg2,seg3,seg4,seg5,seg6) \
	pSeg[now][next][0] = seg0;\
	pSeg[now][next][1] = seg1;\
	pSeg[now][next][2] = seg2;\
	pSeg[now][next][3] = seg3;\
	pSeg[now][next][4] = seg4;\
	pSeg[now][next][5] = seg5;\
	pSeg[now][next][6] = seg6;

  uint8_t i= 0, j = 0,k = 0;

	uint8_t (*pSeg)[MAX_SEG_STATUE][SEG_NUM] = (uint8_t (*)[MAX_SEG_STATUE][SEG_NUM])pSegAction;

	if(pSegAction == 0) return 0;
	if(pSuperNum == 0) return 0;


	//首选初始化状态查询库，均为无处理状态
	for(i = 0 ;i < MAX_SEG_STATUE;i++)
	{
		for(j = 0; j< MAX_SEG_STATUE;j++)
		{
			for(k = 0; k< SEG_NUM;k++)
			{
			  pSeg[i][j][k] = 0; //无动作
			}
		}
	}
/*
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
*/

	//定义具体的每段动作 
	//从无到有
	// ----------------
	//
	/**						1
	 *             --------------------
	 * 			   |				  |
	 * 			   |				  |
	 * 			   |2				  |	3
	 * 			   |				  |
	 * 			   |		4		  | 
	 *             --------------------
	 * 			   |				  |
	 * 			   |				  |
	 * 			   |5				  |	6
	 * 			   |				  |
	 * 			   |		7		  | 
	 *             --------------------
	 */


	//________________1,2,3,4,5,6,7-------
	SET_ACTION(10,0,  3,7,5,0,5,7,1); 
	SET_ACTION(10,1,  0,0,7,0,0,5,0); 
	SET_ACTION(10,2,  3,0,5,3,5,0,3); 
	SET_ACTION(10,3,  3,0,5,3,0,5,3); 
	SET_ACTION(10,4,  0,5,5,3,0,5,0); 
	SET_ACTION(10,5,  3,5,0,3,0,5,3); 
	SET_ACTION(10,6,  3,5,0,3,5,5,3); 
	SET_ACTION(10,7,  3,0,5,0,0,5,0); 
	SET_ACTION(10,8,  3,5,5,3,5,5,3); 
	SET_ACTION(10,9,  3,5,5,3,0,5,3); 

	//数字切换
	//SET_ACTION(0,0,  3,7,5,0,5,7,1); 
    SET_ACTION(0,1,  2,9,0,2,9,0,2);
	SET_ACTION(1,2,  3,0,0,3,0,11,3);
	SET_ACTION(2,3,  0,0,0,0,9,0,0);
	SET_ACTION(3,4,  4,5,0,0,9,0,2);
	SET_ACTION(4,5,  3,0,8,0,0,0,3);
	SET_ACTION(5,6,  0,0,0,0,5,0,0);
	SET_ACTION(6,7,  0,9,0,2,9,0,2);
	SET_ACTION(7,8,  0,0,12,3,0,12,3);
	SET_ACTION(8,9,  0,0,0,0,6,0,0);
	SET_ACTION(9,0,  0,0,0,4,5,0,0);

	SET_ACTION(10,11,  0,17,0,0,17,0,0);  
	SET_ACTION(11,10,  0,18,0,0,18,0,0);

	SET_ACTION(5,0,  0,0,7,4,5,0,0);  //加入6到0
	SET_ACTION(2,0,  0,0,12,2,0,5,0);  //加入2到0  //到了23点需要切到0点
	SET_ACTION(3,0,  0,5,0,4,5,0,0);  //加入3到0

#undef SET_ACTION
	return 1;
}

/*************************************************************************
 ** Function Name:	SuperNumActionPlay		                               
 ** Purpose:	 SuperNumber Action play show		   		        
 ** Params:															                              
 **	@ pSuperNum:	pSuperNum object pointer.					                   
 **	@ pSegAction:	segment Show Action Map			
 **	@ staNext:	next need play dynamic statue	
 ** Return:		False or True							  	 
 ** Notice:	  None.												 
 ** Author:		公众号:最后一个bug											 
 *************************************************************************/
uint8_t SuperNumActionPlay(sSuperNum *pSuperNum,uint8_t *pSegAction,uint8_t staNext)
{
	uint8_t segIndex = 0;
	uint8_t SegFinishCnt = 0;

	if(pSuperNum->staNow  == staNext)return 0;
	if(pSuperNum == 0)return 0;
	if(pSegAction == 0)return 0;

	SegFinishCnt = 0;
	for(segIndex = 0 ;segIndex < SEG_NUM;segIndex++)
	{
		if(SegmentShow(pSuperNum,pSegAction,segIndex,pSuperNum->staNow ,staNext) == 1)
		{
			SegFinishCnt++;
		}
	}
	if(SegFinishCnt == SEG_NUM)
	{
		//表示所有段都已经完成
		RsetAllSegmentCnt(pSuperNum);
		pSuperNum->staNow = staNext;
		return 1; //返回成功
	}
	return 0;
}

/*************************************************************************
 ** Function Name:	SegmentShow		                               
 ** Purpose:	 every segment play show   		        
 ** Params:															                              
 **	@ pSuperNum:	pSuperNum object pointer.					                   
 **	@ pSegAction:	segment Show Action Map	
 **	@ segIndex:	 segment Index
 **	@ staNext:	next need play dynamic statue	
 ** Return:		False or True							  	 
 ** Notice:	  None.												 
 ** Author:		公众号:最后一个bug											 
 *************************************************************************/
uint8_t SegmentShow(sSuperNum *pSuperNum,uint8_t *pSegAction,uint8_t segIndex,uint8_t staNow,uint8_t staNext)
{
	uint16_t startPos = pSuperNum->SegPara[segIndex].X_pos;  //起点位置
	uint16_t endPos   = pSuperNum->SegPara[segIndex].Y_pos;  //终点位置
	uint16_t with     = pSuperNum->SegPara[segIndex].with;  //起点长度
	uint16_t heigh    = pSuperNum->SegPara[segIndex].heigh;  //终点长度

	uint8_t ActionType = 0;
  int i = 0;
/*
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
*/

	uint8_t (*pSeg)[MAX_SEG_STATUE][SEG_NUM] = (uint8_t (*)[MAX_SEG_STATUE][SEG_NUM])pSegAction;
  // ActionType = SegAction[staNow][staNext][segIndex];
   ActionType = pSeg[staNow][staNext][segIndex];
	
	switch(ActionType)
	{
	case HOLD_NOW: //如果没有变换直接return即可
		  return 1;
		break;
	case RIGHT_SHOW: 

		pSuperNum->pDrawPoint(startPos + pSuperNum->SegPara[segIndex].timercount,endPos,FC);
		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}
		break;
	case RIGHT_LOSS: 

		pSuperNum->pDrawPoint(startPos + pSuperNum->SegPara[segIndex].timercount,endPos,BC);
		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}
		break;
	case LEFT_SHOW:

		pSuperNum->pDrawPoint(startPos + with - pSuperNum->SegPara[segIndex].timercount,endPos,FC);
		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}
		break;
	case LEFT_LOSS: 

		pSuperNum->pDrawPoint(startPos + with - (pSuperNum->SegPara[segIndex].timercount),endPos,BC);
		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}
		break;	
	case DOWN_SHOW: 

		pSuperNum->pDrawPoint(startPos ,endPos+ pSuperNum->SegPara[segIndex].timercount,FC);
		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}
		break;	
	case DOWN_LOSS:

		pSuperNum->pDrawPoint(startPos ,endPos + pSuperNum->SegPara[segIndex].timercount,BC);

		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}
		break;
	case UP_SHOW:

		pSuperNum->pDrawPoint(startPos ,endPos + heigh - pSuperNum->SegPara[segIndex].timercount,FC);

		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}
		break;
	case UP_LOSS:

		pSuperNum->pDrawPoint(startPos ,endPos + heigh - pSuperNum->SegPara[segIndex].timercount,BC);

		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount +=1;
		}
		else 
		{
			return 1;
		}

		break;
	case RIGHT_MOV:

		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}

		for(i = 0; i<=heigh;i++)
			pSuperNum->pDrawPoint(startPos + pSuperNum->SegPara[segIndex].timercount-1,endPos + i,BC);
		for(i = 0; i<=heigh;i++)
			pSuperNum->pDrawPoint(startPos + pSuperNum->SegPara[segIndex].timercount,endPos + i,FC);

		break;
	case RIGHT_MOV_R:

		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}

		if(pSuperNum->SegPara[segIndex].timercount != 1)
		{
			for(i = 0; i <= heigh;i++)
				pSuperNum->pDrawPoint(startPos + pSuperNum->SegPara[segIndex].timercount-1,endPos + i,BC);
		}

		for( i = 0; i <= heigh;i++)
			pSuperNum->pDrawPoint(startPos + pSuperNum->SegPara[segIndex].timercount,endPos + i,FC);

		break;
	case LEFT_MOV:

		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}

		for( i = 0; i<=heigh;i++)
			pSuperNum->pDrawPoint(startPos - (pSuperNum->SegPara[segIndex].timercount-1),endPos + i,BC);

		for( i = 0; i<=heigh;i++)
			pSuperNum->pDrawPoint(startPos - pSuperNum->SegPara[segIndex].timercount,endPos + i,FC);

		break;
	case LEFT_MOV_R:

		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}

		if(pSuperNum->SegPara[segIndex].timercount != 1)
		{
			for( i = 0; i<=heigh;i++)
				pSuperNum->pDrawPoint(startPos - (pSuperNum->SegPara[segIndex].timercount-1),endPos + i,BC);
		}

		for( i = 0; i<=heigh;i++)
			pSuperNum->pDrawPoint(startPos - pSuperNum->SegPara[segIndex].timercount,endPos + i,FC);

		break;
	case DOWN_MOV:

		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}

		for( i = 0; i<with;i++)
			pSuperNum->pDrawPoint(startPos + i ,endPos + pSuperNum->SegPara[segIndex].timercount - 1,BC);

		for( i = 0; i<with;i++)
			pSuperNum->pDrawPoint(startPos + i ,endPos + pSuperNum->SegPara[segIndex].timercount,FC);

		break;
	case DOWN_MOV_R:

		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}
		if(pSuperNum->SegPara[segIndex].timercount != 1)
		{
			for( i = 0; i<with;i++)
				pSuperNum->pDrawPoint(startPos + i ,endPos + pSuperNum->SegPara[segIndex].timercount - 1,BC);
		}

		for( i = 0; i<with;i++)
			pSuperNum->pDrawPoint(startPos + i ,endPos + pSuperNum->SegPara[segIndex].timercount,FC);

		break;
	case UP_MOV:

		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}

		for( i = 0; i < with;i++)
			pSuperNum->pDrawPoint(startPos + i ,endPos  -(pSuperNum->SegPara[segIndex].timercount - 1),BC);

		for( i = 0; i < with;i++)
			pSuperNum->pDrawPoint(startPos + i ,endPos  - pSuperNum->SegPara[segIndex].timercount,FC);

		break;
	case UP_MOV_R:

		if(pSuperNum->SegPara[segIndex].timercount < heigh)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}
		if(pSuperNum->SegPara[segIndex].timercount != 1)
		{
			for( i = 0; i < with;i++)
				pSuperNum->pDrawPoint(startPos + i ,endPos  -(pSuperNum->SegPara[segIndex].timercount - 1),BC);
		}
		for( i = 0; i < with;i++)
			pSuperNum->pDrawPoint(startPos + i ,endPos  - pSuperNum->SegPara[segIndex].timercount,FC);

		break;
	case RIGHT_ALL_SHOW:

		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}
		for( i = 0; i<=heigh/2;i++)
			pSuperNum->pDrawPoint(startPos + pSuperNum->SegPara[segIndex].timercount,endPos +heigh/3+ i,FC);



		break;
	case RIGHT_ALL_LOSS:

		for( i = 0; i<=heigh/2;i++)
			pSuperNum->pDrawPoint(startPos + with - pSuperNum->SegPara[segIndex].timercount,endPos +heigh/3 + i,BC);

		if(pSuperNum->SegPara[segIndex].timercount < with)
		{
			pSuperNum->SegPara[segIndex].timercount += 1;
		}
		else
		{
			return 1;
		}
		break;
	default:
		return 1 ;
		break;
	}

	return 0;
}

/*************************************************************************
 ** Function Name:	RsetSegmentCnt		                               
 ** Purpose:	 reset every segment count 		        
 ** Params:															                              
 **	@ pSuperNum:	pSuperNum object pointer.					                   
 **	@ segNum:	 segment Index
 ** Return:		False or True							  	 
 ** Notice:	  None.												 
 ** Author:		公众号:最后一个bug											 
 *************************************************************************/
void RsetSegmentCnt(sSuperNum *pSuperNum,uint8_t segIndex)
{
	pSuperNum->SegPara[segIndex].timercount = 0;
}

/*************************************************************************
 ** Function Name:	RsetAllSegmentCnt		                               
 ** Purpose:	 reset all segment count 		        
 ** Params:															                              
 **	@ pSuperNum:	pSuperNum object pointer.					                   
 ** Return:		void				  	 
 ** Notice:	  None.												 
 ** Author:		公众号:最后一个bug											 
 *************************************************************************/
void RsetAllSegmentCnt(sSuperNum *pSuperNum)
{
	int i = 0;
	for( i = 0 ;i < SEG_NUM;i++)
		pSuperNum->SegPara[i].timercount = 0;
}


