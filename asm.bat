@echo off
ca65 asm/sys.s -o asm/sys.o
ld65 -C asm/bios.cfg asm/sys.o -o sys.out
@REM ca65 asm/maddness.s -o asm/maddness.o
@REM ld65 -C asm/bios.cfg asm/maddness.o -o maddness.out