#ifndef ROTOR_GUARD_HPP
#define ROTOR_GUARD_HPP

#include "MappingTool.hpp"

class Rotor : public MappingTool
{
  public:

    //params:
    //filename - filename containing rotor configuration
    Rotor(const std::string& filename, const char notch_position);

    //"rotates" the rotor by one turn.
    void rotate();


    //returns whether or not the rotor has completed a full round
    bool isReset() const { return rotates == 0; }

    //params:
    //index - the index of the letter
    //returns the value at the index mapping
    int getReverseMapping(const int index) const;

    //returns the number of rotations out of 26 the rotor has performed
    int numRotations() const { return rotates; }

    //normalises the rotors. i.e. shift all items to the right by 1 index
    void normalise();

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

    //shift all the elements to the left by one index
    void leftRotate();
};

#endif
