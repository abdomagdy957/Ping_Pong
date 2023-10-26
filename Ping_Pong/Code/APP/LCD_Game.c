#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "LCD_Game.h"
#include "DIO.h"
#include "LCD_Interface.h"


#define  F_CPU	8000000
#include <util/delay.h>
/*************************Variables*************************/
u8 p1_Xpos = 2;
u8 p1_Ypos = 0;
u8 p2_Xpos = 2;
u8 p2_Ypos = 19;

u8 ball_Xpos = 2;
u8 ball_Ypos =10;

u8 p1_score = 0;
u8 p2_score = 0;
u8 flag=0;
/*************************Patterns*************************/
const u8 Player_Pattern[8] = {0x04, 0x0A, 0x04, 0x0E, 0x15, 0x04, 0x0A, 0x11};
const u8 Ball_Pattern[8] = {0x00, 0x0E, 0x1F, 0x1B, 0x1F, 0x0E, 0x00, 0x00};

void game_Init(void)
{
	/*initialization*/
	p1_score=0;
	p2_score=0;
	p1_Xpos = 2;
	p1_Ypos = 0;
	p2_Xpos = 2;
	p2_Ypos = 19;
	ball_Xpos = 2;
	ball_Ypos =10;
	/*************/
	LCD_Clear();
	LCD_GoTo(0,1);
	LCD_WriteString("Welcome to my game.");
	LCD_WriteString_GoTo(1,4,"Ping Pong!");
	_delay_ms(2000);
	LCD_Clear();
	
	/*display score*/
	LCD_GoTo(0,0);
	LCD_WriteString("P1: 0");
	LCD_GoTo(0,13);
	LCD_WriteString("P2: 0");
	
	/*draw player 1*/
	LCD_CustomChar(0,Player_Pattern);
	LCD_GoTo(p1_Xpos,p1_Ypos);
	LCD_WriteChar(0);
	
	/*draw player 2*/
	LCD_CustomChar(0,Player_Pattern);
	LCD_GoTo(p2_Xpos,p2_Ypos);
	LCD_WriteChar(0);
	
	/* draw ball */
	draw_Ball();
}
void movePlayers(void)
{
	//move technique for player1
	if(DIO_ReadPin(P1_UP)==LOW)
	{
		_delay_ms(30);
		if(p1_Xpos>1)
		{
			LCD_Clear_Position(p1_Xpos,p1_Ypos,1);
			p1_Xpos--;
			LCD_CustomChar(0,Player_Pattern);
			LCD_GoTo(p1_Xpos,p1_Ypos);
			LCD_WriteChar(0);
		}
		while(DIO_ReadPin(P1_UP)==LOW);
	}
	if(DIO_ReadPin(P1_DOWN)==LOW)
	{
		_delay_ms(30);
		if(p1_Xpos<3)
		{
			LCD_Clear_Position(p1_Xpos,p1_Ypos,1);
			p1_Xpos++;
			LCD_CustomChar(0,Player_Pattern);
			LCD_GoTo(p1_Xpos,p1_Ypos);
			LCD_WriteChar(0);
		}
		while(DIO_ReadPin(P1_DOWN)==LOW);
	}
	
	//move technique for player2
	if(DIO_ReadPin(P2_UP)==LOW)
	{
		_delay_ms(30);
		if(p2_Xpos>1)
		{
			LCD_Clear_Position(p2_Xpos,p2_Ypos,1);
			p2_Xpos--;
			LCD_CustomChar(0,Player_Pattern);
			LCD_GoTo(p2_Xpos,p2_Ypos);
			LCD_WriteChar(0);
		}
		while(DIO_ReadPin(P2_UP)==LOW);
	}
	if(DIO_ReadPin(P2_DOWN)==LOW)
	{
		_delay_ms(30);
		if(p2_Xpos<3)
		{
			LCD_Clear_Position(p2_Xpos,p2_Ypos,1);
			p2_Xpos++;
			LCD_CustomChar(0,Player_Pattern);
			LCD_GoTo(p2_Xpos,p2_Ypos);
			LCD_WriteChar(0);
		}
		while(DIO_ReadPin(P2_DOWN)==LOW);
	}
}
void draw_Ball(void)
{
	LCD_CustomChar(1,Ball_Pattern);
	LCD_GoTo(ball_Xpos,ball_Ypos);
	LCD_WriteChar(1);
	_delay_ms(100);
	LCD_Clear_Position(ball_Xpos,ball_Ypos,1);
}
void Ball_Running(void)
{
	if(p1_score >= 5 || p2_score >= 5)
	{
		Winner();
	}
	//move technique for BALL
	if(DIO_ReadPin(BALL_UP)==LOW)
	{
		_delay_ms(30);
		if(ball_Xpos>1)
		{
			ball_Xpos--;
		}
		while(DIO_ReadPin(BALL_UP)==LOW);
	}
	if(DIO_ReadPin(BALL_DOWN)==LOW)
	{
		_delay_ms(30);
		if(ball_Xpos<3)
		{
			ball_Xpos++;
		}
		while(DIO_ReadPin(BALL_DOWN)==LOW);
	}
	if(flag==0)
	{
		if(ball_Ypos <19)
		{
			ball_Ypos++;
			if((ball_Ypos == p2_Ypos) && (ball_Xpos == p2_Xpos))
			{
				move_Ball_Left();
			}
			draw_Ball();
		}
		else
		{
			ball_Ypos= 10;
			Increment_Score_Player1();
		}
		
	}
	else if(flag==1)
	{
		if(ball_Ypos>0)
		{
			ball_Ypos--;
			if((ball_Ypos == p1_Ypos) && (ball_Xpos == p1_Xpos))
			{
				move_Ball_Right();
			}
			draw_Ball();
		}
		else
		{
			ball_Ypos=10;
			Increment_Score_Player2();
		}
		
	}
}

void move_Ball_Right(void)
{
	ball_Ypos++;
	flag=0;
}

void move_Ball_Left(void)
{
	ball_Ypos--;
	flag=1;
}

void Increment_Score_Player1(void)
{
	p1_score++;
	LCD_Clear_Position(0,P1_SCORE_POS,2);
	LCD_GoTo(0,P1_SCORE_POS);
	LCD_WriteNumber_2(p1_score);
}
void Increment_Score_Player2(void)
{
	p2_score++;
	LCD_Clear_Position(0,P2_SCORE_POS,2);
	LCD_GoTo(0,P2_SCORE_POS);
	LCD_WriteNumber_2(p2_score);
}

void Winner(void)
{
	_delay_ms(100);
	LCD_Clear();
	LCD_GoTo(2,2);
	if(p1_score>=5)
	{
		LCD_WriteString("Player 1 is Winner");
	}
	if(p2_score>=5)
	{
		LCD_WriteString("Player 2 is Winner");
	}
	_delay_ms(5000);
	game_Init();
}