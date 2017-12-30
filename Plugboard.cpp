#include <iostream>
#include "Plugboard.hpp"

using std::map;
using std::vector;
using std::ifstream;
using std::cerr;
using std::endl;
using std::string;
using std::fill_n;

Plugboard::Plugboard(const string& filename)
{
  auto inputFile = validateFile(filename);
  auto mappings = getFileContents(inputFile);
  initialiseMap(mappings);
}

ifstream Plugboard::validateFile(const string& filename) const
{
  ifstream inputFile;
  inputFile.open(filename);

  //check that file exists and can be opened
  if (!inputFile) {
    cerr << "Unable to open file: " + filename << endl;
    exit(1);
  }

  return inputFile;
}

vector<int> Plugboard::getFileContents(ifstream& file) const
{
  //return all numbers stored in the file
  int x;
  vector<int> mappings;
  while (file >> x) mappings.push_back(x);

  //validate mappings
  validateMappingsSize(mappings.size());
  validateMappingsContent(mappings);

  return mappings;
}

void Plugboard::validateMappingsSize(const int num_items) const
{
  if (num_items % 2 != 0)
  {
    cerr << "Error: The number of items should be even." << endl;
    exit(1);
  }
}

void Plugboard::validateMappingsContent(const vector<int>& mappings) const
{
  //create array storing 26 booleans all set to false
  bool numbers_parsed[NUM_LETTERS];
  fill_n(numbers_parsed, NUM_LETTERS, false);

  //ensure that no number has been mapped more than once
  for (auto it = mappings.begin(); it != mappings.end(); ++it)
  {
    int curr_num = *it;
    if (numbers_parsed[curr_num])
    {
      cerr << "Error: Something has been mapped more than once!" << endl;
      exit(1);
    }

    numbers_parsed[curr_num] = true;
  }
}

void Plugboard::initialiseMap(vector<int>& mappings)
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

int Plugboard::getMapping(int index) const
{
  if (!(index >= 0 && index < NUM_LETTERS))
  {
    cerr << "Error: Index out of range." << endl;
    exit(1);
  }

  auto it = config.find(index);
  return it->second;
}
