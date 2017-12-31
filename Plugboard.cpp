#include <iostream>
#include "Plugboard.hpp"

using std::vector;
using std::cerr;
using std::endl;
using std::string;

Plugboard::Plugboard(const string& filename): MappingTool(filename)
{
  validateMappingsSize();
  initialiseMap();
}

void Plugboard::validateMappingsSize() const
{
  if (mappings.size() % 2 != 0)
  {
    cerr << "Error: The number of items should be even." << endl;
    exit(1);
  }
}

void Plugboard::initialiseMap()
{
  //default map a number to itself
  for (int i = 0; i < NUM_LETTERS; ++i)
  {
    config[i] = i;
  }

  //update map with new mappings
  for(auto it = mappings.begin(); it != mappings.end(); )
  {
    int a = *it++;
    int b = *it++;

    //create "plug"
    config[a] = b;
    config[b] = a;
  }
}
