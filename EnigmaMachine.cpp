#include "EnigmaMachine.hpp"

using std::vector;
using std::string;

EnigmaMachine::EnigmaMachine(const vector<string>& rotor_configs,
  const string& plugboard_config)
{

}

EnigmaMachine::EnigmaMachine(const string& plugboard_config)
{

}

char EnigmaMachine::encrypt(char letter)
{
  //TODO: Implement
  //pass through plugboard
  //pass through rotors

  //reflect letter
  int reflect_index = reflector->reflect(getIndex(letter));
  letter = getChar(reflect_index);

  return letter;
}

char EnigmaMachine::getChar(int index) const
{
  return index + ASCII_A_INDEX;
}

int EnigmaMachine::getIndex(char letter) const
{
  return letter - ASCII_A_INDEX;
}
