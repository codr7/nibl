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

  inline PC eval_and(VM &vm, Op op) {
      Val v(vm.stack.back());
      if (!v.as<bool>()) { return ops::and_next(op); }      
      vm.stack.pop_back();
      return  vm.pc;
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

  inline PC eval_if(VM &vm, Op op) {
      Val v(vm.stack.back());
      vm.stack.pop_back();
      if (!v.as<bool>()) { return ops::if_next(op); }      
      return vm.pc;
  }

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

  inline PC eval_or(VM &vm, Op op) {
      Val v(vm.stack.back());
      if (v.as<bool>()) { return ops::and_next(op); }      
      vm.stack.pop_back();
      return  vm.pc;
  }

  inline void eval_sub(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() - b.as<types::Int>();
  }
}

#endif
