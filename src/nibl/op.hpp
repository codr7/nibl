#ifndef NIBL_OP_HPP
#define NIBL_OP_HPP

#include <cstdint>
#include <cstddef>
#include <ostream>

#include "nibl/types.hpp"

namespace nibl {
  using namespace std;

  using PC = size_t;
  using Op = uint64_t;

  const size_t OP_WIDTH = 64;
  const size_t OP_CODE_WIDTH = 6;

  enum class OpCode { ADD, DIV, DUP, MOD, MUL, POP, PUSH_INT1, SUB, SWAP, TRACE,
    STOP };

  inline OpCode op_code(Op op) {
    return static_cast<OpCode>(op & ((1 << OP_CODE_WIDTH) - 1));
  }

  void op_trace(PC pc, Op op, ostream &out);

  namespace ops {
    const size_t PUSH_INT1_VALUE_POS = OP_CODE_WIDTH;
    const size_t PUSH_INT1_VALUE_WIDTH = OP_WIDTH - PUSH_INT1_VALUE_POS;

    template <typename T, size_t pos, size_t width>
    T get(Op op) { return static_cast<T>((op >> pos) & ((static_cast<T>(1) << width) - 1)); }
    
    Op add();
    Op div();
    Op dup();
    Op mod();
    Op mul();
    Op pop();

    Op push_int1(types::Int value);
    types::Int push_int1_value(Op op);
    
    Op sub();
    Op swap();
    Op trace();
    
    Op stop();
  }
}

#endif
