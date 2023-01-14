#include <iostream>

#include "nibl/vm.hpp"
#include "nibl/repl.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Nibl v" << nibl::VERSION << endl << endl;
  nibl::VM vm;
  nibl::REPL repl(vm, cin, cout);
  repl.run();
  return 0;
}
