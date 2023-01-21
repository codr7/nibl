#include "nibl/lib.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Lib::Lib(VM &vm, Env &env, const optional<string> &name):
    name(name),
    tag(vm.tag(vm.abc_lib.lib_type, this)) {
    if (name) { env.bind(*name, vm.abc_lib.lib_type, this); }
  }

  ostream &operator <<(ostream &out, const Lib &l) {
    out << "Lib(";
    if (l.name) { out << *l.name; }
    out << ')';
    return out;
  }
}
