#ifndef ROTOR_GUARD_HPP
#define ROTOR_GUARD_HPP

#include <map>
#include <vector>
#include <fstream>
#include "MappingTool.hpp"

class Rotor : public MappingTool
{
  public:
    Rotor(const std::string& filename);
  private:
    void validateMappingsSize(const int num_items) const;
    void initialiseMap(const std::vector<int>& mappings);
};

#endif
