#ifndef NIBL_LIB_HPP
#define NIBL_LIB_HPP

#include <map>

#include "nibl/env.hpp"

namespace nibl {
  struct VM;
  
  struct Lib: Env {
    const optional<string> name;
    const optional<Pos> pos;
    const size_t tag;
    
    Lib(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos);
  };

  ostream &operator <<(ostream &out, const Lib &l);
}

#endif
