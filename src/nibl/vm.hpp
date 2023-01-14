#ifndef NIBL_VM_HPP
#define NIBL_VM_HPP

#include <map>
#include <optional>
#include <vector>

#include "nibl/error.hpp"
#include "nibl/libs/abc.hpp"
#include "nibl/op.hpp"
#include "nibl/read.hpp"
#include "nibl/val.hpp"

namespace nibl {
  const unsigned int VERSION = 1;
  
  using PC = size_t;
  
  struct VM {
    libs::ABC abc_lib;
    map<string, Val> env;
    
    vector<Op> ops;
    PC pc = 0;

    vector<Val> stack;

    bool trace = false;

    Read read(istream &in, Pos &pos) const;
    optional<Val> get_env(const string &name);
    Op *emit_no_trace(unsigned int n = 1);
    Op *emit(unsigned int n = 1);
    optional<Error> eval(PC start_pc);
    void push(const Type &type, any &&data);
    void dump_stack(ostream &out) const;
  };

  inline void VM::push(const Type &type, any &&data) { stack.emplace_back(type, move(data)); }
}

#endif
