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
    void rotate();
    bool isReset() const { return rotates == 0; }
    int getReverseMapping(int index) const;
  private:
    int rotates = 0;
    void validateMappingsSize() const;
    void initialiseMap();
    int reverseLookup(const int value) const;
    int outputShifted(const int index) const;
    void updateRotateCounter();
};

#endif
