C:\devkitPro\devkitPPC\bin\powerpc-eabi-gcc.exe %1 -S -o %~n1.s -O1 -std=c99
C:\devkitPro\devkitPPC\bin\powerpc-eabi-gcc.exe %1 -c -o %~n1.o -O1 -std=c99
if ERRORLEVEL 1 pause
if ERRORLEVEL 1 exit
C:\devkitPro\devkitPPC\bin\powerpc-eabi-ld.exe -Os -T linker -T smsFuncs -o obj_%~n1.o %~n1.o -Map %~n1.map
if ERRORLEVEL 1 pause
if ERRORLEVEL 1 exit
C:\devkitPro\devkitPPC\bin\powerpc-eabi-objdump.exe obj_%~n1.o --full-content
if ERRORLEVEL 1 pause
if ERRORLEVEL 1 exit
C:\devkitPro\devkitPPC\bin\powerpc-eabi-objcopy.exe obj_%~n1.o %~n1.bin -O binary -R .eh_frame -R .comment -R .sdata -R .gnu.attributes -g -S
bin2gecko.exe %~n1.bin -m %~n1.map -c OnUpdate:0x800f9b64:3 -c OnSetup:0x800ece3c:0 -c OnDraw2D:0x80206734:0 -c OnWaterHitsGround:0x8015ebf8:0 -c OnObjectTouchMario:0x801886d8:3 -c OnAllNPCsUpdate:0x80251d50:0 -c OnSmallEnemyHitMario:0x8027f64c:3 -r OnEMarioControl:0x80253ac0 -r IsMario:0x8012cfe0
pause
