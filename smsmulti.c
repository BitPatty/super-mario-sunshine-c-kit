/* Super Mario Sunshine Multiplayer */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include "inc/sms.h"

#define NUM_PLAYERS 2

volatile const char* CREDITS = "Super Mario Sunshine Multiplayer https://egaddsworkshop.com/";

const float PI = 3.14159265f;
const int MARIO_COLSIZE = 6;
const float MULTI_MAXDISTANCE = 4000.0f;
const char* MARIO_EMITTER = "/barrel.prm";
const float MARIO_TRAMPLEHEIGHT = 60.0f;

const int32_t ENEMYMARIO_VTABLE[0x3b];
const int32_t EMARIO_VTABLE[0x45];

//static J2DTextBox textbox;
//static char* info;

int LimitDistance;

MarioActor* Players[NUM_PLAYERS];
EMario* EMarios[NUM_PLAYERS];

Yoshi* CurrentYoshi;
int IsPlaying[NUM_PLAYERS];
int HeldPlayer[NUM_PLAYERS];
int MarioOnYoshi[NUM_PLAYERS];
WaterEmitInfo* ShadowMarioEmitters[NUM_PLAYERS];
int WaterSprayTimer[NUM_PLAYERS];

int Started;

int16_t CameraPhi;
int16_t CameraTheta;
int CameraModeTimer;
int CameraMode;

int playerLoopIndex;

int multimode;

//int bBx, bBy, mX, mY, cX, cY; // Background x, y  -  MENU x, y - Cursor x,y
//int tX, tY; // TextBox x,y
//int isMenuEnabled, menuTimer, isExit, exitTimer, repTimer, chooseTimer, hasChosen;

//const char *optAry[] = {"Enabled", "Disabled"};
//int opt, boolDis;

//float camDis;

Vector cameraGuide;
Vector playerAverage;
Vector difplayerAverage;

