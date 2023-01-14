#ifndef NIBL_TYPE_HPP
#define NIBL_TYPE_HPP

#include <any>
#include <string>

namespace nibl {
  using namespace std;

  struct VM;
  
  struct Type {
    const string name;

    Type(string &&name);
    virtual void dump(any data, ostream &out) const = 0;
    virtual void emit(VM &vm, const any &data) const = 0;
  };
}

#endif
