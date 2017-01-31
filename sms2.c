/* <> are external libs, "" are files we include */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "sms.h"

/* 
	Super Mario Sunshine Disassembly example
*/

/* This code is always running, and is constantly updating. */
J2DTextBox textbox;


bool inAir;
int timesjumped;
int glasstimer;
bool eqip;
int timemilli;
int time;
int timerx;
int timery;

int OnUpdate(MarDirector* director) {	
	int (*GameUpdate)(MarDirector* director) = (void*)*(void**)((int)*(int*)director + 0x64);

	
	/* 
	   We simply keep track of Mario's jumping amount. 
	   He needs to stop jumping, or else he'll have an effect!
	*/
	
	/* is he jumping? */
	bool jumping = IsMarioJumping();
	
	timemilli--;
	timery++;
	if (timemilli <=0) {
		time--;
		timemilli=30;
	}
	
	if (ControllerOne->buttons & PRESS_DU) {
		MarioActor* mario = GetMarioHitActor();
		SetMarioAnim(1.0, mario, 109);
	}
	JUTRect rect;
	JUTRect_Set(&rect, timerx, timery, 800, 512);
	
	//Update
	return GameUpdate(director);
}

void OnDraw2D(J2DOrthoGraph* graphics)
{
	/* Here are his states that we read. 
	   If Mario is doing said action, the return should be 1.
	*/
	snprintf(J2DTextBox_GetStringPtr(&textbox), 128, "Time x %d", time);
			 
	//Run replaced branch
	J2DGrafContext_Setup2D((J2DGrafContext*)graphics);	
	
	J2DScreen_Draw((J2DScreen*)&textbox, 0, 0, (J2DGrafContext*)graphics, 0x81);
	GXSetScissor(0, 0, 0x0280, 0x01c0);
	
	JUTRect rect;
	JUTRect_Set(&rect, timerx, timery, 800, 512);
}

/* This code gets ran once. */
void OnSetup(MarDirector* director)
{
	MarioActor* mario = GetMarioHitActor();
	WearGlasses(mario);
	
	timemilli=30;
	time=300;
	timerx=440;
	timery=-420;
	
	JUTRect rect;
	
	MarDirector_SetupObjects(director);	//Run replaced branch
	
	JUTRect_Set(&rect, timerx, timery, 800, 512);
	//textbox = (J2DTextBox*)malloc(sizeof(J2DTextBox));
	J2DTextBox_Create(&textbox, 0, &rect, GameFont, GameStrTable, 2, 0);
	
	char* info;
	info = (char*)malloc(128);
	J2DTextBox_SetString(&textbox, info);
	
	void (*TestNull)(void) = 0x80247fa4;
	TestNull();
	
	
	info = (char*)malloc(128);
}
void *TestNull() {
	  asm(
        "blr ;"
        "ori %r1, %r1, 0xd138 ;"
    );

}