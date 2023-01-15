#include "nibl/macro.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Macro::Macro(Lib &lib, string &&name, Body body):
    name(move(name)), body(body) {
    lib.bind(this->name, lib.vm.abc_lib.macro_type, this);  
  }

  optional<Error> Macro::emit(VM &vm, deque<Form> &args, Pos pos) {
    return body(vm, *this, args, pos);
  }

  ostream &operator <<(ostream &out, const Macro &m) {
    out << m.name;
    return out;
  }
}
