#include <iostream>

#include <ostream>

#include "nibl/libs/abc.hpp"
#include "nibl/types.hpp"
#include "nibl/vm.hpp"

namespace nibl::libs {
  IntType::IntType(string &&name): Type(move(name)) {}
  
  optional<Error> IntType::emit(VM &vm, const any &data) const {
    *vm.emit() = ops::push_int1(any_cast<types::Int>(data));
    return nullopt;
  }

  void IntType::dump(any data, ostream &out) const {
    out << any_cast<types::Int>(data);
  }

  ABC::ABC(): int_type("Int") {}
}
