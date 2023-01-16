#include "nibl/form.hpp"

namespace nibl {
  Form::Imp::~Imp() {}

  Form::Form(const Pos &pos, shared_ptr<const Imp> imp): pos(pos), imp(imp) {}

  void Form::dump(ostream& out) { imp->dump(*this, out); }

  optional<Error> Form::emit(VM &vm, deque<Form> &args) { return imp->emit(vm, *this, args); }

  ostream &operator<<(ostream &out, Form f) {
    f.dump(out);
    return out;
  }
}
