#include "nibl/error.hpp"

namespace nibl {
  ostream &operator <<(ostream &out, const Error &e) {
    out << e.message;
    return out;
  }
}
