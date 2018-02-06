#ifndef SMS_H
	#define SMS_H

	#include <stdlib.h>
	#include <stdint.h>
	#include <stdarg.h>

	#define PRESS_START	0x1000
	#define PRESS_B		0x0200
	#define PRESS_A		0x0100
	#define PRESS_Z		0x0010
	#define PRESS_X		0x0400
	#define PRESS_Y		0x0800
	#define PRESS_DU	0x0008
	#define PRESS_DD	0x0004
	#define PRESS_DL	0x0001
	#define PRESS_DR	0x0002
	#define PRESS_L		0x0040
	#define PRESS_R		0x0020

	#define MARIOFLAG_ALIVE						0x00000001
	#define MARIOFLAG_INVISIBLE					0x00000004
	#define MARIOFLAG_ALLDEAD					0x00000F00
	#define MARIOFLAG_GAMEOVER					0x00000400
	#define MARIOFLAG_SLIP						0x00000080
	#define MARIOFLAG_HASHELMET_FOLLOWCAMERA	0x00001000
	#define MARIOFLAG_HASHELMET					0x00002000
	#define MARIOFLAG_HASFLUDD					0x00008000
	#define MARIOFLAG_SPLASH					0x00010000
	#define MARIOFLAG_PUDDLE					0x00020000
	#define MARIOFLAG_SHIRT						0x00100000
	#define MARIOFLAG_GONE						0x00200000
	
	#define STATE_NUMBER	0x0000000F
	#define STATE_AIRBORN	0x00000800
	#define STATE_DOJUMP	0x00000080
	#define STATE_AIRBORN	0x00000800
	#define STATE_CUTSCENE	0x00001000
	#define STATE_STUNNED	0x00002000
	
	#define STATE_RUNNING	0x04000440
	#define STATE_IDLE		0x0C400201
	#define STATE_STOP		0x0C00023D
	#define STATE_SPIN		0x00000441
	#define STATE_JUMPSPIN	0x00000890
	#define STATE_JUMPSPIN1	0x00000895
	#define STATE_JUMPSPIN2	0x00000896
	#define STATE_JUMP		0x02000880
	#define STATE_D_JUMP	0x02000881
	#define STATE_TRIPLE_J	0x00000882
	#define STATE_JMP_LAND  0x04000470
	#define STATE_HVY_LAND	0x04000473
	#define STATE_D_LAND	0x04000472
	#define STATE_T_LAND	0x0800023A
	#define STATE_JUMPSIDE	0x00000880
	#define STATE_SIDESTEP	0x0C008220
	#define STATE_SIDE_FLIP 0x00000887
	#define STATE_FALL      0x0000088C
	#define STATE_SWIM		0x000024D7
	#define STATE_DIVE		0x0080088A
	#define STATE_DIVEJUMP	0x02000889
	#define STATE_DIVESLIDE	0x00800456
	#define STATE_CLIMB		0x18100340
	#define STATE_CLIMBUP	0x10100343
	#define STATE_WALLJUMP	0x02000886
	#define STATE_WALLSLIDE 0x000008A7
	#define STATE_HANG		0x3800034B
	#define STATE_HANGCLIMB	0x3000054F
	#define STATE_SLAMSTART	0x008008A9
	#define STATE_SLAM		0x0080023C
	#define STATE_SPRAY		0x0C008220
	#define STATE_THROWN	0x000208B8
	#define STATE_HOVER		0x0000088B
	#define STATE_STUCK		0x0002033C
	#define STATE_TALKING	0x10001308
	#define STATE_TURNING	0X00000444
	//add new
	#define STATE_SHINE_C	0x00001302 // Collected Shine Sprite
	#define STATE_DEATH		0x00020467
	#define STATE_DOOR_F_O	0x00001321 // Door open fail
	#define STATE_WALL_S_L	0x04000471
	#define STATE_WALL_SLD	0x000008A7
	#define STATE_F_KNCK_H	0X000208B0 // hard knockback from front (bumping into a wall from dive)
	#define STATE_KNCK_LND	0X00020462 // Landing from front knockback
	#define STATE_KNCK_GND  0x00020466 // Front knockback while grounded
	#define STATE_FIRE_HIT	0x000208B7
	#define STATE_FIRE_RVR	0x08000239 // Recover from fire on ground
	#define STATE_HOVER_F	0x0000088D // Falling from hover
	#define STATE_SLIDE_R1	0x000008A6 // Recover from slide by flipping
	#define STATE_SLIDE_R2 	0x00000386 // Recover from slide by getting up
	#define STATE_R_SPRAY	0x0C008220 // Recover from spray
	#define STATE_G_POUND	0x008008A9 // Ground pounding
	
	//#define
	
	#define BGM_DOLPIC          0x80010001
	#define BGM_BIANCO          0x80010002
	#define BGM_MAMMA           0x80010003
	#define BGM_PINNAPACO_SEA   0x80010004
	#define BGM_PINNAPACO       0x80010005
	#define BGM_MARE_SEA        0x80010006
	#define BGM_MONTEVILLAGE    0x80010007
	#define BGM_SHILENA         0x80010008
	#define BGM_RICCO           0x80010009
	#define BGM_GET_SHINE       0x8001000A
	#define BGM_CHUBOSS         0x8001000B
	#define BGM_MISS            0x8001000C
	#define BGM_BOSS            0x8001000D
	#define BGM_MAP_SELECT      0x8001000E
	#define BGM_BOSSPAKU_DEMO   0x8001000F
	#define BGM_MAIN_TITLE      0x80010010
	#define BGM_CHUBOSS2        0x80010011
	#define BGM_EXTRA           0x80010012
	#define BGM_DELFINO         0x80010013
	#define BGM_MAREVILLAGE     0x80010014
	#define BGM_CORONA          0x80010015
	#define BGM_KAGEMARIO       0x80010016
	#define BGM_CAMERA          0x80010017
	#define BGM_MONTE_ONSEN     0x80010018
	#define BGM_MECHAKUPPA      0x80010019
	#define BGM_AIRPORT         0x8001001A
	#define BGM_UNDERGROUND     0x8001001B
	#define BGM_TITLEBACK       0x8001001C
	#define BGM_MONTE_NIGHT     0x8001001D
	#define BGM_CASINO          0x8001001E
	#define BGM_EVENT           0x8001001F
	#define BGM_TIME_IVENT      0x80010020
	#define BGM_SKY_AND_SEA     0x80010021
	#define BGM_MONTE_RESCUE    0x80010022
	#define BGM_MERRY_GO_ROUND  0x80010023
	#define BGM_SCENARIO_SELECT 0x80010024
	#define BGM_FANFARE_CASINO  0x80010025
	#define BGM_FANFARE_RACE    0x80010026
	#define BGM_CAMERA_KAGE     0x80010027
	#define BGM_GAMEOVER        0x80010028
	#define BGM_BOSSHANA_2ND3RD 0x80010029
	#define BGM_BOSSGESO_2DN3RD 0x8001002A
	#define BGM_CHUBOSS_MANTA   0x8001002B
	#define BGM_MONTE_LAST      0x8001002C
	#define BGM_SHINE_APPEAR    0x8001002D
	#define BGM_KUPPA           0x8001002E
	#define BGM_SPACEWORLD		0x80011030
	
	#define SND_PIPE			9598
	
	//#define GFX_OFF				0x09A4 - E3
	#define GFX_OFF				0x07F4
	
	#define AIRPORT		0
	#define DOLPIC0		1
	#define	BIANCO0		2
	#define RICCO0		3
	#define MAMMA0		4
	#define PINNABEACH0	5
	#define SIRENA0		6
	#define DELFINO0	7
	#define	MONTE0		8
	#define MARE0		9
	#define NONE0		10
	#define SCALE0		11
	#define TEST10		12
	#define PINNAPARCO0	13
	#define CASINO0		14
	
	#define GFX_OFF     0x09A4
	

