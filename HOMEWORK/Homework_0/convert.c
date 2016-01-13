/*
Minhhue H. Khuu
EE474 HW0
2016.01.13
*/

/* Included libraries*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* mapping to hexadecimal */
const char num_key[16] = "0123456789abcdef";

/* Prototype function definitions */
void convertBinary(int num);
void convert(int num, int base); 
void reverse(char* s);
int isNumber(char* s);

/*
The main() function.
Given one argument, it converts the interger value to binary representation.
Given two arguments, it converts the interger value to the new base
representation.

Has input validation:
  checks for the ammount of command line arguments.
  checks if the command line arguments are integers.

@param argc The command-line arguments count.
@param argv The command-line arguments.
@return The status code, 0 = no error, and 1 = error.
*/
int main(int argc, char** argv) {

  /* define argument count */
  int count = argc - 1;
  
  /* Check argument counts for error */
  if (count < 1) {
    fprintf(stderr, "ERROR: You must enter atleast 1 argument!\n");
    return 1;
  } else if (count > 2) {
    fprintf(stderr, "ERROR: You cannot have more than 2 arguments!\n");
    return 1;
  } 

  /* call function base on argument count */
  /* binary case */
  if (count == 1 && isNumber(argv[1])) {
    convertBinary(atoi(argv[1]));
    
  /* general case */
  } else if (count == 2 && isNumber(argv[1]) && isNumber(argv[2])) {
    convert(atoi(argv[1]), atoi(argv[2]));
    
  /* non integer input case */
  } else {
    fprintf(stderr, "ERROR: You must enter integer values!\n");
    return 1;
  }
  
  /* success code */
  return 0;
}

/*
The convertBinary() function converts a given number in base 10 to a binary
representation.

@param num The number to be converted.
*/
void convertBinary(int num) {
  convert(num, 2);
}

/*
The convert() function converts a given number in base 10 to a new base
representation.

Has input validation:
  checks if the base is between 1 - 16 (INCLUSIVE)

@param num The number to be converted.
@param base The new base.
*/
void convert(int num, int base) { 

  /* Less than ONE base case */
  if (base < 1) {
    fprintf(stderr, "ERROR: You cannot have a base of less than 1!\n");
    return;
    
  /* More than SIXTEEN base case */
  } else if (base > 16) {
    fprintf(stderr, "ERROR: You cannot have a base more than 16!\n");
    return;
    
  /* One Case */
  } else if (base == 1) { 
    /* Initialize character array to hold num amount of 1s */
    char s[num];
    for(int i = 1; i < num; i++) {
      strncat(s, "1", num);
    }
    
    /* prints result */
    printf("%d in base %d is: %s\n", num, base, s);
    
  /* General Case */
  } else if (base <= 16) {
    /* Initialize mod count and character array */
    /* Allocated 33 characters spaces because an integer is 32 bits + null */
    int mod;
    char s[33] = "";
    
    /* parse through each digit place left to right until end */
    while(num) {
      mod = num % base;
      num /= base;
      char t[2] = {num_key[mod], '\0'};  // string that contains current digit
      strncat(s, t, 33);                 // concatenate with current digit
    }
    
    /* reverse the string to correctly display the digit */
    reverse(s);
    
    /* prints result */
    printf("%d in base %d is: %s\n", num, base, s);
  } 
}

/*
The reverse() function takes a character pointer (string) and reverses the
string by mirroring the string, modifying the pointer.

@param begin The pointer to the start of the character array.
*/
void reverse(char* begin) {

  /* variables to keep track of switching */
  char temp;
  int len = strlen(begin) - 1;
  char* end = begin + len;  
  
  /* switch ends and begining pointers*/
  while(begin < end) {
    temp = *end;
    *end = *begin;
    *begin = temp;
    begin++;
    end--;
  }
}

/* 
The isNumber() function checks if a string is a number.

@param s The string to check.
@return The int value representing true as 1, and false as 0.
*/
int isNumber(char* s) {
  for(int i = 0; i < strlen(s); i++) {
    if(!isdigit(s[i])) {
      return 0;
    }
  }
  return 1;
}


