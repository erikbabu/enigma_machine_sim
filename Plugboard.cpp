#include <iostream>
#include "Plugboard.hpp"

using std::map;
using std::vector;
using std::cerr;
using std::endl;
using std::string;

Plugboard::Plugboard(const string& filename): MappingTool(filename)
{
  validateMappingsSize(mappings.size());
  initialiseMap(mappings);
}

void Plugboard::validateMappingsSize(const int num_items) const
{
  if (num_items % 2 != 0)
  {
    cerr << "Error: The number of items should be even." << endl;
    exit(1);
  }
}

void Plugboard::initialiseMap(const vector<int>& mappings)
{
  //default map a number to itself
  for (int i = 0; i < NUM_LETTERS; ++i)
  {
    config.insert({i, i});
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
