#include "nibl/error.hpp"

namespace nibl {
  ostream &operator <<(ostream &out, const Error &e) {
    out << e.pos.line << ':' << e.pos.column << ' ' << e.message;
    return out;
  }
}
