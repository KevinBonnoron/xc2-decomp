#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class CriticalSection;
} // namespace ml

namespace grlib {

struct CGLibMemType {
  static const u32 TYPE_EXTERNAL = 5;
  static const u32 TYPE_UNKNOWN_6 = 6;

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
  static mtl::ALLOC_HANDLE s_hCntHandle;
  static mtl::ALLOC_HANDLE s_hPxlHandle;
  static mtl::ALLOC_HANDLE s_hVtxHandle;
  static mtl::ALLOC_HANDLE s_hUniHandle;
  static mtl::ALLOC_HANDLE s_hMemHandle;

  static ml::CriticalSection &getCriticalSection();

  static void setMemBuff(CGLibMemType &memType, void *buffer);
  static void allocVertex(CGLibMemType &memType, u32 size);
  static void allocUniform(CGLibMemType &memType, u32 size);
  static void free(CGLibMemType &memType);
};

} // namespace grlib
