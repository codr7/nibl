#include "nibl/prim.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Prim::Prim(VM &vm, Env &env, const string &name, Body body):
    name(name),
    tag(vm.tag(vm.abc_lib.prim_type, this)),
    body(body) {
    env.bind(name, vm.abc_lib.prim_type, this);
  }

  E Prim::call(VM &vm, PC &pc) { return body(vm, *this, pc); }

  ostream &operator <<(ostream &out, const Prim &p) {
    out << p.name;
    return out;
  }
}
