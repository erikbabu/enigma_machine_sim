#include <iostream>
#include "Rotor.hpp"
#include "Utils.hpp"

using std::string;
using std::cerr;
using std::vector;
using std::endl;

Rotor::Rotor(const string& filename) : MappingTool(filename)
{
  validateMappingsSize();
  initialiseMap();
}

void Rotor::validateMappingsSize() const
{
  if (mappings.size() != NUM_LETTERS)
  {
    cerr << "Error: Should be 26 numbers in file from 0-25 inclusive!" << endl;
    exit(1);
  }
}

void Rotor::initialiseMap()
{
  for (int i = 0; i < NUM_LETTERS; ++i)
  {
    config[i] = mappings[i];
  }
}

int Rotor::getReverseMapping(const int value) const
{
  ::validateInput(value);
  // int shifted_output = outputShifted(value);
  return reverseLookup(value);
}

int Rotor::reverseLookup(const int value) const
{
  int i;
  for (i = 0; i < NUM_LETTERS; ++i)
  {
    if (config[i] == value) return i;
  }

  return NUM_LETTERS - 1;
}

int Rotor::outputShifted(const int index) const
{
  if (rotates % 2 == 0) return index;

  int value_shifted = (index - rotates - 1);
  value_shifted = (value_shifted >= 0) ? value_shifted : NUM_LETTERS - 1 + value_shifted;
  return reverseLookup(value_shifted);
}

void Rotor::rotate()
{
  int i;
  int temp;
  //shift all the elements to the left by one index
  temp = config[0];
  for (i = 0; i < NUM_LETTERS; ++i) config[i] = config[i+1];
  config[--i] = temp;

  updateRotateCounter();
}

void Rotor::updateRotateCounter()
{
  rotates = (rotates + 1) % (NUM_LETTERS);
}
