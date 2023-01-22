#include "nibl/macro.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Macro::Macro(VM &vm, Env &env, const optional<string> &name, Body body):
    name(name),
    tag(vm.tag(vm.abc_lib.macro_type, this)),
    body(body) {
    if (name) { env.bind(*name, vm.abc_lib.macro_type, this); }
  }

  E Macro::emit(VM &vm, Env &env, deque<Form> &args, const Pos &pos) {
    return body(vm, env, *this, args, pos);
  }

  ostream &operator <<(ostream &out, const Macro &m) {
    out << "Macro(";
    if (m.name) { out << *m.name; }
    out << ')';
    return out;
  }
}
