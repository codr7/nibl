#include "nibl/env.hpp"

namespace nibl {
  optional<Val> Env::find(const string &name) const {
    if (auto found = bindings.find(name); found != bindings.end()) { return found->second; }
    return nullopt;
  }
  
  void Env::bind(const string &name, Type &type, any &&data) {
    bindings.insert(make_pair(name, Val(type, move(data))));
  }
}
