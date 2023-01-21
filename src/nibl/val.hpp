#ifndef NIBL_VAL_HPP
#define NIBL_VAL_HPP

#include <any>
#include <optional>

#include "nibl/error.hpp"

namespace nibl {
  using namespace std;

  struct Env;
  struct Type;
  struct VM;
  
  struct Val {
    Type *type;
    any data;

    Val(Type &type, any &&data);
    optional<Error> emit(VM &vm, Env &env) const;

    template <typename T>
    T as() const { return any_cast<T>(data); }
  };

  ostream &operator <<(ostream &out, const Val &v);
  bool operator ==(const Val &v1, const Val &v2);
}

#endif
