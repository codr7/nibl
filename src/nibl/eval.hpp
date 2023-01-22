#ifndef NIBL_EVAL_HPP
#define NIBL_EVAL_HPP

#include "nibl/vm.hpp"

namespace nibl {
  inline void eval_add(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<Int>() + b.as<Int>();
  }

  inline void eval_and(VM &vm, PC next_pc) {
      if (vm.stack.back().as<bool>()) {
	vm.stack.pop_back();
      } else {
	vm.pc = next_pc;
      }
  }

  inline void eval_call(VM &vm) {
    Func &f = *vm.stack.back().as<Func *>();
    vm.stack.pop_back();
    vm.call(f);
  }

  inline void eval_div(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<Int>() / b.as<Int>();
  }

  inline void eval_dup(VM &vm) {
    vm.stack.emplace_back(vm.stack.back());
  }
  
  inline void eval_eq(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a == b);
  }

  inline void eval_goto(VM &vm, PC pc) { vm.pc = pc; }

  inline void eval_gt(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a.as<Int>() > b.as<Int>());
  }

  inline void eval_if(VM &vm, PC next_pc) {
      Val v(vm.stack.back());
      vm.stack.pop_back();
      if (!v.as<bool>()) { vm.pc = next_pc; }      
  }

  inline void eval_lt(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a.as<Int>() < b.as<Int>());
  }

  inline void eval_mod(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<Int>() % b.as<Int>();
  }

  inline void eval_mul(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<Int>() * b.as<Int>();
  }

  inline void eval_not(VM &vm) {
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, !a.as<bool>());
  }

  inline void eval_or(VM &vm, PC next_pc) {
      Val v(vm.stack.back());

      if (v.as<bool>()) {
	vm.pc = next_pc;
      } else {      
	vm.stack.pop_back();
      }
  }

  inline void eval_pop(VM &vm) {
      vm.stack.pop_back();
  }
  
  inline void eval_push_bool(VM &vm, bool value) {
    vm.push(vm.abc_lib.bool_type, value);
  }

  inline void eval_push_int(VM &vm, Int value) {
    vm.push(vm.abc_lib.int_type, value);
  }

  inline void eval_push_tag(VM &vm, size_t value) {
    vm.stack.push_back(vm.tags[value]);
  }

  inline void eval_ret(VM &vm) {
    vm.pc = vm.calls.back().ret_pc;
    vm.calls.pop_back();
  }

  inline void eval_sub(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<Int>() - b.as<Int>();
  }

  inline void eval_swap(VM &vm) {
    iter_swap(vm.stack.end()-2, vm.stack.end()-1);
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

  inline void eval_trace(VM &vm, ostream &stdout) {
    op_trace(vm, vm.pc, stdout);
  }

  inline void eval_type_of(VM &vm) {
    vm.stack.back() = Val(vm.abc_lib.meta_type, vm.stack.back().type);
  }
}

#endif
