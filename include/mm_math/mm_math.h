#pragma once
#include "mm/mm_std_base.h"
#include "types.h"

namespace mm {

const f32 DEG_TO_RAD = 0.017453292f;
const f32 RAD_TO_DEG = 57.29578f;

template <typename T> T clamp(T value, T mi, T ma) {
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    return mi;
  }

  return value > ma ? ma : value;
}

template <typename T> const T &min(const T &a, const T &b) { return a < b ? a : b; }

template <typename T> void clampRef(T &value, const T &mi, const T &ma) {
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    value = mi;
  } else if (value > ma) {
    value = ma;
  }
}

} // namespace mm
