#include "Utils.hpp"

char getChar(int index)
{
  return index + ASCII_A_INDEX;
}

int getIndex(char letter)
{
  return letter - ASCII_A_INDEX;
}
