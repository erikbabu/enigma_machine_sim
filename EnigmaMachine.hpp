#ifndef ENIGMA_MACHINE_GUARD_HPP
#define ENIGMA_MACHINE_GUARD_HPP

#define ASCII_A_INDEX 65

#include <memory>
#include <vector>
#include "Reflector.hpp"

//Enigma Machine class
class EnigmaMachine
{
  const int NUM_LETTERS = 26;
  //Using Ceasar(M) cipher (shift by 13)
  const int SHIFT_VALUE = 13;

  public:
    EnigmaMachine(const std::vector<std::string>& rotor_configs,
      const std::string& plugboard_config);
    EnigmaMachine(const std::string& plugboard_config);
    ~EnigmaMachine() {}
    char encrypt(char letter);
  private:
    std::shared_ptr<Reflector> reflector = std::make_shared<Reflector>(
        SHIFT_VALUE, NUM_LETTERS);
    char getChar(int index) const;
    int getIndex(char letter) const;
};

#endif
