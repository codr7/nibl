#ifndef NIBL_TYPE_HPP
#define NIBL_TYPE_HPP

#include <any>
#include <optional>
#include <string>

#include "nibl/error.hpp"

namespace nibl {
  using namespace std;

  struct Lib;
  struct Val;
  struct VM;
  
  struct Type {
    const string name;
    const size_t tag;
    
    Type(Lib &lib, string &&name);
    virtual void dump(const Val &val, ostream &out) const = 0;
    virtual optional<Error> emit(VM &vm, const Val &val) const = 0;
    virtual bool eq(const Val &val1, const Val &val2) const = 0;
  };

  ostream &operator <<(ostream &out, Type &t);
  bool operator ==(Type &t1, Type &t2);
}

#endif
