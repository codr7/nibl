#ifndef NIBL_EVAL_HPP
#define NIBL_EVAL_HPP

#include "nibl/vm.hpp"

namespace nibl {
  inline void eval_add(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() + b.as<types::Int>();
  }

  inline PC eval_and(VM &vm, PC next_pc) {
      Val v(vm.stack.back());
      if (!v.as<bool>()) { return next_pc; }      
      vm.stack.pop_back();
      return vm.pc;
  }

  inline void eval_div(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() / b.as<types::Int>();
  }
  
  inline void eval_eq(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a == b);
  }

  inline void eval_gt(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a.as<types::Int>() > b.as<types::Int>());
  }

  inline PC eval_if(VM &vm, PC next_pc) {
      Val v(vm.stack.back());
      vm.stack.pop_back();
      if (!v.as<bool>()) { return next_pc; }      
      return vm.pc;
  }

  inline PC eval_jump(VM &vm, PC pc) { return pc; }

  inline void eval_lt(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a.as<types::Int>() < b.as<types::Int>());
  }

  inline void eval_mod(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() % b.as<types::Int>();
  }

  inline void eval_mul(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() * b.as<types::Int>();
  }

  inline void eval_not(VM &vm) {
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, !a.as<bool>());
  }

  inline PC eval_or(VM &vm, PC next_pc) {
      Val v(vm.stack.back());
      if (v.as<bool>()) { return next_pc; }      
      vm.stack.pop_back();
      return vm.pc;
  }

  inline void eval_sub(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() - b.as<types::Int>();
  }

  inline void eval_test(VM &vm, ostream &stdout) {
    Stack expected(move(vm.stack));
    vm.eval(vm.pc, stdout);
    Stack actual(move(vm.stack));
    
    if (actual == expected) {
      stdout << "Test ok: " << expected << endl;
    } else {
      stdout << "Test failed, expected: " << expected << ", actual: " << actual << endl;
    }
  }
}

#endif
