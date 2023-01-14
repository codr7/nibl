#include "nibl/forms/lit.hpp"

namespace nibl::forms {
  Lit::Imp::Imp(const Type &type, any &&data): val(type, move(data)) {}

  void Lit::Imp::dump(ostream &out) const { val.dump(out); }
  
  void Lit::Imp::emit(VM &vm) const { val.emit(vm); }

  Lit::Lit(Pos pos, const Type &type, any &&data): Form(pos, make_shared<const Imp>(type, move(data))) {}
}
