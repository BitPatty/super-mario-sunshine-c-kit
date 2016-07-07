powerpc-eabi-gcc.exe sms.s -c -o sms.o
C:\devkitPro\devkitPPC\bin\powerpc-eabi-ld.exe -T linker -o smsobj.o sms.o
C:\devkitPro\devkitPPC\bin\powerpc-eabi-objdump.exe smsobj.o --full-content
C:\devkitPro\devkitPPC\bin\powerpc-eabi-objcopy.exe smsobj.o sms.bin -O binary -R .comment -g -S
bin2gekko.exe sms.bin 0x80248b18