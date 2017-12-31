#include <iostream>
#include "Rotor.hpp"

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
  validateInput(value);

  int i;
  for (i = 0; i < NUM_LETTERS; ++i)
  {
    if (config[i] == value) return i;
  }

  return NUM_LETTERS - 1;
}

void Rotor::rotate()
{
  int i;
  int temp;
  //shift all the elements to the left by one index
  temp = config[0];
  for (i = 0; i < NUM_LETTERS; ++i) config[i] = config[i+1];
  config[i] = temp;
  updateRotateCounter();
}

void Rotor::updateRotateCounter()
{
  rotates = (rotates + 1) % (NUM_LETTERS);
}
