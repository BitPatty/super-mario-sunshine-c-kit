/* Super Mario Sunshine Chaos Edition */
/* by miluaces */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include "sms.h"

//This version is different from the released version:
/* 4 effects can occur at the same time
 * Boring effects removed
 * Fixed some crashes
 * A few optimizations for space because of 229 byte limit
 */

//Static variables don't take up code space
static int timer[4] __attribute__((section(".sdata")));			//Effect timers
static int currentEffect[4] __attribute__((section(".sdata")));	//Current effects
static int val[4] __attribute__((section(".sdata")));			//Effect values
static int oval[4] __attribute__((section(".sdata")));			//Effect reset values
static Vector lastposition __attribute__((section(".sdata")));	//Stage start position
static MarioActor* mario __attribute__((section(".sdata")));	//Mario

//Runs every frame
int OnUpdate(MarDirector* director) {	
	int (*GameUpdate)(MarDirector* director) = GetObjectFunction(director, Director_GameUpdate);

	//If a cutscene is running or anything else is wrong, don't do effects (saves alot of crashes)
	if (director != *gpMarDirector || mario == NULL || (mario->status & STATE_CUTSCENE))
		goto EndUpdate;
	
	//Kill switch
	if (ControllerOne->buttons & PRESS_DD)
		**gpMarioFlag = MARIOFLAG_GAMEOVER;
	
	//Four effects at once
	for (int i = 0; i < 4; i++){
		//If timer passed then generate another effect
		if (timer[i] == 0){
			currentEffect[i] = rand() / 1639;	//Random effect (between 0 and 19), division takes less space than modulus
			timer[i] = (rand() / 36) + 450;		//Random time (between 15s - 45s)
			val[i] = rand() / 32;				//Random effect modifier (between 0 and 1023)
			oval[i] = 0;						//Reset effect memory
		}
		
		HitActor* other;
		switch (currentEffect[i]){
			case 0:
				//Teleport Mario randomly
				if (rand() <= 500)
					mario->position.x += (float)(val[i] - 500);
				//Only teleport in one direction :(
				break;
			case 1:
				//Gravity reduce
				**gpMarioSpeedY += 1.0f;
				break;
				//Removed annoying camera
			case 4:
				//Maybe remove
				timer[i] = 1;
				
				//Test if items can be spawned
				if (*gpItemManager == NULL)
					break;
				
				//Create coin
				other = MakeObjAppear(*gpItemManager, OBJ_COIN);
				((ItemActor*)other)->position.x = mario->position.x;
				((ItemActor*)other)->position.y = mario->position.y + 200.0f;
				((ItemActor*)other)->position.z = mario->position.z;
				((ItemActor*)other)->velocity.y = 20.0f;
				((ItemActor*)other)->flags = ((ItemActor*)other)->flags & ~ITEMFLAG_STATIC;
				break;
			case 5:
				//Randomize flags
				//Saved so they can be restored
				if (oval[i] == 0){
					oval[i] = **gpMarioFlag;
					val[i] = (rand() & 0x0FFF) | (rand() << 12);
					val[i] = val[i] | 0x00000001;
					val[i] = val[i] & 0x0013B085;
				}
				**gpMarioFlag = val[i];
				if (timer[i] == 1)
					**gpMarioFlag = oval[i];
				break;
			case 6:
				//Teleport to beginning of stage
				mario->position = lastposition;
				timer[i] = 1;
				break;
			case 7:
				//Random noises
				//Todo: find bounds
				Mario_StartVoice(mario, rand());
				break;
			case 8:
				//Random jump
				//if (rand() <= 1500){
					MarioDoJump(mario);
				//	**gpMarioSpeedY = (float)val[i] / 200.0f;
				//}
				break;
			case 9:
				//Hurt mario slowly
				//Todo: no flinch
				if (oval[i] == 0)
				{																											
					SendMsgToMario(mario, MARIOMSG_HURT);
					oval[i] = 350;
				}
				oval[i]--;
				break;
				//Removed sun changed side
				//Removed sweat and electrify
			case 12:
				//Y textures (taken from gecko code by )
				*(float*)0x803db224 = val[i] / 20.47f;
				if (timer[i] == 1)
					*(float*)0x803db224 = 1.0f;
				break;
			case 13:
				//Launch mario
				MarioDoThrow(mario);
				**gpMarioSpeedY = 200.0f;
				timer[i] = 1;
				break;
			case 14:
				//Jump = launch
				if (mario->status & STATE_AIRBORN)
					MarioDoThrow(mario);
				break;
			case 15:
				//Tremble mario to oblivion
				StartTrembleEffect(GetMarioTrembleEffect(mario), 5.0f, 2.0f, 1.02f, timer[i]);
				timer[i] = 1;
				break;
			case 16:
				//Mario super speed
				SetMarioVelocity(mario, (float)val[i]);
				break;
		}
		timer[i]--;
	}

EndUpdate:
	//Run the replaced branch
	return GameUpdate(director);
}

//Called at the start of every scene
void OnSetup(MarDirector* director)
{
	//Run replaced branch
	MarDirector_SetupObjects(director);
	
	//Save mario's position and reset variables
	mario = GetMarioHitActor();
	lastposition = mario->position;
	
	//Fix bad textures, takes less space to just set to 1.0 without if statement
	*(float*)0x803db224 = 1.0f;
	
	//Clear effects
	for (int i = 0; i < 4; i++)
	{
		currentEffect[i] = 0xFF;
		timer[i] = 60;
	}
}

//Called every time water touches the floor
void OnWaterHitsGround(PollutionManager* pollution, float x, float y, float z, float r)
{
	//If pollution effect is running, place pollution instead of cleaning it
	if (currentEffect[0] == 17 || currentEffect[1] == 17)
		StampPollution(pollution, 2, x, y, z, r);
	else
		CleanPollution(pollution, x, y, z, r);
}

//Called every time an object touches mario
void OnObjectTouchMario(HitActor* this, HitActor* other)
{
	//If effect is running don't run TouchPlayer()
	if (currentEffect[0] == 18 || currentEffect[1] == 18)
		return;
	
	//Run replaced branch
	HitActor* (*TouchPlayer)(void* t, void* o) = GetObjectFunction(this, HitActor_TouchPlayer);
	TouchPlayer((void*)this, (void*)other);
}

//Called for each NPC every frame
void OnAllNPCsUpdate(HitActor* this, int a1, void* drama, void* graphics, int obj)
{
	Vector dif;
	if (currentEffect[0] == 19 || currentEffect[1] == 19)
	{
		//Get difference between mario and NPC using built in functions to save precious instruction space
		dif = mario->position;
		Vector_Subtract(&dif, &(this->position));
		Vector_Normalize(&dif, &dif);
		Vector_Scale(&dif, 2.0f);
		
		//Add to NPC position
		Vector_Add(&(this->position), &dif, &(this->position));
	}
	
	//Run replaced branch
	Drama_PrepareUpdate(this, a1, drama, graphics, obj);
}