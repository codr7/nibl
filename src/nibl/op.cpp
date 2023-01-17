#include "nibl/op.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  void op_trace(const VM &vm, PC pc, Op op, ostream &out) {
    out << pc << ' ';
    
    switch (op_code(op)) {
    case OpCode::ADD:
      out << "ADD";
      break;
    case OpCode::AND:
      out << "AND" << ops::and_next(op);
      break;
    case OpCode::DIV:
      out << "DIV";
      break;
    case OpCode::DUP:
      out << "DUP";
      break;
    case OpCode::EQ:
      out << "EQ";
      break;
    case OpCode::GT:
      out << "GT";
      break;
    case OpCode::IF:
      out << "IF " << ops::if_next(op);
      break;
    case OpCode::LT:
      out << "LT";
      break;
    case OpCode::MOD:
      out << "MOD";
      break;
    case OpCode::MUL:
      out << "MUL";
      break;
    case OpCode::NOT:
      out << "NOT";
      break;
    case OpCode::OR:
      out << "OR" << ops::or_next(op);
      break;
    case OpCode::POP:
      out << "POP";
      break;
    case OpCode::PUSH_BOOL:
      out << "PUSH_BOOL " << (ops::push_bool_value(op) ? 'T' : 'F');
      break;
    case OpCode::PUSH_INT1:
      out << "PUSH_INT1 " << ops::push_int1_value(op);
      break;
    case OpCode::PUSH_TAG:
      out << "PUSH_TAG " << ops::push_tag_value(op) << ' ' << vm.tags[ops::push_tag_value(op)];
      break;
    case OpCode::SUB:
      out << "SUB";
      break;
    case OpCode::SWAP:
      out << "SWAP";
      break;
    case OpCode::TRACE:
      out << "TRACE";
      break;
    case OpCode::TYPE_OF:
      out << "TYPEOF";
      break;

    case OpCode::STOP:
      out << "STOP";
      break;
    }
    
    out << endl;
  }
}

namespace nibl::ops {
  Op add() { return static_cast<Op>(OpCode::ADD); }
  
  Op _and(PC next) {
    return
      static_cast<Op>(OpCode::AND) +
      static_cast<Op>(next << AND_NEXT_POS);
  }

  Op div() { return static_cast<Op>(OpCode::DIV); }
  Op dup() { return static_cast<Op>(OpCode::DUP); }
  Op eq() { return static_cast<Op>(OpCode::EQ); }
  Op gt() { return static_cast<Op>(OpCode::GT); }

  Op _if(PC next) {
    return
      static_cast<Op>(OpCode::IF) +
      static_cast<Op>(next << IF_NEXT_POS);
  }

  Op lt() { return static_cast<Op>(OpCode::LT); }
  Op mod() { return static_cast<Op>(OpCode::MOD); }
  Op mul() { return static_cast<Op>(OpCode::MUL); }
  Op _not() { return static_cast<Op>(OpCode::NOT); }

  Op _or(PC next) {
    return
      static_cast<Op>(OpCode::OR) +
      static_cast<Op>(next << OR_NEXT_POS);
  }

  Op pop() { return static_cast<Op>(OpCode::POP); }

  Op push_bool(bool value) {
    return
      static_cast<Op>(OpCode::PUSH_BOOL) +
      static_cast<Op>(value << PUSH_BOOL_VALUE_POS);
  }

  Op push_int1(types::Int value) {
    return
      static_cast<Op>(OpCode::PUSH_INT1) +
      static_cast<Op>(value << PUSH_INT1_VALUE_POS);
  }

  Op push_tag(size_t value) {
    return
      static_cast<Op>(OpCode::PUSH_TAG) +
      static_cast<Op>(value << PUSH_TAG_VALUE_POS);
  }

  Op sub() { return static_cast<Op>(OpCode::SUB); }
  Op swap() { return static_cast<Op>(OpCode::SWAP); }
  Op trace() { return static_cast<Op>(OpCode::TRACE); }
  Op type_of() { return static_cast<Op>(OpCode::TYPE_OF); }
  Op stop() { return static_cast<Op>(OpCode::STOP); }
}
