#include <iostream>

#include "nibl/eval.hpp"

#define DISPATCH(next_pc)						\
  goto *dispatch[static_cast<uint8_t>(op_code(op = ops[pc = (next_pc)]))] \

namespace nibl {
  using namespace std;
  
  optional<Error> VM::eval(PC start_pc, ostream &stdout) {
    static const void* dispatch[] = {
      &&ADD, &&DIV, &&DUP, &&MOD, &&MUL, &&POP, &&PUSH_INT1, &&PUSH_TAG, &&SUB, &&SWAP, &&TRACE,
      &&STOP};
    Op op = 0;
    DISPATCH(start_pc);
  ADD:
    eval_add(*this);
    DISPATCH(pc+1);
  DIV:
    eval_div(*this);
    DISPATCH(pc+1);
  DUP:
    stack.emplace_back(stack.back());
    DISPATCH(pc+1);
  MOD:
    eval_mod(*this);
    DISPATCH(pc+1);
  MUL:
    eval_mul(*this);
    DISPATCH(pc+1);
  POP:
    stack.pop_back();
    DISPATCH(pc+1);
  PUSH_INT1:
    push(abc_lib.int_type, ops::push_int1_value(op));
    DISPATCH(pc+1);
  PUSH_TAG:
    stack.push_back(tags[ops::push_tag_value(op)]);
    DISPATCH(pc+1);
  SUB:
    eval_sub(*this);
    DISPATCH(pc+1);
  SWAP:
    iter_swap(stack.end()-2, stack.end()-1);
    DISPATCH(pc+1);
  TRACE:
    op_trace(*this, pc, ops[pc+1], stdout);
    DISPATCH(pc+1);
    
  STOP:
    pc++;
    return nullopt;
  }
}
