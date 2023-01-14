#include "nibl/forms/id.hpp"
#include "nibl/vm.hpp"

namespace nibl::forms {
  Id::Imp::Imp(Pos pos, string &&name): Form::Imp(pos), name(move(name)) {}

  void Id::Imp::dump(ostream &out) const { out << name; }
  
  optional<Error> Id::Imp::emit(VM &vm, deque<Form> &args) const {
    auto found = vm.env.find(name);

    if (found) {
      if (found->type == vm.abc_lib.macro_type) {
	return found->as<Macro *>()->emit(vm, args, pos);
      }
      
      return found->emit(vm);
    }
    
    return Error(pos, name, '?');
  }

  Id::Id(Pos pos, string &&name): Form(make_shared<const Imp>(pos, move(name))) {}
}
