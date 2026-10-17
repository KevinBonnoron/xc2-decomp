#pragma once
#include <stddef.h>

namespace mm {
namespace mtl {

class RTTI {
public:
  bool isKindOf(const RTTI *rtti) const {
    if (this == rtti) {
      return true;
    }
    for (int i = 0; i < 2; i++) {
      if (m_parents[i] != nullptr && m_parents[i]->isKindOf(rtti)) {
        return true;
      }
    }
    return false;
  }

  const char *m_name;
  const RTTI *m_parents[2];
};

static_assert(offsetof(RTTI, m_parents) == 0x08, "");
static_assert(sizeof(RTTI) == 0x18, "");

template <typename T, typename U> T *dynamicCast(U *object) { return object->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T *>(object) : nullptr; }

} // namespace mtl
} // namespace mm
