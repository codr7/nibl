#include "nibl/lib.hpp"
#include "nibl/type.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Type::Type(Lib &lib, string &&name):
    name(move(name)),
    tag(lib.vm.tag(lib.vm.abc_lib.meta_type, this)) {
    lib.bind(this->name, lib.vm.abc_lib.meta_type, this);  
  }

  ostream &operator <<(ostream &out, Type &t) {
    out << t.name;
    return out;
  }

  bool operator ==(Type &t1, Type &t2) {
    return &t1 == &t2;
  }
}
