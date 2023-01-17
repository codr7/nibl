#ifndef NIBL_VM_HPP
#define NIBL_VM_HPP

#include <map>
#include <optional>
#include <vector>

#include "nibl/env.hpp"
#include "nibl/error.hpp"
#include "nibl/libs/abc.hpp"
#include "nibl/op.hpp"
#include "nibl/read.hpp"
#include "nibl/val.hpp"

namespace nibl {
  const unsigned int VERSION = 3;
    
  struct VM {
    vector<Val> tags;
    libs::ABC abc_lib;
    Env env;
    
    vector<Op> ops;
    PC pc = 0;

    vector<Val> stack;

    bool trace = false;

    VM();
    size_t tag(Type &type, any &&data);
    optional<Error> import(const Env &source, initializer_list<string> names, const Pos &pos);
    Read read(istream &in, Pos &pos);
    Op *emit_no_trace(unsigned int n = 1);
    Op *emit(unsigned int n = 1);
    void eval(PC start_pc, ostream &stdout);
    void push(Type &type, any &&data);
    void dump_stack(ostream &out) const;
  };

  inline void VM::push(Type &type, any &&data) { stack.emplace_back(type, move(data)); }
}

#endif
