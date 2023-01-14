#ifndef NIBL_READ_HPP
#define NIBL_READ_HPP

#include <optional>

#include "nibl/form.hpp"
#include "nibl/error.hpp"

namespace nibl {
  using namespace std;
  
  using Read = pair<optional<Form>, optional<Error>>;

  struct VM;

  Read read_id(const VM &vm, istream &in, Pos &pos);
  Read read_int(const VM &vm, istream &in, Pos &pos, int base);
}

#endif
