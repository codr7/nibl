#include "nibl/type.hpp"
#include "nibl/val.hpp"

namespace nibl {
  Val::Val(Type &type, any &&data): type(&type), data(move(data)) {}

  E Val::emit(VM &vm, Env &env) const { return type->emit(vm, env, *this); }

  ostream &operator <<(ostream &out, const Val &v) {
    v.type->dump(v, out);
    return out;
  }

  bool operator ==(const Val &v1, const Val &v2) {
    return v1.type == v2.type && v1.type->eq(v1, v2);
  }
}
