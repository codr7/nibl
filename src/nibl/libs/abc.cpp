#include <iostream>

#include <ostream>

#include "nibl/form.hpp"
#include "nibl/libs/abc.hpp"
#include "nibl/types.hpp"
#include "nibl/vm.hpp"

namespace nibl::libs {
  BoolType::BoolType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  void BoolType::dump(const Val &val, ostream &out) const {
    out << (val.as<bool>() ? 'T' : 'F');
  }

  optional<Error> BoolType::emit(VM &vm, const Val &val) const {
    *vm.emit() = ops::push_bool(val.as<bool>());
    return nullopt;
  }

  bool BoolType::eq(const Val &val1, const Val &val2) const {
    return val1.as<bool>() == val2.as<bool>();
  }

  IntType::IntType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  void IntType::dump(const Val &val, ostream &out) const {
    out << val.as<types::Int>();
  }

  optional<Error> IntType::emit(VM &vm, const Val &val) const {
    *vm.emit() = ops::push_int1(val.as<types::Int>());
    return nullopt;
  }

  bool IntType::eq(const Val &val1, const Val &val2) const {
    return val1.as<types::Int>() == val2.as<types::Int>();
  }

  MacroType::MacroType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  void MacroType::dump(const Val &val, ostream &out) const {
    out << *val.as<Macro *>();
  }

  optional<Error> MacroType::emit(VM &vm, const Val &val) const {
    *vm.emit() = ops::push_tag(val.as<Macro *>()->tag);
    return nullopt;
  }

  bool MacroType::eq(const Val &val1, const Val &val2) const {
    return val1.as<Macro *>() == val2.as<Macro *>();
  }

  MetaType::MetaType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  void MetaType::dump(const Val &val, ostream &out) const {
    out << *val.as<Type *>();
  }

  optional<Error> MetaType::emit(VM &vm, const Val &val) const {
    *vm.emit() = ops::push_tag(val.as<Type *>()->tag);
    return nullopt;
  }

  bool MetaType::eq(const Val &val1, const Val &val2) const {
    return val1.as<Type *>() == val2.as<Type *>();
  }

  ABC::ABC(VM &vm):
    Lib(vm, "abc"),
    bool_type(*this, "Bool"),
    int_type(*this, "Int"),
    macro_type(*this, "Macro"),
    meta_type(*this, "Meta"),
    add_macro(*this, "+", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::add();
      return nullopt;
    }),
    and_macro(*this, "and:", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) -> optional<Error> {
      const PC pc = vm.pc;
      vm.emit();
      if (auto e = pop_front(args).emit(vm, args); e) { return e; }
      vm.ops[pc] = ops::_and(vm.pc);
      return nullopt;
    }),
    div_macro(*this, "/", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::div();
      return nullopt;
    }),
    dup_macro(*this, "dup", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::dup();
      return nullopt;
    }),
    else_macro(*this, "else:", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      return Error(pos, "Missing if");
    }),
    eq_macro(*this, "=", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::eq();
      return nullopt;
    }),
    gt_macro(*this, ">", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::gt();
      return nullopt;
    }),
    if_macro(*this, "if:", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) -> optional<Error> {
      const PC pc = vm.pc;
      vm.emit();
      
      while (!args.empty()) {
	Form f = pop_front(args);
	if (f.imp == Form::END) { break; }
	if (auto e = f.emit(vm, args)) { return e; }
      }

      vm.ops[pc] = ops::_if(vm.pc);
      return nullopt;
    }),
    lt_macro(*this, "<", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::lt();
      return nullopt;
    }),
    mod_macro(*this, "%", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::mod();
      return nullopt;
    }),
    mul_macro(*this, "*", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::mul();
      return nullopt;
    }),
    not_macro(*this, "not", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::_not();
      return nullopt;
    }),
    or_macro(*this, "or:", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) -> optional<Error> {
      const PC pc = vm.pc;
      vm.emit();
      if (auto e = pop_front(args).emit(vm, args); e) { return e; }
      vm.ops[pc] = ops::_or(vm.pc);
      return nullopt;
    }),
    pop_macro(*this, "pop", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::pop();
      return nullopt;
    }),
    stop_macro(*this, "stop", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::stop();
      return nullopt;
    }),
    sub_macro(*this, "-", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::sub();
      return nullopt;
    }),
    swap_macro(*this, "swap", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::swap();
      return nullopt;
    }),
    trace_macro(*this, "trace", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      vm.trace = !vm.trace;
      return nullopt;
    }),
    type_of_macro(*this, "type-of", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::type_of();
      return nullopt;
    }) {

    bind("T", bool_type, true);
    bind("F", bool_type, false);    
  }
}
