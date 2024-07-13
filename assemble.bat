@echo off
ca65 asm/sys.s -o asm/sys.o
ld65 -C asm/bios.cfg asm/sys.o -o sys.out