#include <fstream>
#include <iostream>
#include <locale>
#include "nibl/vm.hpp"

namespace nibl {
  VM::VM(const optional<Pos> &pos): stdin(cin), stdout(cout), abc_lib(*this, root_env, pos) {}

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

  E VM::read(istream &in, Forms &out, Pos &pos) {
    	for (;;) {
	  auto [f, e] = read(in, pos);
	  if (e) { return e; }
	  if (!f) { break; }
	  out.push_back(*f);
	}

	return nullopt;
  }

  PC VM::emit_pc() const { return ops.size(); }

  PC VM::emit_no_trace(unsigned int n) {
    const PC pc = ops.size();
    ops.resize(pc + n);
    return pc;
  }

  PC VM::emit(unsigned int n) {
    if (trace) { ops[emit_no_trace()] = ops::trace(); }
    return emit_no_trace(n);
  }

  E VM::emit(Forms &forms) {
    while (!forms.empty()) {
      Form f = pop_front(forms);
      if (auto e = f.emit(*this, root_env, forms); e) { return e; }
    }

    return nullopt;
  }
  
  E VM::load(fs::path filename, Pos &pos) {
    auto p(filename.is_absolute() ? filename : path/filename);
    ifstream in(p);
    if (in.fail()) { return Error(pos, p, '?'); }

    Forms fs;
    if (auto e = read(in, fs, pos); e) { return e; }

    PC pc = emit_pc();
    if (auto e = emit(fs); e) { return e; }
    ops[emit()] = ops::stop();	
    
    auto pp(path);
    path = p.parent_path();
    auto e = eval(pc);
    path = pp;
    return e;
  }
}
