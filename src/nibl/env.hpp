#ifndef NIBL_ENV_HPP
#define NIBL_ENV_HPP

#include <map>

#include "nibl/val.hpp"

namespace nibl {
  struct Env {
    map<string, Val> bindings;
    optional<string> def_name;
        
    optional<Val> find(const string &name) const;
    void bind(const string &name, Type &type, any &&data);
    E import(const Env &source, initializer_list<string> names, const Pos &pos);
  };
}

#endif