typedef float Mtx[3][4];
typedef float Mtx44[4][4];

enum GXProjectionType
{
	GX_PERSPECTIVE = 0,
	GX_ORTHOGRAPHIC = 1
};

typedef struct
{

	float x, y, z;

} Vec, *VecPtr, Point3d, *Point3dPtr;

typedef	struct	{
    Point3d	position;
    Point3d	target;
    Vec		up;
    float	fovy;
    float	znear;
    float	zfar;
    Mtx		viewMtx;
    Mtx44	projMtx;
}   Camera;

typedef	struct {
    int		xorg;
    int		yorg;
    int		width;
    int		height;
}   ViewPort;

typedef struct{
	int u1;
} WaterGun;

typedef struct{
	uint16_t buttons; // 0x0
	int8_t lanalogx; // 0x4
	int8_t lanalogy; // 0x8
	int8_t ranalogx; // 0xC
	int8_t ranalogy; // 0xA
	uint8_t ltrig; // 0xE
	uint8_t rtrig; // 0x12
	uint8_t status; //0x16
	uint8_t u2;
	uint8_t u3;
	uint8_t u4;
} __attribute__((packed)) Controller;

typedef struct{
	void* type;
	void* u1[55];
	int u2;
	int u3[7];
} MarioGamePad;

// MarDirector* mardirector = (MarDirector*)(r13 + 0x9FB8)
typedef struct{
	int u1;
} MarDirector;

typedef struct{
	float x;
	float y;
	float z;
} Vector;

typedef struct {
	int flag1;
	int flag2;
	int flag3;
	int flag4;
	int flag5;
	int flag6;
	int flag7;
	int flag8;
	int flag9;
	int flag10;
} NormalSoundData;

typedef struct {
	float u1;
	float u2;
	float u3;
	float u4;
} HitTable;

typedef struct{
	char* colKey;
	int flag;
} ColData;

typedef struct AnimData_t{
	char* modelKey;
	int unk1;
	int unk2;
	int unk3;
	int unk4;
	int unk5;
	int unk6;
	int unk7;
	int unk8;
	int unk9;
	char* animModel;
	char* animKey;
	int unk10;
	int unk11;
	int unk12;
} AnimData;

typedef struct {
	int info1;
	AnimData* aData;
} AnimInfo;

typedef struct {
	int flag1;
	int flag2;
	int flag3;
	HitTable* hitData;
} HitInfo;

typedef struct {
	int flag1;
	ColData* cData;
} ColInfo;

typedef struct {
	int flag1;
	NormalSoundData* normSoundData; // okay what?
} SoundInfo;

