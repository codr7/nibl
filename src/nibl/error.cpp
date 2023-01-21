#include "nibl/error.hpp"

namespace nibl {
  ostream &operator <<(ostream &out, const Error &e) {
    out << e.pos << ' ' << e.message;
    return out;
  }
}
