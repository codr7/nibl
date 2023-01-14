#include "nibl/lib.hpp"

namespace nibl {
  Lib::Lib(VM &vm, string &&name): vm(vm), name(move(name)) {}
}
