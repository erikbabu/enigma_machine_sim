#ifndef ENIGMA_MACHINE_GUARD_HPP
#define ENIGMA_MACHINE_GUARD_HPP

#include <memory>
#include <vector>
#include "Reflector.hpp"
#include "Rotor.hpp"
#include "Plugboard.hpp"

#define NUM_LETTERS 26
//Using Ceasar(M) cipher (shift by 13)
#define SHIFT_VALUE 13

//Enigma Machine class
class EnigmaMachine
{
  public:
    //params:
    //rotor_configs - filenames of all rotor files
    //plugboard_config - filename of plugboard file
    EnigmaMachine(const std::vector<std::string>& rotor_configs,
      const std::string& plugboard_config);

    //params:
    //letter - the char that is going to be encrypted by enigma
    //returns the encrypted char
    char encrypt(char letter);

  private:
    std::shared_ptr<Reflector> reflector = std::make_shared<Reflector>(
        SHIFT_VALUE, NUM_LETTERS);
    std::vector<std::shared_ptr<Rotor> > rotors;
    std::shared_ptr<Plugboard> plugboard;

    void initialiseRotors(const std::vector<std::string>& rotor_configs);
    void initialisePlugboard(const std::string& plugboard_config);

    //returns value after input has passed through all rotors
    //if reversed, returns value after input passes in reverse order
    int getPostRotorsMapping(int prev_val, bool reversed);

    //helper function for getPostRotorsMapping
    template<typename Iterator> int passThroughAllRotors(int prev_val,
      Iterator start, Iterator end);
};

#endif
