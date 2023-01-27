#include "nibl/eval.hpp"

#define DISPATCH()						\
  goto *dispatch[static_cast<uint8_t>(op_code(op = ops[pc++]))]	\

namespace nibl {
  using namespace std;
  
  E VM::eval(PC start_pc) {
    static const void* dispatch[] = {
      &&ADD, &&AND, &&CALL, &&DIV, &&DUP, &&EQ, &&GT, &&GOTO, &&IF, &&LT, &&MOD, &&MUL, &&NOT, &&OR, &&POP,
      &&PRIM_CALL, &&PUSH_BOOL, &&PUSH_INT, &&PUSH_TAG, &&REC, &&RET, &&SUB, &&SWAP, &&TEST, &&TRACE,
      &&TYPE_OF,
      
      &&STOP};
    
    Op op;
    pc = start_pc;
    DISPATCH();
  ADD:
    eval_add(*this);
    DISPATCH();
  AND:
    eval_and(*this, ops::and_next_pc(op));
    DISPATCH();
  CALL:
    eval_call(*this);
    DISPATCH();
  DIV:
    eval_div(*this);
    DISPATCH();
  DUP:
    eval_dup(*this);
    DISPATCH();
  EQ:
    eval_eq(*this);
    DISPATCH();
  GT:
    eval_gt(*this);
    DISPATCH();
  GOTO:
    eval_goto(*this, ops::goto_pc(op));
    DISPATCH();
  IF:
    eval_if(*this, ops::if_next_pc(op));
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
    eval_or(*this, ops::or_next_pc(op));
    DISPATCH();
  POP:
    eval_pop(*this);
    DISPATCH();
  PRIM_CALL:
    if (auto e = eval_prim_call(*this, ops::prim_call_tag(op)); e) { return e; }
    DISPATCH();
  PUSH_BOOL:
    eval_push_bool(*this, ops::push_bool_value(op));
    DISPATCH();
  PUSH_INT:
    eval_push_int(*this, ops::push_int_value(op));
    DISPATCH();
  PUSH_TAG:
    eval_push_tag(*this, ops::push_tag_value(op));
    DISPATCH();
  REC:
    eval_rec(*this);
    DISPATCH();
  RET:
    eval_ret(*this);
    DISPATCH();
  SUB:
    eval_sub(*this);
    DISPATCH();
  SWAP:
    eval_swap(*this);
    DISPATCH();
  TEST:
    if (auto e = eval_test(*this); e) { return e; }
    DISPATCH();
  TRACE:
    eval_trace(*this);
    DISPATCH();
  TYPE_OF:
    eval_type_of(*this);
    DISPATCH(); 
  STOP:
    return nullopt;
  }
}
