#include <iostream>

#include <ostream>

#include "nibl/form.hpp"
#include "nibl/libs/abc.hpp"
#include "nibl/types.hpp"
#include "nibl/vm.hpp"

namespace nibl::libs {
  BoolType::BoolType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  optional<Error> BoolType::emit(VM &vm, const any &data) const {
    *vm.emit() = ops::push_bool(any_cast<bool>(data));
    return nullopt;
  }

  void BoolType::dump(any data, ostream &out) const {
    out << (any_cast<bool>(data) ? 'T' : 'F');
  }

  IntType::IntType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  optional<Error> IntType::emit(VM &vm, const any &data) const {
    *vm.emit() = ops::push_int1(any_cast<types::Int>(data));
    return nullopt;
  }

  void IntType::dump(any data, ostream &out) const {
    out << any_cast<types::Int>(data);
  }

  MacroType::MacroType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  optional<Error> MacroType::emit(VM &vm, const any &data) const {
    *vm.emit() = ops::push_tag(any_cast<Macro *>(data)->tag);
    return nullopt;
  }

  void MacroType::dump(any data, ostream &out) const {
    out << *any_cast<Macro *>(data);
  }

  MetaType::MetaType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  optional<Error> MetaType::emit(VM &vm, const any &data) const {
    *vm.emit() = ops::push_tag(any_cast<Type *>(data)->tag);
    return nullopt;
  }

  void MetaType::dump(any data, ostream &out) const {
    out << *any_cast<Type *>(data);
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
