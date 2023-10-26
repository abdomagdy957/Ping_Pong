#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO.h"
#include "LCD_Interface.h"

#include "LCD_Game.h"

#define  F_CPU	8000000
#include <util/delay.h>

int main(void)
{
	DIO_Init();
	LCD_Init();
	
	game_Init();
    while(1) 
    {
			movePlayers();
			Ball_Running();

	}
}
