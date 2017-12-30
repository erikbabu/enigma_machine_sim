#include <iostream>
#include "MappingTool.hpp"

using std::map;
using std::vector;
using std::ifstream;
using std::cerr;
using std::endl;
using std::string;
using std::fill_n;

MappingTool::MappingTool(const string& filename)
{
  auto inputFile = validateFile(filename);
  mappings = getFileContents(inputFile);
  validateMappings(mappings);
}

ifstream MappingTool::validateFile(const string& filename) const
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

vector<int> MappingTool::getFileContents(ifstream& file) const
{
  //return all numbers stored in the file
  int x;
  vector<int> mappings;
  while (file >> x) mappings.push_back(x);

  return mappings;
}

void MappingTool::validateMappings(const vector<int>& mappings) const
{
  validateMappingsSize(mappings.size());
  validateMappingsContent(mappings);
}

void MappingTool::validateMappingsContent(const vector<int>& mappings) const
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

int MappingTool::getMapping(int index) const
{
  if (!(index >= 0 && index < NUM_LETTERS))
  {
    cerr << "Error: Index out of range." << endl;
    exit(1);
  }

  auto it = config.find(index);
  return it->second;
}
