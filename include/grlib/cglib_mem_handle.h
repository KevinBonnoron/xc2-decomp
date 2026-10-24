#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

struct CGLibMemType {
  static const u32 TYPE_EXTERNAL = 5;

  CGLibMemType() {
    unknown08 = TYPE_EXTERNAL;
    m_buffer = nullptr;
  }

  void *m_buffer;
  u32 unknown08; // Inferred role: type; original member name unknown.
};

static_assert(offsetof(CGLibMemType, unknown08) == 0x8, "");

class CGLibMemHandle {
public:
  static mtl::ALLOC_HANDLE s_hDefHandle;

  static void setMemBuff(CGLibMemType &memType, void *buffer);
  static void allocVertex(CGLibMemType &memType, u32 size);
  static void allocUniform(CGLibMemType &memType, u32 size);
  static void free(CGLibMemType &memType);
};

} // namespace grlib
