/*Ricardo Varona
CPSC 1071
4/25/2023
Purpose of file is to load in a dictionary, search for matches with cards, and print out those matches
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Quiddler.h"

// Purpose of the function is to get all the valid words from the dictionary that are maxLength or less
int loadDictionary(char *words[] , int maxLength) {
   // pointer to file object(as shown in cplusplus.com
   FILE * pFile;
   // declare dictionarry array large enough to hold all words in dictionary and initalize to null
   char *dictionary [103000] = {NULL};
   // int count to iterate through array
   int count = 0;
   // tempDict size 50 to temparily hold any word in the dictionary 
   char tempDict[50] = "";
   // newWord to copy word in tempDict
   char *newWord;
   // word incrementer to count how many valid words found in dictionary
   int wordAmount = 0;

   // Opens file for dictionary and reads it
   pFile = fopen ("/usr/share/dict/words" , "r");

   // While there is still stuff in the dictionary, reads in word to temptGuess
   // with size 50(largest word in dictionary was 46 when I searched online)
   while (fgets(tempDict, 50, pFile) != NULL) {
       // because im reading in the dictionary using fgets and im basing what im putting into dictionary based on strnlength
       // I have to account for the newline altering the length of strings
       //change newlineto null to stop it from being read into the string
       tempDict[strlen(tempDict) - 1] = '\0';
       // if the length of the word read in dictionary is less than or equal max length, then will begin putting it into words
       if (strlen(tempDict) <= maxLength) {
           // Allocates memory for newWord and accounts for null character
           newWord = malloc(sizeof(char) * (strlen(tempDict) + 1));
           // copies word from tempDict to newWord
           strcpy(newWord, tempDict);
           //Sets current element in dictionary = to new word
           dictionary[count] = newWord;
           // iterates count and wordAmount(to get the amount of words as shown in autoGrader)
           count++;
           wordAmount++;
       }
   }
   // closes the file
   fclose(pFile);
   
   // for the length of worfs put in the dictionary
   for (int i = 0; i < count; i++) {
       // allocates memory for words 
       words[i] = malloc(sizeof(char) * (strlen(dictionary[i]) + 1));
       // copies words from dictionary to words
       strcpy(words[i], dictionary[i]);
       //printf("%s", words[i]);
       // free up memory used for dictionary
       free(dictionary[i]);
   }
   // prints out number of words found in the propor format 
   puts("Processing Dictionary");
   printf("%d out of 102401 words in the dictionary are less than %d!\n", wordAmount, maxLength);

   // returns words found
   return count;

}

// Purpose of function is to print the results of processGuess
void printResults(char *words[], int length) {
    
    // number to iterate through words
    int number = 0;

    // prints out words in the proper format. If the word is larger than 2, it will print out the word
    puts("Possible Options:");
    for(int i = 0; i < length; i++) {
        if(strlen(words[i]) > 2) {
            printf("\t%d: %s\n", number, words[i]);
            number++;
        }
    }
    //\n to print out in propor format
    printf("\n"); 
}

// Purpose of function is to prompt the user for what cards they wish to enter and how to enter them
char * promptUser() {
    // There are 30 possible cards but 
    char inputString[30];
    puts("\nWelcome to the Quiddler Assistant!\n");
    puts("Enter your Quiddler cards with the following scheme:");
    puts("\tSeparate each card with a space");
    puts("\tEnter cards in any order");
    puts("\tExample input: 'CL E N A T'");
    printf("\tCards: ");
    fgets(inputString, 30, stdin);

    // for the length of inputString, captilizes every character in character array using toupper
    for(int i = 0; i < strlen(inputString); i++) {
            inputString[i] = toupper(inputString[i]);
    }

    // char stringPointer declared so that string can be used in proccessGuess
    char *stringPointer;

    // allocates memory for largest possible number of cards possible in quiddler(30)
    stringPointer = (char*)malloc(sizeof(char) * 30);
    // copies inputString to stringPointer
    strcpy(stringPointer, inputString);

    // return stringPointer so it can be used when calling processGuess
    return stringPointer;

}

// Purpose of the function is to is split what the user inputted for cards, compared it to the dictionary, and find all possible words that can be made
void processGuess(char *cardString) {
    // initalize char words and passes words and length when calling load dictionary
    char *words[103000];
    int count = loadDictionary(words, 6);
    // declare char pointer array and allocate space for it
    char *cards[30];
    for (int i = 0; i < 30; i++) {
        cards[i] = (char*)malloc(sizeof(char) * 30);
    }

    //cardCount represents number of cards
    int cardCount = 0;
    // Learned about strTok because of charlie!. He said I should use a c command specifcally for splitting strings
    // Found it on cpluscplus.com Made this so much easier!
    
    // pch pointer to serve as beginning of strtok token 
    char *pch;
    
    // card string passed as input string and " " working as the delimeter
    pch = strtok(cardString, " ");
    while (pch != NULL) {
        // copies token pointed by pch into cards[CardCount]
        strcpy(cards[cardCount], pch);
        //cardCount increases since an new card was inputed
        cardCount++;
        // If there are no more tokens, pch set to null and code will end
        pch = strtok(NULL, " ");
    }
    
    // initialize needed counters
    int wordCounter = 0;
    int characterCounter = 0;
    int size = 0; 
    // declare char pointer to hold every possible string that could be in the dictionary 
    char *holdString[count];

    // array of boolean to check if each card has been used or not. defaults to false
    bool fixRepeat[cardCount];

    // using str str, use pointer add tempory result, if not = to null, move that on to the next card, and so on and so forth.
    // everytime check a card letter against dictionary 
    // make sure no gaps in words

    while(words[wordCounter] != NULL) {
        characterCounter = 0;
        for(int j = 0; j < strlen(words[wordCounter]); j++) {
            for(int k = 0; k < cardCount; k++) {
                // checks if the cards length is two to account for the four 2 letter cards
                // sets the word at position 0 to a capital letter as well as at position 0
                // checks if the current character in word counter is equal to the firt in the two letter card
                // checks if the next character in word counter is equal to to the second character in card
                if(strlen(cards[k]) == 2 && toupper(words[wordCounter][j]) == cards[k][0] && (j+1 < strlen(words[wordCounter]) && toupper(words[wordCounter][j+1]) == cards[k][1]) && !fixRepeat[k]) {
                    // card is set to true indicating its been used
                    fixRepeat[k] = true;
                    // character counter increments by two since the card its 2 letters
                    characterCounter+=2;
                    // the word is moved up by two since the card its two letters long 
                    j+=1;
                }
                // if the card is only one character and matches a character in the dictionary word and has not been used yet
                else if(toupper(words[wordCounter][j]) == cards[k][0] && !fixRepeat[k]){
                    // hardcode check to ensure two letter cards no not get incremented a second time
                    if(!(cards[k][0] == 'C' && cards[k][1] == 'L') && !(cards[k][0] == 'I' && cards[k][1] == 'N') && !(cards[k][0] == 'E' && cards[k][1] == 'R') && !(cards[k][0] == 'T' && cards[k][1] == 'H')) {
                        // fixRepeat set to true so card isnt reused
                        fixRepeat[k] = true;
                        // character counter goes up one since only one character matched
                        characterCounter++;
                    }
                } 
            }
        }
        // fix repeat set false for each card at the end of the loop
        for(int i = 0; i < cardCount; i++) {
            fixRepeat[i] = false;
        }
        
        // if character counter is equal to the length of a word in the dictionary, space is allocated and it is copied into holdstring
        // size is incremented so the array size of holdstring is dynmaically allocated
        if(characterCounter == strlen(words[wordCounter])) {
            holdString[size] = malloc(sizeof(char) * (strlen(words[wordCounter] + 1)));
            strcpy(holdString[size], words[wordCounter]);
            size++;
        }
        // wordCounter incremented to get the next word in the dictionary
        wordCounter++;
    }
    // calls print results and pases the size and contents of holdstring array 
    printResults(holdString, size);

    // Each element in holdstring is freed for the length of the size
    for(int i = 0; i < size; i++) {
        free(holdString[i]);
    }
    
    // each element in cards is free for the length of the card array
    for (int i = 0; i < 30; i++) {
        free(cards[i]);
    }
}

// Purpose of function is to work as a driver. 
void helpMe() {
    // calls prompt user and stores it as a char pointerso it can be passed to proccessGuess 
    char *storeUser = promptUser();
    processGuess(storeUser);
}
