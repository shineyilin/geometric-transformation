/*
 * main.cpp
 *
 *  Created on: 2015��11��27��
 *      Author: YLG
 *	������ �˵�  �Ҽ���� ���ĵ� ������ת�Ƕ�  �м� ���ƶ� �� λ������
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
const int W =600; //���ڵĴ�С
const int H =600;
//const char author[]={"YLG"}; //help
const int DRW[]={40, 40, 460, 560, 250, 300};//draw start1 window size {0x1, 1y1, 2x2, 3y2, 4cx1, 5cx2}
button B_button[4]; //button 1 point , button 2 center ,button 3 angle, button 4 clear
pline  *TOP=new pline;  // ������� ��ͷ
int FLAG=0; 		//ȫ�ֱ�־λ  =0 ���¿�ʼ�����������
int MCCODX=DRW[4];  //���������ڴ����е�λ��
int MCCODY=DRW[5];  //
double ANGEL=0;  //��ת�Ƕ�
point CENTER;   //��ת����
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "source.cpp"
int main ()
{
  mouse_msg event;
  SY_InitWindow(W,H);
  for ( ; is_run(); delay_fps(60))  //��ѭ��
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
