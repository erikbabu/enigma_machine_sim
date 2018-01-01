#ifndef MAPPING_TOOL_GUARD_HPP
#define MAPPING_TOOL_GUARD_HPP

#include <fstream>
#include <vector>
#include "Utils.hpp"

//superclass for enigma machine parts (rotor/plugboard)
class MappingTool
{
  friend class Plugboard;
  friend class Rotor;
  friend class Reflector;

  public:

    //params:
    //filename - the name of the file that will be used to configure the tool
    MappingTool(const std::string& filename);

    //params:
    //index - the index of the letter that needs to be mapped
    //returns the position in the array of the index representing the letter
    int getMapping(const int index) const;

  private:

    //stores the mappings read from file
    std::vector<int> mappings;

    //internal representation of mapping
    int config[NUM_LETTERS];

    //ensures file exists and can be read from
    std::ifstream validateFile(const std::string& filename) const;

    //stores the contents in mappings
    std::vector<int> getFileContents(std::ifstream& file) const;

    //ensures that no same item is mapped more than once
    void validateMappingsContent() const;

    //defined in subclasses. Sanity checks that the mappings are valid
    virtual void validateMappingsSize() const = 0;

    //defined in subclasses. Creates mapping based on configuration files
    virtual void initialiseMap() = 0;
};

#endif
