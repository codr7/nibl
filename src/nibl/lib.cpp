#include "nibl/lib.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Lib::Lib(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos):
    name(name),
    pos(pos),
    tag(vm.tag(vm.abc_lib.lib_type, this)) {
    if (name) { env.bind(*name, vm.abc_lib.lib_type, this); }
  }

  ostream &operator <<(ostream &out, const Lib &l) {
    if (l.name) {
      out << *l.name;
    } else if (l.pos) {
      out << "Lib(" << *l.pos << ')';
    }
    
    return out;
  }
}
