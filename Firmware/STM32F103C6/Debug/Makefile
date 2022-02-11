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
#  H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/main.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/main.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/system_stm32f1xx.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/system_stm32f1xx.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/startup_stm32f103.o: TOOL=ASM
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/startup_stm32f103.s
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/ds1307.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/ds1307.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/i2c.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/i2c.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/lcd.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/lcd.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/glcd.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/glcd.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/spi_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/spi_drive.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/utils.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/utils.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/dht22.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/dht22.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/mef.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/mef.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/Debug/gpio.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/Firmware/STM32F103C6/gpio.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o system_stm32f1xx.o startup_stm32f103.o ds1307.o i2c.o lcd.o glcd.o spi_drive.o utils.o dht22.o mef.o gpio.o 
	$(LD)  $(LDFLAGS)  "main.o" "system_stm32f1xx.o" "startup_stm32f103.o" "ds1307.o" "i2c.o" "lcd.o" "glcd.o" "spi_drive.o" "utils.o" "dht22.o" "mef.o" "gpio.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

system_stm32f1xx.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "system_stm32f1xx.o"

startup_stm32f103.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "startup_stm32f103.o"

ds1307.o:	../ds1307.c 
	$(CC) $(CCFLAGS)  "../ds1307.c" -c -o "ds1307.o"

i2c.o:	../i2c.c 
	$(CC) $(CCFLAGS)  "../i2c.c" -c -o "i2c.o"

lcd.o:	../lcd.c 
	$(CC) $(CCFLAGS)  "../lcd.c" -c -o "lcd.o"

glcd.o:	../glcd.c 
	$(CC) $(CCFLAGS)  "../glcd.c" -c -o "glcd.o"

spi_drive.o:	../spi_drive.c 
	$(CC) $(CCFLAGS)  "../spi_drive.c" -c -o "spi_drive.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

dht22.o:	../dht22.c 
	$(CC) $(CCFLAGS)  "../dht22.c" -c -o "dht22.o"

mef.o:	../mef.c 
	$(CC) $(CCFLAGS)  "../mef.c" -c -o "mef.o"

gpio.o:	../gpio.c 
	$(CC) $(CCFLAGS)  "../gpio.c" -c -o "gpio.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf system_stm32f1xx.o
	rm -rf startup_stm32f103.o
	rm -rf ds1307.o
	rm -rf i2c.o
	rm -rf lcd.o
	rm -rf glcd.o
	rm -rf spi_drive.o
	rm -rf utils.o
	rm -rf dht22.o
	rm -rf mef.o
	rm -rf gpio.o
