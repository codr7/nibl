#include "nibl/forms/lit.hpp"

namespace nibl::forms {
  Lit::Imp::Imp(const Pos &pos, Type &type, any &&data): Form::Imp(pos), val(type, move(data)) {}

  void Lit::Imp::dump(ostream &out) const { out << val; }
  
  optional<Error> Lit::Imp::emit(VM &vm, Env &env, deque<Form> &args) const { return val.emit(vm, env); }

  Lit::Lit(const Pos &pos, Type &type, any &&data): Form(make_shared<const Imp>(pos, type, move(data))) {}
}
