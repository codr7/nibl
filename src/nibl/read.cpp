#include <map>

#include "nibl/forms/id.hpp"
#include "nibl/forms/lit.hpp"
#include "nibl/forms/ref.hpp"
#include "nibl/read.hpp"
#include "nibl/types.hpp"
#include "nibl/vm.hpp"

namespace nibl {
  Read read_id(VM &vm, istream &in, Pos &pos) {
    const Pos fpos(pos);
    stringstream buf;
    char c;
    
    while (in.get(c)) {
      if (c == ';' || !isgraph(c)) {
	in.unget();
	break;
      }

      buf << c;
      pos.column++;
    }

    if (!buf.tellp()) {
      return Read(nullopt, nullopt);
    }

    string n(buf.str());
    if (n.front() == '&') { return Read(forms::Ref(fpos, n.substr(1)), nullopt); }
    return Read(forms::Id(fpos, move(n)), nullopt);
  }

  Read read_int(VM &vm, istream &in, Pos &pos, int base) {
    const Pos fpos = pos;
    types::Int v(0);
      
    static const map<char, int8_t> cs = {
      {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
      {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14},
      {'f', 15}
    };
    
    auto ci(cs.end());
    char c;
    
    while (in.get(c)) {
      if ((ci = cs.find(c)) == cs.end()) { break; }
      auto cv(ci->second);

      if (cv >= base) { return Read(nullopt, Error(pos, "Invalid Int: ", c)); }
      v = v * base + cv;
      pos.column++;
    }
    
    if (!in.eof()) { in.unget();}
    return Read(forms::Lit(fpos, vm.abc_lib.int_type, v), nullopt);
  }

  Read read_string(VM &vm, istream &in, Pos &pos) {
    const Pos fpos(pos);
    stringstream buf;
    char c;
    
    while (in.get(c)) {
      if (c == '"') { break; }
      buf << c;
      pos.column++;
    }

    if (!buf.tellp()) {
      return Read(nullopt, nullopt);
    }

    string s(buf.str());
    return Read(forms::Lit(fpos, vm.abc_lib.string_type, move(s)), nullopt);
  }
}
