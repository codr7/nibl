#include "nibl/type.hpp"
#include "nibl/val.hpp"

namespace nibl {
  Val::Val(const Type &type, any &&data): type(type), data(move(data)) {}

  void Val::dump(ostream &out) const { type.dump(data, out); }

  void Val::emit(VM &vm) const { type.emit(vm, data); }

  ostream &operator <<(ostream &out, const Val &v) {
    v.dump(out);
    return out;
  }
}
