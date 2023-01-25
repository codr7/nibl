#include "nibl/fun.hpp"
#include "nibl/lib.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Fun::Fun(VM &vm, Env &env, const optional<string> &name, const optional<Pos> &pos, PC pc):
    name(name),
    pos(pos),
    tag(vm.tag(vm.abc_lib.fun_type, this)),
    pc(pc) {
    if (name) { env.bind(*name, vm.abc_lib.fun_type, this); }
  }

  ostream &operator <<(ostream &out, const Fun &f) {
    if (f.name) {
      out << *f.name;
    } else if (f.pos) {
      out << "Fun(" << *f.pos << ')';
    }
    
    return out;
  }
}
