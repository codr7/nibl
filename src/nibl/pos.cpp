#include "nibl/pos.hpp"

namespace nibl {
  const Pos Pos::INVALID;

  ostream &operator <<(ostream &out, Pos p) {
    out << "'" << p.source << "' at line " << p.line << ", column " << p.column;
    return out;
  }
}
