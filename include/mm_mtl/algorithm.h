#pragma once

namespace mm {
namespace mtl {

template <typename InputIterator, typename Function> Function for_each(InputIterator first, InputIterator last, Function function) {
  for (; first != last; ++first) {
    function(*first);
  }
  return function;
}

} // namespace mtl
} // namespace mm
