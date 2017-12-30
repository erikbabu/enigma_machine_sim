#include <stdexcept>
#include <iostream>
#include <vector>
#include <memory>
#include "EnigmaMachine.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;
using std::cin;
using std::istream;

typedef shared_ptr<EnigmaMachine> em_s_ptr;

//params:
//rotor_start - the iterator start position
//rotor_end - the iterator end position
//returns a vector storing the filenames of the rotor configurations
template<typename Iterator> vector<string> getRotorConfigs(
  Iterator rotor_start, Iterator rotor_end);

//params:
//in - reference to std input
//em - reference to enigma machine
//returns the cipher text for the message entered into std in
vector<char> getCipherText(istream& in, em_s_ptr& em);

//params:
//input - the character being tested
//returns whether or not character is in range A-Z (inclusive)
bool isValidInput(char input);

//params:
//cipher - the encrypted chars to be displayed to std out
void display_cipher(vector<char>& cipher);

int main(int argc, char **argv)
{
  //program requires optional rotor args and 1 plugboard arg
  if (argc < 2)
  {
    cerr << "Invalid args entered. Please ensure program is invoked like:\n" <<
      "./enigma <rotor_config>* <plugboard_config>" << endl;
    exit(1);
  }

  //store positions of rotors and plugboard
  auto rotor_start = argv + 1;
  auto rotor_end = argv + argc - 1;
  auto plugboard_config = argv[argc - 1];

  //rotor configs are every file except arg0(filename) and last arg(plugboard)
  vector<string> rotor_configs = getRotorConfigs(rotor_start, rotor_end);

  //set up enigma machine
  em_s_ptr em_ptr = rotor_configs.empty() ?
  make_shared<EnigmaMachine>(plugboard_config) :
  make_shared<EnigmaMachine>(rotor_configs, plugboard_config);
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
  while (rotor_start != rotor_end) rotor_configs.push_back(*rotor_start++);
  return rotor_configs;
}

vector<char> getCipherText(istream& in, em_s_ptr& em)
{
  char input;
  vector<char> cipher;
  while (in >> input)
  {
    if (isValidInput(input))
    {
      //encrypt character and store
      cipher.push_back(em->encrypt(input));
    }
    else
    {
      cerr << "The char: " << input << " is not in range A-Z. Aborting!" << endl;
      exit(1);
    }
  }

  return cipher;
}

bool isValidInput(char input) {
  return input >= 'A' && input <= 'Z';
}

void display_cipher(vector<char>& cipher)
{
  for(auto it = cipher.begin(); it != cipher.end(); ++it) cout << *it;
  cout << endl;
}
