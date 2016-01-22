/*
Jack Lee
Minh Khuu
Seewan Kim
2016.01.18
EE474 Lab 0: sound.c
*/

/* included libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/* define constants */
#define ONE_SECOND 1000000


/* Prototype headers */
int hz2ns(double);
void init();
void playNote(int, int, FILE*, FILE*);
void pause(FILE*, FILE*);
void run();
void stop();
void note_setting();
void readNote(FILE*, FILE*, int*, char);
void usleep();


/* 
The main() function initializes the beagle board for the pwm pin to power a speaker module.
It then opens the corresponding period, duty, and run files in the pwm pin for programming.
The user is then prompted with a menu:
    (1) Play Song, allows the user to select a .txt file and plays the song (has to be in
        a special format. [1 - 8] for notes and 'p' for pause
    (2) Play Piano, allows the user to play real time.
    (3) Quit, exit the program.

@param argc The argument count.
@param argv The command-line arguments.
@return The return status.
*/
int main(int argc, char *argv[]) {

    
    
    /* intialize beagle board's pwm pin */
    init();
    
    /* delay */
    printf("Intializing.........................\n");
    usleep(ONE_SECOND);
    
    /* declare intialize notes */
    int notes[8];
    note_setting(notes);
    
    /* declare  files */
    FILE* file_period;
    FILE* file_duty;
    FILE* file_run;
    
    /* initialize files */
    file_period = fopen("/sys/devices/ocp.3/pwm_test_P9_14.15/period", "w");
    file_duty = fopen("/sys/devices/ocp.3/pwm_test_P9_14.15/duty", "w");
    file_run = fopen("/sys/devices/ocp.3/pwm_test_P9_14.15/run", "w");
    
    /* check for null files*/
    if(file_period == NULL) {
        fprintf(stderr, "%s does not exist!\n", "period"); 
        return 1;   
    } 
    if(file_duty == NULL) {
        fprintf(stderr, "%s does not exist!\n", "duty"); 
        return 1;   
    }
    if(file_run == NULL) {
        fprintf(stderr, "%s does not exist!\n", "run");  
        return 1;  
    }
    
    /* menu */
    char option = '0';
    while(option != '3') {
    
        /* Display Menu to user*/
        printf("\n------Menu------\n");
        printf("Press 1: Play Song\nPress 2: Play Piano\nPress 3: Quit\n\n");
        printf("> ");
        scanf("%c", &option);          
        char input;
        
          /* Play Song Option */
          if(option == '1') {
              char song[20];
              printf("\n------Song Mode------\n");
              printf("Enter filename of song file: ");
              scanf("%s", song);
              FILE* file_song = fopen(song, "r");
              if(file_song == NULL) {
                  fprintf(stderr, "%s does not exist!\n", "song");    
                  break;
              }
              while(fscanf(file_song, "%c", &input) != EOF) {
                  printf(" %c\n", input);
                  readNote(file_period, file_duty, notes, input);
              }
              
          /* Play Piano Option */
          } else if (option == '2') {
              input = 'p';
              printf("\n------Piano Mode------\n");
              while(input != 'x') {
                  scanf(" %c", &input);
                  readNote(file_period, file_duty, notes, input);
              }

          /* Exit */
          } else if (option == '3') {
              printf("Exit\n\n");
              
          /* Error Case */
          } else {
              fprintf(stderr, "ERROR: Please enter a valid menu option 1 - 3!\n");
          }
       
    }
   
    /* Close Files */
    fclose(file_period);
    fclose(file_duty);
    fclose(file_run);
    
    /* Success Return Code */
    return 0;
}

/*
The init() function intializes the beagleboard's pwm pin P9_14
*/
void init() {
    system("echo am33xx_pwm > /sys/devices/bone_capemgr.9/slots");
    system("echo bone_pwm_P9_14 > /sys/devices/bone_capemgr.9/slots");
}

