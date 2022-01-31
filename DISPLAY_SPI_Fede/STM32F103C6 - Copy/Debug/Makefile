###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103C6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -IC:/Keil_v5/ARM/CMSIS/Include -g
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/main.o: TOOL=CC
#        C:/Users/Fede/AppData/Local/Temp/VSM Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/main.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/SYSTEM~1.o: TOOL=CC
#        C:/Users/Fede/AppData/Local/Temp/VSM Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/system_stm32f1xx.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/STARTU~1.o: TOOL=ASM
#        C:/Users/Fede/AppData/Local/Temp/VSM Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/startup_stm32f103.s
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/glcd.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/glcd.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/gp_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/gp_drive.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/spi_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/spi_drive.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/Debug/utils.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DISPLAY_SPI_Fede/STM32F103C6/utils.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o SYSTEM~1.o STARTU~1.o glcd.o gp_drive.o spi_drive.o utils.o 
	$(LD)  $(LDFLAGS)  "main.o" "SYSTEM~1.o" "STARTU~1.o" "glcd.o" "gp_drive.o" "spi_drive.o" "utils.o" --output "Debug.elf"

main.o:	C:/Users/Fede/AppData/Local/Temp/VSM\ Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/main.c 
	$(CC) $(CCFLAGS)  "C:/Users/Fede/AppData/Local/Temp/VSM Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/main.c" -c -o "main.o"

SYSTEM~1.o:	C:/Users/Fede/AppData/Local/Temp/VSM\ Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "C:/Users/Fede/AppData/Local/Temp/VSM Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/system_stm32f1xx.c" -c -o "SYSTEM~1.o"

STARTU~1.o:	C:/Users/Fede/AppData/Local/Temp/VSM\ Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "C:/Users/Fede/AppData/Local/Temp/VSM Studio/94e6b2b6178b46d6b8295bf1ef3b0a8a/STM32F103C6/startup_stm32f103.s" -o "STARTU~1.o"

glcd.o:	../glcd.c 
	$(CC) $(CCFLAGS)  "../glcd.c" -c -o "glcd.o"

gp_drive.o:	../gp_drive.c 
	$(CC) $(CCFLAGS)  "../gp_drive.c" -c -o "gp_drive.o"

spi_drive.o:	../spi_drive.c 
	$(CC) $(CCFLAGS)  "../spi_drive.c" -c -o "spi_drive.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf SYSTEM~1.o
	rm -rf STARTU~1.o
	rm -rf glcd.o
	rm -rf gp_drive.o
	rm -rf spi_drive.o
	rm -rf utils.o
