#ifndef NIBL_CALL_HPP
#define NIBL_CALL_HPP

#include "nibl/pos.hpp"
#include "nibl/types.hpp"

namespace nibl {
  struct Fun;
  
  struct Call {
    const Fun &fun;
    const PC ret_pc;

    Call(const Fun &fun, PC ret_pc);
  };

  inline Call::Call(const Fun &fun, PC ret_pc): fun(fun), ret_pc(ret_pc) {}
}

#endif
