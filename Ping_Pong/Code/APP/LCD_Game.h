

#ifndef LCD_GAME_H_
#define LCD_GAME_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "DIO.h"
					/***********************Macros******************************/
					
#define P1_UP		PIND4
#define P1_DOWN		PIND5
#define P2_UP		PIND3				/* PUSH BUTTONS*/
#define P2_DOWN		PIND2
#define BALL_UP		PIND6
#define BALL_DOWN	PIND7

#define P1_SCORE_POS	4
#define P2_SCORE_POS	17				


						/**********************Prototypes***********************/
void movePlayers(void);
void draw_Ball(void);
void Ball_Running(void);
void move_Ball_Right(void);
void move_Ball_Left(void);
void Winner(void);

#endif /* LCD_GAME_H_ */