# Super-Mario-Sunshine-C-Kit
A WIP C library for everyone's favorite game: Super Mario Sunshine.

What can this do? 

You can make Gecko code modifications in C for Super Mario Sunshine, and Super Mario Sunshine only, for now. (I'll probably make another kit for some other games in the future, though only me working on them; I don't want to involve Miluaces into the pain. ^ ^' ) 


Neato!... Well, how do I set this up? 

First, you need to install devkitPro in order for your code to compile, and don't forget to set up the environment for devkitPPC. (Ex., C:\devkitPro\devkitPPC\bin) You can install the lib anywhere on your computer, as long as a folder in the file path doesn't contain any spaces. To compile your code, simply drag your C code file into build.bat. 


Alright. Do you have any examples to show? 

Yes, actually. Here's an item spawning example from Miluaces: 

#include "sms.h"

static int laststate __attribute__((section(".sdata"))); //Last state

int OnUpdate(MarDirector* director) {	
	int (*GameUpdate)(MarDirector* director) = (void*)*(void**)((int)*(int*)director + 0x64);
	
	MarioActor* mario = GetMarioHitActor();
	ItemActor* item = 0;
	
	if (!laststate){
		if (ControllerOne->buttons & PRESS_DU)	//Dpad up spawns a coin
			item = MakeObjAppear(*gpItemManager, OBJ_COIN);
		else if (ControllerOne->buttons & PRESS_DL) //Dpad left spawns a 1-up
			item = MakeObjAppear(*gpItemManager, OBJ_ONEUP);
		else if (ControllerOne->buttons & PRESS_DR) //Dpad right spawns a rocket nozzle
			item = MakeObjAppear(*gpItemManager, OBJ_ROCKETNOZZLE);
		else if (ControllerOne->buttons & PRESS_DD) //Dpad down spawns a turbo nozzle
			item = MakeObjAppear(*gpItemManager, OBJ_TURBONOZZLE);
	}
	
	// If no dpad buttons are pressed, reset laststate
	if (!(ControllerOne-> buttons & (PRESS_DU | PRESS_DL | PRESS_DR | PRESS_DD)))
		laststate = 0;
	
	//If item was assigned, set it up
	if (item != 0){
		//Set laststate to 1 to prevent more than one item spawning from one button press
		laststate = 1;
		
		//Set item position
		item->position.x = mario->position.x;
		item->position.y = mario->position.y + 200.0f;
		item->position.z = mario->position.z;
		
		//Set item velocity
		item->velocity.y = 20.0f;
		
		//Make item moveable
		item->flags = item->flags & ~ITEMFLAG_STATIC;
	}
	
	return GameUpdate(director);
}

You can find other examples on the GitHub page. (Thanks MrRean for making a repo for us.  :) ) 


My code compiled! What do I do now? 

That's good! The Gecko code should have automatically been copied to your clipboard. (Thanks Miluaces :D ) With that, you should now be able to paste that into your cheat code list in Dolphin and play your modification! 

--- 

More examples and updates to the lib will surely come at the right moment. Stick around in the IRC channel #sunshinerealm in irc.nolimitzone.com/6667 to meet and converse with the Sunshine Realm crew and see updates on current SMS modifications, big or small.
