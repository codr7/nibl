#ifndef NIBL_LIB_HPP
#define NIBL_LIB_HPP

#include <map>

#include "nibl/env.hpp"
#include "nibl/macro.hpp"
#include "nibl/val.hpp"

namespace nibl {
  struct VM;
  
  struct Lib: Env {
    VM &vm;
    const string name;
    
    Lib(VM &vm, string &&name);
  };
}

#endif
