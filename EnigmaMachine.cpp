#include "EnigmaMachine.hpp"

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;

EnigmaMachine::EnigmaMachine(const vector<string>& rotor_configs,
  const string& plugboard_config)
{
  initialiseRotors(rotor_configs);
  initialisePlugboard(plugboard_config);
}

void EnigmaMachine::initialisePlugboard(const string& plugboard_config)
{
  plugboard = make_shared<Plugboard>(plugboard_config);
}

void EnigmaMachine::initialiseRotors(const vector<string>& rotor_configs)
{
  for (auto it = rotor_configs.begin(); it != rotor_configs.end(); ++it)
  {
    shared_ptr<Rotor> rotor = make_shared<Rotor>(*it);
    rotors.push_back(rotor);
  }
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
