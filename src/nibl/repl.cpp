#include <sstream>

#include "nibl/pos.hpp"
#include "nibl/repl.hpp"
#include "nibl/utils.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  void repl(VM &vm) {
    stringstream buf;
    
    for (;;) {
      vm.stdout << "  ";
      
      string line;
      if (!getline(vm.stdin, line)) { break; }
      
      if (line.empty()) {
	Pos pos("repl", 1, 1);
	Forms fs;
	PC pc = vm.emit_pc();

	if (auto e = vm.read(buf, fs, pos); e) {
	  vm.stdout << *e << endl;
	  goto END;
	}

	buf.str("");
	buf.clear();

	if (auto e = vm.emit(fs); e) {
	    vm.stdout << *e << endl;
	    goto END;
	}

	vm.ops[vm.emit()] = ops::stop();	
	if (auto e = vm.eval(pc); e) { vm.stdout << *e << endl; }
      END:
	vm.stdout << vm.stack << endl;
      } else {
	buf << line << endl;
      }
    }
  }
}

