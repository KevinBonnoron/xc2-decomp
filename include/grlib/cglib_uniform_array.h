#pragma once
#include "types.h"

namespace grlib {

template <typename T> class CGLibUniformArray {
public:
  void setupArray(u32 count);

  T *m_items;
};

} // namespace grlib
