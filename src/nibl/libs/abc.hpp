#ifndef NIBL_LIBS_ABC_HPP
#define NIBL_LIBS_ABC_HPP

#include "nibl/error.hpp"
#include "nibl/type.hpp"

namespace nibl::libs {
  using namespace nibl;
  
  struct IntType: Type {
    IntType(string &&name);
    optional<Error> emit(VM &vm, const any &data) const override;
    void dump(any data, ostream &out) const override;
  };
  
  struct ABC {
    const IntType int_type;

    ABC();
  };
}

#endif
