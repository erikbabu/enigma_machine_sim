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
    void validateMappingsSize() const;
    void initialiseMap();
    void rotateRotor();
};

#endif
