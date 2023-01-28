#include "nibl/forms/lit.hpp"
#include "nibl/forms/ref.hpp"
#include "nibl/vm.hpp"

namespace nibl::forms {
  Ref::Imp::Imp(const Pos &pos, string &&name): Form::Imp(pos), name(move(name)) {}

  void Ref::Imp::dump(ostream &out) const { out << '&' << name; }
  
  E Ref::Imp::emit(VM &vm, Env &env, deque<Form> &args) const {
    auto found = env.find(name);

    if (found) {
      args.emplace_front(Lit(pos, *found->type, found->data));
      return nullopt;
    }
    
    return Error(pos, name, '?');
  }

  Ref::Ref(const Pos &pos, string &&name): Form(make_shared<const Imp>(pos, move(name))) {}
}
