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
    int getMapping(const int index) const;
  protected:
    std::vector<int> mappings;
    int config[NUM_LETTERS];
    std::ifstream validateFile(const std::string& filename) const;
    std::vector<int> getFileContents(std::ifstream& file) const;
    void validateMappingsContent() const;
    virtual void validateMappingsSize() const = 0;
    virtual void initialiseMap() = 0;
    void validateInput(const int index) const;
};

#endif