typedef struct ObjectData_t {
	char* modelKey;
	float unknown1;
	char* shiftJis;
	char* shiftJis2;
	AnimInfo* aInfo;
	HitInfo* hInfo;
	ColInfo* cInfo;
	SoundInfo* sInfo;
	int unused1;
	int unused2;
	int unused3;
	int unused4;
	float unknown2;
	int flag1;
	int flag2;
} ObjectData;

struct HitActor_t;
struct EMario_t;
struct EnemyMario_t;
struct WaterGun_t;
struct Yoshi_t;
struct ObjectData_t;
struct AnimData_t;

typedef struct PolarSubCamera_t {
	void* Type;
	void* u2;
	int u3;
	int u4;
	Vector position;
	int u5;
	void* u6;
	int u7;
	Vector u8;
	float u9;
	int u10;
	Vector rotation;
	Vector u11;
	int u12[51];
	MarioGamePad* gamepad;
} PolarSubCamera;

typedef struct MapObjBase_t{
	void* Type;			//0
	void* u2;
	int u3;
	int u4;	
	Vector position;	//10
	int u5;
	void* u6;			//20
	Vector scale;
} __attribute__((packed)) MapObjBase;

typedef struct HitActor_t{
	void* Type;			//0
	void* u2;
	int u3;
	int u4;	
	Vector position;	//10
	int u5;
	void* u6;			//20
	Vector scale;
	Vector direction;	//30
	void* u7;
	void* u8;			//40
	struct HitActor_t** colarray;
	uint16_t colcount;
	uint16_t colarraysize;
	int colsettings;
	float bound1;			//50
	float bound2;
	float bound3;
	float bound4;
	float bound5;			//60
	int colflags;
	int u18;
	int u19;
	void* u20;			//70
	void* u21[0x2F];
	ObjectData* objData; // 130
} __attribute__((packed)) HitActor;

typedef struct {
	void* Type;			//0
	void* u2;
	int u3;
	int u4;	
	Vector position;	//10
	int u5;
	void* u6;			//20
	Vector scale;
	Vector direction;	//30
	void* u7;
	void* u8;			//40
	struct HitActor_t** colarray;
	uint16_t colcount;
	uint16_t colarraysize;
	int colsettings;
	float bound1;			//50
	float bound2;
	float bound3;
	float bound4;
	float bound5;			//60
	int colflags;
	int u18;
	int u19;
	void* u20;			//70
	void* u21;			//74
	void* u22;			//78
	int snd1;			//7C
	int snd2;			//80
	char* bas;			//84
	int status;			//88
	int init;			//8c
	int status_timer;	//90
	int temp6;			//94
	int temp7;			//98
	int temp8;			//9c
	int temp9;			//a0
	int temp10;			//a4
	int temp11;			//a8
	int temp12;			//ac
	float dirY;			//b0
	int current;        //b4
	float u23;			//b8
	float u24;			//bc
	float u25;			//c0
	void* u26;			//c4
	float u27;			//c8
	float u28;			//cc
	int reserved1;		//d0
	int u29; 			// Used - d4
	int analogX;		//d8
	int analogY;		//dc
	int reserved4;		//e0
	int reserved5;		//e4
	void* u30[18];
	ObjectData* objData; // 130
} __attribute__((packed)) MultiActor;

typedef struct {
	void* Type;			//0
	void* u2;
	int u3;
	int u4;	
	Vector position;	//10
	int u5;
	void* u6;			//20
	Vector scale;
	Vector direction;	//30
	void* u7;
	void* u8;			//40
	struct HitActor_t** colarray;
	uint16_t colcount;
	uint16_t colarraysize;
	int colsettings;
	float bound1;			//50
	float bound2;
	float bound3;
	float bound4;
	float bound5;			//60
	int colflags;
	int u18;
	int u19;
	void* u20;			//70
	void* u21;
	void* u22;
	int u23;
	int isFlipped;
	int flipTimer;
} __attribute__((packed)) flipBlockActor;

typedef struct{
	void* Type;
	void* u2;
	int u3;
	int hitCount;
	Vector position;
	int u5;
	void* u6;
	Vector scale;
	Vector direction;
	void* u7;
	void* u8;
	void* u9;
	int u10;
	int collision;
	float u12;
	float u13;
	float u14;
	float u15;
	float u16;
	int u17;
	int u18;
	int u19;
	void* u20;
} BlockActor;

typedef struct {
	void* Type;			//0
	void* u2;
	int u3;
	int u4;	
	Vector position;	//10
	int u5;
	void* u6;			//20
	Vector scale;
	Vector direction;	//30
	void* u7;
	void* u8;			//40
	struct HitActor_t** colarray;
	uint16_t colcount;
	uint16_t colarraysize;
	int colsettings;
	float bound1;			//50
	float bound2;
	float bound3;
	float bound4;
	float bound5;			//60
	int colflags;
	int u18;
	int u19;
	void* u20;			//70
	void* u21;
	void* u22;
	int u23;
	int isDown;
	int isRot;
} __attribute__((packed)) hexActor;