int OnUpdate(MarDirector* director) {
	int (*GameUpdate)(MarDirector* director) = GetObjectFunction(director, Director_GameUpdate);
	
	Players[0] = *gpMarioAddress;
	if (Players[0] == 0 || gpMarioAddress == 0)
		return GameUpdate(director);
	
	int realcount = 1;
	difplayerAverage.x = playerAverage.x;
	difplayerAverage.y = playerAverage.y;
	difplayerAverage.z = playerAverage.z;
	playerAverage.x = Players[0]->position.x;
	playerAverage.y = Players[0]->position.y;
	playerAverage.z = Players[0]->position.z;
	
	if (!Started)
		CameraPhi = Players[0]->roty + 0x7FFF;
	for (int i = 1; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		
		if (IsPlaying[i] && ((EnemyMario*)Players[i])->emariohealth > 0){
			realcount++;
			playerAverage.x += Players[i]->position.x;
			playerAverage.y += Players[i]->position.y;
			playerAverage.z += Players[i]->position.z;
		}
		
		if (!Started){
			if (IsPlaying[i])
			{
				Players[i]->position = Players[0]->position;
				Players[i]->position.y += 180 * i;
				Camera_AddMultiPlayer(*gpCamera, &(Players[i]->position));
			}
			
			Players[i]->gamepad = &(GamePads[i]);
			((EnemyMario*)Players[i])->emarioflags = 0x0082;		//Show healthbar and visible shadow mario
			((EnemyMario*)Players[i])->emariodamage = 0x000D;		//Doesnt hurt mario
			
			GamePadTwo->u2 = 2;
			GamePadThree->u2 = 3;
			Players[i]->colsettings = 0x80000001;	//item collision
			EMarios[i]->colsettings = 0x80000001;
			
			*(int*)((int)Players[i] + 0x388) = 0x0000FFFF;	//Pollution collision
		}
		if (!IsPlaying[i] && (Controllers[i].buttons & PRESS_START)){
			Players[i]->flags = MARIOFLAG_ALIVE;
			Players[i]->position = Players[0]->position;
			Players[i]->position.y += 180;
			Camera_AddMultiPlayer(*gpCamera, &(Players[i]->position));
			
			IsPlaying[i] = 1;
		}
		
		if (((EnemyMario*)Players[i])->emariohealth <= 0 || ((MarioActor*)Players[i])->flags & MARIOFLAG_GAMEOVER){
			SetMarioStatus(Players[i], STATE_STUNNED, 0, 0);
			Camera_RemoveMultiPlayer(*gpCamera, &(Players[i]->position));
			((EnemyMario*)Players[i])->emariohealth = 0;
		}
		
		int rstate = Players[i]->status & 0xFFFFFFF0;
		if (Players[0]->flags & MARIOFLAG_HASFLUDD){
			if ((rstate == STATE_IDLE || rstate == STATE_RUNNING || rstate == STATE_JUMP || rstate == STATE_JUMPSIDE) && rstate != STATE_JUMPSPIN){
				WaterSprayTimer[i] = 30;
				if (Controllers[i].buttons & PRESS_R){
					MapObjBase_EmitSplash(Players[i]);
					SetMarioStatus(Players[i], STATE_JUMPSPIN1, 0, 0);
					Players[i]->speed.y = 40.0f;
					WaterSprayTimer[i] = 0;
				}
			}
			else if (rstate == STATE_JUMPSPIN && Controllers[i].buttons & PRESS_R){
				MapObjBase_EmitSplash(Players[i]);
				WaterSprayTimer[i] = 0;
			}
			
			if (rstate == STATE_JUMPSPIN && WaterSprayTimer[i] < 30){
				ShadowMarioEmitters[i]->position = Players[i]->position;
				ShadowMarioEmitters[i]->u3 = 0.35f;
				ShadowMarioEmitters[i]->u5 = 5.0f;
				ShadowMarioEmitters[i]->u7 = 5.0f;
				ShadowMarioEmitters[i]->u9 = 5.0f;
				ShadowMarioEmitters[i]->u11 = 0;
				ShadowMarioEmitters[i]->count = 16;
				ModelWaterManager_EmitRequest(*gpModelWaterManager, ShadowMarioEmitters[i]);
				
				WaterSprayTimer[i]++;
			}
		}
		
		if (!(Players[0]->status & STATE_CUTSCENE) && Players[i]->status & STATE_CUTSCENE)
			Players[i]->status = Players[0]->status;
		
		if (IsPlaying[i] && LimitDistance && ((EnemyMario*)Players[i])->emariohealth > 0){
			float xdist = Players[i]->position.x - Players[0]->position.x;
			float zdist = Players[i]->position.z - Players[0]->position.z;
			float yplanedist = sqrtf((xdist * xdist) + (zdist * zdist));
			if (yplanedist > MULTI_MAXDISTANCE){
				ParticleManager_EmitWithRotate(*gpMarioParticleManager, 0x15, &Players[i]->position, 0x4000, 0, 0, 0, 0);
				Players[i]->position.y += 60;
				ParticleManager_EmitWithRotate(*gpMarioParticleManager, 0x15, &Players[i]->position, 0x4000, 0, 0, 0, 0);
				Players[i]->position = Players[0]->position;
				ParticleManager_EmitWithRotate(*gpMarioParticleManager, 0x15, &Players[i]->position, 0x4000, 0, 0, 0, 0);
				Players[i]->position.y += 60;
				ParticleManager_EmitWithRotate(*gpMarioParticleManager, 0x15, &Players[i]->position, 0x4000, 0, 0, 0, 0);
				Players[i]->position.y += 240;
				Players[i]->speed.y = 0.0f;
			}
		}
	}
	
	//if (Started)
	//{
	//	checkMultiplayerMenu(); // Check if the multiplayer menu is active :)
	//}
	//else {	//When not started, add mario and cursor to camera
	if (!Started){
		Camera_AddMultiPlayer(*gpCamera, &(Players[0]->position));
		Camera_AddMultiPlayer(*gpCamera, &cameraGuide);
	}
	
	playerAverage.x /= (float)realcount;
	playerAverage.y /= (float)realcount;
	playerAverage.z /= (float)realcount;
	difplayerAverage.x = playerAverage.x - difplayerAverage.x;
	difplayerAverage.y = playerAverage.y - difplayerAverage.y;
	difplayerAverage.z = playerAverage.z - difplayerAverage.z;
	cameraGuide.x = playerAverage.x;
	cameraGuide.y = playerAverage.y;
	cameraGuide.z = playerAverage.z;
	
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (Players[i] == 0)
			continue;
		if (!IsPlaying[i])
			continue;
		//Camera controls
		if (Controllers[i].buttons & PRESS_L && (!(Players[i]->status & (STATE_AIRBORN | STATE_DOJUMP))) || (Players[i]->flags & 0x3000))
			CameraPhi = Players[i]->roty + 0x7FFF;
		
		if (CameraModeTimer == 0){
			if (Controllers[i].buttons & PRESS_DL){
				CameraMode++;
				CameraModeTimer = 30;
			}
			else if (Controllers[i].buttons & PRESS_DR){
				CameraMode--;
				CameraModeTimer = 30;
			}
		}
		
		CameraTheta += Controllers[i].ranalogy * 2;
		CameraPhi += Controllers[i].ranalogx * 4;
	}
	if (CameraTheta > 6000)
		CameraTheta = 6000;
	if (CameraTheta < -1000)
		CameraTheta = -1000;
	if (CameraModeTimer > 0)
		CameraModeTimer--;
	if (CameraMode > 3)
		CameraMode = 0;
	if (CameraMode < 0)
		CameraMode = 2;
	
	Started = 1;

	return GameUpdate(director);
}

