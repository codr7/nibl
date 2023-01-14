#include "nibl/form.hpp"

namespace nibl {
  Form::Imp::Imp(Pos pos): pos(pos) {}
  
  Form::Imp::~Imp() {}

  Form::Form(shared_ptr<const Imp> imp): imp(imp) {}

  void Form::dump(ostream& out) const { imp->dump(out); }

  optional<Error> Form::emit(VM &vm, deque<Form> &args) const { return imp->emit(vm, args); }

  ostream &operator<<(ostream &out, Form f) {
    f.dump(out);
    return out;
  }
}
