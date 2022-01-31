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
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -IC:/Keil_v5/ARM/CMSIS/Include -g --c90 -O0
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/main.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/main.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/system_stm32f1xx.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/system_stm32f1xx.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/startup_stm32f103.o: TOOL=ASM
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/startup_stm32f103.s
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/utils.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/utils.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/gp_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/gp_drive.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/spi_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/spi_drive.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/Debug/n5110_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/SPI + DISPLAY/STM32F103C6/n5110_drive.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o system_stm32f1xx.o startup_stm32f103.o utils.o gp_drive.o spi_drive.o n5110_drive.o 
	$(LD)  $(LDFLAGS)  "main.o" "system_stm32f1xx.o" "startup_stm32f103.o" "utils.o" "gp_drive.o" "spi_drive.o" "n5110_drive.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

system_stm32f1xx.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "system_stm32f1xx.o"

startup_stm32f103.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "startup_stm32f103.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

gp_drive.o:	../gp_drive.c 
	$(CC) $(CCFLAGS)  "../gp_drive.c" -c -o "gp_drive.o"

spi_drive.o:	../spi_drive.c 
	$(CC) $(CCFLAGS)  "../spi_drive.c" -c -o "spi_drive.o"

n5110_drive.o:	../n5110_drive.c 
	$(CC) $(CCFLAGS)  "../n5110_drive.c" -c -o "n5110_drive.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf system_stm32f1xx.o
	rm -rf startup_stm32f103.o
	rm -rf utils.o
	rm -rf gp_drive.o
	rm -rf spi_drive.o
	rm -rf n5110_drive.o
