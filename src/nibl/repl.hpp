#ifndef NIBL_REPL_HPP
#define NIBL_REPL_HPP

#include <istream>
#include <ostream>

namespace nibl {
  using namespace std;

  struct VM;
  
  struct REPL {
    VM &vm;
    istream &stdin;
    ostream &stdout;

    REPL(VM &vm, istream &stdin, ostream &stdout);
    void run();
  };
}

#endif
