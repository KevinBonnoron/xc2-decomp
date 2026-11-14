#pragma once
#include <utility>

namespace mm {
namespace mtl {

template <int N> struct int_to_type {
  enum { unknown001 = N }; // Inferred role: the integer template argument; original name unknown.
};

template <typename T> struct is_pod {
  static const bool unknown001 = __is_pod(T); // Inferred role: whether the type is plain old data, so it is copied with memcpy; original name unknown.
};

template <typename T1, typename T2> struct is_pod<std::pair<T1, T2>> {
  static const bool unknown001 = is_pod<T1>::unknown001 && is_pod<T2>::unknown001; // Inferred role: whether the type is plain old data, so it is copied with memcpy; original name unknown.
};

} // namespace mtl
} // namespace mm
