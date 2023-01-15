#ifndef NIBL_VAL_HPP
#define NIBL_VAL_HPP

#include <any>
#include <optional>

#include "nibl/error.hpp"

namespace nibl {
  using namespace std;

  struct Type;
  struct VM;
  
  struct Val {
    Type *type;
    any data;

    Val(Type &type, any &&data);
    void dump(ostream &out) const;
    optional<Error> emit(VM &vm) const;

    template <typename T>
    T as() const { return any_cast<T>(data); }
  };

  ostream &operator <<(ostream &out, const Val &v);
}

#endif