/*
void OnDraw2D(J2DOrthoGraph* graphics)
{
	snprintf(info, 128, "\33CC[FFFFFFFF]\33GC[FF0000FF]Distance Limit \n%s \n \nCamera Distance \n%f",
			 optAry[opt], camDis);
	J2DTextBox_SetString(&textbox, info);
			 
	J2DGrafContext_Setup2D((J2DGrafContext*)graphics);	//Run replaced branch
	
	J2DScreen_Draw((J2DScreen*)&textbox, tX, tY, (J2DGrafContext*)graphics, 0x81);
	GXSetScissor(0, 0, 0x0280, 0x01c0);
	
}
*/

void OnSetup(MarDirector* director)
{
	playerLoopIndex = 0;
	
	HeldPlayer[0] = 0;
	IsPlaying[0] = 1;
	LimitDistance = 1;
	
	CameraPhi = 0;
	CameraTheta = 0;
	CameraModeTimer = 0;
	CameraMode = 0;
	
	cameraGuide.x = cameraGuide.y = cameraGuide.z = 0.0f;
	playerAverage.x = playerAverage.y = playerAverage.z = 0.0f;
	difplayerAverage.x = difplayerAverage.y = difplayerAverage.z = 0.0f;
	
	//assembly edit to allow shadow mario to slide on water
	int* address = 0x8024fc98;
	*address = 0x60000000;
	//and to disable loading params that arent needed and crash on console
	address = 0x8004370c;
	*address = 0x60000000;
	
	//Run replaced branch
	MarDirector_SetupObjects(director);

	EMarios[1] = (EMario*)SearchObjByRef("MarMP2");
	if (NUM_PLAYERS > 2)
		EMarios[2] = (EMario*)SearchObjByRef("MarMP3");
	if (NUM_PLAYERS > 3)
		EMarios[3] = (EMario*)SearchObjByRef("MarMP4");
	
	MarioOnYoshi[0] = 0;
	for (int i = 1; i < NUM_PLAYERS; i++){
		Players[i] = 0;
		HeldPlayer[i] = 0;			//Clear to 0 for real hw
		MarioOnYoshi[i] = 0;
		ShadowMarioEmitters[i] = 0;
		WaterSprayTimer[i] = 0;
		
		if (EMarios[i] == 0)
			continue;
		HeldPlayer[i] = 0;
		
		Players[i] = (MarioActor*)(EMarios[i]->enemymario);	//Get EnemyMario
		Players[i]->Type = ENEMYMARIO_VTABLE;
		EMarios[i]->Type = EMARIO_VTABLE;
		
		Players[i]->yoshi = CurrentYoshi;	//Add yoshi, prevent some crashes on hw
		
		//Mario_InitValues(Players[i]);
	
		Players[i]->position.x = 10000;
		Players[i]->position.y = 10000;
		Players[i]->position.y = -10000;
		Players[i]->flags |= MARIOFLAG_INVISIBLE | MARIOFLAG_GONE;
		Players[i]->status = 0x0000133f;
		
		((EnemyMario*)Players[i])->emariohealth = 0x40;

		Players[i]->colarray = malloc(sizeof(void*) * MARIO_COLSIZE);
		
		//Give shadow mario fludd to prevent yoshi crash...
		WaterGun* gun = malloc(7632);	//fludd is fat
		if (gun != 0){
			WaterGun_Create(gun, Players[i]);
			WaterGun_Init(gun);
			Players[i]->watergun = gun;
		}
		
		//Let shadow mario make water
		ShadowMarioEmitters[i] = malloc(sizeof(WaterEmitInfo));
		if (ShadowMarioEmitters[i] != 0)
			WaterEmitInfo_Create(ShadowMarioEmitters[i], MARIO_EMITTER);
	}
	
	/*
	int* menuTrans = *TGCCConsole2 + GFX_OFF + 0xCC;
	int* blackTrans = *TGCCConsole2 + GFX_OFF - 0x1B0 + 0xCC;
	int* sMarioCTrans = *TGCCConsole2 + GFX_OFF + 0x1B0 + 0xCC;
	movePane(*TGCCConsole2 + GFX_OFF - 0x1B0, bBx, bBy); // Black background
	movePane(*TGCCConsole2 + GFX_OFF, mX + 170, mY + 50); // MENU Text (Add 0x1B0 for next entry)
	movePane(*TGCCConsole2 + GFX_OFF + 0x1B0, 50, 150); // Shadow Mario Cursor
	*menuTrans = 0x00000000;
	*blackTrans = 0x00000000;
	*sMarioCTrans = 0x00000000;
	
	JUTRect rect;
	JUTRect_Set(&rect, 0, 0, 512, 512);
	J2DTextBox_Create(&textbox, 0, &rect, GameFont, GameStrTable, 2, 0);
	
	tX = 100;
	tY = -35;
	
	boolDis = 1;
	*/
	
	Started = 0;
}

