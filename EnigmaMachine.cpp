#include "EnigmaMachine.hpp"
#include "Utils.hpp"
#include <iostream>

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;

EnigmaMachine::EnigmaMachine(const vector<string>& rotor_configs,
  const string& plugboard_config)
{
  initialisePlugboard(plugboard_config);
  initialiseRotors(rotor_configs);
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
  //FIRST STAGE (plugboard, rotors, reflect)
  int letter_index = getIndex(letter);

  //pass through plugboard
  int plugboard_mapping = plugboard->getMapping(letter_index);

  //pass through rotors
  int rotor_mapping = getPostRotorsMapping(plugboard_mapping, false);

  //reflect letter
  int reflect_index = reflector->reflect(rotor_mapping);

  //SECOND STAGE (rotors, plugboard, output)
  //pass through rotors in reverse order
  rotor_mapping = getPostRotorsMapping(reflect_index, true);

  //pass through plugboard
  plugboard_mapping = plugboard->getMapping(rotor_mapping);

  //output
  letter = getChar(plugboard_mapping);
  return letter;
}

int EnigmaMachine::getPostRotorsMapping(int prev_val, bool reversed)
{
  if (rotors.empty()) return prev_val;

  return reversed ?
    passThroughAllRotors(prev_val, rotors.rbegin(), rotors.rend()) :
    passThroughAllRotors(prev_val, rotors.begin(), rotors.end());
}

template<typename Iterator> int EnigmaMachine::passThroughAllRotors(int prev_val,
  Iterator start, Iterator end)
{
  int result = prev_val;
  for (Iterator it = start; it != end; ++it) result = (*it++)->getMapping(result);
  return result;
}
