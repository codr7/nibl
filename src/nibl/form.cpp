#include "nibl/form.hpp"

namespace nibl {
  const shared_ptr<const Form::Imp> Form::END(nullptr);

  Form::Imp::Imp(const Pos &pos): pos(pos) {}
  
  Form::Imp::~Imp() {}

  Form::Form(shared_ptr<const Imp> imp): imp(imp) {}

  void Form::dump(ostream& out) { imp->dump(out); }

  optional<Error> Form::emit(VM &vm, deque<Form> &args) { return imp->emit(vm, args); }

  ostream &operator<<(ostream &out, Form f) {
    f.dump(out);
    return out;
  }
}
