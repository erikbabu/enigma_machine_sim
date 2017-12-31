#include <iostream>
#include "Utils.hpp"

using std::cerr;
using std::endl;

char getChar(int index)
{
  return index + ASCII_A_INDEX;
}

int getIndex(char letter)
{
  return letter - ASCII_A_INDEX;
}

void validateInput(int index)
{
  if (!(index >= 0 && index < NUM_LETTERS))
  {
    cerr << "Error: Current character is not uppercase. "
      << "Please ensure all input is in range A-Z inclusive!" << endl;
    exit(1);
  }
}
