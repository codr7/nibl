#include "nibl/form.hpp"

namespace nibl {
  Form::Imp::~Imp() {}

  Form::Form(Pos pos, shared_ptr<const Imp> imp): pos(pos), imp(imp) {}

  void Form::dump(ostream& out) const { imp->dump(out); }

  void Form::emit(VM &vm) const { imp->emit(vm); }

  ostream &operator<<(ostream &out, Form f) {
    f.dump(out);
    return out;
  }
}
