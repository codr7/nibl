#ifndef NIBL_FUNC_HPP
#define NIBL_FUNC_HPP

#include <optional>
#include "op.hpp"

namespace nibl {
  struct Env;
  
  struct Func {
    const optional<string> name;
    const Tag tag;
    const PC pc;

    Func(VM &vm, Env &env, const optional<string> &name, PC pc);
  };

  ostream &operator <<(ostream &out, const Func &f);
}

#endif
