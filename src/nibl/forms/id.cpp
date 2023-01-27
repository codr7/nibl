#include "nibl/forms/id.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  struct Prim;
}

namespace nibl::forms {  
  Id::Imp::Imp(const Pos &pos, string &&name): Form::Imp(pos), name(move(name)) {}

  void Id::Imp::dump(ostream &out) const { out << name; }
  
  E Id::Imp::emit(VM &vm, Env &env, deque<Form> &args) const {
    auto found = env.find(name);

    if (found) {
      if (*found->type == vm.abc_lib.macro_type) {
	return found->as<Macro *>()->emit(vm, env, args, pos);
      }

      if (*found->type == vm.abc_lib.prim_type) {
	vm.ops[vm.emit()] = ops::prim_call(*found->as<Prim *>());
	return nullopt;
      }

      return found->emit(vm, env);
    }
    
    return Error(pos, name, '?');
  }

  Id::Id(const Pos &pos, string &&name): Form(make_shared<const Imp>(pos, move(name))) {}
}
