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
    passThroughAllRotors(reversed, prev_val, rotors.rbegin(), rotors.rend()) :
    passThroughAllRotors(reversed, prev_val, rotors.begin(), rotors.end());
}

template<typename Iterator> int EnigmaMachine::passThroughAllRotors(
  bool reversed, int prev_val, Iterator start, Iterator end)
{
  int result = prev_val;

  for (Iterator it = start; it != end; ++it)
  {
    result = reversed ? (*it)->getReverseMapping(result) : (*it)->getMapping(result);
  }

  //rotate rotors if necessary (only on backwards pass)
  if (reversed)
  {
    //first rotor rotates every time
    (*start)->rotate();
    Iterator rot_manager;
    for (rot_manager = start; rot_manager != end; ++rot_manager)
    {
      shared_ptr<Rotor> curr_rotor = *rot_manager;
      //when current rotor has gone full circle and there is a next rotor
      //rotate the next rotor
      if (curr_rotor->isReset() && rot_manager + 1 != end)
      {
        shared_ptr<Rotor> next_rotor = *(rot_manager + 1);
        next_rotor->rotate();
      }
      else
      {
        //if current has not gone full cirlce, none of the rotors need to update
        break;
      }
    }
  }

  return result;
}
