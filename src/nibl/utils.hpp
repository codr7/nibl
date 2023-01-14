#include <sstream>
#include <string>

#ifndef NIBL_UTILS_HPP
#define NIBL_UTILS_HPP

namespace nibl {
  using namespace std;

  template <typename...Args>
  string format(Args &&...args) {
    stringstream buf;
    ((buf << forward<Args>(args)), ...);
    return buf.str();
  }
}

#endif
