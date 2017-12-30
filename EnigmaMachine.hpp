#ifndef ENIGMA_MACHINE_GUARD_HPP
#define ENIGMA_MACHINE_GUARD_HPP

#define ASCII_A_INDEX 65

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
    EnigmaMachine(const std::vector<std::string>& rotor_configs,
      const std::string& plugboard_config);
    ~EnigmaMachine() {}
    char encrypt(char letter);
  private:
    std::shared_ptr<Reflector> reflector = std::make_shared<Reflector>(
        SHIFT_VALUE, NUM_LETTERS);
    std::vector<std::shared_ptr<Rotor> > rotors;
    std::shared_ptr<Plugboard> plugboard;
    void initialiseRotors(const std::vector<std::string>& rotor_configs);
    void initialisePlugboard(const std::string& plugboard_config);
    char getChar(int index) const;
    int getIndex(char letter) const;
};

#endif
