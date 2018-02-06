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
DolInsert.exe %~n1.bin -m %~n1.map -dol ./Start.dol -o %~n1.dol -c OnUpdate:0x802a6160:3 -c OnSetup:0x802998b8:0 -c OnDraw2D:0x80143f14:0 -c OnWaterHitsGround:0x8027f7dc:0 -c OnObjectTouchMario:0x801b02fc:3 -c OnAllNPCsUpdate:0x8003e2f0:0 -c OnSmallEnemyHitMario:0x8006c76c:3 -r IsMario:0x8024db0c -r MarioSendMessage:0x80273870 -c OnMarioIncHP:0x80282ee0:0x80282f04:0x80282f84:0x80283414:0x80283490:0x802834d4:0 -c OnMarioDecHP:0x80242b10:0 -r IsMultiplayerMap:0x802a8b30 -c OnCheckActorsHit:0x80299af8:0 -c OnDetectHit:0x8021bfb4:0x8021bc00:0  -c OnMarioHeld:0x80284bd0:0 -c OnMarioThrow:0x802437bc:5 -c OnMarioDrop:0x8023f89c:3 -c OnChangeNozzle:0x80283204:0x80283154:0x802830a4:0 -c OnRideYoshi:0x8028121c:0 -r IsOnYoshi:0x802558c8 -r IsOnYoshi2:0x8024e2e4 -c OnDismountYoshi:0x8024dfc8:0x80270638:0 -c OnWaterGunUpdate:0x8024e2a0:0 -c OnUpdateMultiplayerCamera:0x80023860:0 -c CalcMultiplayerCameraPos:0x80030c04:0 -c CheckOtherObjectCollisions:0x8021bc08:1 -c CheckOtherObjectCollisions2:0x8021bba8:0 -c ChangeAllPlayerStatus:0x80240798:0x80240928:80240a2c:0 -c CreateYoshi:0x80276850:0 -c OnInitApp:0x8000561c:0 -c OnCameraMove:0x80023150:0
pause