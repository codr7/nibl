#include "nibl/forms/id.hpp"
#include "nibl/vm.hpp"

namespace nibl::forms {
  Id::Imp::Imp(string &&name): name(move(name)) {}

  void Id::Imp::dump(Form &form, ostream &out) const { out << name; }
  
  optional<Error> Id::Imp::emit(VM &vm, Form &form, deque<Form> &args) const {
    auto found = vm.env.find(name);

    if (found) {
      if (*found->type == vm.abc_lib.macro_type) {
	return found->as<Macro *>()->emit(vm, args, form.pos);
      }
      
      return found->emit(vm);
    }
    
    return Error(form.pos, name, '?');
  }

  Id::Id(const Pos &pos, string &&name): Form(pos, make_shared<const Imp>(move(name))) {}
}
