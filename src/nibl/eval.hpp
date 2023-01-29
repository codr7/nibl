#ifndef NIBL_EVAL_HPP
#define NIBL_EVAL_HPP

#include "nibl/prim.hpp"
#include "nibl/timer.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  inline void eval_add(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a.data = a.as<Int>() + b.as<Int>();
  }

  inline void eval_and(VM &vm, PC &pc, Op op) {
    if (vm.stack.back().as<bool>()) {
      vm.stack.pop_back();
    } else {
      pc = ops::and_end_pc(op);
    }
  }

  inline E eval_bench(VM &vm, PC &pc, Op op) {
    Int reps = pop_back(vm.stack).as<Int>();
    PC start_pc = pc;
    Timer t;
    
    for (Int i  = 0; i < reps; i++, pc = start_pc) {
      if (auto e = vm.eval(pc); e) { return e; }
    }

    vm.push(vm.abc_lib.int_type, t.get<Timer::ms>());
    return nullopt;
  }

  inline void eval_call(VM &vm, PC &pc, Op op) {
    vm.call(*vm.tags[ops::call_tag(op)].as<Fun *>(), pc);
  }

  inline void eval_dec(VM &vm, PC &pc, Op op) {
    Val &v(vm.stack.back());
    v = Val(vm.abc_lib.int_type, v.as<Int>()-1);
  }

  inline void eval_div(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a.data = a.as<Int>() / b.as<Int>();
  }

  inline void eval_dup(VM &vm, PC &pc, Op op) {
    vm.stack.emplace_back(vm.stack.back());
  }
  
  inline void eval_eq(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a = Val(vm.abc_lib.bool_type, a == b);
  }

  inline void eval_goto(VM &vm, PC &pc, Op op) {
    pc = ops::goto_pc(op);
  }

  inline void eval_gt(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a = Val(vm.abc_lib.bool_type, a.as<Int>() > b.as<Int>());
  }

  inline void eval_if(VM &vm, PC &pc, Op op) {
    if (!pop_back(vm.stack).as<bool>()) { pc = ops::if_end_pc(op); }
  }

  inline void eval_lt(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a = Val(vm.abc_lib.bool_type, a.as<Int>() < b.as<Int>());
  }

  inline void eval_mod(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a.data = a.as<Int>() % b.as<Int>();
  }

  inline void eval_mul(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a.data = a.as<Int>() * b.as<Int>();
  }

  inline void eval_not(VM &vm, PC &pc, Op op) {
    Val &a(vm.stack.back());
    a = Val(vm.abc_lib.bool_type, !a.as<bool>());
  }

  inline void eval_or(VM &vm, PC &pc, Op op) {
    if (vm.stack.back().as<bool>()) {
      pc = ops::or_end_pc(op);
    } else {
      vm.stack.pop_back();
    }
  }

  inline void eval_pop(VM &vm, PC &pc, Op op) { vm.stack.pop_back(); }

  inline E eval_prim_call(VM &vm, PC &pc, Op op) {
    return vm.tags[ops::prim_call_tag(op)].as<Prim *>()->call(vm, pc);
  }

  inline void eval_push_bool(VM &vm, PC &pc, Op op) {
    vm.push(vm.abc_lib.bool_type, ops::push_bool_value(op));
  }

  inline void eval_push_int(VM &vm, PC &pc, Op op) {
    vm.push(vm.abc_lib.int_type, ops::push_int_value(op));
  }

  inline void eval_push_tag(VM &vm, PC &pc, Op op) {
    vm.stack.push_back(vm.tags[ops::push_tag_value(op)]);
  }

  inline void eval_rec(VM &vm, PC &pc, Op op) { pc = vm.calls.back().fun.pc; }

  inline void eval_ret(VM &vm, PC &pc, Op op) { pc = pop_back(vm.calls).ret_pc; }

  inline void eval_sub(VM &vm, PC &pc, Op op) {
    Val b(pop_back(vm.stack));
    Val &a(vm.stack.back());
    a.data = a.as<Int>() - b.as<Int>();
  }

  inline void eval_swap(VM &vm, PC &pc, Op op) {
    iter_swap(vm.stack.end()-2, vm.stack.end()-1);
  }

  inline E eval_test(VM &vm, PC &pc, Op op) {
    Stack expected(move(vm.stack));
    if (auto e = vm.eval(pc); e) { return e; }
    Stack actual(move(vm.stack));
    
    if (actual == expected) {
      vm.stdout << "Test ok: " << expected << endl;
    } else {
      vm.stdout << "Test failed, expected: " << expected << ", actual: " << actual << endl;
    }

    return nullopt;
  }

  inline void eval_trace(VM &vm, PC &pc, Op op) {
    op_trace(vm, pc, vm.stdout);
  }
}

#endif
