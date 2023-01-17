#include <deque>
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

  template <typename T>
  T pop_front(deque<T> &in) {
    T it = in.front();
    in.pop_front();
    return it;
  }
}

#endif
