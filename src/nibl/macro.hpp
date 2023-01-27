#ifndef NIBL_MACRO_HPP
#define NIBL_MACRO_HPP

#include <deque>
#include <functional>

#include "nibl/error.hpp"
#include "nibl/op.hpp"
#include "nibl/types.hpp"

namespace nibl {
  struct Env;
  struct Form;
  struct VM;

  struct Macro {
    using Body = function<E (VM &vm, Env &env, Macro &macro, deque<Form> &args, const Pos &pos)>;
    
    Macro(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos, Body body);
    Macro(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos, Op op);
    E emit(VM &vm, Env &env, deque<Form> &args, const Pos &pos);
    
    const optional<string> name;
    const optional<Pos> pos;
    const Tag tag;
    const Body body;
  };

  ostream &operator <<(ostream &out, const Macro &m);
}

#endif
