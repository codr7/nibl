#ifndef NIBL_EVAL_HPP
#define NIBL_EVAL_HPP

#include "nibl/vm.hpp"

namespace nibl {
  inline void eval_add(VM &vm) {
      Val y(vm.stack.back());
      vm.stack.pop_back();
      Val &x(vm.stack.back());
      x.data = x.as<types::Int>() + y.as<types::Int>();
  }

  inline void eval_div(VM &vm) {
      Val y(vm.stack.back());
      vm.stack.pop_back();
      Val &x(vm.stack.back());
      x.data = x.as<types::Int>() / y.as<types::Int>();
  }
  
  inline void eval_gt(VM &vm) {
      Val y(vm.stack.back());
      vm.stack.pop_back();
      Val &x(vm.stack.back());
      x = Val(vm.abc_lib.bool_type, x.as<types::Int>() > y.as<types::Int>());
  }

  inline void eval_lt(VM &vm) {
      Val y(vm.stack.back());
      vm.stack.pop_back();
      Val &x(vm.stack.back());
      x = Val(vm.abc_lib.bool_type, x.as<types::Int>() < y.as<types::Int>());
  }

  inline void eval_mod(VM &vm) {
      Val y(vm.stack.back());
      vm.stack.pop_back();
      Val &x(vm.stack.back());
      x.data = x.as<types::Int>() % y.as<types::Int>();
  }

  inline void eval_mul(VM &vm) {
      Val y(vm.stack.back());
      vm.stack.pop_back();
      Val &x(vm.stack.back());
      x.data = x.as<types::Int>() * y.as<types::Int>();
  }

  inline void eval_sub(VM &vm) {
      Val y(vm.stack.back());
      vm.stack.pop_back();
      Val &x(vm.stack.back());
      x.data = x.as<types::Int>() - y.as<types::Int>();
  }
}

#endif
