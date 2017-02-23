#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "inc/sms.h"

static J2DTextBox textbox;

int OnUpdate(MarDirector* director) {	
	int (*GameUpdate)(MarDirector* director) = GetObjectFunction(director, Director_GameUpdate);
	
	//Update

	return GameUpdate(director);
}

void OnDraw2D(J2DOrthoGraph* graphics)
{
	Vector mariopos = **gpMarioPos;
	int state = GetMarioStatus();
	snprintf(J2DTextBox_GetStringPtr(&textbox), 128, "Mario X: %f\nMario Y: %f\nMario Z: %f\nMario State: %X\nNext Stage: %d-%d", 
			 mariopos.x, mariopos.y, mariopos.z, state, *ChangeScenario, *ChangeEpisode);
			 
	J2DGrafContext_Setup2D((J2DGrafContext*)graphics);	//Run replaced branch
	
	J2DScreen_Draw((J2DScreen*)&textbox, 0, 0, (J2DGrafContext*)graphics, 0x81);
	//GXSetScissor(0, 0, 0x0280, 0x01c0);
}

void OnSetup(MarDirector* director)
{
	JUTRect rect;
	
	MarDirector_SetupObjects(director);	//Run replaced branch
	
	JUTRect_Set(&rect, 0, 0, 512, 512);
	//textbox = (J2DTextBox*)malloc(sizeof(J2DTextBox));
	J2DTextBox_Create(&textbox, 0, &rect, GameFont, GameStrTable, 2, 0);
	
	char* info;	
	info = (char*)malloc(128);
	
	J2DTextBox_SetString(&textbox, info);
}