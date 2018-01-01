#ifndef REFLECTOR_GUARD_HPP
#define REFLECTOR_GUARD_HPP

#include "MappingTool.hpp"

class Reflector : public MappingTool
{
  public:

    //params:
    //filename - file containing reflector configurations
    Reflector(const std::string& filename);

    //params:
    //index - the value that needs to be reflected
    //returns the reflected value provided the index is valid
    int reflect(int index) const;

  private:

    //ensures that there are 26 unique letters in the mapping
    void validateMappingsSize() const;

    //configures map to specified rotor configurations
    void initialiseMap();
};

#endif
