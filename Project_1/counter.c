#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// This program initializes the beagle board and functions as a 
// three bit counter (0 - 7) that is represented by LEDS.

//#define ONE_SECOND 100000000

void init();
void usleep();

int main(int argc, char *argv[]) {
	int i;
	char zero = '0';
	char one = '1';

	// initialize environment
	init();

	// delay 
    printf("Intializing.........................\n");

    usleep(1000000);

	// 1 bit
	FILE* file_one;

	// 2 bit 
	FILE* file_two;

	// 3 bit 
	FILE* file_three; 
	file_one = fopen("/sys/class/gpio/gpio49/value", "w");
	file_two = fopen("/sys/class/gpio/gpio115/value", "w");
	file_three = fopen("/sys/class/gpio/gpio112/value", "w");

	// check if error in files
	if(file_one == NULL) {
		fprintf(stderr, "%s does not exist!\n", "file");
		return 1;
	} 
	if(file_two == NULL) {
		fprintf(stderr, "%s does not exist!\n", "file");
		return 1;
	}
	if(file_three == NULL) {
		fprintf(stderr, "%s does not exist!\n", "file");
		return 1;
	}
	while(1) {
		for(i = 0; i < 8; i++) {
			// setup pointer in file stream 
			fseek(file_one, 0, SEEK_SET);
			fseek(file_two, 0, SEEK_SET);
			fseek(file_three, 0, SEEK_SET);

			// check if 1 bit should be on
			if(i % 2 == 1) {
				fwrite(&one, 1, 1, file_one);
			} else {
				fwrite(&zero, 1, 1, file_one);
			}

			// check if 2 bit should be on
			if((i / 2) % 2 == 1) {
				fwrite(&one, 1, 1, file_two);
			} else {
				fwrite(&zero, 1, 1, file_two);
			}

			// check if 3 bit should be on
			if((i / 4) % 2 == 1) {
				fwrite(&one, 1, 1, file_three);
			} else {
				fwrite(&zero, 1, 1, file_three);
			}

			// delay to slow down execution
			usleep(1000000);
			
		}
	}
	fclose(file_one);
	fclose(file_two);
	fclose(file_three);
	return 0;
}

// set GPIO pins

void init() {
	system("echo 49 > /sys/class/gpio/export");
	system("echo 115 > /sys/class/gpio/export");
	system("echo 112 > /sys/class/gpio/export");
	system("echo out > /sys/class/gpio/gpio49/direction");
	system("echo out > /sys/class/gpio/gpio115/direction");
	system("echo out > /sys/class/gpio/gpio112/direction");
}
