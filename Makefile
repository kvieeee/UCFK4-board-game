# File:   Makefile
# Author: Kvie Nguyen (kvn17), Zoe Sharp (zsh44)
# Date:   5th October 2021
# Descr:  Makefile for maze game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr 
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/navswitch.h ../../drivers/avr/timer.h ../../drivers/avr/pio.h ../../fonts/font5x7_1.h ../../utils/font.h ../../utils/tinygl.h player.h ../../drivers/button.h ../../drivers/led.h ../../drivers/display.h

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

player.o: player.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/navswitch.h ../../drivers/avr/timer.h ../../utils/tinygl.h player.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/button.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@
	
# Link: create ELF output file from object files.
game.out: game.o pio.o system.o timer.o pacer.o navswitch.o tinygl.o font.o display.o ledmat.o player.o button.o led.o display.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