//Should only really be used for initializing
void OnInitApp(void* application){
	Application_Init(application);
	
	if (CalcKeyCode(CREDITS) != 9397)
		*(int*)MarDirector_SetupObjects = 0x4e800020;
	
	//Disable default multiplayer camera
	*(int*)0x80276b44 = 0x60000000;
	*(int*)0x800397f8 = 0x60000000;
	
	//info = (char*)malloc(128);
	
	//camDis = 0.667f;
	multimode = 1;
	for (int i = 0; i < NUM_PLAYERS; i++)
		IsPlaying[i] = 0;
}

void SetMarioAddresses(MarioActor* mario){
	*gpMarioAddress = mario;
	*gpMarioPos = (int)mario + 0x10;
	*gpMarioAngleX = (int)mario + 0x94;
	*gpMarioAngleY = (int)mario + 0x96;
	*gpMarioAngleZ = (int)mario + 0x98;
	*gpMarioSpeedX = (int)mario + 0xA4;
	*gpMarioSpeedY = (int)mario + 0xA8;
	*gpMarioSpeedZ = (int)mario + 0xAC;
}

void EMarioControl(MarioActor* enemymario, void* drama, void* graphics){
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (Players[i] == 0)
			continue;
		
		if (enemymario == Players[i] && IsPlaying[i])
			return Mario_CheckController(enemymario, drama, graphics);
	}
}

void MarioSendMessage(HitActor* sender, unsigned long message){
	//if (CurrentCollision == 0)
	//	return 0;

	MarioActor* closest = 0;
	float distance = 1000000;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (Players[i] == 0)
			continue;
		
		Vector dif = Players[i]->position;
		Vector_Subtract(&dif, &(sender->position));
		float magnitude = Vector_Magnitude(&dif);
		if (magnitude < distance)
		{
			closest = Players[i];
			distance = magnitude;
		}
	}
	if (closest == 0)
		return;
	
	int (*receiveMessage)(HitActor* t, HitActor* s, unsigned long m) = GetObjectFunction(closest, HitActor_ReceiveMessage);
	if (receiveMessage(closest, sender, message) == 0)
		return 0;
	else
		return 1;
}

void EMarioDamageExec(HitActor* this, HitActor* other, int u1, int u2, int u3, float f1, int u4, float f2, short u5)
{
	for (int i = 1; i < NUM_PLAYERS; i++)
		if (Players[i] == this && ((EnemyMario*)Players[i])->emariohealth <= 0)
			return;
		
	Mario_DamageExec(this, other, u1, u2, u3, f1, u4, f2, u5);
}

void EMarioReceiveMessage(HitActor* this, HitActor* sender, unsigned long message){
	for (int i = 1; i < NUM_PLAYERS; i++)
		if (Players[i] == this && ((EnemyMario*)Players[i])->emariohealth <= 0)
			return;
		
	Mario_ReceiveMessage(this, sender, message);
}

void EMarioPlayerControl(HitActor* this, void* drama, void* graphics){
	Mario_PlayerControl(this, drama, graphics);
}

int IsMultiplayerMap(){
	if (*ChangeScenario == 58 || *ChangeScenario == 30 || (*ChangeScenario == 3 && *ChangeEpisode == 5))
		return 0;
	return multimode;
}

void OnMarioIncHP(HitActor* mario, int n){
	if (mario == Players[0])
		Mario_IncHP(mario, n);
	else
	{
		EnemyMario* enemymario = ((EnemyMario*)mario);
		if (enemymario->emariohealth < 0x40)
			enemymario->emariohealth += 8 * n;
		enemymario->hpmetertimer = 0x400;
	}
}
void OnMarioDecHP(HitActor* mario, int n){
	if (mario == Players[0])
		Mario_DecHP(mario, n);
	else
	{
		EnemyMario* enemymario = ((EnemyMario*)mario);
		if (enemymario->emariohealth > 0)
			enemymario->emariohealth -= 8 * n;
		enemymario->hpmetertimer = 0x400;
	}
}

void RemoveObjectFromColArray(HitActor* actor, HitActor* col){
	if (actor->colcount == 0)
		return;
	
	int i = actor->colcount - 1;
	while (i >= 0){
		if (actor->colarray[i] == col)
			break;
		i--;
	}
	actor->colcount--;
	if (i == actor->colcount){
		return;
	}
	while (i < actor->colcount)
		actor->colarray[i] = actor->colarray[++i];
}

