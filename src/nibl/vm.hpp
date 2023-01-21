#ifndef NIBL_VM_HPP
#define NIBL_VM_HPP

#include <map>
#include <optional>
#include <vector>

#include "nibl/error.hpp"
#include "nibl/libs/abc.hpp"
#include "nibl/op.hpp"
#include "nibl/read.hpp"
#include "nibl/stack.hpp"

namespace nibl {
  const unsigned int VERSION = 6;
  
  struct VM {
    Env root_env;
    vector<Val> tags;

    libs::ABC abc_lib;
    
    vector<Op> ops;
    PC pc = 0;

    Stack stack;

    bool trace = false;

    VM();
    size_t tag(Type &type, any &&data);
    Read read(istream &in, Pos &pos);
    PC emit_no_trace(unsigned int n = 1);
    PC emit(unsigned int n = 1);
    void eval(PC start_pc, ostream &stdout);
    void push(Type &type, any &&data);
  };

  inline void VM::push(Type &type, any &&data) { stack.emplace_back(type, move(data)); }
}

#endif
