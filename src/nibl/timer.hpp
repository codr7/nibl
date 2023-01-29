#ifndef NIBL_TIMER_HPP
#define NIBL_TIMER_HPP

#include <chrono>
#include "nibl/types.hpp"

namespace nibl {
  using namespace std;
  
  struct Timer {
    using Clock = chrono::steady_clock;
    using ms = chrono::milliseconds;
    Clock::time_point started_at = Clock::now();

    template <typename U>
    Int get() { return chrono::duration_cast<U>(Clock::now() - started_at).count(); }
  };
}

#endif
