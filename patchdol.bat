C:\devkitPro\devkitPPC\bin\powerpc-eabi-gcc.exe %1 -S -o %~n1.s -O1 -std=c99 -w
C:\devkitPro\devkitPPC\bin\powerpc-eabi-gcc.exe %1 -c -o %~n1.o -O1 -std=c99 -w
if ERRORLEVEL 1 pause
if ERRORLEVEL 1 exit
C:\devkitPro\devkitPPC\bin\powerpc-eabi-ld.exe -Os -T dollinker -T smsFuncs -o obj_%~n1.o %~n1.o -Map %~n1.map
if ERRORLEVEL 1 pause
if ERRORLEVEL 1 exit
C:\devkitPro\devkitPPC\bin\powerpc-eabi-objdump.exe obj_%~n1.o --full-content
if ERRORLEVEL 1 pause
if ERRORLEVEL 1 exit
C:\devkitPro\devkitPPC\bin\powerpc-eabi-objcopy.exe obj_%~n1.o %~n1.bin -O binary -R .eh_frame -R .comment -R .gnu.attributes -g -S
DolInsert.exe %~n1.bin -m %~n1.map -dol ./Start.dol -o %~n1.dol -c OnUpdate:0x802a6160:3 -c OnSetup:0x802998b8:0 -c OnDraw2D:0x80143f14:0 -c OnWaterHitsGround:0x8027f7dc:0 -c OnObjectTouchMario:0x801b02fc:3 -c OnAllNPCsUpdate:0x8003e2f0:0 -c OnSmallEnemyHitMario:0x8006c76c:3 -r EMarioControl:0x8004010c -r IsMario:0x8024db0c -r EMarioReceiveMessage:0x8003956c -r MarioSendMessage:0x80273870 -r EMarioPlayerControl:8004006c -c OnMarioIncHP:0x80282ee0:0x80282f04:0x80282f84:0x80283414:0x80283490:0x802834d4:0 -c OnMarioDecHP:0x80242b10:0 -r EMarioDamageExec:0x80040068 -r IsMultiplayerMap:0x802a8b30
pause