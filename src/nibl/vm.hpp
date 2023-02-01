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

  const unsigned int VERSION = 13;
    
  struct VM {
    bool trace = false;
    fs::path path;
    istream *_stdin;
    ostream *_stdout;
    
    Env root_env;
    vector<Val> tags;
    libs::ABC abc_lib;    
    vector<Op> ops;
    Stack stack;
    vector<Call> calls;
    deque<Error> errors;
    
    VM(const optional<Pos> &pos);
    istream &stdin() { return *_stdin; }
    ostream &stdout() { return *_stdout; }
    Tag tag(Type &type, any &&data);
    Read read(istream &in, Pos &pos);
    E read(istream &in, Forms &out, Pos &pos);
    PC emit_pc() const;
    PC emit_no_trace(unsigned int n = 1);
    PC emit(unsigned int n = 1);
    E emit(Forms &forms);
    E eval(PC &pc);
    void push(Type &type, any &&data);
    Val pop();
    void call(Fun &fun, PC &pc);
    E load(fs::path filename, Pos &pos, bool eval);
  };

  inline void VM::push(Type &type, any &&data) { stack.emplace_back(type, move(data)); }

  inline Val VM::pop() { return pop_back(stack); }

  inline void VM::call(Fun &fun, PC &pc) {
    calls.emplace_back(fun, pc);
    pc = fun.pc;
  }
}

#endif
