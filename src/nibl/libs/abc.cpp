#include <iostream>

#include <ostream>

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
    and_macro(*this, "and", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::_and();
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
    or_macro(*this, "or", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::_or();
      return nullopt;
    }),
    pop_macro(*this, "pop", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::pop();
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
    typeof_macro(*this, "typeof", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::_typeof();
      return nullopt;
    }) {

    bind("T", bool_type, true);
    bind("F", bool_type, false);    
  }
}
