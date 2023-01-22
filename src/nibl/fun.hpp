#ifndef NIBL_FUN_HPP
#define NIBL_FUN_HPP

#include <optional>
#include "op.hpp"

namespace nibl {
  struct Env;
  
  struct Fun {
    const optional<string> name;
    const Tag tag;
    const PC pc;

    Fun(VM &vm, Env &env, const optional<string> &name, PC pc);
  };

  ostream &operator <<(ostream &out, const Fun &f);
}

#endif
