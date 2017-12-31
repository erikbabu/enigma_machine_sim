#include <iostream>
#include "Rotor.hpp"

using std::string;
using std::cerr;
using std::vector;
using std::endl;

Rotor::Rotor(const string& filename) : MappingTool(filename)
{
  validateMappingsSize(mappings.size());
  initialiseMap(mappings);
}

void Rotor::validateMappingsSize(const int num_items) const
{
  if (num_items != NUM_LETTERS)
  {
    cerr << "Error: Should be 26 numbers in file from 0-25 inclusive!" << endl;
    exit(1);
  }
}

void Rotor::initialiseMap(const vector<int>& mappings)
{
  for (int i = 0; i < NUM_LETTERS; ++i)
  {
    config[i] = mappings[i];
  }
}
