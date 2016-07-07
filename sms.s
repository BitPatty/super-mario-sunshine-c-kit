	.file	"sms.c"
	.section	".text"
	.align 2
	.globl OnUpdate
	.type	OnUpdate, @function
OnUpdate:
	stwu 1,-32(1)
	mflr 0
	stw 0,36(1)
	stw 30,24(1)
	stw 31,28(1)
	mr 31,3
	lwz 9,0(3)
	lwz 30,100(9)
	bl IsMarioJumping
	lis 10,timemilli@ha
	lwz 9,timemilli@l(10)
	addi 9,9,-1
	stw 9,timemilli@l(10)
	lis 10,timery@ha
	lwz 8,timery@l(10)
	addi 8,8,1
	stw 8,timery@l(10)
	cmpwi 7,9,0
	bgt+ 7,.L2
	lis 9,time@ha
	lwz 10,time@l(9)
	addi 10,10,-1
	stw 10,time@l(9)
	li 10,30
	lis 9,timemilli@ha
	stw 10,timemilli@l(9)
.L2:
	lis 9,0x8040
	ori 9,9,17492
	lhz 9,0(9)
	rlwinm 9,9,0,28,28
	andi. 10,9,0xffff
	beq+ 0,.L3
	bl GetMarioHitActor
	lis 9,.LC0@ha
	lfs 1,.LC0@l(9)
	li 4,109
	bl SetMarioAnim
.L3:
	addi 3,1,8
	lis 9,timerx@ha
	lwz 4,timerx@l(9)
	lis 9,timery@ha
	lwz 5,timery@l(9)
	li 6,800
	li 7,512
	bl JUTRect_Set
	mr 3,31
	mtctr 30
	bctrl
	lwz 0,36(1)
	mtlr 0
	lwz 30,24(1)
	lwz 31,28(1)
	addi 1,1,32
	blr
	.size	OnUpdate, .-OnUpdate
	.align 2
	.globl OnDraw2D
	.type	OnDraw2D, @function
OnDraw2D:
	stwu 1,-40(1)
	mflr 0
	stw 0,44(1)
	stw 29,28(1)
	stw 30,32(1)
	stw 31,36(1)
	mr 31,3
	lis 29,.LANCHOR0@ha
	lwz 3,.LANCHOR0@l(29)
	li 4,128
	lis 5,.LC1@ha
	la 5,.LC1@l(5)
	lis 9,time@ha
	lwz 6,time@l(9)
	crxor 6,6,6
	bl snprintf
	lis 30,textbox@ha
	la 30,textbox@l(30)
	mr 3,30
	lwz 4,.LANCHOR0@l(29)
	bl J2DTextBox_SetString
	mr 3,31
	bl J2DGrafContext_Setup2D
	mr 3,30
	li 4,0
	li 5,0
	mr 6,31
	li 7,129
	bl J2DScreen_Draw
	li 3,0
	li 4,0
	li 5,640
	li 6,448
	bl GXSetScissor
	addi 3,1,8
	lis 9,timerx@ha
	lwz 4,timerx@l(9)
	lis 9,timery@ha
	lwz 5,timery@l(9)
	li 6,800
	li 7,512
	bl JUTRect_Set
	lwz 0,44(1)
	mtlr 0
	lwz 29,28(1)
	lwz 30,32(1)
	lwz 31,36(1)
	addi 1,1,40
	blr
	.size	OnDraw2D, .-OnDraw2D
	.align 2
	.globl OnSetup
	.type	OnSetup, @function
OnSetup:
	stwu 1,-40(1)
	mflr 0
	stw 0,44(1)
	stw 29,28(1)
	stw 30,32(1)
	stw 31,36(1)
	mr 29,3
	bl GetMarioHitActor
	bl WearGlasses
	li 10,300
	lis 9,time@ha
	stw 10,time@l(9)
	lis 30,timerx@ha
	li 9,440
	stw 9,timerx@l(30)
	lis 31,timery@ha
	li 9,-420
	stw 9,timery@l(31)
	mr 3,29
	bl MarDirector_SetupObjects
	addi 3,1,8
	lwz 4,timerx@l(30)
	lwz 5,timery@l(31)
	li 6,800
	li 7,512
	bl JUTRect_Set
	lwz 9,-24632(13)
	lis 3,textbox@ha
	la 3,textbox@l(3)
	li 4,0
	addi 5,1,8
	lwz 6,72(9)
	addi 7,2,-19304
	li 8,2
	li 9,0
	bl J2DTextBox_Create
	lis 9,0x8024
	ori 9,9,32676
	mtctr 9
	bctrl
	li 3,128
	crxor 6,6,6
	bl __nwa__FUl
	lis 9,.LANCHOR0@ha
	stw 3,.LANCHOR0@l(9)
	lwz 0,44(1)
	mtlr 0
	lwz 29,28(1)
	lwz 30,32(1)
	lwz 31,36(1)
	addi 1,1,40
	blr
	.size	OnSetup, .-OnSetup
	.align 2
	.globl TestNull
	.type	TestNull, @function
TestNull:
 # 113 "C:\Users\ronal\Desktop\SunshineKit\Clib\sms.c" 1
	blr ;ori %r1, %r1, 0xd138 ;
 # 0 "" 2
	blr
	.size	TestNull, .-TestNull
	.comm	timery,4,4
	.comm	timerx,4,4
	.globl time
	.globl timemilli
	.section	.rodata.cst4,"aM",@progbits,4
	.align 2
.LC0:
	.4byte	1065353216
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 2
.LC1:
	.string	"Time x %d"
	.section	.sdata,"aw",@progbits
	.align 2
	.type	time, @object
	.size	time, 4
time:
	.long	30
	.type	timemilli, @object
	.size	timemilli, 4
timemilli:
	.long	30
	.type	textbox, @object
	.size	textbox, 432
textbox:
	.zero	432
	.section	".bss"
	.align 2
	.set	.LANCHOR0,. + 0
	.type	info, @object
	.size	info, 4
info:
	.zero	4
	.ident	"GCC: (devkitPPC release 27) 4.8.2"
	.gnu_attribute 4, 1
