
SEARCH_DIR(".")
SEARCH_DIR("C:\Program Files\Raisonance\Ride\Lib\ARM")
STARTUP("C:\Program Files\Raisonance\Ride\lib\ARM\crt0_STM32x.o")
INPUT("E:\WORK\uK\STM32\KS0108\main.o")
INPUT("E:\WORK\uK\STM32\KS0108\KS0108-STM32.o")
INPUT("E:\WORK\uK\STM32\KS0108\graphic.o")
INPUT("E:\WORK\uK\STM32\KS0108\KS0108.o")
INPUT("STM32F10x_thumb.lib")
OUTPUT("E:\WORK\uK\STM32\KS0108\ks0108.elf")
INCLUDE "C:\Program Files\Raisonance\Ride\lib\ARM\STM32F103_32K_20K_FLASH.ld"
