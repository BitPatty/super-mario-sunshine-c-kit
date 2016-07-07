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
	This example is a basic drawing script. It takes a bunch of
	Mario's statuses and reports them to the screen. 
	These states are 0s and 1s, so we call each function and assign it to an int
	so we can call it and get it's result. However, we have to convert it to string first,
	which is what snprintf() does. We also chuck Mario...places. Have fun!
	This doesn't seem to work on console at all. It does work on Dolphin, however.
	- MrRean
*/

/* This code is always running, and is constantly updating. */
static J2DTextBox textbox __attribute__((section(".sdata")));
static char* info;

static int timesjumped = 0;
static int glasstimer=0;
static bool eqip=false;
int timemilli=30;
int time=30;
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
	/* this fixes a bug with the counting. jumping counts for every frame, which is what we do NOT want */
	static bool inAir __attribute__((section(".sdata")));
	static bool eqip __attribute__((section(".sdata")));
	static int glasstimer __attribute__((section(".sdata")));
	/* create our Mario actor. */
	
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
	snprintf(info, 128, "Time x %d", time);
	
	// now we set our string to a J2DTextBox
	J2DTextBox_SetString(&textbox, info);
			 
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
	
	time=300;
	timerx=440;
	timery=-420;
	
	JUTRect rect;
	
	MarDirector_SetupObjects(director);	//Run replaced branch
	
	JUTRect_Set(&rect, timerx, timery, 800, 512);
	//textbox = (J2DTextBox*)malloc(sizeof(J2DTextBox));
	J2DTextBox_Create(&textbox, 0, &rect, GameFont, GameStrTable, 2, 0);
	
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