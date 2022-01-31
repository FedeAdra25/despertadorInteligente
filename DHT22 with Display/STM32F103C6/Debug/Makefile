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
#  H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/Debug/main.o: TOOL=CC
#        C:/Users/Fede/AppData/Local/Temp/VSM Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/main.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/Debug/SYSTEM~1.o: TOOL=CC
#        C:/Users/Fede/AppData/Local/Temp/VSM Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/system_stm32f1xx.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/Debug/STARTU~1.o: TOOL=ASM
#        C:/Users/Fede/AppData/Local/Temp/VSM Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/startup_stm32f103.s
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/Debug/dht22.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/dht22.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/Debug/n5510_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22 with Display/STM32F103C6/n5510_drive.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o SYSTEM~1.o STARTU~1.o dht22.o n5510_drive.o 
	$(LD)  $(LDFLAGS)  "main.o" "SYSTEM~1.o" "STARTU~1.o" "dht22.o" "n5510_drive.o" --output "Debug.elf"

main.o:	C:/Users/Fede/AppData/Local/Temp/VSM\ Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/main.c 
	$(CC) $(CCFLAGS)  "C:/Users/Fede/AppData/Local/Temp/VSM Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/main.c" -c -o "main.o"

SYSTEM~1.o:	C:/Users/Fede/AppData/Local/Temp/VSM\ Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "C:/Users/Fede/AppData/Local/Temp/VSM Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/system_stm32f1xx.c" -c -o "SYSTEM~1.o"

STARTU~1.o:	C:/Users/Fede/AppData/Local/Temp/VSM\ Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "C:/Users/Fede/AppData/Local/Temp/VSM Studio/97681e931c244b5c9cf7a74042cae949/STM32F103C6/startup_stm32f103.s" -o "STARTU~1.o"

dht22.o:	../dht22.c 
	$(CC) $(CCFLAGS)  "../dht22.c" -c -o "dht22.o"

n5510_drive.o:	../n5510_drive.c 
	$(CC) $(CCFLAGS)  "../n5510_drive.c" -c -o "n5510_drive.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf SYSTEM~1.o
	rm -rf STARTU~1.o
	rm -rf dht22.o
	rm -rf n5510_drive.o
