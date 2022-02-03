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
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -I../../../../../../../../Keil_v5/ARM/CMSIS/Include -g --c90 -O0
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/main.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/main.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/SYSTEM~1.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/system_stm32f1xx.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/STARTU~1.o: TOOL=ASM
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/startup_stm32f103.s
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/ds1307.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/ds1307.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/i2c.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/i2c.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/lcd.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/lcd.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/glcd.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/glcd.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/SPI_DR~1.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/spi_drive.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/utils.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/utils.c
#     C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/Debug/dht22.o: TOOL=CC
#        C:/Users/Reino/Desktop/Trabajo Practico 4/despertadorInteligente/Firmware/STM32F103C6/dht22.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o SYSTEM~1.o STARTU~1.o ds1307.o i2c.o lcd.o glcd.o SPI_DR~1.o utils.o dht22.o 
	$(LD)  $(LDFLAGS)  "main.o" "SYSTEM~1.o" "STARTU~1.o" "ds1307.o" "i2c.o" "lcd.o" "glcd.o" "SPI_DR~1.o" "utils.o" "dht22.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

SYSTEM~1.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "SYSTEM~1.o"

STARTU~1.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "STARTU~1.o"

ds1307.o:	../ds1307.c 
	$(CC) $(CCFLAGS)  "../ds1307.c" -c -o "ds1307.o"

i2c.o:	../i2c.c 
	$(CC) $(CCFLAGS)  "../i2c.c" -c -o "i2c.o"

lcd.o:	../lcd.c 
	$(CC) $(CCFLAGS)  "../lcd.c" -c -o "lcd.o"

glcd.o:	../glcd.c 
	$(CC) $(CCFLAGS)  "../glcd.c" -c -o "glcd.o"

SPI_DR~1.o:	../spi_drive.c 
	$(CC) $(CCFLAGS)  "../spi_drive.c" -c -o "SPI_DR~1.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

dht22.o:	../dht22.c 
	$(CC) $(CCFLAGS)  "../dht22.c" -c -o "dht22.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf SYSTEM~1.o
	rm -rf STARTU~1.o
	rm -rf ds1307.o
	rm -rf i2c.o
	rm -rf lcd.o
	rm -rf glcd.o
	rm -rf SPI_DR~1.o
	rm -rf utils.o
	rm -rf dht22.o
