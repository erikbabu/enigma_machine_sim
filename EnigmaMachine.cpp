#include "EnigmaMachine.hpp"
#include <iostream>

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::cerr;
using std::endl;

EnigmaMachine::EnigmaMachine(const vector<string>& rotor_configs,
  const vector<char>& notch_configs,
  const string& plugboard_config)
{
  initialisePlugboard(plugboard_config);
  initialiseRotors(rotor_configs, notch_configs);
}

void EnigmaMachine::initialisePlugboard(const string& plugboard_config)
{
  plugboard = make_shared<Plugboard>(plugboard_config);
}

void EnigmaMachine::initialiseRotors(const vector<string>& rotor_configs,
  const vector<char>& notch_configs)
{
  //validate that num rotors is num configs
  if (rotor_configs.size() != notch_configs.size())
  {
    cerr << "Number of rotors does not equal number of notch configurations!"<< endl;
    exit(1);
  }
  auto notch_iterator = notch_configs.begin();

  for (auto it = rotor_configs.begin(); it != rotor_configs.end(); ++it)
  {
    shared_ptr<Rotor> rotor = make_shared<Rotor>(*it, *notch_iterator++);
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

  //noralise next rotor if it exists
  if (hasNextRotor(start, end))
  {
    auto second_rotor = *(start + 1);
    second_rotor->normalise();
  }

  Iterator rot_manager;
  for (rot_manager = start; rot_manager != end; ++rot_manager)
  {
    auto curr_rotor = *rot_manager;
    //when current rotor has gone full circle and there is another rotor
    //rotate the next rotor
    //if rotated rotor has next, normalise the inputs into the next
    if (curr_rotor->isReset() && hasNextRotor(rot_manager, end))
    {
      shared_ptr<Rotor> next_rotor = *(rot_manager + 1);
      next_rotor->rotate();

      if (hasNextRotor(rot_manager + 1, end)) next_rotor->normalise();
    }
    else break;
  }
}

template<typename Iterator> bool EnigmaMachine::hasNextRotor(
  Iterator current, Iterator end)
{
  return current + 1 != end;
}

template<typename Iterator> int EnigmaMachine::passThroughAllRotors(
  bool reversed, int prev_val, Iterator start, Iterator end)
{
  int result = prev_val;
  for (Iterator it = start; it != end; ++it)
  {
    shared_ptr<Rotor> current = *it;
    result = reversed ? current->getReverseMapping(result) : current->getMapping(result);
  }
  return result;
}
