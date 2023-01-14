#ifndef NIBL_ENV_HPP
#define NIBL_ENV_HPP

#include <map>

#include "nibl/val.hpp"

namespace nibl {
  struct Env {
    map<string, Val> bindings;

    optional<Val> find(const string &name) const;
    void bind(const string &name, const Type &type, any &&data);
  };
}

#endif
