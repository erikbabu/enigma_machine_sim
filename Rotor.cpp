#include <iostream>
#include "Rotor.hpp"
#include "Utils.hpp"

using std::string;
using std::cerr;
using std::vector;
using std::endl;

Rotor::Rotor(const string& filename, const int notch_position) :
  MappingTool(filename)
{
  validateMappingsSize();
  initialiseMap();

  //set up rotors to match notch config
  for (int i = 0; i < notch_position; ++i)
  {
    leftRotate();
    normalise();
  }
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

void Rotor::rotate()
{
  leftRotate();
  updateRotateCounter();
}

void Rotor::updateRotateCounter()
{
  rotates = (rotates + 1) % (NUM_LETTERS);
}

void Rotor::normalise()
{
  int i;
  int temp = config[NUM_LETTERS - 1];
  //shift all elements to the right by one index
  for (i = NUM_LETTERS - 1; i >= 0; --i) config[i] = config[i - 1];
  config[0] = temp;
}

void Rotor::leftRotate()
{
  int i;
  int temp = config[0];
  for (i = 0; i < NUM_LETTERS; ++i) config[i] = config[i+1];
  config[NUM_LETTERS - 1] = temp;
}
