#pragma once

namespace mm {
namespace mtl {

template <typename InputIterator, typename Function> Function for_each(InputIterator first, InputIterator last, Function function) {
  for (; first != last; ++first) {
    function(*first);
  }
  return function;
}

template <typename InputIterator, typename T> InputIterator find(InputIterator first, InputIterator last, const T &value) {
  for (; first != last; ++first) {
    if (*first == value) {
      break;
    }
  }
  return first;
}

} // namespace mtl
} // namespace mm
