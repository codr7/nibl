#include <map>

#include "nibl/forms/lit.hpp"
#include "nibl/read.hpp"
#include "nibl/types.hpp"
#include "nibl/vm.hpp"

namespace nibl { 
  Read read_int(const VM &vm, istream &in, Pos &pos, int base) {
    Pos fpos = pos;
    types::Int v(0);
      
    static map<char, int8_t> cs = {
      {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
      {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14},
      {'f', 15}
    };
    
    auto ci(cs.end());
    char c = 0;
    
    while (in.get(c)) {
      if ((ci = cs.find(c)) == cs.end()) { break; }
      auto cv(ci->second);

      if (cv >= base) { return Read(nullopt, Error(pos, "Invalid integer: ", c)); }
      v = v * base + cv;
      pos.column++;
    }
    
    if (!in.eof()) { in.unget();}
    return Read(forms::Lit(fpos, vm.abc_lib.int_type, v), nullopt);
  }
}
