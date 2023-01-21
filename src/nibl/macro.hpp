#ifndef NIBL_MACRO_HPP
#define NIBL_MACRO_HPP

#include <deque>
#include <functional>
#include <optional>

#include "nibl/error.hpp"

namespace nibl {
  struct Env;
  struct Form;
  struct Lib;
  struct VM;

  struct Macro {
    using Body = function<optional<Error> (VM &vm, Env &env, Macro &macro, deque<Form> &args, const Pos &pos)>;
    
    Macro(VM &vm, Env &env, const optional<string> &name, Body body);
    optional<Error> emit(VM &vm, Env &env, deque<Form> &args, const Pos &pos);
    
    const optional<string> name;
    const size_t tag;
    const Body body;
  };

  ostream &operator <<(ostream &out, const Macro &m);
}

#endif