typedef struct{
	void* Type;					//0
	void* u2;					//4
	int u3;						//8
	int u4;						//c
	Vector position;			//10
	int u5;
	void* u6;					//20
	Vector scale;
	Vector direction;			//30
	void* u7;
	void* u8;					//40
	HitActor** colarray;
	uint16_t colcount;
	uint16_t colarraysize;
	int colsettings;
	float bound1;				//50
	float bound2;
	float bound3;
	float bound4;
	float bound5;				//60
	int colflags;
	int u18;
	int u19;
	void* u20;					//70
	int u21;
	int u22;
	uint32_t status;
	uint32_t laststatus;		//80
	int statustime;
	void* u23;					//88
	void* u24;					//8c
	void* u25;					//90
	uint16_t rotx;				//94
	uint16_t roty;				//96
	uint16_t rotz;				//98
	uint16_t roty2;				//9a
	void* u26;					//9c
	void* u27;					//a0
	Vector speed;				//a4
	void* u28[26];				//b0
	int flags;					//118
	void* u29[178];				//11c
	WaterGun* watergun;         //3e4
	void* u31;					//3e8
	void* u32;					//3ec
	struct Yoshi_t* yoshi;		//3f0
	void* u33[40];				//3f4
	MarioGamePad* gamepad; 		//4f4
} __attribute__((packed)) MarioActor;

typedef struct EnemyMario_t{
	void* Type;			//0
	void* u2;
	int u3;
	int u4;	
	Vector position;	//10
	int u5;
	void* u6;			//20
	Vector scale;
	Vector direction;	//30
	void* u7;
	void* u8;			//40
	HitActor** colarray;
	uint16_t colcount;
	uint16_t colarraysize;
	int colsettings;
	float bound1;			//50
	float bound2;
	float bound3;
	float bound4;
	float bound5;			//60
	int colflags;
	int u18;
	int u19;
	void* u20;			//70
	int u21;
	int u22;
	uint32_t status;
	uint32_t laststatus;//80
	int statustime;
	void* u23[36];		//88
	int flags;			//118
	void* u24[64];
	char name[16];		//218
	void* u25[180];		//228
	MarioGamePad* gamepad; //4fc
	void* u26[3940];
	uint16_t emarioflags;
	uint16_t emariodamage;	//4294
	uint16_t emariohealth;	//4296
	uint16_t u27;			//4298
	int u28;
	int u29;
	struct EMario_t* emario;
	int u30;
	int u31;
	float u32;
	float u33;
	uint16_t u34;
	uint16_t u35;
	uint16_t u36;
	uint16_t hpmetertimer;
} __attribute__((packed)) EnemyMario;

typedef struct EMario_t{
	void* Type;			//0
	void* u2;
	int u3;
	int u4;	
	Vector position;	//10
	int u5;
	void* u6;			//20
	Vector scale;
	Vector direction;	//30
	void* u7;
	void* u8;			//40
	HitActor** colarray;
	uint16_t colcount;
	uint16_t colarraysize;
	int colsettings;
	float bound1;			//50
	float bound2;
	float bound3;
	float bound4;
	float bound5;			//60
	int colflags;
	int u18;
	int u19;
	void* u20;			//70
	void* u21[55];
	EnemyMario* enemymario;
} __attribute__((packed)) EMario;

#define ITEMFLAG_STATIC 0x00000010

typedef struct{
	void* Type;
	void* u2;
	int u3;
	int u4;
	Vector position;
	int u5;
	void* u6;
	Vector scale;
	Vector direction;
	void* u7;
	void* u8;
	void* u9;
	int u10;
	int itemtype;
	float u12;
	float u13;
	float u14;
	float u15;
	float u16;
	int u17;
	int u18;
	int u19;
	void* u20;
	//0x74
	int pad1[14];
	Vector velocity;
	int pad2[14];
	int flags;
} __attribute__((packed)) ItemActor;

typedef struct{
	uint8_t u1;	//00
	uint8_t u2;
	uint8_t u3;
	uint8_t u4;
	int u5;		//04
	int u6;		//08
	int u7;		//0c
	MarioActor* mario;
} __attribute__((packed)) Yoshi;

typedef struct{
	void* u1[6];
	int count;			//18
	void* u1_2[21];
	Vector position;	//70
	void* u2[11];		//7c
	float u3;			//a8
	void* u4[4];		//7c
	float u5; 			//bc
	void* u6[4];		//c0
	float u7; 			//d0
	void* u8[9];		//d4
	float u9;			//f8
	void* u10[13];
	uint16_t u11;		//134
	uint16_t u12;
} __attribute__((packed)) WaterEmitInfo;

typedef struct {
 int u1;
 float u2;
} Sound;

typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
} JUTRect;
typedef struct {
	void* type;
	int content[64];
} J2DGrafContext;
typedef struct {
	void* type;
	int content[64];
} J2DOrthoGraph;
typedef struct {
	void* type;
	int content[9];
} J2DPrint;
typedef struct {
	void* type;
} JUTResFont;
typedef struct {
} ResFONT;
typedef struct {
	void* type;
	int pad1[2];
	int flags;
	JUTRect bounds;
	int content[100];
} J2DTextBox;
typedef struct {
	void* type;
	int content[64];
} J2DPaneO;
typedef struct {
	void* type;
	int content[64];
} J2DScreen;

typedef struct {
	int charIndex;
	int unk1;
	uint8_t voice;
} JMSMesgEntry;

typedef struct {
	int unk1;
	char* textBuf;
	JMSMesgEntry* entry[10];
} TalkMesEntry;

typedef struct {
	void* type;
	void* data[596];
	TalkMesEntry* msgEntry;
} Talk2D;

