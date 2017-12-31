#ifndef PLUGBOARD_GUARD_HPP
#define PLUGBOARD_GUARD_HPP

#include "MappingTool.hpp"

class Plugboard: public MappingTool
{
  public:
    Plugboard(const std::string& filename);
  private:
    // void validateMappings(const std::vector<int>& mappings) const;
    void validateMappingsSize() const;
    void initialiseMap();
};

#endif
