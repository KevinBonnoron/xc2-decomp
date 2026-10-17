#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {

struct CGLibMemType {
  static const u32 TYPE_EXTERNAL = 5;

  CGLibMemType() : m_buffer(nullptr), m_type(TYPE_EXTERNAL) {}

  void *m_buffer;
  u32 m_type;
};

static_assert(offsetof(CGLibMemType, m_type) == 0x8, "");

class CGLibMemHandle {
public:
  static void setMemBuff(CGLibMemType &memType, void *buffer);
  static void allocUniform(CGLibMemType &memType, u32 size);
  static void free(CGLibMemType &memType);
};

} // namespace grlib