typedef struct {
	void* type;
} GCConsole;
typedef struct {
	void* type;
} PollutionManager;
typedef struct {
	void* type;
} ItemManager;
typedef struct {
	void* type;
	void* u1;
	int flags1;
	int flags2;
	int timer;
} TrembleModelEffect;
typedef struct {
	float a1[4];
	float a2[4];
	float a3[4];
} A3_A4_f;

typedef struct {
	int x;
	int y;
	int w;
	int h;
} Rect;

typedef struct {
	void* type;
	int type2;
	int id;
	int isVisible;
	int pane_id;
	JUTRect rect;
	JUTRect cRect;
	JUTRect clipRect;
	JUTRect scissorBounds;
	void* unk1[0x4A];
	long* tmem;
} J2DPane;

typedef struct CARDFileInfo
{
    int chan;
    int fileNo;
    int offset;
    int length;
    int iBlock;
} CARDFileInfo;

const int32_t testObjectVTable[119] =
{
    0x00000000, 0x00000000, 0x801C4580, 0x80007D70, 
    0x801AF750, 0x802FA6F4, 0x801B2FF0, 0x802FA6FC, 
    0x801B3364, 0x00000000, 0x00000000, 0x801C4918, 
    0x803370C0, 0x8033720C, 0x80337214, 0x8033721C, 
    0x80337220, 0x80337228, 0x8033722C, 0x80337230, 
    0x80337234, 0x80007FA8, 0x80007FA0, 0x80007F98, 
    0x80007F90, 0x80007F88, 0x80007F80, 0x803370E0, 
    0x803370E8, 0x803370EC, 0x803370F4, 0x803370F8, 
    0x80337100, 0x80337104, 0x802F7004, 0x802F7020, 
    0x802F703C, 0x802F7058, 0x802F7074, 0x802F7090, 
    0x801B305C, 0x800C6E9C, 0x801B4194, 0x80007D40, 
    0x800C6E94, 0x80218CC0, 0x801AFA4C, 0x802187D0, 
    0x801B345C, 0x801AFF74, 0x801B35F8, 0x801B36B8, 
    0x8021818C, 0x80218020, 0x80217FC8, 0x80217DE4, 
    0x801AFA80, 0x801B4114, 0x80217D88, 0x80217D6C, 
    0x80217CC8, 0x80217B30, 0x80217990, 0x801B401C, 
    0x801B0430, 0x801B0738, 0x801B12F8, 0x801B1368, 
    0x801B9C24, 0x801B1058, 0x801B118C, 0x800C6ED0, 
    0x801B17DC, 0x800C6F08, 0x801B238C, 0x801B1D64, 
    0x801B12F0, 0x801AEBEC, 0x800C6F0C, 0x800C6F10, 
    0x800C6F14, 0x801B02D0, 0x801C42E4, 0x801B43D0, 
    0x801B03B8, 0x801B03F4, 0x801B08F4, 0x800C6F18, 
    0x800C6F20, 0x801AEBE4, 0x801B1764, 0x801B4F30, 
    0x801B3F2C, 0x801B4580, 0x801B4528, 0x801B4644, 
    0x801B46C4, 0x801B48F8, 0x801B4D78, 0x801B47E4, 
    0x801B4DD0, 0x801B4950, 0x801B49A4, 0x801B4200, 
    0x801B4BDC, 0x801B49F8, 0x801B4CEC, 0x801B4274, 
    0x801B4D54, 0x801B4470, 0x801B44DC, 0x801B444C, 
    0x801B3938, 0x801B3ADC, 0x801B3B8C, 0x801B3DFC, 
    0x801B3EE4, 0x801B3D64, 0x801B3DF0, 
};

//For C++ inheritence
#define GetObjectFunction( object, func ) (void*)*(void**)((int)*(int*)object + func)
#define Director_GameUpdate 0x64
#define HitActor_TouchPlayer 0x0148
#define HitActor_ReceiveMessage 0xA0

//Only works with objects with vtables
#define GetType( object ) *(int*)object
#define TYPE_ENEMYMARIO 0x803aef24
#define TYPE_EMARIO 	0x803ae404
#define TYPE_ITEMNOZZLE 0x803c942c


//Free is done automatically on stage transition
#define malloc(n) __nwa__FUl((n))
#define free(n) __dla__FUl((n))

void GXSetScissor(int x, int y, int x2, int y2);
void GXSetViewport(float x, float y, float w, float h, float nearZ, float farZ);
void GXSetProjection(float mtx[4][4], int projType);
void GXFlush();
void C_MTXLookAt(Mtx mtx, Point3dPtr* camPos, VecPtr* camUp, Point3dPtr* target);
void setSrcRect(int viewPortObj, int rect);
void GXInvalidateTexAll();

void J2DOrthoGraph_Create(J2DOrthoGraph* targetaddr, JUTRect* view);

void J2DGrafContext_Setup2D(J2DGrafContext* graphics);

void J2DPrint_Create(J2DPrint* targetaddr, JUTResFont* font, int u);
float J2DPrint_GetWidth(J2DPrint* j2dprint, char* text);
void J2DPrint_Initiate(J2DPrint* j2dprint);
void J2DPrint_Print(J2DPrint* j2dprint, int x, int y, char* text, int u1, int u2, int u3);
void J2DPrint_Delete(J2DPrint* j2dprint, int mask);

