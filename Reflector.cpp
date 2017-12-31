#include <iostream>
#include "Reflector.hpp"
#include "Utils.hpp"

using std::cout;
using std::endl;

int Reflector::reflect(int index) const
{
  validateInput(index);
  return (index + shift_value) % num_items;
}
