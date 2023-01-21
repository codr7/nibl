#include "nibl/lib.hpp"
#include "nibl/type.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Type::Type(VM &vm, Env &env, const optional<string> &name):
    name(name),
    tag(vm.tag(vm.abc_lib.meta_type, this)) {
    if (name) { env.bind(*name, vm.abc_lib.meta_type, this); }
  }

  ostream &operator <<(ostream &out, Type &t) {
    out << "Type(";
    if (t.name) { out << *t.name; }
    out << ')';
    return out;
  }

  bool operator ==(Type &t1, Type &t2) {
    return &t1 == &t2;
  }
}
