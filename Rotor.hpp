#ifndef ROTOR_GUARD_HPP
#define ROTOR_GUARD_HPP

#include "MappingTool.hpp"

class Rotor : public MappingTool
{
  public:

    //params:
    //filename - filename containing rotor configuration
    Rotor(const std::string& filename);

    //"rotates" the rotor by one turn.
    void rotate();

    //returns whether or not the rotor has completed a full round
    bool isReset() const { return rotates == 0; }

    //params:
    //index - the index of the letter
    //returns the value at the index mapping
    int getReverseMapping(int index) const;

  private:

    //keeps track of the number of times the rotor has rotated
    int rotates = 0;

    //ensures that there are 26 unique letters in the mapping
    void validateMappingsSize() const;

    //configures map to specified rotor configurations
    void initialiseMap();

    //helper function for getReverseMapping
    int reverseLookup(const int value) const;

    //increments the rotor counter, resetting it everytime it reaches 26
    void updateRotateCounter();
};

#endif
