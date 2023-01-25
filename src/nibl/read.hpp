#ifndef NIBL_READ_HPP
#define NIBL_READ_HPP

#include <optional>

#include "nibl/form.hpp"
#include "nibl/error.hpp"

namespace nibl {
  using namespace std;
  
  using Read = pair<optional<Form>, E>;

  struct VM;

  Read read_id(VM &vm, istream &in, Pos &pos);
  Read read_int(VM &vm, istream &in, Pos &pos, int base);
  Read read_str(VM &vm, istream &in, Pos &pos);
}

#endif
