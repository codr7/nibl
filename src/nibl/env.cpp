#include <vector>
#include "nibl/env.hpp"

namespace nibl {
  optional<Val> Env::find(const string &name) const {
    if (auto found = bindings.find(name); found != bindings.end()) { return found->second; }
    return nullopt;
  }
  
  void Env::bind(const string &name, Type &type, any &&data) {
    bindings.insert(make_pair(name, Val(type, move(data))));
  }

  void Env::bind(const string &name, Type &type, const any &data) {
    bindings.insert(make_pair(name, Val(type, data)));
  }

  E Env::import(const Env &source, initializer_list<string> names, const Pos &pos) {
    vector<string> ns(names);

    if (ns.empty()) {
      bindings.insert(source.bindings.begin(), source.bindings.end());
    } else {
      for (const string &n: ns) {
	auto v = source.find(n);
	if (!v) { return Error(pos, n, '?'); }
	bindings.insert(make_pair(n, *v));
      }
    }

    return nullopt;
  }
}
