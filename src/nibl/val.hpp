#ifndef NIBL_VAL_HPP
#define NIBL_VAL_HPP

#include <any>
#include <optional>

#include "nibl/error.hpp"
#include "nibl/type.hpp"

namespace nibl {
  using namespace std;

  struct Env;
  struct Type;
  struct VM;
  
  struct Val {
    Type *type;
    any data;

    Val(Type &type, any &&data);
    Val(Type &type, const any &data);
    E emit(VM &vm, Env &env) const;
    void write(ostream &out) const { type->write(*this, out); }
      
    template <typename T>
    T as() const { return any_cast<T>(data); }

    operator bool() const { return (data.type() == typeid(bool)) ? as<bool>() : true; }
  };

  ostream &operator <<(ostream &out, const Val &v);
  bool operator ==(const Val &v1, const Val &v2);
}

#endif
