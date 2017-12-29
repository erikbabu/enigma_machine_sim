#include <iostream>
#include "Reflector.hpp"

using std::cout;
using std::endl;

int Reflector::getMapping(int index) const
{
  validateInput(index);
  return (index + shift_value) % num_items;
}

void Reflector::validateInput(int index) const
{
  if (!(index >= 0 && index < num_items))
  {
    cout << "Error: Current character is not uppercase. "
      << "Please ensure all input is in range A-Z inclusive!" << endl;
    exit(1);
  }
}
