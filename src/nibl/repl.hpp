#ifndef NIBL_REPL_HPP
#define NIBL_REPL_HPP

#include <istream>
#include <ostream>

namespace nibl {
  using namespace std;

  struct VM;
  
  void repl(VM &vm);
}

#endif
