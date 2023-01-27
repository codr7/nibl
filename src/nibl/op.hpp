#ifndef NIBL_OP_HPP
#define NIBL_OP_HPP

#include <cstdint>
#include <cstddef>
#include <ostream>

#include "nibl/types.hpp"

namespace nibl {
  using namespace std;

  struct Prim;
  struct VM;
  
  using Op = uint64_t;

  const size_t OP_WIDTH = sizeof(Op) * 8;
  const size_t OP_CODE_WIDTH = 6;

  enum class OpCode {
    ADD, AND, CALL, DIV, DUP, EQ, GT, GOTO, IF, LT, MOD, MUL, NOT, OR, POP, PRIM_CALL, PUSH_BOOL, PUSH_INT,
    PUSH_TAG, REC, RET, SUB, SWAP, TEST, TRACE, TYPE_OF,
    
    STOP };

  inline OpCode op_code(Op op) { return static_cast<OpCode>(op & ((1 << OP_CODE_WIDTH) - 1)); }
  void op_trace(VM &vm, PC pc, ostream &out);

  namespace ops {
    const size_t AND_NEXT_PC_POS = OP_CODE_WIDTH;
    const size_t AND_NEXT_PC_WIDTH = OP_WIDTH - AND_NEXT_PC_POS;

    const size_t GOTO_PC_POS = OP_CODE_WIDTH;
    const size_t GOTO_PC_WIDTH = OP_WIDTH - GOTO_PC_POS;

    const size_t IF_NEXT_PC_POS = OP_CODE_WIDTH;
    const size_t IF_NEXT_PC_WIDTH = OP_WIDTH - IF_NEXT_PC_POS;

    const size_t OR_NEXT_PC_POS = OP_CODE_WIDTH;
    const size_t OR_NEXT_PC_WIDTH = OP_WIDTH - OR_NEXT_PC_POS;

    const size_t PRIM_CALL_TAG_POS = OP_CODE_WIDTH;
    const size_t PRIM_CALL_TAG_WIDTH = OP_WIDTH - PRIM_CALL_TAG_POS;

    const size_t PUSH_BOOL_VALUE_POS = OP_CODE_WIDTH;
    const size_t PUSH_BOOL_VALUE_WIDTH = 1;

    const size_t PUSH_INT_VALUE_POS = OP_CODE_WIDTH;
    const size_t PUSH_INT_VALUE_WIDTH = OP_WIDTH - PUSH_INT_VALUE_POS;

    const size_t PUSH_TAG_VALUE_POS = OP_CODE_WIDTH;
    const size_t PUSH_TAG_VALUE_WIDTH = OP_WIDTH - PUSH_TAG_VALUE_POS;

    template <typename T, size_t pos, size_t width>
    T get(Op op) { return static_cast<T>((op >> pos) & ((static_cast<T>(1) << width) - 1)); }
    
    Op add();
    
    Op _and(PC next_pc);
    inline PC and_next_pc(Op op) { return get<PC, AND_NEXT_PC_POS, AND_NEXT_PC_WIDTH>(op); }

    Op call();
    Op div();
    Op dup();
    Op eq();
    Op gt();
    
    Op _goto(PC pc);
    inline PC goto_pc(Op op) { return get<PC, GOTO_PC_POS, GOTO_PC_WIDTH>(op); }

    Op _if(PC next_pc);
    inline PC if_next_pc(Op op) { return get<PC, IF_NEXT_PC_POS, IF_NEXT_PC_WIDTH>(op); }

    Op lt();
    Op mod();
    Op mul();
    Op _not();
    
    Op _or(PC next_pc);
    inline PC or_next_pc(Op op) { return get<PC, OR_NEXT_PC_POS, OR_NEXT_PC_WIDTH>(op); }

    Op pop();

    Op prim_call(Prim &prim);
    inline PC prim_call_tag(Op op) { return get<Tag, PRIM_CALL_TAG_POS, PRIM_CALL_TAG_WIDTH>(op); }
    
    Op push_bool(bool value);
    inline bool push_bool_value(Op op) { return get<bool, PUSH_BOOL_VALUE_POS, PUSH_BOOL_VALUE_WIDTH>(op); }

    Op push_int(Int value);

    inline Int push_int_value(Op op) {
      return get<Int, PUSH_INT_VALUE_POS, PUSH_INT_VALUE_WIDTH>(op);
    }

    Op push_tag(Tag value);
    inline size_t push_tag_value(Op op) { return get<Tag, PUSH_TAG_VALUE_POS, PUSH_TAG_VALUE_WIDTH>(op); }

    Op rec();
    Op ret();
    Op sub();
    Op swap();
    Op test();
    Op trace();
    Op type_of();
    
    Op stop();
  }
}

#endif
