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

  template <template <typename...> typename C, typename T, typename...Args>
  T pop_front(C<T, Args...> &in) {
    T it = move(in.front());
    in.pop_front();
    return it;
  }

  template <template <typename...> typename C, typename T, typename...Args>
  inline T pop_back(C<T, Args...> &in) {
    T it(move(in.back()));
    in.pop_back();
    return it;
  }
}

#endif
