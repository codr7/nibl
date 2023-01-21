#ifndef NIBL_STACK_HPP
#define NIBL_STACK_HPP

#include <vector>
#include "nibl/val.hpp"

namespace nibl {
  using Stack = vector<Val>;
  
  ostream &operator <<(ostream &out, const Stack &s);
}

#endif
