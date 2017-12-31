#ifndef UTILS_GUARD_HPP
#define UTILS_GUARD_HPP

//ascii position of A
#define ASCII_A_INDEX 65
//number of uppercase letters in the alphabet
#define NUM_LETTERS 26

//params:
//index - the index of the letter
//returns the character representation of the index
char getChar(int index);

//params:
//letter - the char that needs to be converted to an int
//returns the int representation of the letter
int getIndex(char letter);

//params:
//index - the index of the letter
//checks that index is within range 0-25
void validateInput(int index);

#endif
