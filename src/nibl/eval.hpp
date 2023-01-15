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

  inline void eval_and(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a.as<bool>() && b.as<bool>());
  }

  inline void eval_div(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() / b.as<types::Int>();
  }
  
  inline void eval_gt(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a.as<types::Int>() > b.as<types::Int>());
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

  inline void eval_or(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a = Val(vm.abc_lib.bool_type, a.as<bool>() || b.as<bool>());
  }

  inline void eval_sub(VM &vm) {
      Val b(vm.stack.back());
      vm.stack.pop_back();
      Val &a(vm.stack.back());
      a.data = a.as<types::Int>() - b.as<types::Int>();
  }
}

#endif
