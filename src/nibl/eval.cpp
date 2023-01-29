#include "nibl/eval.hpp"

#define DISPATCH()						\
  goto *dispatch[static_cast<uint8_t>(op_code(op = ops[pc++]))]	\

namespace nibl {
  using namespace std;
  
  E VM::eval(PC &pc) {
    static const void* dispatch[] = {
      &&ADD, &&AND, &&BENCH, &&CALL, &&DEC, &&DIV, &&DUP, &&EQ, &&GT, &&GOTO, &&IF, &&LT, &&MOD, &&MUL, &&NOT,
      &&OR, &&POP, &&PRIM_CALL, &&PUSH_BOOL, &&PUSH_INT, &&PUSH_TAG, &&REC, &&RET, &&ROTL, &&ROTR, &&SUB,
      &&SWAP, &&TEST, &&TRACE,
      
      &&STOP};
    
    Op op;
    DISPATCH();
  ADD:
    eval_add(*this, pc, op);
    DISPATCH();
  AND:
    eval_and(*this, pc, op);
    DISPATCH();
  BENCH:
    eval_bench(*this, pc, op);
    DISPATCH();
  CALL:
    eval_call(*this, pc, op);
    DISPATCH();
  DEC:
    eval_dec(*this, pc, op);
    DISPATCH();
  DIV:
    eval_div(*this, pc, op);
    DISPATCH();
  DUP:
    eval_dup(*this, pc, op);
    DISPATCH();
  EQ:
    eval_eq(*this, pc, op);
    DISPATCH();
  GT:
    eval_gt(*this, pc, op);
    DISPATCH();
  GOTO:
    eval_goto(*this, pc, op);
    DISPATCH();
  IF:
    eval_if(*this, pc, op);
    DISPATCH();
  LT:
    eval_lt(*this, pc, op);
    DISPATCH();
  MOD:
    eval_mod(*this, pc, op);
    DISPATCH();
  MUL:
    eval_mul(*this, pc, op);
    DISPATCH();
  NOT:
    eval_not(*this, pc, op);
    DISPATCH();
  OR:
    eval_or(*this, pc, op);
    DISPATCH();
  POP:
    eval_pop(*this, pc, op);
    DISPATCH();
  PRIM_CALL:
    eval_prim_call(*this, pc, op);
    DISPATCH();
  PUSH_BOOL:
    eval_push_bool(*this, pc, op);
    DISPATCH();
  PUSH_INT:
    eval_push_int(*this, pc, op);
    DISPATCH();
  PUSH_TAG:
    eval_push_tag(*this, pc, op);
    DISPATCH();
  REC:
    eval_rec(*this, pc, op);
    DISPATCH();
  RET:
    eval_ret(*this, pc, op);
    DISPATCH();
  ROTL:
    eval_rotl(*this, pc, op);
    DISPATCH();
  ROTR:
    eval_rotr(*this, pc, op);
    DISPATCH();
  SUB:
    eval_sub(*this, pc, op);
    DISPATCH();
  SWAP:
    eval_swap(*this, pc, op);
    DISPATCH();
  TEST:
    eval_test(*this, pc, op);
    DISPATCH();
  TRACE:
    eval_trace(*this, pc, op);
    DISPATCH();
  STOP:
    if (errors.empty()) { return nullopt; }
    return pop_front(errors);
  }
}
