#ifndef MAPPING_TOOL_GUARD_HPP
#define MAPPING_TOOL_GUARD_HPP

#define NUM_LETTERS 26

#include <map>
#include <fstream>
#include <vector>
#include <string>

class MappingTool
{
  public:
    MappingTool(const std::string& filename);
    int getMapping(int index) const;

  protected:
    std::vector<int> mappings;
    std::map<int, int> config;
    std::ifstream validateFile(const std::string& filename) const;
    std::vector<int> getFileContents(std::ifstream& file) const;
    void validateMappingsContent(const std::vector<int>& mappings) const;
    virtual void validateMappingsSize(const int num_items) const = 0;
    void validateMappings(const std::vector<int>& mappings) const;
    virtual void initialiseMap(std::vector<int>& mappings) = 0;
};

#endif
