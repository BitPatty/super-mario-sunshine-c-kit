/*
 * Empty c file demonstrating available functions the Bin2Gecko and DolInsert tools can replace
 */

#include "inc/sms.h"

//Variable
int variable;

//Update every frame
int OnUpdate(MarDirector* director) {	
	int (*GameUpdate)(MarDirector* director) = GetObjectFunction(director, Director_GameUpdate);
	
	//Update Here
	
	//Run original replaced function
	//Removing this will halt the game
	return GameUpdate(director);
}

//Setup after every stage load
void OnSetup(MarDirector* director)
{
	//Run original replaced function
	//Removing this will cause no stage setup to occur and will likely crash the game
	MarDirector_SetupObjects(director);
	
	//Setup here
}

//Whenever water touches ground
void OnWaterHitsGround(PollutionManager* pollution, float x, float y, float z, float r)
{
	//Run original replaced function
	//If you remove this, water will no longer clean pollution
	CleanPollution(pollution, x, y, z, r);
	
	//Code here
}

//Whenever object touches mario
void OnObjectTouchMario(HitActor* this, HitActor* other)
{
	//Get the function from the object's vtable
	HitActor* (*TouchPlayer)(void* t, void* o) = GetObjectFunction(this, HitActor_TouchPlayer);
	
	//Code here
	
	//Run original replaced function
	//If you remove this,  no object will react to touching mario
	TouchPlayer((void*)this, (void*)other);
}

//Runs once per frame for each NPC
void OnAllNPCsUpdate(HitActor* this, int a1, void* drama, void* graphics, int obj)
{
	//Code here
	
	//Run original replaced function
	//If you remove this, no NPCs will update
	Drama_PrepareUpdate(this, a1, drama, graphics, obj);
}

//Runs once per frame, but allows drawing to HUD
void OnDraw2D(J2DOrthoGraph* graphics)
{
	//Run original replaced function
	//Removing this will no longer draw FLUDD HUD
	MarDirector_SetupObjects(director);
	
	//Draw here
}