/*
The run() function sets the beagleboard's pwm pin's run setting to ON.
*/
void run() {
    system("echo 1 > /sys/devices/ocp.3/pwm_test_P9_14.15/run");
}

/*
The run() function sets the beagleboard's pwm pin's run setting to OFF.
*/
void stop() {
    system("echo 0 > /sys/devices/ocp.3/pwm_test_P9_14.15/run");
}

/*
The note_setting() function takes an int array of notes and intializes the period values
for each note in a corresponding index.

@param notes The note int array that stores note period's in nanoseconds.
*/
void note_setting(int* notes) {
    double A =  220 * pow(2,0.0/12);
    double B =  220 * pow(2,2.0/12);
    double C =  220 * pow(2,3.0/12);
    double D =  220 * pow(2,5.0/12);
    double E =  220 * pow(2,7.0/12);
    double Fs = 220 * pow(2,9.0/12);
    double G =  220 * pow(2,10.0/12);

    notes[0] = hz2ns(G/2.0);
    notes[1] = hz2ns(A);
    notes[2] = hz2ns(B);
    notes[3] = hz2ns(C);
    notes[4] = hz2ns(D);
    notes[5] = hz2ns(E);
    notes[6] = hz2ns(Fs);
    notes[7] = hz2ns(G);
} 


/* 
The hz2ns() function converts a given frequency to nanoseconds in int value.

@param hz The frequency in hertz.
@return The period in nanoseconds.
*/
int hz2ns(double hz) {
    int ns = 1/hz * pow(10, 9);
    return ns;
}

/*
The pause() function plays a pause quarter note.

@param file_period The period file to be written to.
@param file_duty The duty file to written to.
*/
void pause(FILE* file_period, FILE* file_duty) {
    playNote(0, ONE_SECOND/4, file_period, file_duty);
}

/*
The playNote() function plays a note of a given period and duration.

@param period The period of the note in nanoseconds.
@param dur The duration of the note.
@param file_period The period file to be written to.
@param file_duty The duty file to written to.
*/
void playNote(int period, int dur, FILE* file_period, FILE* file_duty) {

    /* intialize values */
    int duty = period / 2;
    char dut[15];
    char prd[15];
    
    /* covert period and duty to strings */
    snprintf(dut, sizeof(dut), "%d", duty);
    snprintf(prd, sizeof(prd), "%d", period);
    
    /* write the period and duty */
    fseek(file_period, 0, SEEK_SET);
    fseek(file_duty, 0, SEEK_SET);
    fwrite(prd, 15, sizeof(prd), file_period);
    fwrite(dut, 15, sizeof(dut), file_duty);
    fflush(file_period);
    fflush(file_duty);
    
    /* delay for duration */
    usleep(dur);
}

/*
The readNote() function takes a given input character and does the following:
    'p', Plays a pause quarter note
    'x', Display exit message
    '1' - '8', Plays a quarter note of the corresponding period
If the input is invalid, an error message will be displayed.

@param file_period The period file to be written to.
@param file_duty The duty file to written to.
@param notes The note array that stores corresponding note periods in nanoseconds.
@param input The input character to be analyzed.
*/
void readNote(FILE* file_period, FILE* file_duty, int* notes, char input) {
    
    /* Play Pause Note */
    if (input == 'p') {
        pause(file_period, file_duty);
        
    /* Exit Message */
    } else if (input == 'x') {
        printf("Exiting......\n");
        
    /* Play Note */
    } else if (input >= '1' && input <= '8') {
        run();
        playNote(notes[input - '1'], ONE_SECOND/4, file_period, file_duty);
    
    /* Null Character or EOF or newline char does nothing */
    } else if (input == '\0' || input == EOF || input == '\n') { 
    
    /* Error Message */
    } else {
      fprintf(stderr, "ERROR: Enter a value between 1 - 8, inclusive!\n");
    }
    /* Turn off PWM module */
    stop();
}
