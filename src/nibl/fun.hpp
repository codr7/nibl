#ifndef NIBL_FUN_HPP
#define NIBL_FUN_HPP

#include <optional>
#include "nibl/pos.hpp"
#include "nibl/types.hpp"

namespace nibl {
  struct Env;
  struct VM;
  
  struct Fun {
    const optional<string> name;
    const optional<Pos> pos;
    const Tag tag;
    const PC pc;

    Fun(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos, PC pc);
  };

  ostream &operator <<(ostream &out, const Fun &f);
}

#endif
