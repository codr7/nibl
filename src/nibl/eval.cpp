#include <iostream>

#include "nibl/eval.hpp"

#define DISPATCH()						\
  goto *dispatch[static_cast<uint8_t>(op_code(op = ops[pc++]))] \

namespace nibl {
  using namespace std;
  
  void VM::eval(PC start_pc, ostream &stdout) {
    static const void* dispatch[] = {
      &&ADD, &&AND, &&DIV, &&DUP, &&GT, &&LT, &&MOD, &&MUL, &&NOT, &&OR, &&POP, &&PUSH_BOOL, &&PUSH_INT1,
      &&PUSH_TAG, &&SUB, &&SWAP, &&TRACE, &&TYPE_OF,
      &&STOP};
    Op op;
    pc = start_pc;
    DISPATCH();
  ADD:
    eval_add(*this);
    DISPATCH();
  AND:
    eval_and(*this);
    DISPATCH();
  DIV:
    eval_div(*this);
    DISPATCH();
  DUP:
    stack.emplace_back(stack.back());
    DISPATCH();
  GT:
    eval_gt(*this);
    DISPATCH();
  LT:
    eval_lt(*this);
    DISPATCH();
  MOD:
    eval_mod(*this);
    DISPATCH();
  MUL:
    eval_mul(*this);
    DISPATCH();
  NOT:
    eval_not(*this);
    DISPATCH();
  OR:
    eval_or(*this);
    DISPATCH();
  POP:
    stack.pop_back();
    DISPATCH();
  PUSH_BOOL:
    push(abc_lib.bool_type, ops::push_bool_value(op));
    DISPATCH();
  PUSH_INT1:
    push(abc_lib.int_type, ops::push_int1_value(op));
    DISPATCH();
  PUSH_TAG:
    stack.push_back(tags[ops::push_tag_value(op)]);
    DISPATCH();
  SUB:
    eval_sub(*this);
    DISPATCH();
  SWAP:
    iter_swap(stack.end()-2, stack.end()-1);
    DISPATCH();
  TRACE:
    op_trace(*this, pc, ops[pc+1], stdout);
    DISPATCH();
  TYPE_OF:
    stack.back() = Val(abc_lib.meta_type, stack.back().type);
    DISPATCH();
    
  STOP:
    pc++;
  }
}
