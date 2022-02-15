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
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -IC:/Keil_v5/ARM/CMSIS/Include -g -O0 --c90
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/main.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/main.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/system_stm32f1xx.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/system_stm32f1xx.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/startup_stm32f103.o: TOOL=ASM
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/startup_stm32f103.s
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/dht22.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/dht22.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/n5510_drive.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/n5510_drive.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/utils.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/utils.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/lcd.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/lcd.c
#     H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/Debug/usart.o: TOOL=CC
#        H:/Fede/Facultad/2021/2do cuatrimestre/Taller de proyecto I/Prácticas/Práctica 4/Project/DHT22_Fede/STM32F103C6/usart.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o system_stm32f1xx.o startup_stm32f103.o dht22.o n5510_drive.o utils.o lcd.o usart.o 
	$(LD)  $(LDFLAGS)  "main.o" "system_stm32f1xx.o" "startup_stm32f103.o" "dht22.o" "n5510_drive.o" "utils.o" "lcd.o" "usart.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

system_stm32f1xx.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "system_stm32f1xx.o"

startup_stm32f103.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "startup_stm32f103.o"

dht22.o:	../dht22.c 
	$(CC) $(CCFLAGS)  "../dht22.c" -c -o "dht22.o"

n5510_drive.o:	../n5510_drive.c 
	$(CC) $(CCFLAGS)  "../n5510_drive.c" -c -o "n5510_drive.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

lcd.o:	../lcd.c 
	$(CC) $(CCFLAGS)  "../lcd.c" -c -o "lcd.o"

usart.o:	../usart.c 
	$(CC) $(CCFLAGS)  "../usart.c" -c -o "usart.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf system_stm32f1xx.o
	rm -rf startup_stm32f103.o
	rm -rf dht22.o
	rm -rf n5510_drive.o
	rm -rf utils.o
	rm -rf lcd.o
	rm -rf usart.o
