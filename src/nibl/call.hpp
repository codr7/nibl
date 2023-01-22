#ifndef NIBL_CALL_HPP
#define NIBL_CALL_HPP

#include "nibl/pos.hpp"
#include "nibl/types.hpp"

namespace nibl {
  struct Func;
  
  struct Call {
    const Func &func;
    const PC ret_pc;

    Call(const Func &func, PC ret_pc);
  };

  inline Call::Call(const Func &func, PC ret_pc): func(func), ret_pc(ret_pc) {}
}

#endif
