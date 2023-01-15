#ifndef NIBL_MACRO_HPP
#define NIBL_MACRO_HPP

#include <deque>
#include <functional>
#include <optional>

#include "nibl/error.hpp"

namespace nibl {
  struct Form;
  struct Lib;
  struct VM;

  struct Macro {
    using Body = function<optional<Error> (VM &vm, const Macro &macro, deque<Form> &args, Pos pos)>;
    
    Macro(Lib &lib, string &&name, Body body);
    optional<Error> emit(VM &vm, deque<Form> &args, Pos pos);
    
    const string name;
    const Body body;
  };

  ostream &operator <<(ostream &out, const Macro &m);
}

#endif
