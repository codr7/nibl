#include "nibl/forms/ref.hpp"
#include "nibl/vm.hpp"

namespace nibl::forms {
  Ref::Imp::Imp(string &&name): name(move(name)) {}

  void Ref::Imp::dump(Form &form, ostream &out) const { out << '&' << name; }
  
  optional<Error> Ref::Imp::emit(VM &vm, Form &form, deque<Form> &args) const {
    auto found = vm.env.find(name);
    if (found) { return found->emit(vm); }
    return Error(form.pos, name, '?');
  }

  Ref::Ref(const Pos &pos, string &&name): Form(pos, make_shared<const Imp>(move(name))) {}
}
