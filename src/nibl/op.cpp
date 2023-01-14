#include "nibl/op.hpp"

namespace nibl {
  void op_trace(Op op, ostream &out) {
    out << "TRACE " << op << endl;
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
  
  Op trace() {
    return static_cast<Op>(OpCode::POP);
  }

  Op stop() {
    return static_cast<Op>(OpCode::STOP);
  }
}
