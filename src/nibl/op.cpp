#include "nibl/op.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  void op_trace(VM &vm, PC pc, ostream &out) {
    out << pc << ' ';
    const Op op = vm.ops[pc];
    
    switch (op_code(op)) {
    case OpCode::ADD:
      out << "ADD";
      break;
    case OpCode::AND:
      out << "AND" << ops::and_next_pc(op);
      break;
    case OpCode::CALL:
      out << "CALL";
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
      out << "IF " << ops::if_next_pc(op);
      break;
    case OpCode::GOTO:
      out << "GOTO " << ops::goto_pc(op);
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
      out << "OR" << ops::or_next_pc(op);
      break;
    case OpCode::POP:
      out << "POP";
      break;
    case OpCode::PRIM_CALL: {
      Tag t(ops::prim_call_tag(op));
      out << "PRIM_CALL " << t << ' ' << *vm.tags[t].as<Prim *>();
      break;
    }
    case OpCode::PUSH_BOOL:
      out << "PUSH_BOOL " << (ops::push_bool_value(op) ? 'T' : 'F');
      break;
    case OpCode::PUSH_INT:
      out << "PUSH_INT " << ops::push_int_value(op);
      break;
    case OpCode::PUSH_TAG: {
      Tag t(ops::push_tag_value(op));
      out << "PUSH_TAG " << t << ' ' << vm.tags[t];
      break;
    }
    case OpCode::REC:
      out << "REC";
      break;
    case OpCode::RET:
      out << "RET";
      break;
    case OpCode::SUB:
      out << "SUB";
      break;
    case OpCode::SWAP:
      out << "SWAP";
      break;
    case OpCode::TEST:
      out << "TEST";
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
  
  Op _and(PC next_pc) {
    return
      static_cast<Op>(OpCode::AND) +
      static_cast<Op>(next_pc << AND_NEXT_PC_POS);
  }

  Op call() { return static_cast<Op>(OpCode::CALL); }
  Op div() { return static_cast<Op>(OpCode::DIV); }
  Op dup() { return static_cast<Op>(OpCode::DUP); }
  Op eq() { return static_cast<Op>(OpCode::EQ); }
  Op gt() { return static_cast<Op>(OpCode::GT); }

  Op _if(PC next_pc) {
    return
      static_cast<Op>(OpCode::IF) +
      static_cast<Op>(next_pc << IF_NEXT_PC_POS);
  }

  Op _goto(PC pc) {
    return
      static_cast<Op>(OpCode::GOTO) +
      static_cast<Op>(pc << GOTO_PC_POS);
  }

  Op lt() { return static_cast<Op>(OpCode::LT); }
  Op mod() { return static_cast<Op>(OpCode::MOD); }
  Op mul() { return static_cast<Op>(OpCode::MUL); }
  Op _not() { return static_cast<Op>(OpCode::NOT); }

  Op _or(PC next_pc) {
    return
      static_cast<Op>(OpCode::OR) +
      static_cast<Op>(next_pc << OR_NEXT_PC_POS);
  }

  Op pop() { return static_cast<Op>(OpCode::POP); }

  Op prim_call(Prim &prim) {
    return
      static_cast<Op>(OpCode::PRIM_CALL) +
      static_cast<Op>(prim.tag << PRIM_CALL_TAG_POS);
  }
  
  Op push_bool(bool value) {
    return
      static_cast<Op>(OpCode::PUSH_BOOL) +
      static_cast<Op>(value << PUSH_BOOL_VALUE_POS);
  }

  Op push_int(Int value) {
    return
      static_cast<Op>(OpCode::PUSH_INT) +
      static_cast<Op>(value << PUSH_INT_VALUE_POS);
  }

  Op push_tag(Tag value) {
    return
      static_cast<Op>(OpCode::PUSH_TAG) +
      static_cast<Op>(value << PUSH_TAG_VALUE_POS);
  }

  Op rec() { return static_cast<Op>(OpCode::REC); }
  Op ret() { return static_cast<Op>(OpCode::RET); }
  Op sub() { return static_cast<Op>(OpCode::SUB); }
  Op swap() { return static_cast<Op>(OpCode::SWAP); }
  Op test() { return static_cast<Op>(OpCode::TEST); }
  Op trace() { return static_cast<Op>(OpCode::TRACE); }
  Op type_of() { return static_cast<Op>(OpCode::TYPE_OF); }
  Op stop() { return static_cast<Op>(OpCode::STOP); }
}
