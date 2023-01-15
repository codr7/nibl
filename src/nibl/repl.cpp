#include <sstream>
#include "nibl/pos.hpp"
#include "nibl/repl.hpp"
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
	  Form f = forms.front();
	  forms.pop_front();
	  
	  if (auto e = f.emit(vm, forms); e) {
	    stdout << *e << endl;
	    goto END;
	  }
	}

	*vm.emit() = ops::stop();
	
	if (auto e = vm.eval(pc, stdout); e) {
	  stdout << *e << endl;
	  break;
	}

      END:
	vm.dump_stack(stdout);
	stdout << endl;
      } else {
	buf << line << endl;
      }
    }
  }
}