#define GameFont (*(ResFONT**)((*(int*)(SceneReference - 0x6038)) + 0x48))
#define GameStrTable (RTOC - 19304)
void J2DTextBox_Create(J2DTextBox* targetaddr, int u1, JUTRect* bounds, ResFONT* font, void* table, int HBinding, int VBinding);
void J2DTextBox_Draw(J2DTextBox* textbox);
void J2DTextBox_Drawii(J2DTextBox* textbox, int a1, int a2);
void J2DTextBox_DrawSelf(J2DTextBox* textbox, int a1, int a2, A3_A4_f* matrix);
void J2DTextBox_SetString(J2DTextBox* textbox, char* string);
char* J2DTextBox_GetStringPtr(J2DTextBox* textbox);
void J2DTextBox_Delete(J2DTextBox* textbox);

void J2DPane_Draw(J2DPane* pane, int a1, int a2, J2DGrafContext* graphics, int a3);
void J2DPane_SetBasePosition(J2DPane* pane, int pos);
void J2DPane_MakeMatrix(J2DPane* pane, int a1, int a2);

void J2DScreen_Draw(J2DScreen* pane, int a1, int a2, J2DGrafContext* graphics, int a3);

void JUTRect_Set(JUTRect* rect, int x, int y, int w, int h);

void setTalkBox(Talk2D* tManager, char* textBuffer, JMSMesgEntry* entry);

void MarDirector_SetupObjects(MarDirector* director);
void Drama_PrepareUpdate(HitActor* this, int a1, void* drama, void* graphics, int obj);

/*
typedef ObjItemManager{
	int a1;
	int a2;
	void (*__dt__)();
	void (*GetType)();
	void (*Load)();
	void (*Save)();
	void (*LoadAfter)();
	void (*SearchF)();
	void (*Perform)();
	void (*CreateModelData)();
	void (*CreateModelData)();
	void (*CreateAnmData)();
	void (*CreateModelDataArray)();
	void (*ClipActors)();
	void (*SetFlagOutOfCube)();
	void (*CreateSpcBinary)();
	bool (*HasMapCollision)();
}*/

register void* RTOC	__asm ("r2");
register void* SceneReference __asm ("r13");

// math
float cosf(float);
float sinf(float);
float sqrtf(float);

// GC
//static void (*GXSetBlendMode)(int a1, int a2, int a3, int a4) = (void*)0x80361dd0;
//static void (*GXBegin)(int a1, int a2, int a3) = (void*)0x8035df88;

static const Controller* Controllers = (Controller*)0x80404454;
static const Controller* ControllerOne = (Controller*)0x80404454;
static const Controller* ControllerTwo = (Controller*)0x80404460;
static const Controller* ControllerThree = (Controller*)0x8040446c;
static const Controller* ControllerFour = (Controller*)0x80404478;

static MarioGamePad* GamePads = (MarioGamePad*)0x8057738c;
static MarioGamePad* GamePadOne = (MarioGamePad*)0x8057738c;
static MarioGamePad* GamePadTwo = (MarioGamePad*)0x8057748c;
static MarioGamePad* GamePadThree = (MarioGamePad*)0x8057758c;
static MarioGamePad* GamePadFour = (MarioGamePad*)0x8057768c;

void MarioGamePad_Read();
void MarioGamePad_Update(MarioGamePad* pad);
void MarioGamePad_Reset(MarioGamePad* pad);

static void* gpSystemFont = (void*)0x8040e188;
static void* gpRomFont = (void*)0x8040e18c;

// SMS
static void* gpApplication = (void*)0x803e9700;
static Talk2D** TalkManager = (Talk2D**)0x8040ddd8;
static void** gpMarioParticleManager = (void**)0x8040e150;
static void** gpModelWaterManager = (void**)0x8040e138;
uint32_t* gModelWaterManagerWaterColor = (uint32_t*)0x803dd898;
unsigned int CalcKeyCode(char* key);
void Vector_Add(Vector* v1, Vector* v2, Vector* vo);
void Vector_Subtract(Vector* v1, Vector* v2);
void Vector_Normalize(Vector* vi, Vector* vo);
void Vector_Scale(Vector* vi, float scale);
float Vector_Magnitude(Vector* v);
void Talk2D_OpenWindow(Talk2D* talkmanager, int a1, float f1);
void openNormalTalkWindow(Talk2D* manager);
void DrawWaterBackground(GCConsole* console);

void StampPollution(PollutionManager* pollution, int stamp, float x, float y, float z, float r);
void CleanPollution(PollutionManager* pollution, float x, float y, float z, float r);

// Stage
static MarDirector** gpMarDirector = (void*)0x8040e178;
static void** gpItemManager = (void**)0x8040df10;
static void** gpMap = (void*)0x8040de98;
static PollutionManager** gpPollution = (void*)0x8040ded0;
static void** gpStrategy = (void*)0x8040e080;
static void** gpSunManager = (void*)0x8040d0c0;
static HitActor** gpSunModel = (void*)0x8040d0c8;

static uint8_t* ChangeScenario = (void*)0x003e9712;
static uint8_t* ChangeEpisode = (void*)0x003e9713;
void ChangeStage(MarDirector* director, uint32_t stageinfo);
HitActor* SearchF(void* namereflist, int keycode, char* ref);
#define SearchObjByRef(ref) SearchF((void*)*(((int*)*(int*)(SceneReference - 0x5db8)) + 1), CalcKeyCode((ref)), (ref))
int GetShineStage(uint8_t stageid);

int IsPolluted(void);

