#ifndef NIBL_ERROR_HPP
#define NIBL_ERROR_HPP

#include <string>

#include "nibl/pos.hpp"
#include "nibl/utils.hpp"

namespace nibl {
  using namespace std;
  
  struct Error {
    const Pos pos;
    const string message;

    template <typename...Args>
    Error(const Pos &pos, Args &&...args): pos(pos), message(format(forward<Args>(args)...)) {}
  };

  ostream &operator <<(ostream &out, const Error &e);
}

#endif
