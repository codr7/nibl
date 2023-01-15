#include "nibl/op.hpp"

namespace nibl {
  void op_trace(PC pc, Op op, ostream &out) {
    out << pc << ' ';
    
    switch (op_code(op)) {
    case OpCode::DUP:
      out << "DUP";
      break;
    case OpCode::POP:
      out << "POP";
      break;
    case OpCode::PUSH_INT1:
      out << "PUSH_INT1 " << ops::push_int1_value(op);
      break;
    case OpCode::SWAP:
      out << "SWAP";
      break;
    case OpCode::TRACE:
      out << "TRACE";
      break;

    case OpCode::STOP:
      out << "STOP";
      break;
    }
    
    out << endl;
  }
}

namespace nibl::ops {
  Op dup() {
    return static_cast<Op>(OpCode::DUP);
  }

  Op pop() {
    return static_cast<Op>(OpCode::POP);
  }

  Op push_int1(types::Int value) {
    return
      static_cast<Op>(OpCode::PUSH_INT1) +
      static_cast<Op>(value << PUSH_INT1_VALUE_POS);
  }

  types::Int push_int1_value(Op op) {
    return get<types::Int, PUSH_INT1_VALUE_POS, PUSH_INT1_VALUE_WIDTH>(op);
  }

  Op swap() {
    return static_cast<Op>(OpCode::SWAP);
  }

  Op trace() {
    return static_cast<Op>(OpCode::TRACE);
  }

  Op stop() {
    return static_cast<Op>(OpCode::STOP);
  }
}