//Camera
static HitActor** gpCamera = (void*)0x8040d0a8;
void Camera_AddMultiPlayer(void* camera, Vector* position);
void Camera_RemoveMultiPlayer(void* camera, Vector* position);
void Camera_CreateMultiPlayer(void* camera, unsigned char players);
void PolarSubCamera_UpdateMultiplayer(void* camera);

// Mario
static HitActor** gpMarioOriginal = (void*)0x8040e0e8;
static HitActor** gpMarioAddress = (void*)0x8040e108;
#define GetFludd(mario) (HitActor*)((mario) + 0x03E4)
static Vector** gpMarioPos = (void*)0x8040e10c;
static uint16_t** gpMarioAngleX = (void*)0x8040e110;
static uint16_t** gpMarioAngleY = (void*)0x8040e114;
static uint16_t** gpMarioAngleZ = (void*)0x8040e118;
static float** gpMarioSpeedX = (void*)0x8040e11c;
static float** gpMarioSpeedY = (void*)0x8040e120;
static float** gpMarioSpeedZ = (void*)0x8040e124;
static const uint16_t** gpMarioLightID = (void*)0x8040e128;
static int** gpMarioFlag = (void*)0x8040e12c;
static float** gpMarioThrowPower = (void*)0x8040e130;
static const void*** gpMarioGroundPlane = (void*)0x8040e134;
MarioActor* GetMarioHitActor();
HitActor* GetFLUDD();
HitActor* GetMarioYoshi();
int GetMarioHP();
int GetMarioStatus();
int GetMarioStatusFromHitActor(MarioActor* mario);
void IncGoldCoinFlag(uint32_t coinptr, int stage, int amount);
#define IncrementCoin(amount) incGoldCoinFlag(*(int*)(SceneReference - 0x6060), GetShineStage((*(int*)(gpApplication + 0x0E)) & 0xFF), (amount))
void GetMarioMapPosition();
void ThrowMario(void*, void*, float, float, float);
void SetMarioAnim(float a1, int a2, int a3);
int IsMarioJumping();
int SMS_IsMarioDashing();
void SetMarioStatus(MarioActor* mario, int a2, int a3, int a4);
#define MarioDoJump(mario) SetMarioStatus((mario), 0x02000881, 0, 0)
#define MarioDoThrow(mario) SetMarioStatus((mario), 0x000208B8, 0, 0)
void EmitSweat(MarioActor* mario);
void Fludd_Emit(WaterGun* fludd);
void Mario_StartVoice(MarioActor* mario, int id);
void Mario_SetGamePad(MarioActor* mario, MarioGamePad* gamepad);
void Mario_CheckController(HitActor* mario, void* drama, void* graphics);
void Mario_ReceiveMessage(MarioActor* mario, HitActor* other, unsigned long message);
void Mario_PlayerControl(MarioActor* mario, void* drama, void* graphics);
void Mario_CheckCollision(MarioActor* mario);
void Mario_DamageExec(MarioActor* mario, HitActor* other, int u1, int u2, int u3, float f1, int u4, float f2, short u5);
void Mario_IncHP(MarioActor* mario, int n);
void Mario_DecHP(MarioActor* mario, int n);
void EnemyMario_CheckController(HitActor* enemymario, void* drama, void* graphics);
void SetMarioVelocity(MarioActor* mario, float vel);
void StartTrembleEffect(TrembleModelEffect* effectmgr, float maxTremble, float minTremble, float damp, int timer);
void Mario_WearGlasses(MarioActor* mario);
void MapObjBase_RemoveMapCollision(MapObjBase* obj);
void Mario_InitValues(MarioActor* mario);
void Mario_Trample(MarioActor* mario, HitActor* other);
void Mario_SetAnimation(MarioActor* mario, int id, float f1);
void Mario_SetStatusToJumping(MarioActor* mario, long u1, long u2);
void Mario_GetOffYoshi(MarioActor* mario);
void Mario_WaterGunUpdate(MarioActor* martin);
void mario_initModel(MarioActor* mario);
void mario_initValues(MarioActor* mario);
#define GetMarioTrembleEffect(mario) ((TrembleModelEffect*)*((void**)(mario) + 0x014F))

void Yoshi_Ride(Yoshi* yoshi);

void WaterGun_Create(WaterGun* fludd, MarioActor* mario);
void WaterGun_Init(WaterGun* fludd);
void WaterGun_ChangeNozzle(void* this, int nozzletype, int nozzleslot);
void WaterGun_Update(WaterGun*, int, void*);

#define MARIOMSG_THROW		0x07
#define MARIOMSG_HURTFIRE	0x0a
#define MARIOMSG_HURT		0x0e
void SendMsgToMario(MarioActor* mario, int msg);

// Objects
#define OBJ_WATER			0x20000002
#define OBJ_ONEUP			0x20000006
#define OBJ_COIN			0x2000000E
#define OBJ_BLUECOIN		0x20000010
#define OBJ_ROCKETNOZZLE	0x20000022
#define OBJ_HOVERNOZZLE		0x20000026
#define OBJ_TURBONOZZLE		0x2000002A
HitActor* MakeObjAppear(ItemManager* itemManager, int id);
HitActor* makeShineAppearWithDemo(ItemManager* itemManager, char* manager, char* mang2, float x, float y, float z);

