#pragma once

namespace mm {
namespace mtl {

template <typename T> struct is_pod {
  static const bool value = __is_pod(T);
};

} // namespace mtl
} // namespace mm
