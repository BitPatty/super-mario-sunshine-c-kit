#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "inc/smsJP.h"

//Basic in game timer

J2DTextBox textBox;

static unsigned int start; 	//OStime on timer start
unsigned int timerValue; 	//current OSTime - start


void OnDraw2D(J2DOrthoGraph* graphics)
{
	Vector mariopos = **gpMarioPos;


	/*============================================================================
		TIMER
	==============================================================================*/


	unsigned int t_min; 			//displayed t_min
	unsigned int t_sec; 			//displayed t_sec
	unsigned int t_msec; 			//displayed t_msec
	unsigned int t_ticksInMsec; 	//current OSTime in t_msec,

    //Read timer state (external)
	unsigned int *fpTimerState 	= (unsigned int *)0x817F0100;


	/*
        The Wii north bridge is clocked at 243 MHz instead of 162MHz (GCN) which gives us 60.75 MHz for the I/O clock
	*/

    //TODO: Replace with Stopwatch

	t_ticksInMsec = (unsigned int)((double)((unsigned int)(OSGetTime() >> 15) & 0xDFFFFFFF)/(60750.0/32768.0));

	if ((unsigned int)*fpTimerState == 0) {
		start = t_ticksInMsec;
		*fpTimerState = 1;
	}

	//If shine hasn't been touched, update timerValue
	if((unsigned int)*fpTimerState <= 1) {
		timerValue = t_ticksInMsec - start;
	}

	//Set display values
	t_min = timerValue / 60000;
	t_sec = (timerValue / 1000) % 60;
	t_msec = timerValue % 1000;

	//Update textbox buffer
	snprintf(J2DTextBox_GetStringPtr(&textBox),128*sizeof(char*),"(v0.62) TIME: %02d:%02d.%03d",t_min,t_sec,t_msec);


	/*============================================================================
		Draw
	==============================================================================*/


	//Run replaced branch
	J2DGrafContext_Setup2D((J2DGrafContext*)graphics);

	//Draw timerbox
	J2DScreen_Draw((J2DScreen*)&textBox, 0, 0, (J2DGrafContext*)graphics, 0x81);
}


void OnSetup(MarDirector* director)
{
 	JUTRect textRect;

	//Run replaced branch
	MarDirector_SetupObjects(director);

	//allocate memory for textbox
	char* info;
	info = (char*)malloc(128*sizeof(char*));

	//setup textbox
	JUTRect_Set(&textRect, 0, 0, 512, 512);
	J2DTextBox_Create(&textBox, 0, &textRect, GameFont, GameStrTable, 2, 0);
	J2DTextBox_SetString(&textBox,info);
}
