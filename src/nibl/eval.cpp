#include <iostream>

#include "nibl/vm.hpp"

#define DISPATCH(next_pc)						\
  goto *dispatch[static_cast<uint8_t>(op_code(op = ops[pc = (next_pc)]))] \

namespace nibl {
  using namespace std;
  
  optional<Error> VM::eval(PC start_pc, ostream &stdout) {
    static const void* dispatch[] = {&&DUP, &&POP, &&PUSH_INT1, &&TRACE,
      &&STOP};
    Op op = 0;
    DISPATCH(start_pc);
  DUP:
    stack.emplace_back(stack.back());
    DISPATCH(pc+1);
  POP:
    stack.pop_back();
    DISPATCH(pc+1);
  PUSH_INT1:
    push(abc_lib.int_type, ops::push_int1_value(op));
    DISPATCH(pc+1);
  TRACE:
    op_trace(pc, ops[pc+1], stdout);
    DISPATCH(pc+1);
    
  STOP:
    pc++;
    return nullopt;
  }
}
