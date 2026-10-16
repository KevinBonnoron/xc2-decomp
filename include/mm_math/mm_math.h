#pragma once
#include "mm/mm_std_base.h"

namespace mm {

template <typename T> T clamp(T value, T mi, T ma) {
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    return mi;
  }

  return value > ma ? ma : value;
}

template <typename T> const T &min(const T &a, const T &b) { return a < b ? a : b; }

} // namespace mm
