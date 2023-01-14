#include <iostream>

#include "nibl/vm.hpp"
#include "nibl/repl.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Nibl v" << nibl::VERSION << endl << endl;
  nibl::VM vm;
  nibl::Pos pos("init", 1, 1);

  if (auto e = vm.import(vm.abc_lib, {}, pos); e) {
    cout << *e << endl;
    return -1;
  }
  
  nibl::REPL repl(vm, cin, cout);
  repl.run();
  return 0;
}
