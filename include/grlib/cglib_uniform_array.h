#pragma once
#include "types.h"

namespace grlib {

template <typename T> class CGLibUniformArray {
public:
  void setupArray(u32 count);
  T &operator[](u32 index) { return m_items[index]; }

  T *m_items;
};

} // namespace grlib