void BounceMario(MarioActor* mario1, MarioActor* mario2){
	int rstatus = mario1->status & 0xFFFFFFF0;
	if (rstatus != STATE_JUMPSPIN && rstatus != STATE_JUMP && rstatus != STATE_JUMPSIDE && rstatus != 0x02000890)
	{
		if (rstatus == 0x00800230 || rstatus == 0x008008A0){
			//knock over other mario
			if (mario2->status & 0xFFFFFFF0 != 0x000024D0)
				SetMarioStatus(mario2, 0x000208b0, 0, 0);
		}
		return;
	}
	
	Vector temp;
	temp.x = 0.5f;
	temp.y = 0.5f;
	temp.z = 0.5f;
	
	mario1->speed.y = 300.0f;
	Mario_SetAnimation(mario1, 211, 1.0f);	//triple trample animation
	SetMarioStatus(mario1, 0x02000890, 0, 0);
	Mario_SetStatusToJumping(mario1, 0x02000890, 0);
	EasyEmitParticle(8, &(mario1->position), mario1, &temp);
	EasyEmitParticle(9, &(mario1->position), mario1, &temp);
	StartSoundActorWithInfo(6168, &(mario1->position), 0, 0.0f, 3, 0, 0, 0, 4);
	
	rstatus = mario2->status & 0xFFFFFFF0;
	if (rstatus == STATE_JUMPSPIN || rstatus == STATE_JUMP || rstatus == STATE_JUMPSIDE)
	{
		mario2->speed.y = -mario1->speed.y;
	}
	
	RemoveObjectFromColArray(mario1, mario2);
}

void OnCheckActorsHit(void* hitcheckobj){
	//Set up EMario bounds
	for (int i = 1; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		
		EMarios[i]->bound1 = 80.0f;			//Manually
		EMarios[i]->bound2 = 50.0f;
		EMarios[i]->bound3 = 42.0f;
		EMarios[i]->bound4 = 130.0f;
		EMarios[i]->bound5 = 215.880554f;
		EMarios[i]->colflags = 0xFC000000;
	}
	
	playerLoopIndex = 0;
	
	//Run collision check
	ObjHitCheck_CheckActorsHit(hitcheckobj);
	
	for (int i = 1; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		
		//Give EnemyMario EMario's collision data
		Players[i]->colcount = EMarios[i]->colcount;
		Players[i]->colarraysize = EMarios[i]->colarraysize;
		for (int j = 0; j < Players[i]->colcount; j++)
			Players[i]->colarray[j] = EMarios[i]->colarray[j];
		
		//Remove held players from collision
		if (HeldPlayer[i])
			RemoveObjectFromColArray(Players[i], HeldPlayer[i]);
	}
	
	if (Started){
		//Add in some trample for fun
		for (int i = 0; i < NUM_PLAYERS; i++){
			if (Players[i] == 0)
				continue;
			if (Players[i]->speed.y > 0)
				continue;
			if ((int)Players[i]->colarray & 0x80000000 == 0)
				continue;
			for (int j = 0; j < Players[i]->colcount; j++){
				if (GetType((Players[i]->colarray[j])) == ENEMYMARIO_VTABLE || GetType((Players[i]->colarray[j])) == 0x803dd660){
					if (Players[i]->position.y > ((MarioActor*)Players[i]->colarray[j])->position.y + MARIO_TRAMPLEHEIGHT){
						BounceMario(Players[i], (MarioActor*)(Players[i]->colarray[j]));
					}
				}
			}
		}
	}
}

void OnDetectHit(void* hitcheckobj, HitActor* one, HitActor* two){
	EMario* held = 0;
	for (int i = 1; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		if (Players[i] == HeldPlayer[0])
			held = EMarios[i];
	}
		
	if (one == held && two == Players[0])
		return;
	if (two == held && one == Players[0])
		return;
	
	ObjHitCheck_DetectHit(hitcheckobj, one, two);
	
	if (Started){
		//Hacky have things direct collide with shadowmario
		for (int i = 1; i < NUM_PLAYERS; i++){
			if (Players[i] == 0)
				continue;
			if (one->colcount >= 1 && one->colarray[one->colcount - 1] == EMarios[i])
				one->colarray[one->colcount - 1] = Players[i];
			if (two->colcount >= 1 && two->colarray[two->colcount - 1] == EMarios[i])
				two->colarray[two->colcount - 1] = Players[i];
		}
	}
}

