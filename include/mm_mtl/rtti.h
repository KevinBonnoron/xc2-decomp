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
      if (unknown08[i] != nullptr && unknown08[i]->isKindOf(rtti)) {
        return true;
      }
    }
    return false;
  }

  const char *unknown00;    // Inferred role: name; original member name unknown.
  const RTTI *unknown08[2]; // Inferred role: parents; original member name unknown.
};

static_assert(offsetof(RTTI, unknown08) == 0x08, "");
static_assert(sizeof(RTTI) == 0x18, "");

template <typename T, typename U> T *dynamicCast(U *object) { return object->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T *>(object) : nullptr; }

} // namespace mtl
} // namespace mm
