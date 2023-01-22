#ifndef NIBL_VM_HPP
#define NIBL_VM_HPP

#include <map>
#include <optional>
#include <vector>

#include "nibl/call.hpp"
#include "nibl/error.hpp"
#include "nibl/fun.hpp"
#include "nibl/libs/abc.hpp"
#include "nibl/op.hpp"
#include "nibl/read.hpp"
#include "nibl/stack.hpp"

namespace nibl {
  const unsigned int VERSION = 7;
  
  struct VM {
    Env root_env;
    vector<Val> tags;

    libs::ABC abc_lib;
    
    vector<Op> ops;
    PC pc = 0;

    Stack stack;
    vector<Call> calls;
    bool trace = false;

    VM();
    Tag tag(Type &type, any &&data);
    Read read(istream &in, Pos &pos);
    PC emit_no_trace(unsigned int n = 1);
    PC emit(unsigned int n = 1);
    void eval(PC start_pc, ostream &stdout);
    void push(Type &type, any &&data);
    void call(const Fun &fun);
  };

  inline void VM::push(Type &type, any &&data) { stack.emplace_back(type, move(data)); }

  inline void VM::call(const Fun &fun) {
    calls.emplace_back(fun, pc);
    pc = fun.pc;
  }
}

#endif
