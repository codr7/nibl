#include "nibl/macro.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Macro::Macro(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos, Body body):
    name(name),
    pos(pos),
    tag(vm.tag(vm.abc_lib.macro_type, this)),
    body(body) {
    if (name) { env.bind(*name, vm.abc_lib.macro_type, this); }
  }

  Macro::Macro(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos, Op op):
    Macro(vm, env, name, pos, [op](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) {
      vm.ops[vm.emit()] = op;
      return nullopt;
    }) {}

  E Macro::emit(VM &vm, Env &env, deque<Form> &args, const Pos &pos) {
    return body(vm, env, *this, args, pos);
  }

  ostream &operator <<(ostream &out, const Macro &m) {
    if (m.name) {
      out << *m.name;
    } else if (m.pos) {
      out << "Macro(" << *m.pos << ')';
    }
    
    return out;
  }
}
