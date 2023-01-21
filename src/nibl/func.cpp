#include "nibl/func.hpp"
#include "nibl/lib.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Func::Func(VM &vm, Env &env, const optional<string> &name, PC pc):
    name(name),
    tag(vm.tag(vm.abc_lib.func_type, this)),
    pc(pc) {
    if (name) { env.bind(*name, vm.abc_lib.func_type, this); }
  }

  ostream &operator <<(ostream &out, const Func &f) {
    out << "Func(";
    if (f.name) {out << *f.name; }
    out << ')';
    return out;
  }
}