void OnMarioHeld(MarioActor* mario, int a2, int a3, int a4){
	MarioActor* other = 0;

	__asm__ ("addi %0,29,0"		//Forces compiler to stop overwriting r31
			  : "=r" (other)
			  :
			  : "r29");
	
	if (Started)
	{
		SetMarioStatus(mario, a2, a3, a4);
		
		for (int i = 0; i < NUM_PLAYERS; i++){
			if (Players[i] == 0)
				continue;
			if (Players[i] == other)
				HeldPlayer[i] = mario;
		}
	}
}

//I placed branch right after r3 is set to the thrown object.
//r31 holds mario's address
void OnMarioThrow(HitActor* thrownobject){
	MarioActor* mario = 0;
	
	__asm__ ("addi %0,31,0"		//Forces compiler to stop overwriting r31
			  : "=r" (mario)
			  :
			  : "r31");
	
	int (*receiveMessage)(HitActor* t, HitActor* s, unsigned long m) = GetObjectFunction(thrownobject, HitActor_ReceiveMessage);
	
	
	SetMarioAddresses(mario);
	
	receiveMessage(thrownobject, mario, 7);
	
	for (int i = 0; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		if (thrownobject == Players[i]){
			Vector newPos = **gpMarioPos;
			float angle = 2.0f * PI * **gpMarioAngleY / 65535.0f;
			newPos.x += sinf(angle) * 120.0f;
			newPos.z += cosf(angle) * 120.0f;
			Players[i]->position = newPos;
			
			Players[i]->status = STATE_DIVE;
			Players[i]->roty = **gpMarioAngleY;
			
			float speed = sqrtf((**gpMarioSpeedX * **gpMarioSpeedX) + (**gpMarioSpeedZ * **gpMarioSpeedZ));
			SetMarioVelocity(Players[i], 40.0f + speed);
			Players[i]->speed.y = 75.0f;
		}
		if (HeldPlayer[i] == thrownobject)
			HeldPlayer[i] = 0;
	}
	
	SetMarioAddresses(Players[0]);
}

//Same for OnMarioDrop
void OnMarioDrop(HitActor* thrownobject){
	MarioActor* mario = 0;
	
	__asm__ ("addi %0,31,0"		//Forces compiler to stop overwriting r31
			  : "=r" (mario)
			  :
			  : "r31");
	
	int (*receiveMessage)(HitActor* t, HitActor* s, unsigned long m) = GetObjectFunction(thrownobject, HitActor_ReceiveMessage);
	
	SetMarioAddresses(mario);
	
	receiveMessage(thrownobject, mario, 6);
	
	SetMarioAddresses(Players[0]);
}

void OnObjectTouchMario(HitActor* this, HitActor* other)
{
	//Block certain objects from touching shadow mario
	if ((GetType(other) == TYPE_ENEMYMARIO || GetType(other) == TYPE_EMARIO) &&
		GetType(this) == TYPE_ITEMNOZZLE)
		return;
	
	//Run replaced branch
	HitActor* (*TouchPlayer)(void* t, void* o) = GetObjectFunction(this, HitActor_TouchPlayer);
	TouchPlayer((void*)this, (void*)other);
}

void OnChangeNozzle(HitActor* this, int nozzletype, int nozzleslot){
	int (*touchPlayer)(HitActor* t, HitActor* o) = GetObjectFunction(this, HitActor_TouchPlayer);
	
	//If this is shadow mario, ignore
	for (int i = 1; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		if (this == Players[i]->watergun)
			return;
	}
	
	WaterGun_ChangeNozzle(this, nozzletype, nozzleslot);
}

void OnRideYoshi(Yoshi* yoshi){
	MarioActor* mario = 0;
	
	__asm__ ("addi %0,31,0"		//Forces compiler to stop overwriting r31
			  : "=r" (mario)
			  :
			  : "r31");
			  
    for (int i = 0; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		if (Players[i] == mario)
			MarioOnYoshi[i] = 1;
	}
	yoshi->mario = mario;
	
	SetMarioAddresses(mario);
	
	Yoshi_Ride(yoshi);
	
	SetMarioAddresses(Players[0]);
}

void OnDismountYoshi(MarioActor* mario){
	for (int i = 0; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		if (Players[i] == mario)
			MarioOnYoshi[i] = 0;
	}
	
	SetMarioAddresses(mario);
	
	Mario_GetOffYoshi(mario);
	
	SetMarioAddresses(Players[0]);
}

int IsOnYoshi(MarioActor* mario){
	for (int i = 0; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		if (mario == Players[i] && MarioOnYoshi[i])
			return 1;
	}
	return 0;
}

