#ifndef NIBL_OP_HPP
#define NIBL_OP_HPP

#include <cstdint>
#include <cstddef>
#include <ostream>

#include "nibl/types.hpp"

namespace nibl {
  using namespace std;

  struct VM;
  
  using PC = size_t;
  using Op = uint64_t;

  const size_t OP_WIDTH = sizeof(Op) * 8;
  const size_t OP_CODE_WIDTH = 6;

  enum class OpCode {
    ADD, AND, DIV, DUP, EQ, GT, IF, LT, MOD, MUL, NOT, OR, POP, PUSH_BOOL, PUSH_INT1, PUSH_TAG, SUB, SWAP,
    TRACE, TYPE_OF,
    
    STOP };

  inline OpCode op_code(Op op) {
    return static_cast<OpCode>(op & ((1 << OP_CODE_WIDTH) - 1));
  }

  void op_trace(const VM &vm, PC pc, Op op, ostream &out);

  namespace ops {
    const size_t AND_NEXT_POS = OP_CODE_WIDTH;
    const size_t AND_NEXT_WIDTH = OP_WIDTH - AND_NEXT_POS;

    const size_t IF_NEXT_POS = OP_CODE_WIDTH;
    const size_t IF_NEXT_WIDTH = OP_WIDTH - IF_NEXT_POS;

    const size_t OR_NEXT_POS = OP_CODE_WIDTH;
    const size_t OR_NEXT_WIDTH = OP_WIDTH - OR_NEXT_POS;

    const size_t PUSH_BOOL_VALUE_POS = OP_CODE_WIDTH;
    const size_t PUSH_BOOL_VALUE_WIDTH = 1;

    const size_t PUSH_INT1_VALUE_POS = OP_CODE_WIDTH;
    const size_t PUSH_INT1_VALUE_WIDTH = OP_WIDTH - PUSH_INT1_VALUE_POS;

    const size_t PUSH_TAG_VALUE_POS = OP_CODE_WIDTH;
    const size_t PUSH_TAG_VALUE_WIDTH = OP_WIDTH - PUSH_TAG_VALUE_POS;

    template <typename T, size_t pos, size_t width>
    T get(Op op) { return static_cast<T>((op >> pos) & ((static_cast<T>(1) << width) - 1)); }
    
    Op add();
    
    Op _and(PC next);
    inline PC and_next(Op op) { return get<PC, AND_NEXT_POS, AND_NEXT_WIDTH>(op); }

    Op div();
    Op dup();
    Op eq();
    Op gt();
    
    Op _if(PC next);
    inline PC if_next(Op op) { return get<PC, IF_NEXT_POS, IF_NEXT_WIDTH>(op); }

    Op lt();
    Op mod();
    Op mul();
    Op _not();
    
    Op _or(PC next);
    inline PC or_next(Op op) { return get<PC, OR_NEXT_POS, OR_NEXT_WIDTH>(op); }

    Op pop();
    
    Op push_bool(bool value);
    inline bool push_bool_value(Op op) { return get<bool, PUSH_BOOL_VALUE_POS, PUSH_BOOL_VALUE_WIDTH>(op); }

    Op push_int1(types::Int value);

    inline types::Int push_int1_value(Op op) {
      return get<types::Int, PUSH_INT1_VALUE_POS, PUSH_INT1_VALUE_WIDTH>(op);
    }

    Op push_tag(size_t value);
    inline size_t push_tag_value(Op op) { return get<size_t, PUSH_TAG_VALUE_POS, PUSH_TAG_VALUE_WIDTH>(op); }

    Op sub();
    Op swap();
    Op trace();
    Op type_of();
    
    Op stop();
  }
}

#endif
