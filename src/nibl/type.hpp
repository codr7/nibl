#ifndef NIBL_TYPE_HPP
#define NIBL_TYPE_HPP

#include <any>
#include <optional>
#include <string>

#include "nibl/error.hpp"

namespace nibl {
  using namespace std;

  struct Lib;
  struct VM;
  
  struct Type {
    const string name;
    const size_t tag;
    
    Type(Lib &lib, string &&name);
    virtual void dump(any data, ostream &out) const = 0;
    virtual optional<Error> emit(VM &vm, const any &data) const = 0;
  };

  ostream &operator <<(ostream &out, const Type &t);
  bool operator ==(const Type &t1, const Type &t2);
}

#endif
