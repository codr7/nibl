#include <locale>
#include "nibl/vm.hpp"

namespace nibl {
  VM::VM(): abc_lib(*this) {}

  size_t VM::tag(const Type &type, any &&data) {
    const size_t t = tags.size();
    tags.emplace_back(type, move(data));
    return t;
  }

  optional<Error> VM::import(const Env &source, initializer_list<string> names, Pos pos) {
    vector<string> ns(names);

    if (ns.empty()) {
      env.bindings.insert(source.bindings.begin(), source.bindings.end());
    } else {
      for (const string &n: ns) {
	auto v = source.find(n);
	if (!v) { return Error(pos, n, '?'); }
	env.bindings.insert(make_pair(n, *v));
      }
    }

    return nullopt;
  }

  Read VM::read(istream &in, Pos &pos) const {
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
    }

    in.unget();
    if (isdigit(c)) { return read_int(*this, in, pos, 10); }
    if (isgraph(c)) { return read_id(*this, in, pos); }
    return Read(nullopt, Error(pos, c, '?'));
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
