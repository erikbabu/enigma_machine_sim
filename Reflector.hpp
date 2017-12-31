#ifndef REFLECTOR_GUARD_HPP
#define REFLECTOR_GUARD_HPP

//Reflector class
class Reflector
{
  public:
    //params:
    //shift - the value each index should be shifted by
    //range - the total number of possible indices
    Reflector(int shift, int range): shift_value(shift), num_items(range) {}

    //params:
    //index - the value that needs to be reflected
    //returns the reflected value provided the index is valid
    int reflect(int index) const;

  private:
    const int shift_value;
    const int num_items;
};

#endif