//Doesnt get more hacky than this
//The way its written: if yoshi has mario on him, then all marios must be on yoshi
//This should fix that
int IsOnYoshi2(MarioActor* mario){
	MarioActor* pmario1 = 0;
	MarioActor* pmario2 = 0;
	MarioActor* pmario3 = 0;
	
	__asm__ ("addi %0,31,0\n\t"		//Forces compiler to stop overwriting possible mario registers
			 "addi %1,30,0\n\t"
			 "addi %2,29,0"
			  : "=r" (pmario1), "=r" (pmario2), "=r" (pmario3)
			  :
			  : "r29", "r30", "r31");
			  
	for (int i = 0; i < NUM_PLAYERS; i++){
		if (Players[i] == 0)
			continue;
		if ((pmario1 == Players[i] || pmario2 == Players[i] || pmario3 == Players[i]) && MarioOnYoshi[i])
			return 1;
	}
	return 0;
}

void OnWaterGunUpdate(MarioActor* mario){
	if (mario == Players[0])
		Mario_WaterGunUpdate(mario);
}

//Normally converts polar coordinates to cartesian
void CalcMultiplayerCameraPos(Vector* center, Vector* out, float rho, uint16_t theta ,uint16_t phi){
	switch (CameraMode){
		case 2: rho *= 0.667f; break;
		case 1: rho *= 1.5f; break;
	}
	
	CLBPolarToCross(center, out, rho, CameraTheta + theta, CameraPhi + phi);
}

int* CheckOtherObjectCollisions(volatile int* next){	//ugh
	volatile void* res = 0;
	int donext = 0;
	
	do {
		res = (void*)EMarios[++playerLoopIndex];
	} while (res == 0 && playerLoopIndex < NUM_PLAYERS);	//Loop through players, but dont allow non existent ones to pass
	
	if (playerLoopIndex >= NUM_PLAYERS){	//If end of list reached, reset list and continue
		playerLoopIndex = 0;
		donext = 1;
		res = (void*)Players[0];

		__asm__ volatile (	//continue asm
			 "lwz 0,0(%0)\n"
			 "\tstw 0,0xa8(1)\n"
			  : "=r" (next)
			  : 
			  : "r0", "r3", "r4", "r5", "r30");
	}
	__asm__ volatile (	//set current mario
			 "addi 31,%0,0\n"
			  : 
			  : "r" (res)
			  : "r0", "r3", "r4", "r5", "r30");	//don't clobber r31 so it stays changed
	return next;
}
void CheckOtherObjectCollisions2(){	//ugh
	if (playerLoopIndex == 0)
	{
		__asm__ volatile (	//Only reset count on first loop
			 "sth 0, 0x0048(3)\n"
			  : 
			  : 
			  : "r0", "r1", "r2", "r3", "r4");
	}
}

void ChangeAllPlayerStatus(MarioActor* mario, uint32_t u1, uint32_t u2, int u3){
	for (int i = 1; i < NUM_PLAYERS; i++)
		if (Players[i] != 0)
			SetMarioStatus(Players[i], u1, u2, u3);
	SetMarioStatus(mario, u1, u2, u3);
}
Yoshi* CreateYoshi(int size){
	CurrentYoshi = malloc(size);
	return CurrentYoshi;
}

/*
int checkMultiplayerMenu()
{
	int* menuTrans = *TGCCConsole2 + GFX_OFF + 0xCC;
	int* blackTrans = *TGCCConsole2 + GFX_OFF - 0x1B0 + 0xCC;
	int* sMarioCTrans = *TGCCConsole2 + GFX_OFF + 0x1B0 + 0xCC;
	//*menuTrans -= 0x10000000;
	//*blackTrans -= 0x10000000;
	
	if (isExit) // exiting timer
	{
		exitTimer++;
	}
	
	if (!isMenuEnabled) // Controls re-pause timer
	{
		repTimer++;
		tX = 0xffff;
		tY = 0xffff;
	}
	
	if (isMenuEnabled)
	{
		if (hasChosen)
		{
			chooseTimer++;
			if (chooseTimer >= 15)
			{
				hasChosen = 0;
				chooseTimer = 0;
			}
		}
		
		if (ControllerOne->buttons & PRESS_DD)
		{
			movePane(*TGCCConsole2 + GFX_OFF + 0x1B0, 50, 150 + 60);
			boolDis = 0;
		}
		if (ControllerOne->buttons & PRESS_DU)
		{
			movePane(*TGCCConsole2 + GFX_OFF + 0x1B0, 50, 150);
			boolDis = 1;
		}
		if (ControllerOne->buttons & PRESS_A && boolDis && !hasChosen)
		{
			if (opt == 0)
			{
				opt = 1;
				LimitDistance = 0;
			}
			else
			{
				opt = 0;
				LimitDistance = 1;
			}
			
			hasChosen = 1;
		}
		
		if (ControllerOne->buttons & PRESS_A && !boolDis && !hasChosen)
		{
			camDis += 0.5f;
			hasChosen = 1;
		}
		
		if (ControllerOne->buttons & PRESS_B && !boolDis && !hasChosen)
		{
			camDis -= 0.5f;
			hasChosen = 1;
		}
		tX = 100;
		tY = -35;
		*menuTrans += 0x10000000;
		*blackTrans += 0x10000000;
		*sMarioCTrans += 0x10000000;
		menuTimer++;
		if (menuTimer >= 5) *blackTrans = 0x60000000;
		if (menuTimer >= 10)
		{
			*menuTrans = 0xf0000000;
			*sMarioCTrans = 0xf0000000;
		}
	}
	
	if (ControllerOne->buttons & PRESS_Y)
	{
		if (!isMenuEnabled && repTimer >= 15)
		{
			isMenuEnabled = 1;
		}
		if (isMenuEnabled)
		{
			isExit = 1;
			menuTimer = 0;
			tX = 0xffff;
			tY = 0xffff;
			if (isExit && exitTimer >= 15)
			{
				while (*menuTrans > 0)
				{
					*menuTrans -= 0x10000000;
					*blackTrans -= 0x10000000;
					*sMarioCTrans -= 0x10000000;
				}
			
				if (*menuTrans <= 0)
				{
					*menuTrans = 0x00000000;
					*blackTrans = 0x00000000;
					*sMarioCTrans = 0x00000000;
					isMenuEnabled = 0;
					isExit = 0;
					exitTimer = 0;
					repTimer = 0;
				}
			}
		}
	}
}
*/

