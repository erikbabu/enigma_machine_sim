#include "EnigmaMachine.hpp"
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

  //rotate the rotors afterwards
  rotateRotors(rotors.begin(), rotors.end());

  //pass through plugboard
  plugboard_mapping = plugboard->getMapping(rotor_mapping);

  //output
  return getChar(plugboard_mapping);
}

int EnigmaMachine::getPostRotorsMapping(int prev_val, bool reversed)
{
  if (rotors.empty()) return prev_val;

  //get result of passing through all rotors
  return reversed ?
    passThroughAllRotors(reversed, prev_val, rotors.rbegin(), rotors.rend()) :
    passThroughAllRotors(reversed, prev_val, rotors.begin(), rotors.end());
}

template<typename Iterator> void EnigmaMachine::rotateRotors(
  Iterator start, Iterator end)
{
  //if no rotors, do nothing
  if (start == end) return;

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
    else break;
  }
}

template<typename Iterator> int EnigmaMachine::passThroughAllRotors(
  bool reversed, int prev_val, Iterator start, Iterator end)
{
  int result = prev_val;
  int normal_val = 0;
  for (Iterator it = start; it != end; ++it)
  {
    shared_ptr<Rotor> current = *it;

    if (reversed)
      result = current->getReverseMapping(result);
    else
    {
      //TODO: Fix issue here.
      //incorrect value being passed into normalisedValue
      //rest seems to be correct
      std::cerr << "Num rotations: " << normal_val << std::endl;
      std::cerr << "Result before: " << result << std::endl;
      result = current->getMapping(current->normalisedValue(result - normal_val));
      std::cerr << "Result after: " << result << std::endl;
    }

    //normalise input into next rotor
    normal_val = current->numRotations();
  }
  return result;
}
