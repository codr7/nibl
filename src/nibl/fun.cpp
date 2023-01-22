#include "nibl/fun.hpp"
#include "nibl/lib.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Fun::Fun(VM &vm, Env &env, const optional<string> &name, PC pc):
    name(name),
    tag(vm.tag(vm.abc_lib.fun_type, this)),
    pc(pc) {
    if (name) { env.bind(*name, vm.abc_lib.fun_type, this); }
  }

  ostream &operator <<(ostream &out, const Fun &f) {
    out << "Fun(";
    if (f.name) {out << *f.name; }
    out << ')';
    return out;
  }
}
