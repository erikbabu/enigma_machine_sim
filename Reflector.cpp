#include <iostream>
#include "Reflector.hpp"
#include "Utils.hpp"

using std::cerr;
using std::endl;
using std::string;

Reflector::Reflector(const string& filename) : MappingTool(filename)
{
  validateMappingsSize();
  initialiseMap();
}

int Reflector::reflect(int index) const
{
  return getMapping(index);
}

void Reflector::validateMappingsSize() const
{
  if (mappings.size() != NUM_LETTERS)
  {
    cerr << "Error: Should be 26 numbers in file from 0-25 inclusive!" << endl;
    exit(1);
  }
}

void Reflector::initialiseMap()
{
  for (int i = 0; i < NUM_LETTERS; ++i)
  {
    config[i] = mappings[i];
  }
}
