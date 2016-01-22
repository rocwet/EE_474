# Lab 1 - Counter & Piano

## Authors
| Name              | Role          |
| -------------     | ------------- |
| Jack Lee          | Member        |
| Minh Khuu         | Member        |
| Seewan Kim        | Member        |

## Date
2016.01.18

## Files
* counter.c
  * contains the code for the blinker
* sound.c
  * contains the code for the piano
* Makefile
  * automated compiler and cleaner
* README.md
  * This file.
* connect.sh
  * script file to ssh into beagle board
* push.sh
  * script file to push files into beagle board

## Description

This lab contains two portions:
1. Counter, 
2. Piano

### Counter - counter.c
* The counter is a 3-bit counter that counts from 0 - 7 and is displayed
using 3 leds. 
* Pins used:
  * GPIO_49
  * GPIO_112
  * GPIO_115
  
### Piano - sound.c
* Implemented using notes A, B, C, D, E, F, G, and G (one octave lower)
* Simple Menu system implemented, which allows user to select three modes:
  1. Play Song
     * The user enters a file name and the program will play out the notes that match.
     * There is no file input validation.
  2. Play Piano
     * The user enters a valid character and plays a corresponding note.
     * All notes are a quarter note, including the pause note.
  3. Quit
     * To quit the program.
* The following notes correspond to the following:
  * 1 - 8, notes of frequency G/2.0 to G
  * p, pause note
  * x, exit out
