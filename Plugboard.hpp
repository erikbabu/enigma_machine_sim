#ifndef PLUGBOARD_GUARD_HPP
#define PLUGBOARD_GUARD_HPP

#include <map>
#include <vector>
#include <fstream>

#define NUM_LETTERS 26

class Plugboard
{
  public:
    Plugboard(const std::string& filename);
    int getMapping(int index) const;
  private:
    std::map<int, int> config;
    std::ifstream validateFile(const std::string& filename) const;
    std::vector<int> getFileContents(std::ifstream& file) const;
    void validateMappingsSize(const int num_items) const;
    void validateMappingsContent(const std::vector<int>& mappings) const;
    void initialiseMap(std::vector<int>& mappings);
};

#endif
