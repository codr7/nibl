#include <sstream>

#include "nibl/pos.hpp"
#include "nibl/repl.hpp"
#include "nibl/utils.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  REPL::REPL(VM &vm, istream &stdin, ostream &stdout): vm(vm), stdin(stdin), stdout(stdout) {}

  void REPL::run() {
    stringstream buf;
    
    for (;;) {
      stdout << "  ";
      
      string line;
      if (!getline(stdin, line)) { break; }
      
      if (line.empty()) {
	Pos pos("repl", 1, 1);
	deque<Form> forms;
	
	for (;;) {
	  auto [f, e] = vm.read(buf, pos);

	  if (e) {
	    stdout << *e << endl;
	    break;
	  }

	  if (!f) { break; }
	  forms.push_back(*f);
	}

	buf.str("");
	buf.clear();
	const PC pc = vm.pc;

	while (!forms.empty()) {
	  Form f = pop_front(forms);

	  if (auto e = f.emit(vm, forms); e) {
	    stdout << *e << endl;
	    goto END;
	  }
	}

	vm.ops[vm.emit()] = ops::stop();	
	vm.eval(pc, stdout);
      END:
	stdout << vm.stack << endl;
      } else {
	buf << line << endl;
      }
    }
  }
}

