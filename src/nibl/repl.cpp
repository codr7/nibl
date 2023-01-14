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
	const PC pc = vm.pc;

	for (;;) {
	  auto [f, e] = vm.read(buf, pos);

	  if (e) {
	    stdout << *e << endl;
	    break;
	  }

	  if (!f) { break; }
	  
	  if (auto e = f->emit(vm); e) {
	    stdout << *e << endl;
	    goto END;
	  }
	}

	buf.str("");
	buf.clear();
	*vm.emit() = ops::stop();
	
	if (auto e = vm.eval(pc); e) {
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