//Water
void WaterEmitInfo_Create(WaterEmitInfo* this, const char* prm);
void ModelWaterManager_EmitRequest(void* man, void* emitinfo);

// Effects
void GenerateEffectElectric(HitActor* pos);
void emitGetCoinEffect(int unk1, MarioActor* mario);
void emitGotEffect(MarioActor* mario);
void objAppear(HitActor* actor);
void destroyCol(HitActor* actor);
void initModelData(HitActor* actor);
void marioCanTake(MarioActor* mario, HitActor* actor);
void marioStartVoice(MarioActor* mario, int soundIndex);

void ParticleManager_EmitWithRotate(void* man, int particle, Vector* position, uint16_t yaw, uint16_t pitch, uint16_t roll, uint8_t u2, void const* u5);
void MapObjBase_EmitSplash(MapObjBase* obj);

void changeTexture(int gfx, int gfxtype, int amnt);
void setPanePosition(J2DPane* plane, long speed, int unk2, int unk3, int unk4);
void updatePane(J2DPane* pane);
void updateBoundPane(J2DPane* pane);
void updateBlendPane(J2DPane* pane);
void movePane(J2DPane* pane, int u1, int u2);
int searchPane(long root, int id);
void processAppearCoin(int GCConsole);
void startAppearCoin(int GCConsole);
void processDownCoin(int GCConsole, int u1, long u2, long u3);
void getModel(HitActor* actor);
void showAllShapePacket(void);
void makeObjAppeared(HitActor* actor);
void startMapObjAnim(HitActor* actor, int multi);
void createMActor(int u1, int u2, int u3, int u4, int u5);
void startAnimation(int objProp, int anim, int u1);
void setUpMapCollision(HitActor* actor);
void setFrameRate(long _0x74, int unk1, float speed);
void changeCollision(HitActor* actor, int unk1, float unk2, float unk3);
void EasyEmitParticle(int effect, Vector* position, HitActor* actor, Vector* u1);

// Music / SFX
void PlaySound(int rate, Sound* sfx, int nl1, int nl2, int nl3, int four);
void startSoundSystemSE(int id, int unk1, int unk2, int unk3);
void StartStageEntranceDemoSeq(int u1, int u2);
void StartBGM(int u1);
void StopBGM(int u1, int u2);
void StopBGMs(int unk1, int unk2);
void search(int id);
void setAnimSound(HitActor* actor, char* bas);
void initAnimSound(int mBuff, int BAS, float unk1, int unk2);

//TEST LUMA
static float* lumaX = (void*)0x810e21bc;
static float* lumaY = (void*)0x810e21c0;
static float* lumaZ = (void*)0x810e21c4;
static float* lumaRotY = (void*)0x810e21e0;
static float* lumaScaleX = (void*)0x810e21d0;
static float* lumaScaleY = (void*)0x810e21d4;
static float* lumaScaleZ = (void*)0x810e21d8;
static float* CamRotX = (void*)0x812444e8;
static float* CamRotY = (void*)0x812444ec;
static float* CamRotZ = (void*)0x812444f0;
static float* CoinHUD = (void*)0x80e2cfc4;

void startCameraDemo(HitActor* cameraActor, int anim, float startrotation, int u1, long u2, int u3);
void coinTaken(HitActor* coin, HitActor* mario);
void redCoinTaken(HitActor* coin, HitActor* mario);
void startAppearGo(long ConsoleStr);
void startJAIStream(char* audioFile, int u1, void* u2);
void loadToMainRAM(char* file, int unk1, int unk2, int unk3, long unk4, int unk5, int unk6, int unk7);
void DVDOpen(char* file, long unk1);
void DVDPrepareStreamASync(long finfo, int length, int offset, long callback);
void DVDStopStreamAtEndAsync(long commandblock, long callback);
void DVDCancelStreamAsync(long commandblock, long callback);
void loadToARAM(char* file, int unk1, int unk2, int unk3, int unk4);
void loadModelData(char* modelFile, int flags, char* directory);
void setBuffer(void* constructor, void* buffer, int size);
void JSURead(void* constructor, void* buffer, int amount);
int readData(void* constructor, void* buffer, int size);
int getGlbResource(char* file);
void loadBCKDataBase(int bck);
void setBTP(long objPtr, char* animFile);
float getDistance(HitActor* object, Vector position);

static uint32_t** key = (void*)0x80412fec;
static const int* TGCCConsole2 = (void*)0x80902AB4;
//static const int* TGCCConsole2 = (void*)0x80ea3804;
const int* firstPane = (void*)0x80ea40e4;
void StartSoundActorWithInfo(int, Vector*, Vector*, float, int, int, void**, int, uint8_t);

//Other
void PSMTXCopy();
void CLBPolarToCross(Vector* center, Vector* out, float rho, uint16_t theta ,uint16_t phi);
void Application_Init(void* application);

void CARDInit(void);
int CARDMount(int channelNum, void* workArea, long cardCallBack);
int CARDOpen(int channelNum, char* fileName, CARDFileInfo* fileInfo);
int CARDCreate(int channelNum, char* fileName, int size, CARDFileInfo* fileInfo);
int CARDRead(CARDFileInfo* fileInfo, void* bufferAddr, int length, int offset);
int CARDWrite(CARDFileInfo* fileInfo, void* bufferAddr, int length, int offset);

//80e2d0d4 - c_cu
//80143a38
//80578988
//80426df0

//8117002c

#endif