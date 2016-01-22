#!/bin/bash

CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g
SRCFILES = counter.c sound.c
EXE = counter sound

sound: sound.c
	$(CC) $(CFLAGS) -o sound sound.c
	
counter: counter.c
	$(CC) $(CFLAGS) -o counter counter.c
	
runs:
	./sound
	
runc:
	./counter
	
clean:
	@echo Cleaning...
	rm -f *.o *~ $(EXE)
