#include <iostream>

#include "nibl/forms/interp.hpp"
#include "nibl/op.hpp"
#include "nibl/vm.hpp"

namespace nibl::forms {
  Interp::Imp::Imp(const Pos &pos, Str &&spec): Form::Imp(pos), spec(move(spec)) {}

  void Interp::Imp::dump(ostream &out) const { out << spec; }
  
  E Interp::Imp::emit(VM &vm, Env &env, deque<Form> &args) const {
    vm.ops[vm.emit()] = ops::str();
    size_t i = 0, j;
    
    for (;;) {
      j = spec.find('%', i);
      bool esc = false;

      if (j > 0 && spec[j-1] == '\\') {
	j--;
	esc = true;
      }

      const size_t n = (j == string::npos) ? spec.size()-i : j-i;
      
      if (n > 1) {
	Tag t = vm.tag(vm.abc_lib.str_type, spec.substr(i, n));
	vm.ops[vm.emit()] = ops::push_tag(t);
	vm.ops[vm.emit()] = ops::write();
      }

      if (j == string::npos) { break; }

      if (esc) {
	i = j+2;
	vm.ops[vm.emit()] = ops::push_char('%');
	vm.ops[vm.emit()] = ops::write();
	continue;
      }
      
      if (j < spec.size()-1 && spec[j+1] == '{') {
	j += 2;
	
	Forms fs;
	istringstream in(spec.substr(j));
	Pos p = pos;
	p.column += j;
	
	for (;;) {
	  const char c = in.peek();
	  if (c == '}') { break; }
	  if (c == '"') { return Error(p, "Invalid interpolation"); }
	  auto [f, e] = vm.read(in, p);
	  if (e) { return e; }
	  if (!f) { return Error(p, "Invalid interpolation"); }
	  if (auto e = f->emit(vm, env, args); e) { return e; }
	}
	
	vm.ops[vm.emit()] = ops::write();
	j += in.tellg();
      } else {
	vm.ops[vm.emit()] = ops::write();
      }

      i = j+1;
    }
    
    vm.ops[vm.emit()] = ops::stop();
    return nullopt;
  }

  Interp::Interp(const Pos &pos, Str &&spec): Form(make_shared<const Imp>(pos, move(spec))) {}
}
