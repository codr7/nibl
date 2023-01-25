#include <iostream>

#include "nibl/vm.hpp"
#include "nibl/repl.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Nibl v" << nibl::VERSION << endl << endl;
  nibl::Pos pos("init", 1, 1);
  nibl::VM vm(pos);

  if (auto e = vm.root_env.import(vm.abc_lib, {}, pos); e) {
    cout << *e << endl;
    return -1;
  }
  
  nibl::REPL repl(vm, cin, cout);
  repl.run();
  return 0;
}
