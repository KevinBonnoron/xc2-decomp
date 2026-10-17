#pragma once
#include <utility>

namespace mm {
namespace mtl {

template <typename T> struct is_pod {
  static const bool value = __is_pod(T);
};

template <typename T1, typename T2> struct is_pod<std::pair<T1, T2>> {
  static const bool value = is_pod<T1>::value && is_pod<T2>::value;
};

} // namespace mtl
} // namespace mm
