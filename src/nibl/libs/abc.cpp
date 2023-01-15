#include <iostream>

#include <ostream>

#include "nibl/libs/abc.hpp"
#include "nibl/types.hpp"
#include "nibl/vm.hpp"

namespace nibl::libs {
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
    //TODO
    return nullopt;
  }

  void MacroType::dump(any data, ostream &out) const {
    out << *any_cast<Macro *>(data);
  }

  MetaType::MetaType(Lib &lib, string &&name): Type(lib, move(name)) {}
  
  optional<Error> MetaType::emit(VM &vm, const any &data) const {
    //TODO
    return nullopt;
  }

  void MetaType::dump(any data, ostream &out) const {
    out << *any_cast<Type *>(data);
  }

  
  ABC::ABC(VM &vm):
    Lib(vm, "abc"),
    int_type(*this, "Int"),
    macro_type(*this, "Macro"),
    meta_type(*this, "Meta"),
    dup_macro(*this, "dup", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::dup();
      return nullopt;
    }),
    pop_macro(*this, "pop", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      *vm.emit() = ops::pop();
      return nullopt;
    }),
    trace_macro(*this, "trace", [](VM &vm, const Macro &macro, deque<Form> &args, Pos pos) {
      vm.trace = !vm.trace;
      return nullopt;
    }) {}
}
