#include <locale>
#include "nibl/vm.hpp"

namespace nibl {
  Read VM::read(istream &in, Pos &pos) const {
  START:
    char c = 0;
    if (!in.get(c)) { return Read(nullopt, nullopt); }

    switch (c) {
    case 10:
      pos.line++;
      goto START;
    }

    in.unget();
    if (isdigit(c)) { return read_int(*this, in, pos, 10); }
    if (isalpha(c)) { return read_id(*this, in, pos); }
    return Read(nullopt, Error(pos, c, '?'));
  }

  optional<Val> VM::get_env(const string &name) {
    if (auto found = env.find(name); found != env.end()) { return found->second; }
    return nullopt;
  }

  Op *VM::emit_no_trace(unsigned int n) {
    pc = ops.size();
    ops.resize(ops.size() + n);
    return &ops[pc];
  }

  Op *VM::emit(unsigned int n) {
    if (trace) { *emit_no_trace() = ops::trace(); }
    return emit_no_trace(n);
  }

  void VM::dump_stack(ostream &out) const {
    out << '[';
    int i = 0;
    
    for (const Val &v: stack) {
      if (i++) { out << ' '; }
      v.dump(out);
    }

    out << ']';
  }
}
