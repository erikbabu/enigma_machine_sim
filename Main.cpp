#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include "EnigmaMachine.hpp"
#include "Utils.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;
using std::cin;
using std::istream;
using std::distance;
using std::set;

typedef shared_ptr<EnigmaMachine> em_s_ptr;

//params:
//rotor_start - the iterator start position
//rotor_end - the iterator end position
//returns a vector storing the filenames of the rotor configurations
template<typename Iterator> vector<string> getRotorConfigs(
  Iterator rotor_start, Iterator rotor_end);

//parms:
//in - reference to std input
//num_configs - the number of rotors
vector<char> getRotorNotchConfigs(istream& in, int num_rotors);

//params:
//in - reference to std input
//em - reference to enigma machine
//returns the cipher text for the message entered into std in
vector<char> getCipherText(istream& in, em_s_ptr& em);

//params:
//cipher - the encrypted chars to be displayed (in blocks of 5) to std out
void display_cipher(vector<char>& cipher);

int main(int argc, char **argv)
{
  //program requires rotor args (optional), 1 plugboard arg, 1 reflector arg
  if (argc < 2)
  {
    cerr << "Invalid args entered. Please ensure program is invoked like:\n" <<
      "./enigma <rotor_config>* <plugboard_config> <reflector_config>" << endl;
    exit(1);
  }

  //store positions of rotors and plugboard
  auto rotor_start = argv + 1;
  auto rotor_end = argv + argc - 2;
  auto plugboard_config = argv[argc - 2];
  auto reflector_config = argv[argc - 1];

  int num_rotors = distance(rotor_start, rotor_end);
  vector<char> notch_configs;
  if (num_rotors > 0)
  {
    //get rotor notch configs
    cout << "Please enter your rotor configurations\n e.g. BJK if you have 3 rotors.\n"
      << "Please ensure that the number of configurations = number of rotors:"
      << endl;

    notch_configs = getRotorNotchConfigs(cin, num_rotors);
  }

  //rotor configs are every file except arg0(filename) and last arg(plugboard)
  vector<string> rotor_configs = getRotorConfigs(rotor_start, rotor_end);

  //set up enigma machine
  em_s_ptr em_ptr =
    make_shared<EnigmaMachine>(
      rotor_configs, notch_configs, plugboard_config, reflector_config);

  cout << "Please enter the message you would like to encrypt, followed by ctrl + d:"
    << endl;

  vector<char> cipher = getCipherText(cin, em_ptr);

  //separate input from output
  cout << endl;

  //write cipher text to std out
  display_cipher(cipher);

  return 0;
}

template<typename Iterator> vector<string> getRotorConfigs(
  Iterator rotor_start, Iterator rotor_end)
{
  vector<string> rotor_configs;
  //set needed to check duplicate rotors not used
  set<string> r_c;
  while (rotor_start != rotor_end)
  {
    auto config = *rotor_start++;

    if (r_c.find(config) != r_c.end())
    {
      cerr << "Cannot use the same rotor more than once!" << endl;
      exit(1);
    }

    r_c.insert(config);
    rotor_configs.push_back(config);
  }
  return rotor_configs;
}

vector<char> getRotorNotchConfigs(istream& in, int num_rotors)
{
  char c;
  vector<char> notch_configs;
  int counter = 0;
  while (counter++ < num_rotors && (in >> c))
  {
    validateInput(getIndex(c));
    notch_configs.push_back(c);
  }

  return notch_configs;
}

vector<char> getCipherText(istream& in, em_s_ptr& em)
{
  char input;
  vector<char> cipher;
  while (in >> input)
  {
    validateInput(getIndex(input));
    cipher.push_back(em->encrypt(input));
  }
  return cipher;
}

void display_cipher(vector<char>& cipher)
{
  int counter = 0;
  const int grouping_size = 5;
  for(auto it = cipher.begin(); it != cipher.end(); ++it)
  {
    cout << *it;
    ++counter;
    if (counter == grouping_size)
    {
      counter = 0;
      cout << " ";
    }
  }
  cout << endl;
}
