#ifndef NIBL_VM_HPP
#define NIBL_VM_HPP

#include <filesystem>
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
  namespace fs = std::filesystem;

  const unsigned int VERSION = 9;
    
  struct VM {
    bool trace = false;
    fs::path path;
    istream &stdin;
    ostream &stdout;
    Env root_env;
    vector<Val> tags;
    libs::ABC abc_lib;
    
    vector<Op> ops;
    PC pc = 0;

    Stack stack;
    vector<Call> calls;

    VM(const optional<Pos> &pos);
    Tag tag(Type &type, any &&data);
    Read read(istream &in, Pos &pos);
    E read(istream &in, Forms &out, Pos &pos);
    PC emit_no_trace(unsigned int n = 1);
    PC emit(unsigned int n = 1);
    E emit(Forms &forms);
    E eval(PC start_pc);
    void push(Type &type, any &&data);
    Val pop();
    void call(const Fun &fun);
    E load(fs::path filename, Pos &pos);
  };

  inline void VM::push(Type &type, any &&data) { stack.emplace_back(type, move(data)); }

  inline Val VM::pop() { return pop_back(stack); }

  inline void VM::call(const Fun &fun) {
    calls.emplace_back(fun, pc);
    pc = fun.pc;
  }
}

#endif
