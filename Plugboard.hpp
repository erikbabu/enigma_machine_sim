#ifndef PLUGBOARD_GUARD_HPP
#define PLUGBOARD_GUARD_HPP

#include "MappingTool.hpp"

class Plugboard: public MappingTool
{
  public:

    //params:
    //filename - the file containing the Plugboard configs
    Plugboard(const std::string& filename);

  private:

    //ensures that there are an even number of mappings
    void validateMappingsSize() const;

    //creates mapping based on config file. if no mapping give, item maps
    //to itself
    void initialiseMap();
};

#endif