// Generated by wxHexEditor //
const int32_t ENEMYMARIO_VTABLE[0x3b] = {
  0x00000000, 0x00000000, 
  0x8003F738, 0x80007D70, 
  0x80276BD0, 0x802FA6F4, 
  0x80276ADC, 0x802FA6FC, 
  0x8003F814, 0x00000000, 
  0x00000000, 0x800452D0, 
  0x803370C0, 0x8033720C, 
  0x80337214, 0x8033721C, 
  0x80337220, 0x80337228, 
  0x8033722C, 0x80337230, 
  0x80337234, 0x80007FA8, 
  0x80007FA0, 0x80007F98, 
  0x80007F90, 0x80007F88, 
  0x80007F80, 0x803370E0, 
  0x803370E8, 0x803370EC, 
  0x803370F4, 0x803370F8, 
  0x80337100, 0x80337104, 
  0x802F7004, 0x802F7020, 
  0x802F703C, 0x802F7058, 
  0x802F7074, 0x802F7090, 
  0x80282AF4, 0x80247E50, 
  0x80007CFC, 0x80255A8C, 
  0x80007D60, 0x00000000, 
  0x00000000, 0x800452D8, 
  0x80044CA4, 0x800406CC, 
  EMarioControl, EMarioPlayerControl, 
  0x8004440C, 0x80244520, 
  0x80280FE8, EMarioDamageExec, 
  0x802853F8, 0x8024D17C, 
  0x80042E48 };

  // Generated by wxHexEditor //
const int32_t EMARIO_VTABLE[0x45] = {
  0x00000000, 0x00000000, 
  0x80039BF4, 0x80007D70, 
  0x80039810, 0x802FA6F4, 
  0x800397B4, 0x802FA6FC, 
  0x80039148, 0x00000000, 
  0x00000000, 0x80039F5C, 
  0x803370C0, 0x8033720C, 
  0x80337214, 0x8033721C, 
  0x80337220, 0x80337228, 
  0x8033722C, 0x80337230, 
  0x80337234, 0x80007FA8, 
  0x80007FA0, 0x80007F98, 
  0x80007F90, 0x80007F88, 
  0x80007F80, 0x803370E0, 
  0x803370E8, 0x803370EC, 
  0x803370F4, 0x803370F8, 
  0x80337100, 0x80337104, 
  0x802F7004, 0x802F7020, 
  0x802F703C, 0x802F7058, 
  0x802F7074, 0x802F7090, 
  EMarioReceiveMessage, 0x80217CA8, 
  0x80007CFC, 0x80007D40, 
  0x80007D60, 0x80218CC0, 
  0x80218A48, 0x80039600, 
  0x8003BF44, 0x802182F0, 
  0x80218414, 0x802184DC, 
  0x8021818C, 0x80218020, 
  0x80217FC8, 0x80217DE4, 
  0x80218344, 0x8003952C, 
  0x80217D88, 0x80217D6C, 
  0x80217CC8, 0x80217B30, 
  0x80217990, 0x8003C460, 
  0x8003BE2C, 0x8003BCE0, 
  0x8003BF38, 0x80007DFC, 
  0x80007E04 };
