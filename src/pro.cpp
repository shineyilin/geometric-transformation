/*
 * main.cpp
 *
 *  Created on: 2015年11月27日
 *      Author: YLG
 *	左键添加 端点  右键添加 中心点 滚轮旋转角度  中键 标移动 和 位置置零
 */
#include <graphics.h>
#include <ege.h>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define PI 3.141593
typedef struct  //point
{
  float x;
  float y;
  int label;
}point;
typedef struct pline
{
  point p1;
  point p2;
  pline *next;
  char label;
}pline;
typedef struct button
{
  int bx;		//left
  int by;		//top
  int label;
  color_t color;
  char* name;
}button;
const int W =600; //窗口的大小
const int H =600;
//const char author[]={"YLG"}; //help
const int DRW[]={40, 40, 460, 560, 250, 300};//draw start1 window size {0x1, 1y1, 2x2, 3y2, 4cx1, 5cx2}
button B_button[4]; //button 1 point , button 2 center ,button 3 angle, button 4 clear
pline  *TOP=new pline;  // 点输入的 表头
int FLAG=0; 		//全局标志位  =0 从新开始点的坐标输入
int MCCODX=DRW[4];  //坐标中新在窗口中的位置
int MCCODY=DRW[5];  //
double ANGEL=0;  //旋转角度
point CENTER;   //旋转中心
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "source.cpp"
int main ()
{
  mouse_msg event;
  SY_InitWindow(W,H);
  for ( ; is_run(); delay_fps(60))  //主循环
    {
		 while (mousemsg())
		{
			 event=getmouse();
			 SY_GetWindowPoint(event);  //model 1  get point from mouse
			 SY_GetKeyPoint(event);     //model 2  get point from keyboard
		}
    }
  return 0;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
