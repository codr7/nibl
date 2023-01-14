#include "nibl/forms/lit.hpp"

namespace nibl::forms {
  Lit::Imp::Imp(Pos pos, const Type &type, any &&data): Form::Imp(pos), val(type, move(data)) {}

  void Lit::Imp::dump(ostream &out) const { val.dump(out); }
  
  optional<Error> Lit::Imp::emit(VM &vm, deque<Form> &args) const { return val.emit(vm); }

  Lit::Lit(Pos pos, const Type &type, any &&data): Form(make_shared<const Imp>(pos, type, move(data))) {}
}
