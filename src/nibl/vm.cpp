#include <locale>
#include "nibl/vm.hpp"

namespace nibl {
  VM::VM(const optional<Pos> &pos): abc_lib(*this, root_env, pos) {}

  Tag VM::tag(Type &type, any &&data) {
    const Tag t = tags.size();
    tags.emplace_back(type, move(data));
    return t;
  }

  Read VM::read(istream &in, Pos &pos) {
  START:
    char c = 0;
    if (!in.get(c)) { return Read(nullopt, nullopt); }

    switch (c) {
    case 10:
      pos.line++;
      goto START;
    case 32:
      pos.column++;
      goto START;
    case '"': {
      pos.column++;
      return read_str(*this, in, pos);
    }
    case ';': {
      pos.column++;
      return Read(Form(Form::END), nullopt);
    }
    }

    in.unget();
    if (isdigit(c)) { return read_int(*this, in, pos, 10); }
    if (isgraph(c)) { return read_id(*this, in, pos); }
    return Read(nullopt, Error(pos, c, '?'));
  }

  PC VM::emit_no_trace(unsigned int n) {
    const PC i = ops.size();
    pc = i + n;
    ops.resize(pc);
    return i;
  }

  PC VM::emit(unsigned int n) {
    if (trace) { ops[emit_no_trace()] = ops::trace(); }
    return emit_no_trace(n);
  }
}
