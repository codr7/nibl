#include "nibl/forms/lit.hpp"

namespace nibl::forms {
  Lit::Imp::Imp(Type &type, any &&data): val(type, move(data)) {}

  void Lit::Imp::dump(Form &form, ostream &out) const { val.dump(out); }
  
  optional<Error> Lit::Imp::emit(VM &vm, Form &form, deque<Form> &args) const { return val.emit(vm); }

  Lit::Lit(const Pos &pos, Type &type, any &&data):
    Form(pos, make_shared<const Imp>(type, move(data))) {}
}
