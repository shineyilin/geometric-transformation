
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int		SY_InitAllButton();            //��ʼ�� ���еİ�ť
int		SY_ShowAxis(int cx=0, int cy=0, float size=1 );  // ��ʾ������
int		SY_ShowButton(button bbut, int state ); // ��ʾ��ť   state =1 ���� state =0
int 	SY_ShowLine(pline *top);    //��ʾ�߶�      ջ��
int 	SY_DrawLine( int x, int y  );  //�����߶�  x��y �������
int 	SY_DrawMove( mouse_msg event );  //�ƶ�������
int		SY_ClearWindow( void );    //��� ����
int 	SY_History();
int		SY_Undo();
int 	SY_Redo();
int	 	SY_InitWindow (int w, int h);  //��ʼ�� ����
void	SY_GetWindowPoint( mouse_msg event );    //�������λ�û�ȡ��
void 	SY_GetKeyPoint(mouse_msg event);       // �Ӽ����л�ȡ��
bool 	SY_ButtonClickCheek( button bbut, mouse_msg event );  // ��갴�����¼��
pline 	*SY_Rote (pline *top, point center_p, float angle); // ��ת�������

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int	SY_InitWindow (int w, int h)   // ��ʼ����
{
  setinitmode (0);                 	 //initialize
  initgraph (w,h);
  setcaption ("drawing.1");         	//set title
  setbkcolor (BLUE);       		  	//set background color
  setfont(20,0,"����");
  setbkmode(TRANSPARENT);
  TOP->next=NULL;
  SY_InitAllButton();
  SY_ShowAxis();
  return 0;
}
int	SY_ClearWindow ( void )  //��� �������е� ����  ���»���������  ����
{
  cleardevice();
  SY_ShowAxis();
  for ( int i=0; i<4; i++ )
    {
      SY_ShowButton(B_button[i],0);
    }
  return 0;
}
int	SY_InitAllButton()  // ��ʼ�� ˵�е� ��ť
{
  B_button[0].name=" ���� ";
  B_button[1].name="���ĵ�";
  B_button[2].name="��ת��";
  B_button[3].name=" ��� ";
  for ( int i=0; i<4; i++ )
    {
      B_button[i].bx =500;
      B_button[i].by =50*(i+1);
      SY_ShowButton(B_button[i],0);
    }
  return 0;
}
void 	SY_GetKeyPoint(mouse_msg event)
{
	double px;
	double py;
	if ( event.is_down() )// if mouse is down do the follow things
	{
		for ( int i=0; i<4; i++ ) //cheek button
		{
			if ( SY_ButtonClickCheek(B_button[i],event) )
			{
				switch (i)
				{
					case 0:  //�˵�
						px=getDouble();
						py=getDouble();
						SY_DrawLine(px,py);
						break;
					case 1:  //���ĵ�
						CENTER.x=getDouble();
						CENTER.y=getDouble();
						break;
					case 2:  //�Ƕ�
						ANGEL=getDouble();
						char buff[15];
						circle ( 	CENTER.x+MCCODX,MCCODY-CENTER.y,4 );
						sprintf(buff, "(%.2f,%.2f)",CENTER.x+MCCODX,MCCODY-CENTER.y);
						outtextxy(MCCODX+int(CENTER.x), MCCODY-int(CENTER.x),buff);
						SY_ShowLine(SY_Rote(TOP,CENTER,ANGEL));
						break;
					case 3:  //���
					SY_ClearWindow();
					TOP->next=NULL;
					FLAG=0;
					ANGEL=0;
					CENTER={0,0};
						break;
					default:
						break;
				}
				break;
			}
		}// end of for
	}
}
void	SY_GetWindowPoint( mouse_msg event )
{
	if ( event.is_down() )// if mouse is down do the follow things
	{
		SY_DrawMove(event);//
		if ( event.is_left() )// �˵�
		{
			if ( event.x>DRW[0] && event.x<DRW[2] && event.y>DRW[1] && event.y<DRW[3] )  //in draw  window
			SY_DrawLine ( event.x -MCCODX,MCCODY-event.y );
		}
		if ( event.is_right() ) //���ĵ�
		{
			CENTER.x=event.x-MCCODX;
			CENTER.y=MCCODY-event.y;
			ANGEL=0;
			setcolor(RED);
			circle(event.x,event.y,4);
		}
	}
	 if ( event.is_wheel() ) //���ĵ�   ��ת�Ƕ�    ִ����ת
	 {
		 ANGEL=ANGEL+event.wheel/120;
		 SY_ClearWindow();
		 SY_ShowAxis();
		 char buff[15];
		 circle ( 	CENTER.x+MCCODX,MCCODY-CENTER.y,4 );
		 sprintf(buff, "(%.2f,%.2f)",CENTER.x,CENTER.y);
		 outtextxy(MCCODX+int(CENTER.x), MCCODY-int(CENTER.x),buff);
		 SY_ShowLine(SY_Rote(TOP,CENTER,ANGEL));
	 }

}
int SY_ShowLine(pline *top)  //��ʾ�߶�
{
	if ( !top->next )// ���ָ�����
	{
		return 0;
	}
	top=top->next;
	point pb=top->p2;
	point pe;
	char buff[14] ={};
	setbkmode(TRANSPARENT);
	while (top)
	{
		if ( top->label != '0' )
		{
			sprintf(buff, "(%.2f,%.2f)", top->p2.x,top->p2.y);
			outtextxy(int(top->p2.x)+MCCODX,MCCODY-int(top->p2.y),buff);
			pe=top->p1;
		}
		line( MCCODX+int(top->p1.x), MCCODY-int(top->p1.y),MCCODX+int(top->p2.x), MCCODY-int(top->p2.y));
		top=top->next;
	}
	line( MCCODX+int(pb.x), MCCODY-int(pb.y),MCCODX+int(pe.x), MCCODY-int(pe.y));
	float xbf=pe.x,ybf=pe.y;
	sprintf(buff, "(%.2f,%.2f)", xbf,ybf);
	outtextxy(MCCODX+int(xbf), MCCODY-int(ybf),buff);
	return 0;
}
int	SY_ShowAxis(int dx,int dy,float size) //��������ʾ  dx dy λ�Ʋ�����
{
	setcolor(WHITE);
	MCCODX=MCCODX+dx;
	MCCODY=MCCODY+dy;
	rectangle(40,40,460,560);
	if ( MCCODX>DRW[0] && MCCODX<DRW[2] )
	{
		line(MCCODX,DRW[1],MCCODX,DRW[3]);//V
		outtextxy(MCCODX,DRW[1]," y");
	}
	if (  MCCODY>DRW[1] && MCCODY<DRW[3] )
	{
		line(DRW[0],MCCODY,DRW[2],MCCODY);//H
		outtextxy(DRW[2]-20,MCCODY,"x");
	}
	return 0;
}
int	SY_ShowButton(button bbut,int state) //��ť��ʾ
{
  int pcx;
  int pcy;
  pcx=bbut.bx;
  pcy=bbut.by;
  if ( state == 0)
  {
      setfillcolor(BLUE);
      bar (pcx,pcy,pcx+60,pcy+22);
      setcolor(YELLOW);
      rectangle(pcx,pcy,pcx+60,pcy+22);
      setcolor(GREEN);
      outtextxy(pcx,pcy,bbut.name);
  }
  if ( state == 1 )/// ���� ��ʾ
  {
	  setfillcolor(LIGHTGRAY);
	  bar (pcx,pcy,pcx+60,pcy+22);
	  setcolor(YELLOW);
	  rectangle(pcx,pcy,pcx+60,pcy+22);
	  setcolor(GREEN);
	  outtextxy(pcx,pcy,bbut.name);
  }
	return 0;
}
int SY_DrawLine( int x, int y )  //�߶�����  ��������  ȫ �� ���� TOP ѹջ
 {
	static point befp;
	static int i = 1;
	char *txt = new char;
	point p;
	p.x = x;
	p.y = y;
	setcolor(YELLOW);
	circle(p.x+MCCODX,MCCODY-p.y,3);
	sprintf(txt,"%d",i++);
	if ( FLAG == 0  )
	{	befp = p;
		outtextxy(p.x + MCCODX, MCCODY - p.y, "START");
		i=1;
		TOP->next = NULL;
		FLAG = 1;
		return 0;
	}
	pline *newline = new pline;
	newline->p1 = befp;
	newline->label = *txt;
	outtextxy(p.x+MCCODX,MCCODY-p.y,txt);
	befp = p;
	newline->p2 = p;
	newline->next=TOP->next;
	TOP->next=newline;
	line( MCCODX+int(newline->p1.x), MCCODY-int(newline->p1.y),MCCODX+int(newline->p2.x), MCCODY-int(newline->p2.y));
	return 0;
}
int SY_DrawMove(mouse_msg event)  //�߶� ���� ���ƶ�
{
	point mousep;
	if ( !event.is_left() && !event.is_right() )
	{
		if ( event.x>DRW[0] && event.x<DRW[2] && event.y>DRW[1] && event.y<DRW[3] )//if mouse is in draw window
		{
			mousep.x= event.x;
			mousep.y= event.y;
			event=getmouse();
			while(event.is_move())// �м����  �ƶ��¼�   ȷ���������ĵ�λ��
			{
				SY_ClearWindow();
				SY_ShowAxis( (int(event.x)-int(mousep.x) ), (int(event.y)-int(mousep.y) ) );
				SY_ShowLine(TOP);
				mousep.x= event.x;
				mousep.y= event.y;
				event=getmouse();
  			}
			SY_ClearWindow();
			SY_ShowAxis();
			SY_ShowLine(TOP);
		}
	}
	return 0;
}
bool SY_ButtonClickCheek(button bbut,mouse_msg event)  //�����¼����
{
	if ( event.is_left() )
	{
		if( event.x>bbut.bx && event.x<bbut.bx+60 && event.y>bbut.by && event.y<bbut.by+22 )
		{
			SY_ShowButton(bbut,1);
			while ( !event.is_up() )//�ȴ� ��� ����
			{
				event=getmouse();
			}
			SY_ShowButton(bbut,0);
			return true;
		}
	}
	return false;
}
pline *SY_Rote (pline *top, point center_p, float angle)// ������ͷ  ���� ����  ��ת�Ƕ�  return ��ת��������ͷ ԭʼ����
{
 	top=top->next;
	pline *head;
	pline *newline;
	pline *linebuff;
	
	head       = new pline;    //head
	newline    = new pline; //new line
	linebuff   = new pline;// new line buff
	head->next = newline;
	while(top)
	{
		newline->p1.x=cos(angle*PI/180)*top->p1.x+(-sin(angle*PI/180)*top->p1.y)-center_p.x*cos(angle*PI/180)+
				center_p.y*sin(angle*PI/180)+center_p.x;
		newline->p1.y=sin(angle*PI/180)*top->p1.x+cos(angle*PI/180)*top->p1.y-center_p.x*sin(angle*PI/180)-
				center_p.y*cos(angle*PI/180)+center_p.y;
		newline->p2.x=cos(angle*PI/180)*top->p2.x+(-sin(angle*PI/180)*top->p2.y)-center_p.x*cos(angle*PI/180)+
				center_p.y*sin(angle*PI/180)+center_p.x;
		newline->p2.y=sin(angle*PI/180)*top->p2.x+cos(angle*PI/180)*top->p2.y-center_p.x*sin(angle*PI/180)-
				center_p.y*cos(angle*PI/180)+center_p.y;
		newline->label=top->label;
		newline->next=linebuff;
		newline=linebuff;
		linebuff=new pline;
		linebuff->next=NULL;
		top=top->next;
	}
	newline->label='0';// void pointer label
	return head;
}
