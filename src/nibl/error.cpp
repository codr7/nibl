#include "nibl/error.hpp"

namespace nibl {
  ostream &operator <<(ostream &out, const Error &e) {
    out << "Error: " << e.message;
    return out;
  }
}
