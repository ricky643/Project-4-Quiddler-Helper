
/*Ricardo Varona
CPSC 1070
4/25/2023
Purpose of file is to declare all needed functions in Quiddler.c
*/

#ifndef QUIDDLER_H
#define QUIDDLER_H

// Declares all needed functions for Quidder.c
int loadDictionary(char *words[], int maxLength);
void printResults(char *words[], int length);
char * promptUser();
void processGuess(char *cardString);
void helpMe();


#endif

