#ifndef NIBL_PRIM_HPP
#define NIBL_PRIM_HPP

#include <deque>
#include <functional>

#include "nibl/error.hpp"
#include "nibl/op.hpp"
#include "nibl/types.hpp"

namespace nibl {
  struct Env;
  struct VM;

  struct Prim {
    using Body = function<E (VM &vm, Prim &prim, PC &pc)>;
    
    Prim(VM &vm, Env &env, const string &name, Body body);
    E call(VM &vm, PC &pc);
    
    const string name;
    const Tag tag;
    const Body body;
  };

  ostream &operator <<(ostream &out, const Prim &m);
}

#endif
